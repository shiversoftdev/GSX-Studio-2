#include "ImportProjectDialog.h"
#include "NotifyDialog.h"

void GSX_Studio::ImportProjectDialog::BackgroundWorker1_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	e->Result = BeginImportsThread(Directories, (System::ComponentModel::BackgroundWorker^)sender, ScriptPath->Text, CreatorName->Text, ConflictsHandling->Text[0] == 'O');
	if (((System::ComponentModel::BackgroundWorker^)sender)->CancellationPending)
	{
		e->Cancel = true;
	}
}

array<System::Byte>^ GSX_Studio::ImportProjectDialog::BytesFromString(System::String ^ str)
{
	Generic::List<Byte>^ bytes = gcnew Generic::List<Byte>();
	for (int i = 0; i < str->Length; i++)
	{
		bytes->Add((Byte)str[i]);
	}
	bytes->Add(0x0);
	return bytes->ToArray();
}

void GSX_Studio::ImportProjectDialog::AddProject(void)
{
	System::Windows::Forms::DialogResult r = Browser->ShowDialog();
	if (r != System::Windows::Forms::DialogResult::OK)
		return;
	if (!File::Exists(Browser->SelectedPath + Path::DirectorySeparatorChar + "main.gsc"))
	{
		NotifyDialog^ dialog = gcnew NotifyDialog();
		dialog->Text = "Invalid GSC Studio Project";
		dialog->Message->Text = "No 'main.gsc' file found in this folder. If you meant to add a projects folder, please select the 'Add Projects Folder' option.";
		dialog->ShowDialog();
		delete dialog;
		return;
	}
	if (Directories->Contains(Browser->SelectedPath))
		return;;
	Directories->Add(Browser->SelectedPath);
	RefreshProjectsList();
}

void GSX_Studio::ImportProjectDialog::AddProjectsPath(void)
{
	System::Windows::Forms::DialogResult r = Browser->ShowDialog();
	if (r != System::Windows::Forms::DialogResult::OK)
		return;
	Generic::List<String^>^ files = gcnew Generic::List<String^>();
	for each(String^ dir in Directory::GetDirectories(Browser->SelectedPath))
	{
		if (dir + Path::DirectorySeparatorChar + "main.gsc")
		{
			files->Add(dir);
		}
	}
	if (files->Count < 1)
	{
		delete files;
		NotifyDialog^ dialog = gcnew NotifyDialog();
		dialog->Text = "No GSC Studio Projects Found";
		dialog->Message->Text = "None of the folders in this directory contain a 'main.gsc'. This folder doesnt appear to contain any valid projects to import. If you meant to select a single project folder, please select 'Add project'";
		dialog->ShowDialog();
		delete dialog;
		return;
	}
	for each(System::String^ dir in files)
	{
		if (Directories->Contains(dir))
			continue;
		Directories->Add(dir);
	}
	RefreshProjectsList();
}

void GSX_Studio::ImportProjectDialog::ClearProjects(void)
{
	Directories->Clear();
	RefreshProjectsList();
}

void GSX_Studio::ImportProjectDialog::RemoveSelectedProject(void)
{
	if (!ProjectsList->Selection[0])
		return;
	System::String^ dir = (String^)ProjectsList->Selection[0]->GetValue(0);
	Directories->Remove(dir);
	RefreshProjectsList();
}

void GSX_Studio::ImportProjectDialog::OnTreeMouseClick(System::Object ^sender, System::Windows::Forms::MouseEventArgs ^e)
{
	if (e->Button == System::Windows::Forms::MouseButtons::Right)
	{
		RContextMenu->ShowPopup(((System::Windows::Forms::Control^)sender)->PointToScreen(e->Location));
	}
}

void GSX_Studio::ImportProjectDialog::RefreshProjectsList(void)
{
	ProjectsList->BeginUnboundLoad();
	ProjectsList->Nodes->Clear();
	for each(String^ dir in Directories)
	{
		ProjectsList->AppendNode(gcnew array<String^>{ dir }, -1);
	}
	ProjectsList->EndUnboundLoad();
	if (Directories->Count > 0)
	{
		StartImports->Enabled = true;
	}
	else
	{
		StartImports->Enabled = false;
	}
}

void GSX_Studio::ImportProjectDialog::BackgroundWorker1_RunWorkerCompleted(System::Object ^ sender, System::ComponentModel::RunWorkerCompletedEventArgs ^ e)
{
	if (!e->Cancelled && e->Result)
	{
		NotifyDialog^ dialog = gcnew NotifyDialog();
		dialog->Text = "Success!";
		dialog->Message->Text = "Finished importing all projects!";
		dialog->ShowDialog();
		delete dialog;
	}
	progressBarControl1->EditValue = 0;
	progressBarControl1->Update();
	CancelImports->Enabled = false;
	CancelImports->Visible = false;
	StartImports->Enabled = true;
	ProjectsList->Enabled = true;
	simpleButton1->Enabled = true;
	AddProjects->Enabled = true;
}

