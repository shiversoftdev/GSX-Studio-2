#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace Microsoft::Win32;
using namespace System::Reflection;
using namespace System::Diagnostics;
using namespace System::IO;

//TODO
//	[X]	Full Script Optimizations (reduce string pool)
//	[X]	Array Shorthand
//  [X] Finish Macros
//	[X] Fix bracing shit '<'
//  [ ] Disallow naming collisions
//	[ ]	Finish libraries
//  [X]	Finish RPC
//  [ ]	Navigate to definition
//  [ ]	Predictive Linking (files need to contain the prerequisite functions) (will require mp clientids dump)
//  [ ]	CSC Support
//  [ ]	Fast Files (DB_LoadXFile)


#define RELEASE !_DEBUG;

/*
	Main entry point of the program
	Arguments should be file(s) that is either of format .gsx or .gsxp

*/

[STAThread]

int Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	

	try
	{
		String ^ p2 = Path::Combine(Application::StartupPath, "phase2");
		if (Directory::Exists(p2))
		{
			Directory::Delete(p2, true);
		}
	}
	catch(Exception ^E)
	{

	}

	try
	{
		if (File::Exists("CertInstall.exe"))
		{
			File::Delete("CertInstall.exe");
		}
	}
	catch(Exception^)
	{

	}

#if RELEASE

	// Prepare the process to run
	try
	{
		if (File::Exists("ERRLOG.txt"))
		{
			File::Delete("ERRLOG.txt");
			GSX_Studio::MyForm^ form = gcnew GSX_Studio::MyForm(gcnew array<System::String^>(0));
			Application::Run(form);
			return 0;
		}
	}
	catch(Exception^)
	{

	}
	
	if (args->Length > 0 && args[0] == "no-update")
	{
		GSX_Studio::MyForm^ form = gcnew GSX_Studio::MyForm(gcnew array<System::String^>(0));
		Application::Run(form);
		return 0;
	}

	Process ^ p;
	ProcessStartInfo ^start;
	try
	{
		start = gcnew ProcessStartInfo();
		// Enter in the command line arguments, everything you would enter after the executable name itself
		//start->Arguments = arguments;
		// Enter the executable to run, including the complete path
		start->FileName = Path::Combine(Application::StartupPath,"Updater.exe");
		// Do you want to show a console window?
		start->WindowStyle = ProcessWindowStyle::Hidden;
		start->CreateNoWindow = true;
		start->ErrorDialog = true;
		start->UseShellExecute = false;
		p = Process::Start(start);
		p->WaitForExit();
		if (!p->ExitCode || p->ExitCode == 1) //Error or exit that doesnt include phase2
		{
			GSX_Studio::MyForm^ form = gcnew GSX_Studio::MyForm(gcnew array<System::String^>(0));
			Application::Run(form);
		}
		else if (p->ExitCode == 2)
		{
			//Dont continue the app because its time to thread the next update phase
		}
		
	}
	catch(Exception ^e)
	{
		//MessageBox::Show(e->GetBaseException()->ToString());
		//MessageBox::Show(start->FileName);
		if (!p)
		{
			try
			{

				File::AppendAllText("ERRLOG.txt", "\n" + e->GetBaseException()->ToString() + "\n" + "Failed to create process");
			}
			catch(Exception^)
			{

			}
		}
		GSX_Studio::MyForm^ form = gcnew GSX_Studio::MyForm(args);
		Application::Run(form);
	}
	
#else

	GSX_Studio::MyForm^ form = gcnew GSX_Studio::MyForm(args);
	Application::Run(form);

#endif


	return 0;
}

/*
[STAThread]
int main(int numofargs, char* args[])
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	array<System::String^>^ argv = gcnew array<System::String^>(numofargs);
	for (int i = 0; i < numofargs; i++)
	{
		String^ clistr = gcnew String(args[i]);
		argv[i] = clistr;
	}
	GSX_Studio::MyForm^ form = gcnew GSX_Studio::MyForm(argv);
	Application::Run(form);
}
*/

