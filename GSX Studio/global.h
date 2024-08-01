#pragma once
#include "XParser.h"
#include "GSXProject.h"
#include "XParseLanguage.h"
#include "XPlatform.h"

namespace GSX_Studio
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace DevExpress;
	using namespace XParserLib;
	using namespace System::Reflection;
	using namespace Irony::Parsing;
	using namespace Microsoft::Win32;

	public ref class IDE
	{
	public:
		DevExpress::XtraRichEdit::RichEditControl^ GetNewDefaultEditor(System::String^, IDE^);
		static void Print(System::String^, System::String^, DevExpress::XtraRichEdit::RichEditControl^);
		static XParseLanguage^ GetNewGSXHandle(void);
		static XParserLib::XLNonTerminal^ DefineGSX(void);
		static void ClearConsole(DevExpress::XtraRichEdit::RichEditControl^);
		static const int ICON_METHOD = 0;
		static const int ICON_KEYWORD = 1;
		System::Collections::Generic::List<GSCScript^>^ errorscripts;
		bool OptimizeScripts = true;
		bool OptimizeChildren = false;
		bool Symbolize = true;
		DevExpress::XtraBars::BarCheckItem ^Build_Scripts, ^Build_Children, ^Build_Symbolize;
		RegistryKey^ GSXStudioRegistryKey;
		BackgroundWorker^ SyntaxWorker;

		IDE(DevExpress::XtraRichEdit::RichEditControl^ dout, DevExpress::XtraTreeList::TreeList^ derror, DevExpress::XtraTreeList::TreeList^ explorer, DevExpress::XtraBars::Docking2010::Views::Tabbed::TabbedView^ docmanager, DevExpress::XtraBars::Docking::DockManager^ dockmanager)
		{
			GSXProjectSelector = gcnew OpenFileDialog();
			GSXProjectSelector->Filter = "GSX Project File|*.gsxp";
			GSXProjectSelector->Multiselect = false;
			DOutput = dout;
			ProjectsLocation = System::Environment::GetFolderPath(System::Environment::SpecialFolder::MyDocuments) + System::IO::Path::DirectorySeparatorChar + "Black Ops II - GSX Projects";
			DError = derror;
			Explorer = explorer;
			DocumentManager = docmanager;
			DockingManager = dockmanager;
			Explorer->FocusedNodeChanged += gcnew DevExpress::XtraTreeList::FocusedNodeChangedEventHandler(this, &GSX_Studio::IDE::OnFocusedNodeChanged);
			LanguageDefinition = GetNewGSXHandle();
			ParserHandle = gcnew XParser(LanguageDefinition);
			Explorer->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &GSX_Studio::IDE::ExplorerOnMouseClick);
			Explorer->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &GSX_Studio::IDE::OnMouseDoubleClick);
			DocumentManager->DocumentActivated += gcnew DevExpress::XtraBars::Docking2010::Views::DocumentEventHandler(this, &GSX_Studio::IDE::OnDMDocumentActivated);
			DocumentManager->DocumentProperties->AllowFloat = false;
			DocumentManager->DocumentAdded += gcnew DevExpress::XtraBars::Docking2010::Views::DocumentEventHandler(this, &GSX_Studio::IDE::OnDocumentAdded);
			DocumentManager->BeginDocumentsHostDocking += gcnew DevExpress::XtraBars::Docking2010::Views::DocumentCancelEventHandler(this, &GSX_Studio::IDE::OnDMBeginDocumentsHostDocking);
			DocumentManager->BeginDocking += gcnew DevExpress::XtraBars::Docking2010::Views::DocumentCancelEventHandler(this, &GSX_Studio::IDE::OnDMBeginDocking);
			EditorImagesList = gcnew System::Windows::Forms::ImageList();
			System::IO::Stream^ stream = Assembly::GetExecutingAssembly()->GetManifestResourceStream("Method_purple_64x.png");
			EditorImagesList->Images->Add(Image::FromStream(stream));
			stream->Close();
			stream = Assembly::GetExecutingAssembly()->GetManifestResourceStream("IntelliSenseKeyword_16x.png");
			EditorImagesList->Images->Add(Image::FromStream(stream));
			stream->Close();
			GSXParser = GSXCompilerLib::Intellisense::GetGSXParser();
			CompilationWorker = gcnew System::ComponentModel::BackgroundWorker();
			CompilationWorker->WorkerReportsProgress = true;
			CompilationWorker->WorkerSupportsCancellation = true;
			CompilationWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &GSX_Studio::IDE::OnCWDoWork);
			CompilationWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &GSX_Studio::IDE::OnCWRunWorkerCompleted);
			CompilationWorker->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &GSX_Studio::IDE::OnCWProgressChanged);
			RepairWorker = gcnew System::ComponentModel::BackgroundWorker();
			RepairWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &GSX_Studio::IDE::OnRWDoWork);
			RepairWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &GSX_Studio::IDE::OnRWRunWorkerCompleted);
			Platforms = gcnew System::Collections::Generic::List<GSXCompilerLib::XPlatform^>();
			SyntaxWorker = gcnew BackgroundWorker();
			SyntaxWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &GSX_Studio::IDE::SyntaxDoWork);
			SyntaxWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &GSX_Studio::IDE::OnSyntaxRunWorkerCompleted);
			SyntaxWorker->WorkerReportsProgress = true;
			SyntaxWorker->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &GSX_Studio::IDE::SyntaxProgressChanged);
			delete stream;
		}
	internal:
		GSXProject^ ActiveProject;
		System::String^ ProjectsLocation;
		void ReportClicked(void);
		void PlatformMemClicked(void);
		void OpenProject(void);
		void ClearProjectWindows(void);
		void Print(System::String^, System::String^);
		void LoadProjectWindows(void);
		void NewProject(void);
		bool AskToSave(void);
		void SaveProject(void);
		void SaveProjectFile(void);
		void LoadExplorerTree(void);
		void LoadTextEditors(void);
		void CacheOldScript(GSCScript^ OldScript);
		void UnlinkScriptEditors(GSCScript^ OldScript);
		void CreateAndLinkScriptEditors(GSCScript^ NewScript);
		void OnFocusedNodeChanged(System::Object^, DevExpress::XtraTreeList::FocusedNodeChangedEventArgs^);
		void ExplorerOnMouseClick(System::Object ^sender, System::Windows::Forms::MouseEventArgs ^e);
		void RenameScriptFired(void);
		void RenameFileFired(void);
		void DeleteScriptFired(void);
		void DeleteFileFired(void);
		void DeleteSubgroupFired(void);
		void AddNewScript(void);
		void AppendScript(System::String^ Name, System::String^ Description);
		void AddScriptFile(void);
		void AppendScriptFile(System::String^ Name, System::String^ Description, bool DefaultCode);
		void UnloadProject(void);
		void ClearEditorWindows(void);
		void LoadImportsWindow(void);
		void SaveActiveFile(void);
		bool CheckScriptSyntax(void);
		void ClearErrorConsole(void);
		void CheckCurrentFileSyntax(void);
		void NavigateToSyntaxError(DevExpress::XtraTreeList::Nodes::TreeListNode^ node);
		void ActivateWindowByName(System::String^ name);
		void SetUpSyntaxTimer(void);
		void ResetTimerInterval(void);
		void SmartCheckFileSyntax(void);
		void SmartCheckFileGrammar(void);
		void SetProjectSpecificButtonsState(bool);
		void SetProjectDebug(bool);
		void LoadBuildItems(void);
		static Generic::List<Byte>^ GetDefaultProjectData(void);
		void ProjectSettingsWindow(void);
		void AddDefaultMethodAutoCompleteItem(System::String ^ name, System::String ^ Description, System::String^ TTTitle);
		void GSX_Studio::IDE::AddDefaultKeywordAutoCompleteItem(System::String ^ name, System::String ^ Description, System::String ^ TTTitle);
		void AddDefaultAutoComplete(void);
		void SetUndockable(System::String^ panel);
		void BuildProject(bool debug, GSXCompilerLib::PlatformTarget target);
		void DisplayBuildSettings(void);
		System::Object^ RepairProject(void);
		void RepairProjectWrapper(void);
		System::Collections::Generic::List<AutocompleteItem^>^ GetDefaultAutoCompletes(void);
		System::Collections::Generic::List<AutocompleteItem^>^ LoadAutoCompleteItems();
		System::String^ RepairSlashes(System::String^);
		System::String^ RepairFunctionRefs(System::String^);
		void ConnectToPlatform(GSXCompilerLib::XPlatformType platformid);
		void InjectExternalScripts(void);
		void InjectPackage(void);
		void InjectCurrentProject(bool debug);
		void InjectScriptsInternal(array<GSXCompilerLib::GSXInjector::IGSCFile^> ^scripts, array<GSXCompilerLib::XPlatform^>^ platforms);
		void InjectPackageInternal(System::String^ filename);
		array<GSXCompilerLib::GSXInjector::IGSCFile^>^ IGSCListFromDirectory(System::String^ TargetDirectory);

		GSXCompilerLib::Intellisense::ScriptInfo^ DeriveScriptInfo(void);

		GSCPart^ GetActivePart(void);
		XEditor^ GetGSXEditor(System::String^ contents, IDE^ ths);

		OpenFileDialog^ GetGSXProjectSelectorHandle(void);
		XParser^ ParserHandle;
		XParseLanguage^ LanguageDefinition;
		GSCScript^ ActiveScript;
		GSCPart^ ActivePart;
		Random^ r = gcnew Random();
		DevExpress::XtraBars::Docking::DockManager^ DockingManager;
		DevExpress::XtraBars::PopupMenu^ ScriptRightClick;
		DevExpress::XtraBars::PopupMenu^ PartRightClick;
		DevExpress::XtraBars::PopupMenu^ SubgroupPopup;
		DevExpress::XtraBars::Docking::DockManager^ DManager;
		System::Windows::Forms::Control^ FormControl;
		Irony::Parsing::Parser^ GSXParser;
		System::Windows::Forms::Timer^ SyntaxTimer;
		Generic::List<DevExpress::XtraBars::BarItem^>^ ProjectOnlyButtons = gcnew Generic::List<DevExpress::XtraBars::BarItem^>();
		Generic::List<DevExpress::XtraBars::BarItem^>^ InjectButtons = gcnew Generic::List<DevExpress::XtraBars::BarItem^>();
		DevExpress::XtraBars::BarItem^ InjectCurrentProjectButton;
		DevExpress::XtraBars::BarEditItem^ BuildMode;
		DevExpress::XtraBars::BarEditItem^ TargetPlatform;
		System::Collections::Generic::List<FastColoredTextBoxNS::AutocompleteItem^>^ UniversalACItems = gcnew System::Collections::Generic::List<AutocompleteItem^>();
		System::Collections::Generic::List<System::String^>^ Undockables = gcnew System::Collections::Generic::List<System::String^>();
		System::ComponentModel::BackgroundWorker^ CompilationWorker;
		System::ComponentModel::BackgroundWorker^ RepairWorker;
		DevExpress::XtraBars::BarStaticItem^ StatusLabel;
		Irony::Parsing::ParseTree^ ScriptParseTree(GSCScript^ script);
		GSXCompilerLib::Compiler^ Compiler;
		GSXCompilerLib::PlatformTarget SCurrentTarget;
		bool SDebug;
		bool InjectPostBuild = false;
		System::Collections::Generic::List<GSXCompilerLib::XPlatform^>^ Platforms;

	private:
		OpenFileDialog^ GSXProjectSelector;
		DevExpress::XtraRichEdit::RichEditControl^ DOutput;
		DevExpress::XtraTreeList::TreeList^ DError;
		DevExpress::XtraTreeList::TreeList^ Explorer;
		DevExpress::XtraBars::Docking2010::Views::Tabbed::TabbedView^ DocumentManager;
		System::Windows::Forms::ImageList^ EditorImagesList;
		bool UnboundLoad = false;
		bool UnboundWindowTransition = false;

	public:


	internal:
		ref class Utility
		{
		public:
			static bool ByteMatch(array<System::Byte> ^, array<System::Byte> ^);
			static System::String^ StringFromBytes(Generic::List<System::Byte>^, int&);
			static array<System::Byte>^ BytesFromString(System::String^);
			static void DeleteAllFilesAndDirectories(System::String^ path);
		};

		void OnMouseDoubleClick(System::Object ^sender, System::Windows::Forms::MouseEventArgs ^e);
		void OnDMDocumentActivated(System::Object ^sender, DevExpress::XtraBars::Docking2010::Views::DocumentEventArgs ^e);
		void OnFloatActivated(System::Object ^sender, System::EventArgs ^e);
		void OnDocumentAdded(System::Object ^sender, DevExpress::XtraBars::Docking2010::Views::DocumentEventArgs ^e);
		void OnXTextChangedDelayed(System::Object ^sender, FastColoredTextBoxNS::TextChangedEventArgs ^e);
		void OnSyntaxTick(System::Object ^sender, System::EventArgs ^e);
		void OnDMBeginDocking(System::Object ^sender, DevExpress::XtraBars::Docking2010::Views::DocumentCancelEventArgs ^e);
		void OnDMBeginDocumentsHostDocking(System::Object ^sender, DevExpress::XtraBars::Docking2010::Views::DocumentCancelEventArgs ^e);
		void OnCWDoWork(System::Object ^sender, System::ComponentModel::DoWorkEventArgs ^e);
		void SyntaxDoWork(System::Object ^sender, System::ComponentModel::DoWorkEventArgs ^e);
		void OnCWRunWorkerCompleted(System::Object ^sender, System::ComponentModel::RunWorkerCompletedEventArgs ^e);
		void OnSyntaxRunWorkerCompleted(System::Object ^sender, System::ComponentModel::RunWorkerCompletedEventArgs ^e);
		void OnCWProgressChanged(System::Object ^sender, System::ComponentModel::ProgressChangedEventArgs ^e);
		void SyntaxProgressChanged(System::Object ^sender, System::ComponentModel::ProgressChangedEventArgs ^e);
		void OnRWDoWork(System::Object ^sender, System::ComponentModel::DoWorkEventArgs ^e);
		void OnRWRunWorkerCompleted(System::Object ^sender, System::ComponentModel::RunWorkerCompletedEventArgs ^e);
};
}

