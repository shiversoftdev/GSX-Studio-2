#include "GSXProject.h"
#include "global.h"


void GSX_Studio::GSXProject::UpdateModified(void)
{

	for (int i = 0; i < ProjectFiles->Count; i++)
	{
		for (int j = 0; j < ProjectFiles[i]->ScriptFiles->Count; j++)
		{
			if (ProjectFiles[i]->ScriptFiles[j]->Modified)
			{
				Unsaved = true;
				return;
			}
		}
	}
	Unsaved = false;
}

System::String ^ GSX_Studio::GSXProject::GetDefaultProjectCode(System::String^ Creator, System::String^ ProjectName)
{
	System::String^ resourceName = "DefaultCode.txt";
	System::IO::Stream^ stream = Assembly::GetExecutingAssembly()->GetManifestResourceStream(resourceName);
	System::IO::StreamReader^ reader = gcnew System::IO::StreamReader(stream);
	System::String^ result = "\n\n" + reader->ReadToEnd();
	delete reader;
	delete stream;
	return result->Replace("{CREATOR_NAME}", Creator)->Replace("{PROJECT_NAME}",ProjectName);
}

//GSX Project Structure
/*
	byte[6]			%GSXP%			Magic
	string							CreatorName
	string							ProjectName
	byte							NumberOfScripts
	struct[]		GSXFile			Files
	GSXFile:
	string							ScriptName
	byte							NumberOfFiles
	string[NumberOfFiles]			FileName
	SData
*/
GSX_Studio::GSXProject ^ GSX_Studio::GSXProject::LoadProject(System::String ^ FileName)
{
	if (!File::Exists(FileName))
	{
		
		return nullptr;
	}
	GSXProject^ Project = gcnew GSXProject();
	Generic::List<Byte>^ ProjectFile = gcnew Generic::List<Byte>();
	ProjectFile->AddRange(File::ReadAllBytes(FileName));
	array<Byte>^ Magic = gcnew array<Byte>{0x25, 0x47, 0x53, 0x58, 0x50, 0x25};
	array<Byte>^ FileMagic = gcnew array<Byte>(6);
	String^ Path = FileName->Substring(0, FileName->LastIndexOf(Path::DirectorySeparatorChar) + 1);
	if (ProjectFile->Count < Magic->Length)
	{
		throw gcnew Exception("File is not a valid GSX Project"); //Too small
	}
	for (int i = 0; i < FileMagic->Length; i++)
	{
		FileMagic[i] = ProjectFile[i];
	}
	if (!IDE::Utility::ByteMatch(FileMagic, Magic))
	{
		throw gcnew Exception("File is not a valid GSX Project"); //Incorrect File Header
	}
	int index = 6;
	try
	{
		System::String^ CreatorName = IDE::Utility::StringFromBytes(ProjectFile, index);
		System::String^ ProjectName = IDE::Utility::StringFromBytes(ProjectFile, index);
		Project->SourceLocation = Path + ProjectName + Path::DirectorySeparatorChar;
		Project->CreatorName = CreatorName;
		Project->ProjectName = ProjectName;
		Byte NumberOfScripts = ProjectFile[index];
		index++;
		Project->NumberOfScripts = NumberOfScripts;
		for (Byte i = 0; i < NumberOfScripts; i++)
		{
			GSCScript^ script = gcnew GSCScript();
			script->Name = IDE::Utility::StringFromBytes(ProjectFile, index);
			script->NumberOfScriptFiles = ProjectFile[index];
			index++;
			for (Byte j = 0; j < script->NumberOfScriptFiles; j++)
			{
				String^ pname = IDE::Utility::StringFromBytes(ProjectFile, index);
				GSCPart^ spart = gcnew GSCPart(File::ReadAllText(Path + ProjectName + Path::DirectorySeparatorChar + script->Name + Path::DirectorySeparatorChar + pname), pname);
				script->ScriptFiles->Add(spart);
			}
			Project->ProjectFiles->Add(script);
		}
		Project->TypeStrictState = ProjectFile[index];
		index++;
		Project->InlineState = ProjectFile[index];
		index++;
		Project->Debug = ProjectFile[index];
		index++;
		Project->Watermark = IDE::Utility::StringFromBytes(ProjectFile, index);
	}
	catch(System::Exception^)
	{
		throw gcnew Exception("File is not a valid GSX Project");
	}
	return Project;
}

GSX_Studio::GSXProject ^ GSX_Studio::GSXProject::CreateProject(System::String ^ ProjectName, System::String ^ CreatorName, System::String ^ Description, System::String ^ ProjectLocation, System::String^ ScriptName)
{
	String^ invalid = /*gcnew String(Path::GetInvalidFileNameChars()) +*/ gcnew String(Path::GetInvalidPathChars());
	for (int i = 0; i < invalid->Length; i++)
	{
		ProjectName = ProjectName->Replace(invalid[i] + "", "#");
		ScriptName = ScriptName->Replace(invalid[i] + "", "#");
	}
	String^ path = ProjectLocation + Path::DirectorySeparatorChar + ProjectName + Path::DirectorySeparatorChar + ProjectName;
	String^ _ProjectLocation = ProjectLocation + Path::DirectorySeparatorChar + ProjectName;
	try
	{
		Directory::CreateDirectory(_ProjectLocation);
		Directory::CreateDirectory(_ProjectLocation + Path::DirectorySeparatorChar + ProjectName);
		array<String^>^ SubDirs = ScriptName->Split('\\', '/');
		for (int i = 0; i < SubDirs->Length; i++)
		{
			if (!Directory::Exists(path + Path::DirectorySeparatorChar + SubDirs[i]))
			{
				Directory::CreateDirectory(path + Path::DirectorySeparatorChar + SubDirs[i]);
			}
			path = path + Path::DirectorySeparatorChar + SubDirs[i];
		}
	}
	catch (Exception^ e)
	{
		throw gcnew Exception("Couldnt create a new project directory! (" + e->Message + ")");
		return nullptr;
	}
	Generic::List<Byte>^ ProjectFile = gcnew Generic::List<Byte>();
	ProjectFile->AddRange(gcnew array<Byte>{0x25, 0x47, 0x53, 0x58, 0x50, 0x25});
	ProjectFile->AddRange(GSX_Studio::IDE::Utility::BytesFromString(CreatorName));
	ProjectFile->AddRange(GSX_Studio::IDE::Utility::BytesFromString(ProjectName));
	ProjectFile->Add(0x1);
	ProjectFile->AddRange(GSX_Studio::IDE::Utility::BytesFromString(ScriptName));
	ProjectFile->Add(0x1);
	ProjectFile->AddRange(GSX_Studio::IDE::Utility::BytesFromString("main.gsx"));
	ProjectFile->AddRange(GSX_Studio::IDE::GetDefaultProjectData());
	try
	{
		File::WriteAllBytes(_ProjectLocation + Path::DirectorySeparatorChar + ProjectName + ".gsxp", ProjectFile->ToArray());
		File::WriteAllText(path + Path::DirectorySeparatorChar + "main.gsx", "/*\n" + Description + "\n*/" + GSX_Studio::GSXProject::GetDefaultProjectCode(CreatorName, ProjectName));
	}
	catch (Exception^ e)
	{
		throw gcnew Exception("Couldnt create a new project file! (" + e->Message + ")");
		return nullptr;
	}
	return LoadProject(_ProjectLocation + Path::DirectorySeparatorChar + ProjectName + ".gsxp");
}