void GSX_Studio::MyForm::AddDefaultProject(IDE^ ide)
{
	System::String^ resourceName = "README.txt";
	System::IO::Stream^ stream = Assembly::GetExecutingAssembly()->GetManifestResourceStream(resourceName);
	System::IO::StreamReader^ reader = gcnew System::IO::StreamReader(stream);
	System::String^ result = reader->ReadToEnd();
	delete reader;
	delete stream;
	DevExpress::XtraRichEdit::RichEditControl^ control = ide->GetNewDefaultEditor(result->Replace("{VERSION}", FileVersionInfo::GetVersionInfo(Application::ExecutablePath)->FileVersion->ToString()), ide);
	control->ReadOnly = true;
	this->dockPanel2_Container->Controls->Add(control);
}

void GSX_Studio::MyForm::InitUserProjects(void)
{
	RegistryKey
		^rk_software,
		^rk_adt,
		^rk_gsxs;
	try
	{
		rk_software = Registry::CurrentUser->OpenSubKey("Software", true);
		if (!rk_software)
		{
			return;
		}
		rk_adt = rk_software->OpenSubKey("Serious", true);
		if (!rk_adt)
		{
			rk_adt = rk_software->CreateSubKey("Serious");
		}
		rk_gsxs = rk_adt->OpenSubKey("GSX Studio", true);
		if (!(rk_gsxs && rk_gsxs->GetValue("Projects Location")))
		{
			rk_gsxs = rk_adt->CreateSubKey("GSX Studio");
			rk_gsxs->SetValue("Projects Location", Manager->ProjectsLocation);
			if (!Directory::Exists(Manager->ProjectsLocation))
			{
				Directory::CreateDirectory(Manager->ProjectsLocation);
			}
		}
		else
		{
			Manager->ProjectsLocation = rk_gsxs->GetValue("Projects Location")->ToString();
		}
		if (!rk_gsxs->GetValue("Optimize"))
		{
			rk_gsxs->SetValue("Optimize", true, Microsoft::Win32::RegistryValueKind::DWord);
		}
		if (!rk_gsxs->GetValue("OptimizeChildren"))
		{
			rk_gsxs->SetValue("OptimizeChildren", false, Microsoft::Win32::RegistryValueKind::DWord);
		}
		if (!rk_gsxs->GetValue("Symbolize"))
		{
			rk_gsxs->SetValue("Symbolize", true, Microsoft::Win32::RegistryValueKind::DWord);
		}
		Manager->GSXStudioRegistryKey = rk_gsxs;
		Manager->OptimizeScripts = (int)rk_gsxs->GetValue("Optimize");
		Manager->OptimizeChildren = (int)rk_gsxs->GetValue("OptimizeChildren");
		Manager->Symbolize = (int)rk_gsxs->GetValue("Symbolize");
		Manager->Build_Scripts->Checked = Manager->OptimizeScripts;
		Manager->Build_Children->Checked = Manager->OptimizeChildren;
		Manager->Build_Symbolize->Checked = Manager->Symbolize;
	}
	catch (Exception ^e)
	{
		MessageBox::Show("Was unable to manage your project registry key! Please run as administrator!" + e->GetBaseException()->ToString());
		return; //This is most likely a security exception from an underpriveledged access attempt.
	}
}