void GSX_Studio::ImportProjectDialog::BackgroundWorker1_ProgressChanged(System::Object ^ sender, System::ComponentModel::ProgressChangedEventArgs ^ e)
{
	if (progressBarControl1->Properties->Maximum != (int)e->UserState)
	{
		progressBarControl1->Properties->Maximum = (int)e->UserState;
	}
	progressBarControl1->PerformStep();
	progressBarControl1->Update();
}

System::Object ^ GSX_Studio::ImportProjectDialog::BeginImportsThread(System::Collections::Generic::List<System::String^>^ directories, System::ComponentModel::BackgroundWorker ^ bgx, System::String^ ScriptName, System::String^ Creator, bool DoReplace)
{
	for (int i = 0; i < directories->Count && !bgx->CancellationPending; i++)
	{
		array<String^>^ split = directories[i]->Split(Path::DirectorySeparatorChar);
		String^ ProjectName = split[split->Length - 1];
		String^ ProjectPath = ProjectsLocation + Path::DirectorySeparatorChar + ProjectName + Path::DirectorySeparatorChar + ProjectName;
		String^ ScriptPath = ProjectPath;
		if (!Directory::Exists(ProjectsLocation + Path::DirectorySeparatorChar + ProjectName) || DoReplace)
		{
			if (Directory::Exists(ProjectsLocation + Path::DirectorySeparatorChar + ProjectName))
			{
				System::IO::DirectoryInfo^ di = gcnew DirectoryInfo(ProjectsLocation + Path::DirectorySeparatorChar + ProjectName);

				for each(FileInfo^ file in di->GetFiles())
				{
					file->Delete();
				}
				for each(DirectoryInfo^ dir in di->GetDirectories())
				{
					dir->Delete(true);
				}
				if (Directory::Exists(ProjectsLocation + Path::DirectorySeparatorChar + ProjectName))
					Directory::Delete(ProjectsLocation + Path::DirectorySeparatorChar + ProjectName);
			}
			Directory::CreateDirectory(ProjectsLocation + Path::DirectorySeparatorChar + ProjectName);
			Directory::CreateDirectory(ProjectPath);
			for each(System::String^ part in ScriptName->Split('\\'))
			{
				if (!Directory::Exists(ScriptPath + Path::DirectorySeparatorChar + part))
				{
					Directory::CreateDirectory(ScriptPath + Path::DirectorySeparatorChar + part);
				}
				ScriptPath += Path::DirectorySeparatorChar + part;
			}
			Generic::List<System::String^>^ sparts = gcnew Generic::List<String^>();
			for each(System::String^ file in Directory::GetFiles(directories[i], "*.gsc"))
			{
				sparts->Add(file);
				File::Copy(file, ScriptPath + Path::DirectorySeparatorChar + file->Substring(file->LastIndexOf(Path::DirectorySeparatorChar) + 1)->Replace(".gsc", ".gsx"));
			}
			Generic::List<Byte>^ project = gcnew Generic::List<Byte>();
			project->AddRange(gcnew array<Byte>{0x25, 0x47, 0x53, 0x58, 0x50, 0x25});
			project->AddRange(BytesFromString(Creator));
			project->AddRange(BytesFromString(ProjectName));
			project->Add(0x1);
			project->AddRange(BytesFromString(ScriptName));
			project->Add(sparts->Count);
			for each(String^ file in sparts)
			{
				project->AddRange(BytesFromString(file->Substring(file->LastIndexOf(Path::DirectorySeparatorChar) + 1)->Replace(".gsc", ".gsx")));
			}
			project->AddRange(GetDefaultProjectData());
			try
			{
				File::WriteAllBytes(ProjectsLocation + Path::DirectorySeparatorChar + ProjectName + Path::DirectorySeparatorChar + ProjectName + ".gsxp", project->ToArray());
			}
			catch (Exception^)
			{
			}
		}
		bgx->ReportProgress(i / directories->Count, directories->Count);
	}
	return 1;
}

System::Collections::Generic::List<System::Byte>^ GSX_Studio::ImportProjectDialog::GetDefaultProjectData(void)
{
	Generic::List<System::Byte>^ data = gcnew Generic::List<Byte>();
	data->Add(0x1); //typestrict setting
	data->Add(0x2); //inline setting
	data->Add(0x1); //debug 
	data->AddRange(BytesFromString("Created in GSX Studio!")); //Default Watermark
	return data;
}