void GSX_Studio::MyForm::InitializeForm(array<String^>^ args)
{
	Output->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &GSX_Studio::MyForm::OnOutputMouseClick);
	IDE::Print("Version " + FileVersionInfo::GetVersionInfo(Application::ExecutablePath)->FileVersion, "Notification", Output);
	Manager = gcnew IDE(Output, ErrorConsole, ProjectExplorer, tabbedView1, dockManager1);
	AddDefaultProject(Manager);
	Manager->ScriptRightClick = SRightClick;
	Manager->PartRightClick = PRightClick;
	Manager->FormControl = this;
	Manager->SubgroupPopup = SubgroupPopup;
	Manager->DManager = dockManager1;
	Manager->SyntaxTimer = SyntaxTimer;
	Manager->SetUpSyntaxTimer();
	//Manager->InjectButtons->Add(barButtonItem20);//Disable Package Inject for now
	Manager->InjectButtons->Add(barButtonItem21);
	Manager->InjectButtons->Add(barSubItem24);
	Manager->InjectCurrentProjectButton = barButtonItem27;
	Manager->ProjectOnlyButtons->Add(Toolbar_Save);
	Manager->ProjectOnlyButtons->Add(Toolbar_SaveAll);
	Manager->ProjectOnlyButtons->Add(DropDown_NewScript);
	Manager->ProjectOnlyButtons->Add(DropDown_Save);
	Manager->ProjectOnlyButtons->Add(DropDown_SaveAll);
	Manager->ProjectOnlyButtons->Add(DropDown_Close);
	Manager->ProjectOnlyButtons->Add(DropDown_PSettings);
	Manager->ProjectOnlyButtons->Add(DropDown_ConvertZ);
	Manager->ProjectOnlyButtons->Add(DropDown_ConvertM);
	Manager->ProjectOnlyButtons->Add(DropDown_BuildC);
	Manager->ProjectOnlyButtons->Add(DropDown_BuildPC);
	//Manager->ProjectOnlyButtons->Add(DropDown_BuildPK);
	Manager->ProjectOnlyButtons->Add(DropDown_ProjectSub);
	Manager->ProjectOnlyButtons->Add(BuildMode);
	Manager->ProjectOnlyButtons->Add(BuildTarget);
	Manager->ProjectOnlyButtons->Add(ToolbarBuildProject);
	Manager->ProjectOnlyButtons->Add(ToolbarPSettings);
	Manager->ProjectOnlyButtons->Add(Tools_ProjectRepair);
	Manager->ProjectOnlyButtons->Add(Build_Scripts);
	Manager->ProjectOnlyButtons->Add(Build_Children);
	Manager->ProjectOnlyButtons->Add(Build_Symbolize);
	Manager->Build_Scripts = Build_Scripts;
	Manager->Build_Children = Build_Children;
	Manager->Build_Symbolize = Build_Symbolize;
	Manager->SetUndockable(ProjectPanel->Name);
	Manager->SetUndockable(OutputPanel->Name);
	Manager->SetUndockable(ErrorPanel->Name);
	Manager->BuildMode = BuildMode;
	Manager->TargetPlatform = BuildTarget;
	Manager->StatusLabel = StatusLabel;
	BuildMode->Edit->EditValueChanged += gcnew System::EventHandler(this, &GSX_Studio::MyForm::OnBuildEditValueChanged);
	BuildModeCombo->SelectedValueChanged += gcnew System::EventHandler(this, &GSX_Studio::MyForm::OnBuildSelectedValueChanged);
	InitUserProjects();
	if (args->Length > 0)
	{
		if (args[0]->Substring(args[0]->Length - 4) != ".gsxp") //Something else
		{
			//TODO - Dialog, ask if they want to import, inject, etc
		}
		else
		{
			try
			{
				Manager->ActiveProject = GSXProject::LoadProject(args[0]); //We only load 1 File. If they give more than one, we ignore it!
				if (!Manager->ActiveProject)
				{
					Manager->Print("Invalid filename.", "Error");
					
				}
				else
				{
					Manager->ClearProjectWindows();
					//Manager->LoadProjectWindows(); Was running into issues, and found a nice implementation. Forces readme in addition to project load by only calling treeload
					Manager->LoadExplorerTree();
					Manager->SetProjectSpecificButtonsState(true);
					Manager->LoadBuildItems();
					Manager->Print(Manager->ActiveProject->ProjectName, "Loaded Project");
				}
				
			}
			catch (Exception^ e)
			{
				IDE::Print("Failed to load project", "Error", Output);
			}
		}
	}
}

void GSX_Studio::MyForm::OnOutputMouseClick(System::Object ^sender, System::Windows::Forms::MouseEventArgs ^e)
{
	if (e->Button == System::Windows::Forms::MouseButtons::Right)
	{
		OutputPopup->ShowPopup(((System::Windows::Forms::Control^)sender)->PointToScreen(e->Location));
	}
}

void GSX_Studio::MyForm::OnThisClosing(System::Object ^sender, System::ComponentModel::CancelEventArgs ^e)
{
	if (Manager->ActiveProject && Manager->ActiveProject->Unsaved)
	{
		if (!Manager->AskToSave())
			e->Cancel = true;
	}
}

void GSX_Studio::MyForm::OnBuildEditValueChanged(System::Object ^sender, System::EventArgs ^e)
{
}


void GSX_Studio::MyForm::OnBuildSelectedValueChanged(System::Object ^sender, System::EventArgs ^e)
{
	Manager->SetProjectDebug(BuildMode->EditValue != "Debug");
}