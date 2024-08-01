#pragma once
#include "global.h"
#include <Windows.h>
//Convert.ToInt32(prefixedHex , 16);
namespace GSX_Studio {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace DevExpress;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public DevExpress::XtraEditors::XtraForm
	{
	public:

		void AddDefaultProject(IDE^);
		void InitUserProjects(void);
		void InitializeForm(array<String^>^ args);

		MyForm(array<String^>^ args)
		{
			DevExpress::Skins::SkinManager::EnableFormSkins();
			DevExpress::UserSkins::BonusSkins::Register();
			InitializeComponent();
			SyntaxTimer->Stop();
			InitializeForm(args);
			this->Closing += gcnew System::ComponentModel::CancelEventHandler(this, &GSX_Studio::MyForm::OnThisClosing);
			ErrorConsole->Click += gcnew System::EventHandler(this, &GSX_Studio::MyForm::OnGClick);
		}
	private: DevExpress::XtraBars::BarSubItem^  barSubItem13;
	public:
	private: DevExpress::XtraBars::BarSubItem^  barSubItem14;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem33;
	private: DevExpress::XtraBars::BarButtonItem^  DropDown_Close;


	private: DevExpress::XtraBars::BarStaticItem^  barStaticItem2;
	private: DevExpress::XtraBars::Docking2010::Views::Tabbed::DocumentGroup^  documentGroup1;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem35;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem36;
	private: DevExpress::XtraBars::PopupMenu^  SRightClick;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem37;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem38;
	private: DevExpress::XtraBars::PopupMenu^  PRightClick;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem39;
	private: DevExpress::XtraBars::BarButtonItem^  DropDown_NewScript;

	private: DevExpress::XtraBars::BarSubItem^  barSubItem15;
	private: DevExpress::XtraBars::BarCheckItem^  ZombiesToggle;
	private: DevExpress::XtraBars::BarCheckItem^  barCheckItem3;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem40;
	private: DevExpress::XtraBars::BarSubItem^  barSubItem16;
	private: DevExpress::XtraBars::BarButtonItem^  DropDown_ConvertZ;
	private: DevExpress::XtraBars::BarButtonItem^  DropDown_ConvertM;


	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem42;
	private: DevExpress::XtraBars::BarStaticItem^  barStaticItem3;
	private: DevExpress::XtraBars::PopupMenu^  OutputPopup;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem45;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem46;
	private: DevExpress::XtraBars::PopupMenu^  SubgroupPopup;
	private: DevExpress::XtraBars::BarSubItem^  DropDown_ProjectSub;


	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem47;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem48;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem49;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem50;
	private: System::Windows::Forms::ColorDialog^  ColorTool;
	private: DevExpress::XtraTreeList::TreeList^  ErrorConsole;
	private: DevExpress::XtraTreeList::Columns::TreeListColumn^  treeListColumn5;
	private: DevExpress::XtraTreeList::Columns::TreeListColumn^  treeListColumn2;
	private: DevExpress::XtraTreeList::Columns::TreeListColumn^  treeListColumn3;
	private: DevExpress::XtraTreeList::Columns::TreeListColumn^  treeListColumn4;
	private: DevExpress::XtraTreeList::Columns::TreeListColumn^  treeListColumn6;

	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem51;
	private: DevExpress::XtraEditors::Repository::RepositoryItemPictureEdit^  repositoryItemPictureEdit1;
	private: System::Windows::Forms::Timer^  SyntaxTimer;
	private: DevExpress::XtraBars::Bar^  bar1;
	private: DevExpress::XtraBars::BarEditItem^  BuildMode;
	private: DevExpress::XtraEditors::Repository::RepositoryItemComboBox^  BuildModeCombo;




	private: DevExpress::XtraBars::BarCheckItem^  DebugToggleSwitch;
	private: DevExpress::XtraBars::BarToggleSwitchItem^  barToggleSwitchItem1;
	private: DevExpress::XtraBars::BarStaticItem^  barStaticItem4;
	private: DevExpress::XtraBars::BarEditItem^  barEditItem2;
	private: DevExpress::XtraEditors::Repository::RepositoryItemComboBox^  repositoryItemComboBox2;
	private: DevExpress::XtraBars::BarButtonItem^  ToolbarBuildProject;

	private: DevExpress::XtraBars::BarLargeButtonItem^  barLargeButtonItem1;
	private: DevExpress::XtraBars::BarEditItem^  barEditItem3;
	private: DevExpress::XtraEditors::Repository::RepositoryItemTextEdit^  repositoryItemTextEdit1;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem52;
	private: DevExpress::XtraBars::BarEditItem^  barEditItem4;
	private: DevExpress::XtraEditors::Repository::RepositoryItemTextEdit^  repositoryItemTextEdit2;
	private: DevExpress::XtraBars::BarEditItem^  barEditItem5;
	private: DevExpress::XtraEditors::Repository::RepositoryItemComboBox^  repositoryItemComboBox3;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem53;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem55;
	private: DevExpress::XtraBars::BarButtonItem^  Toolbar_Save;


	private: DevExpress::XtraBars::BarButtonItem^  Toolbar_SaveAll;

	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem58;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem59;
	private: DevExpress::XtraBars::BarEditItem^  barEditItem6;
	private: DevExpress::XtraEditors::Repository::RepositoryItemComboBox^  repositoryItemComboBox4;
	private: DevExpress::XtraBars::BarEditItem^  BuildTarget;
private: DevExpress::XtraEditors::Repository::RepositoryItemComboBox^  BuildTargetCombo;



	private: DevExpress::XtraBars::BarButtonItem^  DropDown_PSettings;
private: DevExpress::XtraBars::BarButtonItem^  ToolbarPSettings;
private: DevExpress::XtraBars::Docking::DockPanel^  panelContainer1;
private: DevExpress::XtraBars::BarEditItem^  barEditItem1;
private: DevExpress::XtraEditors::Repository::RepositoryItemProgressBar^  repositoryItemProgressBar1;
private: DevExpress::XtraBars::BarButtonItem^  Tools_ProjectRepair;
private: DevExpress::XtraBars::BarButtonItem^  BuildSettingsButton;
private: DevExpress::XtraBars::BarButtonItem^  Bar_BuildSettings;
private: DevExpress::XtraBars::BarSubItem^  barSubItem17;
private: DevExpress::XtraBars::BarCheckItem^  Build_Scripts;

private: DevExpress::XtraBars::BarButtonItem^  barButtonItem13;
private: DevExpress::XtraBars::BarButtonItem^  barButtonItem17;
private: DevExpress::XtraBars::BarCheckItem^  Build_Children;
private: DevExpress::XtraBars::BarCheckItem^  Build_Symbolize;
private: DevExpress::XtraBars::BarButtonItem^  barButtonItem18;
private: DevExpress::XtraBars::BarSubItem^  barSubItem18;
private: DevExpress::XtraBars::BarButtonItem^  barButtonItem19;
private: DevExpress::XtraBars::BarSubItem^  barSubItem19;
private: DevExpress::XtraBars::BarButtonItem^  barButtonItem32;
private: DevExpress::XtraBars::BarButtonItem^  barButtonItem34;
private: DevExpress::XtraBars::BarButtonItem^  barButtonItem41;
private: DevExpress::XtraBars::BarSubItem^  barSubItem20;
private: DevExpress::XtraBars::BarButtonItem^  barButtonItem43;
private: DevExpress::XtraBars::BarButtonItem^  barButtonItem56;
private: DevExpress::XtraBars::BarButtonItem^  barButtonItem64;
private: DevExpress::XtraBars::BarButtonItem^  barButtonItem63;
private: DevExpress::XtraBars::BarButtonItem^  barButtonItem65;
private: DevExpress::XtraBars::BarButtonItem^  barButtonItem44;
private: DevExpress::XtraBars::BarSubItem^  barSubItem21;
private: DevExpress::XtraBars::BarButtonItem^  barButtonItem54;
private: DevExpress::XtraBars::BarButtonItem^  barButtonItem57;
private: DevExpress::XtraBars::BarSubItem^  barSubItem22;
private: DevExpress::XtraBars::BarButtonItem^  barButtonItem60;
private: DevExpress::XtraBars::BarButtonItem^  barButtonItem61;
private: DevExpress::XtraBars::BarButtonItem^  barButtonItem62;
private: DevExpress::XtraBars::BarSubItem^  barSubItem23;
private: DevExpress::XtraBars::BarSubItem^  barSubItem24;
private: DevExpress::XtraBars::BarButtonItem^  barButtonItem67;
private: DevExpress::XtraBars::BarButtonItem^  barButtonItem66;










		GSX_Studio::IDE^ Manager;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			try
			{
				if (components)
				{
					delete components;
				}
			}
			catch(System::Exception^)
			{
				//Wtf lmao
			}
		}
	private: DevExpress::XtraBars::BarManager^  Toolbars;
	protected:

	protected:

	private: DevExpress::XtraBars::Bar^  bar2;
	private: DevExpress::XtraBars::Bar^  bar3;
	private: DevExpress::XtraBars::BarDockControl^  barDockControlTop;
	private: DevExpress::XtraBars::BarDockControl^  barDockControlBottom;
	private: DevExpress::XtraBars::BarDockControl^  barDockControlLeft;
	private: DevExpress::XtraBars::BarDockControl^  barDockControlRight;
	private: DevExpress::XtraBars::BarSubItem^  barSubItem1;
	private: DevExpress::XtraBars::BarSubItem^  barSubItem2;
	private: DevExpress::XtraBars::BarSubItem^  barSubItem3;
	private: DevExpress::XtraBars::BarSubItem^  barSubItem4;
	private: DevExpress::XtraBars::BarSubItem^  barSubItem5;
private: DevExpress::XtraBars::BarStaticItem^  StatusLabel;

	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem1;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem2;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem3;
	private: DevExpress::XtraBars::DefaultBarAndDockingController^  Toolbarsmanager;
	private: DevExpress::XtraBars::BarSubItem^  barSubItem6;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem4;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem5;
	private: DevExpress::XtraBars::BarSubItem^  barSubItem8;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem8;
	private: DevExpress::XtraBars::BarSubItem^  barSubItem9;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem9;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem10;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem11;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem12;
private: DevExpress::XtraBars::BarButtonItem^  DropDown_SaveAll;

	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem15;
	private: DevExpress::XtraBars::BarSubItem^  barSubItem10;
private: DevExpress::XtraBars::BarButtonItem^  DropDown_BuildC;
private: DevExpress::XtraBars::BarButtonItem^  DropDown_BuildPC;
private: DevExpress::XtraBars::BarButtonItem^  DropDown_BuildPK;




	private: DevExpress::XtraBars::BarSubItem^  barSubItem11;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem20;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem21;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem22;
	private: DevExpress::XtraBars::BarCheckItem^  barCheckItem1;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem6;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem7;
	private: DevExpress::XtraBars::BarSubItem^  barSubItem7;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem14;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem16;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem23;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem24;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem25;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem26;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem27;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem29;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem28;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem30;
	private: DevExpress::XtraBars::BarCheckItem^  barCheckItem2;
	private: DevExpress::XtraBars::BarSubItem^  barSubItem12;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem31;
	private: DevExpress::XtraBars::Docking::DockManager^  dockManager1;
private: DevExpress::XtraBars::Docking::DockPanel^  ProjectPanel;

	private: DevExpress::XtraBars::Docking::ControlContainer^  dockPanel1_Container;
	private: DevExpress::XtraBars::Docking::DockPanel^  dockPanel2;
	private: DevExpress::XtraBars::Docking::ControlContainer^  dockPanel2_Container;
	private: DevExpress::XtraBars::Docking2010::DocumentManager^  documentManager1;
	private: DevExpress::XtraBars::Docking2010::Views::Tabbed::TabbedView^  tabbedView1;

	private: DevExpress::XtraBars::Docking2010::Views::Tabbed::Document^  document1;
private: DevExpress::XtraTreeList::TreeList^  ProjectExplorer;

	private: DevExpress::XtraTreeList::Columns::TreeListColumn^  treeListColumn1;
private: DevExpress::XtraBars::BarButtonItem^  DropDown_Save;
private: DevExpress::XtraBars::Docking::DockPanel^  ErrorPanel;



	private: DevExpress::XtraBars::Docking::ControlContainer^  dockPanel3_Container;
private: DevExpress::XtraBars::Docking::DockPanel^  OutputPanel;




	private: DevExpress::XtraBars::Docking::ControlContainer^  dockPanel4_Container;
private: DevExpress::XtraRichEdit::RichEditControl^  Output;


private:





	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			DevExpress::XtraSplashScreen::SplashScreenManager^  splashScreenManager1 = (gcnew DevExpress::XtraSplashScreen::SplashScreenManager(this,
				nullptr, true, true, true));
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->Toolbars = (gcnew DevExpress::XtraBars::BarManager(this->components));
			this->bar2 = (gcnew DevExpress::XtraBars::Bar());
			this->barSubItem1 = (gcnew DevExpress::XtraBars::BarSubItem());
			this->barSubItem6 = (gcnew DevExpress::XtraBars::BarSubItem());
			this->barButtonItem4 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem5 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barSubItem8 = (gcnew DevExpress::XtraBars::BarSubItem());
			this->barButtonItem8 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barSubItem9 = (gcnew DevExpress::XtraBars::BarSubItem());
			this->barButtonItem9 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem10 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barSubItem2 = (gcnew DevExpress::XtraBars::BarSubItem());
			this->barButtonItem11 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem12 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->DropDown_NewScript = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->DropDown_Save = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->DropDown_SaveAll = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->DropDown_Close = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem30 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->DropDown_ProjectSub = (gcnew DevExpress::XtraBars::BarSubItem());
			this->barSubItem16 = (gcnew DevExpress::XtraBars::BarSubItem());
			this->DropDown_ConvertZ = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->DropDown_ConvertM = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->DropDown_PSettings = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barSubItem11 = (gcnew DevExpress::XtraBars::BarSubItem());
			this->barButtonItem20 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem21 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem27 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barSubItem3 = (gcnew DevExpress::XtraBars::BarSubItem());
			this->DropDown_BuildC = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->DropDown_BuildPC = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->DropDown_BuildPK = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barSubItem17 = (gcnew DevExpress::XtraBars::BarSubItem());
			this->Build_Scripts = (gcnew DevExpress::XtraBars::BarCheckItem());
			this->Build_Children = (gcnew DevExpress::XtraBars::BarCheckItem());
			this->Build_Symbolize = (gcnew DevExpress::XtraBars::BarCheckItem());
			this->barSubItem20 = (gcnew DevExpress::XtraBars::BarSubItem());
			this->barButtonItem56 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem64 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem63 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem65 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barSubItem23 = (gcnew DevExpress::XtraBars::BarSubItem());
			this->barSubItem13 = (gcnew DevExpress::XtraBars::BarSubItem());
			this->barButtonItem50 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem22 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->Tools_ProjectRepair = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barSubItem24 = (gcnew DevExpress::XtraBars::BarSubItem());
			this->barButtonItem67 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barSubItem5 = (gcnew DevExpress::XtraBars::BarSubItem());
			this->barButtonItem25 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem24 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem23 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem26 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->bar3 = (gcnew DevExpress::XtraBars::Bar());
			this->StatusLabel = (gcnew DevExpress::XtraBars::BarStaticItem());
			this->bar1 = (gcnew DevExpress::XtraBars::Bar());
			this->barButtonItem58 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem59 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->Toolbar_Save = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->Toolbar_SaveAll = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->BuildMode = (gcnew DevExpress::XtraBars::BarEditItem());
			this->BuildModeCombo = (gcnew DevExpress::XtraEditors::Repository::RepositoryItemComboBox());
			this->BuildTarget = (gcnew DevExpress::XtraBars::BarEditItem());
			this->BuildTargetCombo = (gcnew DevExpress::XtraEditors::Repository::RepositoryItemComboBox());
			this->ToolbarBuildProject = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->ToolbarPSettings = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barDockControlTop = (gcnew DevExpress::XtraBars::BarDockControl());
			this->barDockControlBottom = (gcnew DevExpress::XtraBars::BarDockControl());
			this->barDockControlLeft = (gcnew DevExpress::XtraBars::BarDockControl());
			this->barDockControlRight = (gcnew DevExpress::XtraBars::BarDockControl());
			this->dockManager1 = (gcnew DevExpress::XtraBars::Docking::DockManager(this->components));
			this->panelContainer1 = (gcnew DevExpress::XtraBars::Docking::DockPanel());
			this->ErrorPanel = (gcnew DevExpress::XtraBars::Docking::DockPanel());
			this->dockPanel3_Container = (gcnew DevExpress::XtraBars::Docking::ControlContainer());
			this->ErrorConsole = (gcnew DevExpress::XtraTreeList::TreeList());
			this->treeListColumn5 = (gcnew DevExpress::XtraTreeList::Columns::TreeListColumn());
			this->repositoryItemPictureEdit1 = (gcnew DevExpress::XtraEditors::Repository::RepositoryItemPictureEdit());
			this->treeListColumn2 = (gcnew DevExpress::XtraTreeList::Columns::TreeListColumn());
			this->treeListColumn3 = (gcnew DevExpress::XtraTreeList::Columns::TreeListColumn());
			this->treeListColumn6 = (gcnew DevExpress::XtraTreeList::Columns::TreeListColumn());
			this->treeListColumn4 = (gcnew DevExpress::XtraTreeList::Columns::TreeListColumn());
			this->OutputPanel = (gcnew DevExpress::XtraBars::Docking::DockPanel());
			this->dockPanel4_Container = (gcnew DevExpress::XtraBars::Docking::ControlContainer());
			this->Output = (gcnew DevExpress::XtraRichEdit::RichEditControl());
			this->ProjectPanel = (gcnew DevExpress::XtraBars::Docking::DockPanel());
			this->dockPanel1_Container = (gcnew DevExpress::XtraBars::Docking::ControlContainer());
			this->ProjectExplorer = (gcnew DevExpress::XtraTreeList::TreeList());
			this->treeListColumn1 = (gcnew DevExpress::XtraTreeList::Columns::TreeListColumn());
			this->dockPanel2 = (gcnew DevExpress::XtraBars::Docking::DockPanel());
			this->dockPanel2_Container = (gcnew DevExpress::XtraBars::Docking::ControlContainer());
			this->barButtonItem1 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem2 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem3 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barSubItem4 = (gcnew DevExpress::XtraBars::BarSubItem());
			this->barButtonItem6 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem7 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barSubItem7 = (gcnew DevExpress::XtraBars::BarSubItem());
			this->barButtonItem14 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem15 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem16 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barSubItem10 = (gcnew DevExpress::XtraBars::BarSubItem());
			this->barCheckItem1 = (gcnew DevExpress::XtraBars::BarCheckItem());
			this->barButtonItem28 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem29 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barSubItem12 = (gcnew DevExpress::XtraBars::BarSubItem());
			this->barButtonItem31 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barCheckItem2 = (gcnew DevExpress::XtraBars::BarCheckItem());
			this->barSubItem14 = (gcnew DevExpress::XtraBars::BarSubItem());
			this->barButtonItem33 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barStaticItem2 = (gcnew DevExpress::XtraBars::BarStaticItem());
			this->barButtonItem35 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem36 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem37 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem38 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem39 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barCheckItem3 = (gcnew DevExpress::XtraBars::BarCheckItem());
			this->barButtonItem40 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->ZombiesToggle = (gcnew DevExpress::XtraBars::BarCheckItem());
			this->barSubItem15 = (gcnew DevExpress::XtraBars::BarSubItem());
			this->barButtonItem42 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barStaticItem3 = (gcnew DevExpress::XtraBars::BarStaticItem());
			this->barButtonItem45 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem46 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem47 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem48 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem49 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem51 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->DebugToggleSwitch = (gcnew DevExpress::XtraBars::BarCheckItem());
			this->barToggleSwitchItem1 = (gcnew DevExpress::XtraBars::BarToggleSwitchItem());
			this->barEditItem2 = (gcnew DevExpress::XtraBars::BarEditItem());
			this->repositoryItemComboBox2 = (gcnew DevExpress::XtraEditors::Repository::RepositoryItemComboBox());
			this->barStaticItem4 = (gcnew DevExpress::XtraBars::BarStaticItem());
			this->barLargeButtonItem1 = (gcnew DevExpress::XtraBars::BarLargeButtonItem());
			this->barEditItem3 = (gcnew DevExpress::XtraBars::BarEditItem());
			this->repositoryItemTextEdit1 = (gcnew DevExpress::XtraEditors::Repository::RepositoryItemTextEdit());
			this->barButtonItem52 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barEditItem4 = (gcnew DevExpress::XtraBars::BarEditItem());
			this->repositoryItemTextEdit2 = (gcnew DevExpress::XtraEditors::Repository::RepositoryItemTextEdit());
			this->barEditItem5 = (gcnew DevExpress::XtraBars::BarEditItem());
			this->repositoryItemComboBox3 = (gcnew DevExpress::XtraEditors::Repository::RepositoryItemComboBox());
			this->barButtonItem53 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem55 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barEditItem6 = (gcnew DevExpress::XtraBars::BarEditItem());
			this->repositoryItemComboBox4 = (gcnew DevExpress::XtraEditors::Repository::RepositoryItemComboBox());
			this->barEditItem1 = (gcnew DevExpress::XtraBars::BarEditItem());
			this->repositoryItemProgressBar1 = (gcnew DevExpress::XtraEditors::Repository::RepositoryItemProgressBar());
			this->Bar_BuildSettings = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->BuildSettingsButton = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem13 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem17 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem18 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barSubItem18 = (gcnew DevExpress::XtraBars::BarSubItem());
			this->barButtonItem19 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barSubItem19 = (gcnew DevExpress::XtraBars::BarSubItem());
			this->barButtonItem32 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem34 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem41 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem43 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem44 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barSubItem21 = (gcnew DevExpress::XtraBars::BarSubItem());
			this->barButtonItem54 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem57 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barSubItem22 = (gcnew DevExpress::XtraBars::BarSubItem());
			this->barButtonItem60 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem61 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem62 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->barButtonItem66 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->Toolbarsmanager = (gcnew DevExpress::XtraBars::DefaultBarAndDockingController(this->components));
			this->documentManager1 = (gcnew DevExpress::XtraBars::Docking2010::DocumentManager(this->components));
			this->tabbedView1 = (gcnew DevExpress::XtraBars::Docking2010::Views::Tabbed::TabbedView(this->components));
			this->documentGroup1 = (gcnew DevExpress::XtraBars::Docking2010::Views::Tabbed::DocumentGroup(this->components));
			this->document1 = (gcnew DevExpress::XtraBars::Docking2010::Views::Tabbed::Document(this->components));
			this->SRightClick = (gcnew DevExpress::XtraBars::PopupMenu(this->components));
			this->PRightClick = (gcnew DevExpress::XtraBars::PopupMenu(this->components));
			this->OutputPopup = (gcnew DevExpress::XtraBars::PopupMenu(this->components));
			this->SubgroupPopup = (gcnew DevExpress::XtraBars::PopupMenu(this->components));
			this->ColorTool = (gcnew System::Windows::Forms::ColorDialog());
			this->SyntaxTimer = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Toolbars))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BuildModeCombo))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BuildTargetCombo))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dockManager1))->BeginInit();
			this->panelContainer1->SuspendLayout();
			this->ErrorPanel->SuspendLayout();
			this->dockPanel3_Container->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ErrorConsole))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->repositoryItemPictureEdit1))->BeginInit();
			this->OutputPanel->SuspendLayout();
			this->dockPanel4_Container->SuspendLayout();
			this->ProjectPanel->SuspendLayout();
			this->dockPanel1_Container->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ProjectExplorer))->BeginInit();
			this->dockPanel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->repositoryItemComboBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->repositoryItemTextEdit1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->repositoryItemTextEdit2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->repositoryItemComboBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->repositoryItemComboBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->repositoryItemProgressBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Toolbarsmanager->Controller))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->documentManager1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tabbedView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->documentGroup1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->document1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SRightClick))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PRightClick))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->OutputPopup))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SubgroupPopup))->BeginInit();
			this->SuspendLayout();
			// 
			// splashScreenManager1
			// 
			splashScreenManager1->ClosingDelay = 500;
			// 
			// Toolbars
			// 
			this->Toolbars->AllowCustomization = false;
			this->Toolbars->AllowQuickCustomization = false;
			this->Toolbars->Bars->AddRange(gcnew cli::array< DevExpress::XtraBars::Bar^  >(3) { this->bar2, this->bar3, this->bar1 });
			this->Toolbars->DockControls->Add(this->barDockControlTop);
			this->Toolbars->DockControls->Add(this->barDockControlBottom);
			this->Toolbars->DockControls->Add(this->barDockControlLeft);
			this->Toolbars->DockControls->Add(this->barDockControlRight);
			this->Toolbars->DockManager = this->dockManager1;
			this->Toolbars->Form = this;
			this->Toolbars->Items->AddRange(gcnew cli::array< DevExpress::XtraBars::BarItem^  >(131) {
				this->StatusLabel, this->barButtonItem1,
					this->barButtonItem2, this->barButtonItem3, this->barSubItem1, this->barSubItem2, this->barSubItem3, this->barSubItem4, this->barSubItem5,
					this->barSubItem6, this->barButtonItem4, this->barButtonItem5, this->barButtonItem6, this->barButtonItem7, this->barSubItem7,
					this->barSubItem8, this->barButtonItem8, this->barSubItem9, this->barButtonItem9, this->barButtonItem10, this->barButtonItem11,
					this->barButtonItem12, this->DropDown_SaveAll, this->barButtonItem14, this->barButtonItem15, this->barButtonItem16, this->barSubItem10,
					this->DropDown_BuildC, this->DropDown_BuildPC, this->DropDown_BuildPK, this->barSubItem11, this->barButtonItem20, this->barButtonItem21,
					this->barButtonItem22, this->barCheckItem1, this->barButtonItem23, this->barButtonItem24, this->barButtonItem25, this->barButtonItem26,
					this->barButtonItem27, this->barButtonItem28, this->barButtonItem29, this->barSubItem12, this->barButtonItem30, this->barButtonItem31,
					this->barCheckItem2, this->DropDown_Save, this->barSubItem13, this->barSubItem14, this->barButtonItem33, this->DropDown_Close,
					this->barStaticItem2, this->barButtonItem35, this->barButtonItem36, this->barButtonItem37, this->barButtonItem38, this->barButtonItem39,
					this->barCheckItem3, this->barButtonItem40, this->ZombiesToggle, this->barSubItem15, this->DropDown_NewScript, this->barButtonItem42,
					this->barSubItem16, this->DropDown_ConvertZ, this->DropDown_ConvertM, this->barStaticItem3, this->barButtonItem45, this->barButtonItem46,
					this->DropDown_ProjectSub, this->barButtonItem47, this->barButtonItem48, this->barButtonItem49, this->barButtonItem50, this->barButtonItem51,
					this->DebugToggleSwitch, this->barToggleSwitchItem1, this->BuildMode, this->barEditItem2, this->barStaticItem4, this->barLargeButtonItem1,
					this->barEditItem3, this->barButtonItem52, this->barEditItem4, this->barEditItem5, this->barButtonItem53, this->ToolbarBuildProject,
					this->barButtonItem55, this->Toolbar_Save, this->Toolbar_SaveAll, this->barButtonItem58, this->barButtonItem59, this->barEditItem6,
					this->BuildTarget, this->DropDown_PSettings, this->ToolbarPSettings, this->barEditItem1, this->Tools_ProjectRepair, this->Bar_BuildSettings,
					this->BuildSettingsButton, this->barSubItem17, this->Build_Scripts, this->barButtonItem13, this->barButtonItem17, this->Build_Children,
					this->Build_Symbolize, this->barButtonItem18, this->barSubItem18, this->barButtonItem19, this->barSubItem19, this->barButtonItem32,
					this->barButtonItem34, this->barButtonItem41, this->barSubItem20, this->barButtonItem43, this->barButtonItem44, this->barSubItem21,
					this->barButtonItem54, this->barButtonItem56, this->barButtonItem57, this->barSubItem22, this->barButtonItem60, this->barButtonItem61,
					this->barButtonItem62, this->barButtonItem63, this->barButtonItem64, this->barButtonItem65, this->barSubItem23, this->barButtonItem66,
					this->barSubItem24, this->barButtonItem67
			});
			this->Toolbars->MainMenu = this->bar2;
			this->Toolbars->MaxItemId = 131;
			this->Toolbars->RepositoryItems->AddRange(gcnew cli::array< DevExpress::XtraEditors::Repository::RepositoryItem^  >(8) {
				this->BuildModeCombo,
					this->repositoryItemComboBox2, this->repositoryItemTextEdit1, this->repositoryItemTextEdit2, this->repositoryItemComboBox3, this->repositoryItemComboBox4,
					this->BuildTargetCombo, this->repositoryItemProgressBar1
			});
			this->Toolbars->StatusBar = this->bar3;
			// 
			// bar2
			// 
			this->bar2->BarName = L"Main menu";
			this->bar2->DockCol = 0;
			this->bar2->DockRow = 0;
			this->bar2->DockStyle = DevExpress::XtraBars::BarDockStyle::Top;
			this->bar2->LinksPersistInfo->AddRange(gcnew cli::array< DevExpress::XtraBars::LinkPersistInfo^  >(8) {
				(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barSubItem1)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barSubItem2)), (gcnew DevExpress::XtraBars::LinkPersistInfo(this->barSubItem11)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barSubItem3)), (gcnew DevExpress::XtraBars::LinkPersistInfo(this->barSubItem20)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barSubItem23)), (gcnew DevExpress::XtraBars::LinkPersistInfo(this->barSubItem13)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barSubItem5))
			});
			this->bar2->OptionsBar->MultiLine = true;
			this->bar2->OptionsBar->UseWholeRow = true;
			this->bar2->Text = L"Main menu";
			// 
			// barSubItem1
			// 
			this->barSubItem1->Caption = L"Connect";
			this->barSubItem1->Id = 4;
			this->barSubItem1->LinksPersistInfo->AddRange(gcnew cli::array< DevExpress::XtraBars::LinkPersistInfo^  >(3) {
				(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barSubItem6)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barSubItem8)), (gcnew DevExpress::XtraBars::LinkPersistInfo(this->barSubItem9))
			});
			this->barSubItem1->Name = L"barSubItem1";
			// 
			// barSubItem6
			// 
			this->barSubItem6->Caption = L"PS3";
			this->barSubItem6->Id = 9;
			this->barSubItem6->LinksPersistInfo->AddRange(gcnew cli::array< DevExpress::XtraBars::LinkPersistInfo^  >(2) {
				(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem4)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem5))
			});
			this->barSubItem6->Name = L"barSubItem6";
			// 
			// barButtonItem4
			// 
			this->barButtonItem4->Caption = L"CCAPI";
			this->barButtonItem4->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"barButtonItem4.Glyph")));
			this->barButtonItem4->Id = 10;
			this->barButtonItem4->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Alt)
				| System::Windows::Forms::Keys::D3), System::Windows::Forms::Keys::C));
			this->barButtonItem4->Name = L"barButtonItem4";
			this->barButtonItem4->PaintStyle = DevExpress::XtraBars::BarItemPaintStyle::CaptionGlyph;
			this->barButtonItem4->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem4_ItemClick);
			// 
			// barButtonItem5
			// 
			this->barButtonItem5->Caption = L"TMAPI";
			this->barButtonItem5->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"barButtonItem5.Glyph")));
			this->barButtonItem5->Id = 11;
			this->barButtonItem5->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Alt)
				| System::Windows::Forms::Keys::D3), System::Windows::Forms::Keys::T));
			this->barButtonItem5->Name = L"barButtonItem5";
			this->barButtonItem5->PaintStyle = DevExpress::XtraBars::BarItemPaintStyle::CaptionGlyph;
			this->barButtonItem5->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem5_ItemClick);
			// 
			// barSubItem8
			// 
			this->barSubItem8->Caption = L"XBOX 360";
			this->barSubItem8->Id = 15;
			this->barSubItem8->LinksPersistInfo->AddRange(gcnew cli::array< DevExpress::XtraBars::LinkPersistInfo^  >(1) { (gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem8)) });
			this->barSubItem8->Name = L"barSubItem8";
			// 
			// barButtonItem8
			// 
			this->barButtonItem8->Caption = L"Default Console (JRPC2)";
			this->barButtonItem8->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"barButtonItem8.Glyph")));
			this->barButtonItem8->Id = 16;
			this->barButtonItem8->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Alt)
				| System::Windows::Forms::Keys::X)));
			this->barButtonItem8->Name = L"barButtonItem8";
			this->barButtonItem8->PaintStyle = DevExpress::XtraBars::BarItemPaintStyle::CaptionGlyph;
			this->barButtonItem8->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem8_ItemClick);
			// 
			// barSubItem9
			// 
			this->barSubItem9->Caption = L"PC";
			this->barSubItem9->Id = 17;
			this->barSubItem9->LinksPersistInfo->AddRange(gcnew cli::array< DevExpress::XtraBars::LinkPersistInfo^  >(2) {
				(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem9)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem10))
			});
			this->barSubItem9->Name = L"barSubItem9";
			// 
			// barButtonItem9
			// 
			this->barButtonItem9->Caption = L"Redacted";
			this->barButtonItem9->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"barButtonItem9.Glyph")));
			this->barButtonItem9->Id = 18;
			this->barButtonItem9->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Alt)
				| System::Windows::Forms::Keys::P), System::Windows::Forms::Keys::R));
			this->barButtonItem9->Name = L"barButtonItem9";
			this->barButtonItem9->PaintStyle = DevExpress::XtraBars::BarItemPaintStyle::CaptionGlyph;
			this->barButtonItem9->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem9_ItemClick);
			// 
			// barButtonItem10
			// 
			this->barButtonItem10->Caption = L"Steam";
			this->barButtonItem10->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"barButtonItem10.Glyph")));
			this->barButtonItem10->Id = 19;
			this->barButtonItem10->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Alt)
				| System::Windows::Forms::Keys::P), System::Windows::Forms::Keys::S));
			this->barButtonItem10->Name = L"barButtonItem10";
			this->barButtonItem10->PaintStyle = DevExpress::XtraBars::BarItemPaintStyle::CaptionGlyph;
			this->barButtonItem10->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem10_ItemClick);
			// 
			// barSubItem2
			// 
			this->barSubItem2->Caption = L"Project";
			this->barSubItem2->Id = 5;
			this->barSubItem2->LinksPersistInfo->AddRange(gcnew cli::array< DevExpress::XtraBars::LinkPersistInfo^  >(8) {
				(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem11)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem12)), (gcnew DevExpress::XtraBars::LinkPersistInfo(this->DropDown_NewScript,
						true)), (gcnew DevExpress::XtraBars::LinkPersistInfo(this->DropDown_Save, true)), (gcnew DevExpress::XtraBars::LinkPersistInfo(this->DropDown_SaveAll)),
						(gcnew DevExpress::XtraBars::LinkPersistInfo(this->DropDown_Close, true)), (gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem30,
							true)), (gcnew DevExpress::XtraBars::LinkPersistInfo(this->DropDown_ProjectSub))
			});
			this->barSubItem2->Name = L"barSubItem2";
			// 
			// barButtonItem11
			// 
			this->barButtonItem11->Caption = L"New Project";
			this->barButtonItem11->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"barButtonItem11.Glyph")));
			this->barButtonItem11->Id = 20;
			this->barButtonItem11->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Shift)
				| System::Windows::Forms::Keys::N)));
			this->barButtonItem11->Name = L"barButtonItem11";
			this->barButtonItem11->PaintStyle = DevExpress::XtraBars::BarItemPaintStyle::CaptionGlyph;
			this->barButtonItem11->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem11_ItemClick);
			// 
			// barButtonItem12
			// 
			this->barButtonItem12->Caption = L"Open Project";
			this->barButtonItem12->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"barButtonItem12.Glyph")));
			this->barButtonItem12->Id = 21;
			this->barButtonItem12->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O)));
			this->barButtonItem12->Name = L"barButtonItem12";
			this->barButtonItem12->PaintStyle = DevExpress::XtraBars::BarItemPaintStyle::CaptionGlyph;
			this->barButtonItem12->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem12_ItemClick);
			// 
			// DropDown_NewScript
			// 
			this->DropDown_NewScript->Caption = L"New Script File";
			this->DropDown_NewScript->Enabled = false;
			this->DropDown_NewScript->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"DropDown_NewScript.Glyph")));
			this->DropDown_NewScript->Id = 61;
			this->DropDown_NewScript->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::N)));
			this->DropDown_NewScript->Name = L"DropDown_NewScript";
			this->DropDown_NewScript->PaintStyle = DevExpress::XtraBars::BarItemPaintStyle::CaptionGlyph;
			this->DropDown_NewScript->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem41_ItemClick);
			// 
			// DropDown_Save
			// 
			this->DropDown_Save->Caption = L"Save File";
			this->DropDown_Save->Enabled = false;
			this->DropDown_Save->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"DropDown_Save.Glyph")));
			this->DropDown_Save->Id = 46;
			this->DropDown_Save->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S)));
			this->DropDown_Save->Name = L"DropDown_Save";
			this->DropDown_Save->PaintStyle = DevExpress::XtraBars::BarItemPaintStyle::CaptionGlyph;
			this->DropDown_Save->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem32_ItemClick);
			// 
			// DropDown_SaveAll
			// 
			this->DropDown_SaveAll->Caption = L"Save Project";
			this->DropDown_SaveAll->Enabled = false;
			this->DropDown_SaveAll->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"DropDown_SaveAll.Glyph")));
			this->DropDown_SaveAll->Id = 22;
			this->DropDown_SaveAll->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Shift)
				| System::Windows::Forms::Keys::S)));
			this->DropDown_SaveAll->Name = L"DropDown_SaveAll";
			this->DropDown_SaveAll->PaintStyle = DevExpress::XtraBars::BarItemPaintStyle::CaptionGlyph;
			this->DropDown_SaveAll->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem13_ItemClick);
			// 
			// DropDown_Close
			// 
			this->DropDown_Close->Caption = L"Close Project";
			this->DropDown_Close->Enabled = false;
			this->DropDown_Close->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"DropDown_Close.Glyph")));
			this->DropDown_Close->Id = 50;
			this->DropDown_Close->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Alt)
				| System::Windows::Forms::Keys::C)));
			this->DropDown_Close->Name = L"DropDown_Close";
			this->DropDown_Close->PaintStyle = DevExpress::XtraBars::BarItemPaintStyle::CaptionGlyph;
			this->DropDown_Close->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem34_ItemClick);
			// 
			// barButtonItem30
			// 
			this->barButtonItem30->Caption = L"Import Project";
			this->barButtonItem30->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"barButtonItem30.Glyph")));
			this->barButtonItem30->Id = 43;
			this->barButtonItem30->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Alt)
				| System::Windows::Forms::Keys::I)));
			this->barButtonItem30->Name = L"barButtonItem30";
			this->barButtonItem30->PaintStyle = DevExpress::XtraBars::BarItemPaintStyle::CaptionGlyph;
			this->barButtonItem30->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem30_ItemClick);
			// 
			// DropDown_ProjectSub
			// 
			this->DropDown_ProjectSub->Caption = L"Project Properties";
			this->DropDown_ProjectSub->Id = 69;
			this->DropDown_ProjectSub->LinksPersistInfo->AddRange(gcnew cli::array< DevExpress::XtraBars::LinkPersistInfo^  >(2) {
				(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barSubItem16)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->DropDown_PSettings))
			});
			this->DropDown_ProjectSub->Name = L"DropDown_ProjectSub";
			// 
			// barSubItem16
			// 
			this->barSubItem16->Caption = L"Convert Project";
			this->barSubItem16->Enabled = false;
			this->barSubItem16->Id = 63;
			this->barSubItem16->LinksPersistInfo->AddRange(gcnew cli::array< DevExpress::XtraBars::LinkPersistInfo^  >(2) {
				(gcnew DevExpress::XtraBars::LinkPersistInfo(this->DropDown_ConvertZ)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->DropDown_ConvertM))
			});
			this->barSubItem16->Name = L"barSubItem16";
			// 
			// DropDown_ConvertZ
			// 
			this->DropDown_ConvertZ->Caption = L"Zombies";
			this->DropDown_ConvertZ->Enabled = false;
			this->DropDown_ConvertZ->Id = 64;
			this->DropDown_ConvertZ->Name = L"DropDown_ConvertZ";
			// 
			// DropDown_ConvertM
			// 
			this->DropDown_ConvertM->Caption = L"Multiplayer";
			this->DropDown_ConvertM->Enabled = false;
			this->DropDown_ConvertM->Id = 65;
			this->DropDown_ConvertM->Name = L"DropDown_ConvertM";
			// 
			// DropDown_PSettings
			// 
			this->DropDown_PSettings->Caption = L"Project Settings";
			this->DropDown_PSettings->Enabled = false;
			this->DropDown_PSettings->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"DropDown_PSettings.Glyph")));
			this->DropDown_PSettings->Id = 94;
			this->DropDown_PSettings->Name = L"DropDown_PSettings";
			this->DropDown_PSettings->PaintStyle = DevExpress::XtraBars::BarItemPaintStyle::CaptionGlyph;
			this->DropDown_PSettings->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::DropDown_PSettings_ItemClick);
			// 
			// barSubItem11
			// 
			this->barSubItem11->Caption = L"Inject";
			this->barSubItem11->Id = 30;
			this->barSubItem11->LinksPersistInfo->AddRange(gcnew cli::array< DevExpress::XtraBars::LinkPersistInfo^  >(3) {
				(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem20)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem21)), (gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem27))
			});
			this->barSubItem11->Name = L"barSubItem11";
			// 
			// barButtonItem20
			// 
			this->barButtonItem20->Caption = L"Inject Package";
			this->barButtonItem20->Enabled = false;
			this->barButtonItem20->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"barButtonItem20.Glyph")));
			this->barButtonItem20->Id = 31;
			this->barButtonItem20->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut(System::Windows::Forms::Keys::F3));
			this->barButtonItem20->Name = L"barButtonItem20";
			this->barButtonItem20->PaintStyle = DevExpress::XtraBars::BarItemPaintStyle::CaptionGlyph;
			this->barButtonItem20->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::InjectPackage);
			// 
			// barButtonItem21
			// 
			this->barButtonItem21->Caption = L"Inject GSC";
			this->barButtonItem21->Enabled = false;
			this->barButtonItem21->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"barButtonItem21.Glyph")));
			this->barButtonItem21->Id = 32;
			this->barButtonItem21->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut(System::Windows::Forms::Keys::F2));
			this->barButtonItem21->Name = L"barButtonItem21";
			this->barButtonItem21->PaintStyle = DevExpress::XtraBars::BarItemPaintStyle::CaptionGlyph;
			this->barButtonItem21->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::InjectGSX);
			// 
			// barButtonItem27
			// 
			this->barButtonItem27->Caption = L"Inject Current Project";
			this->barButtonItem27->Enabled = false;
			this->barButtonItem27->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"barButtonItem27.Glyph")));
			this->barButtonItem27->Id = 39;
			this->barButtonItem27->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut(System::Windows::Forms::Keys::F1));
			this->barButtonItem27->Name = L"barButtonItem27";
			this->barButtonItem27->PaintStyle = DevExpress::XtraBars::BarItemPaintStyle::CaptionGlyph;
			this->barButtonItem27->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::InjectCurrentProject);
			// 
			// barSubItem3
			// 
			this->barSubItem3->Caption = L"Build";
			this->barSubItem3->Id = 6;
			this->barSubItem3->LinksPersistInfo->AddRange(gcnew cli::array< DevExpress::XtraBars::LinkPersistInfo^  >(4) {
				(gcnew DevExpress::XtraBars::LinkPersistInfo(this->DropDown_BuildC)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->DropDown_BuildPC)), (gcnew DevExpress::XtraBars::LinkPersistInfo(this->DropDown_BuildPK)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barSubItem17, true))
			});
			this->barSubItem3->Name = L"barSubItem3";
			// 
			// DropDown_BuildC
			// 
			this->DropDown_BuildC->Caption = L"Build Console";
			this->DropDown_BuildC->Enabled = false;
			this->DropDown_BuildC->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"DropDown_BuildC.Glyph")));
			this->DropDown_BuildC->Id = 27;
			this->DropDown_BuildC->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut(System::Windows::Forms::Keys::F6));
			this->DropDown_BuildC->Name = L"DropDown_BuildC";
			this->DropDown_BuildC->PaintStyle = DevExpress::XtraBars::BarItemPaintStyle::CaptionGlyph;
			this->DropDown_BuildC->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::DropDown_BuildC_ItemClick);
			// 
			// DropDown_BuildPC
			// 
			this->DropDown_BuildPC->Caption = L"Build PC";
			this->DropDown_BuildPC->Enabled = false;
			this->DropDown_BuildPC->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"DropDown_BuildPC.Glyph")));
			this->DropDown_BuildPC->Id = 28;
			this->DropDown_BuildPC->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut(System::Windows::Forms::Keys::F7));
			this->DropDown_BuildPC->Name = L"DropDown_BuildPC";
			this->DropDown_BuildPC->PaintStyle = DevExpress::XtraBars::BarItemPaintStyle::CaptionGlyph;
			this->DropDown_BuildPC->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::DropDown_BuildPC_ItemClick);
			// 
			// DropDown_BuildPK
			// 
			this->DropDown_BuildPK->Caption = L"Build Package";
			this->DropDown_BuildPK->Enabled = false;
			this->DropDown_BuildPK->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"DropDown_BuildPK.Glyph")));
			this->DropDown_BuildPK->Id = 29;
			this->DropDown_BuildPK->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut(System::Windows::Forms::Keys::F8));
			this->DropDown_BuildPK->Name = L"DropDown_BuildPK";
			this->DropDown_BuildPK->PaintStyle = DevExpress::XtraBars::BarItemPaintStyle::CaptionGlyph;
			this->DropDown_BuildPK->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem19_ItemClick);
			// 
			// barSubItem17
			// 
			this->barSubItem17->Caption = L"Build Settings";
			this->barSubItem17->Id = 100;
			this->barSubItem17->LinksPersistInfo->AddRange(gcnew cli::array< DevExpress::XtraBars::LinkPersistInfo^  >(3) {
				(gcnew DevExpress::XtraBars::LinkPersistInfo(this->Build_Scripts)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->Build_Children)), (gcnew DevExpress::XtraBars::LinkPersistInfo(this->Build_Symbolize))
			});
			this->barSubItem17->Name = L"barSubItem17";
			// 
			// Build_Scripts
			// 
			this->Build_Scripts->BindableChecked = true;
			this->Build_Scripts->Caption = L"Optimize Scripts";
			this->Build_Scripts->Checked = true;
			this->Build_Scripts->Id = 101;
			this->Build_Scripts->Name = L"Build_Scripts";
			this->Build_Scripts->CheckedChanged += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barCheckItem4_CheckedChanged);
			// 
			// Build_Children
			// 
			this->Build_Children->Caption = L"Optimize Children";
			this->Build_Children->Id = 104;
			this->Build_Children->Name = L"Build_Children";
			this->Build_Children->CheckedChanged += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barCheckItem5_CheckedChanged);
			// 
			// Build_Symbolize
			// 
			this->Build_Symbolize->BindableChecked = true;
			this->Build_Symbolize->Caption = L"Symbolize Variables";
			this->Build_Symbolize->Checked = true;
			this->Build_Symbolize->Id = 105;
			this->Build_Symbolize->Name = L"Build_Symbolize";
			this->Build_Symbolize->CheckedChanged += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barCheckItem6_CheckedChanged);
			// 
			// barSubItem20
			// 
			this->barSubItem20->Caption = L"Libraries";
			this->barSubItem20->Id = 113;
			this->barSubItem20->Enabled = false;
			this->barSubItem20->LinksPersistInfo->AddRange(gcnew cli::array< DevExpress::XtraBars::LinkPersistInfo^  >(4) {
				(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem56)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem64, true)), (gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem63)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem65, true))
			});
			this->barSubItem20->Name = L"barSubItem20";
			// 
			// barButtonItem56
			// 
			this->barButtonItem56->Caption = L"Export Project";
			this->barButtonItem56->Id = 118;
			this->barButtonItem56->Name = L"barButtonItem56";
			// 
			// barButtonItem64
			// 
			this->barButtonItem64->Caption = L"Share Project";
			this->barButtonItem64->Id = 125;
			this->barButtonItem64->Name = L"barButtonItem64";
			// 
			// barButtonItem63
			// 
			this->barButtonItem63->Caption = L"Get New Libraries";
			this->barButtonItem63->Id = 124;
			this->barButtonItem63->Name = L"barButtonItem63";
			// 
			// barButtonItem65
			// 
			this->barButtonItem65->Caption = L"Library Manager";
			this->barButtonItem65->Id = 126;
			this->barButtonItem65->Name = L"barButtonItem65";
			// 
			// barSubItem23
			// 
			this->barSubItem23->Caption = L"Fast Files";
			this->barSubItem23->Enabled = false;
			this->barSubItem23->Id = 127;
			this->barSubItem23->Name = L"barSubItem23";
			// 
			// barSubItem13
			// 
			this->barSubItem13->Caption = L"Tools";
			this->barSubItem13->Id = 47;
			this->barSubItem13->LinksPersistInfo->AddRange(gcnew cli::array< DevExpress::XtraBars::LinkPersistInfo^  >(4) {
				(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem50)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem22, true)), (gcnew DevExpress::XtraBars::LinkPersistInfo(this->Tools_ProjectRepair,
						true)), (gcnew DevExpress::XtraBars::LinkPersistInfo(this->barSubItem24, true))
			});
			this->barSubItem13->Name = L"barSubItem13";
			// 
			// barButtonItem50
			// 
			this->barButtonItem50->Caption = L"RGB Color Picker";
			this->barButtonItem50->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"barButtonItem50.Glyph")));
			this->barButtonItem50->Id = 73;
			this->barButtonItem50->Name = L"barButtonItem50";
			this->barButtonItem50->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem50_ItemClick);
			// 
			// barButtonItem22
			// 
			this->barButtonItem22->Caption = L"Edit Preferences";
			this->barButtonItem22->Enabled = false;
			this->barButtonItem22->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"barButtonItem22.Glyph")));
			this->barButtonItem22->Id = 33;
			this->barButtonItem22->Name = L"barButtonItem22";
			this->barButtonItem22->PaintStyle = DevExpress::XtraBars::BarItemPaintStyle::CaptionGlyph;
			// 
			// Tools_ProjectRepair
			// 
			this->Tools_ProjectRepair->Caption = L"Project Repair";
			this->Tools_ProjectRepair->Enabled = false;
			this->Tools_ProjectRepair->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Tools_ProjectRepair.Glyph")));
			this->Tools_ProjectRepair->Id = 97;
			this->Tools_ProjectRepair->Name = L"Tools_ProjectRepair";
			this->Tools_ProjectRepair->PaintStyle = DevExpress::XtraBars::BarItemPaintStyle::CaptionGlyph;
			this->Tools_ProjectRepair->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem13_ItemClick_1);
			// 
			// barSubItem24
			// 
			this->barSubItem24->Caption = L"Platform Tools";
			this->barSubItem24->Enabled = false;
			this->barSubItem24->Id = 129;
			this->barSubItem24->LinksPersistInfo->AddRange(gcnew cli::array< DevExpress::XtraBars::LinkPersistInfo^  >(1) { (gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem67)) });
			this->barSubItem24->Name = L"barSubItem24";
			// 
			// barButtonItem67
			// 
			this->barButtonItem67->Caption = L"Memory Editing";
			this->barButtonItem67->Id = 130;
			this->barButtonItem67->Enabled = false;
			this->barButtonItem67->Name = L"barButtonItem67";
			this->barButtonItem67->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem67_ItemClick);
			// 
			// barSubItem5
			// 
			this->barSubItem5->Caption = L"About";
			this->barSubItem5->Id = 8;
			this->barSubItem5->LinksPersistInfo->AddRange(gcnew cli::array< DevExpress::XtraBars::LinkPersistInfo^  >(4) {
				(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem25)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem24, true)), (gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem23)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem26, true))
			});
			this->barSubItem5->Name = L"barSubItem5";
			// 
			// barButtonItem25
			// 
			this->barButtonItem25->Caption = L"Donate";
			this->barButtonItem25->Enabled = false;
			this->barButtonItem25->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"barButtonItem25.Glyph")));
			this->barButtonItem25->Id = 37;
			this->barButtonItem25->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut(System::Windows::Forms::Keys::F9));
			this->barButtonItem25->Name = L"barButtonItem25";
			this->barButtonItem25->PaintStyle = DevExpress::XtraBars::BarItemPaintStyle::CaptionGlyph;
			// 
			// barButtonItem24
			// 
			this->barButtonItem24->Caption = L"Update GSX Studio";
			this->barButtonItem24->Enabled = false;
			this->barButtonItem24->Id = 36;
			this->barButtonItem24->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut(System::Windows::Forms::Keys::F11));
			this->barButtonItem24->Name = L"barButtonItem24";
			// 
			// barButtonItem23
			// 
			this->barButtonItem23->Caption = L"About GSX Studio";
			this->barButtonItem23->Enabled = false;
			this->barButtonItem23->Id = 35;
			this->barButtonItem23->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut(System::Windows::Forms::Keys::F10));
			this->barButtonItem23->Name = L"barButtonItem23";
			// 
			// barButtonItem26
			// 
			this->barButtonItem26->Caption = L"Report a Bug";
			this->barButtonItem26->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"barButtonItem26.Glyph")));
			this->barButtonItem26->Id = 38;
			this->barButtonItem26->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut(System::Windows::Forms::Keys::F12));
			this->barButtonItem26->Name = L"barButtonItem26";
			this->barButtonItem26->PaintStyle = DevExpress::XtraBars::BarItemPaintStyle::CaptionGlyph;
			this->barButtonItem26->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::ReportClicked);
			// 
			// bar3
			// 
			this->bar3->BarName = L"Status bar";
			this->bar3->CanDockStyle = DevExpress::XtraBars::BarCanDockStyle::Bottom;
			this->bar3->DockCol = 0;
			this->bar3->DockRow = 0;
			this->bar3->DockStyle = DevExpress::XtraBars::BarDockStyle::Bottom;
			this->bar3->LinksPersistInfo->AddRange(gcnew cli::array< DevExpress::XtraBars::LinkPersistInfo^  >(1) {
				(gcnew DevExpress::XtraBars::LinkPersistInfo(this->StatusLabel,
					true))
			});
			this->bar3->OptionsBar->AllowQuickCustomization = false;
			this->bar3->OptionsBar->DrawDragBorder = false;
			this->bar3->OptionsBar->UseWholeRow = true;
			this->bar3->Text = L"Status bar";
			// 
			// StatusLabel
			// 
			this->StatusLabel->Caption = L"Ready";
			this->StatusLabel->Id = 0;
			this->StatusLabel->Name = L"StatusLabel";
			this->StatusLabel->TextAlignment = System::Drawing::StringAlignment::Near;
			// 
			// bar1
			// 
			this->bar1->BarName = L"Custom 4";
			this->bar1->DockCol = 0;
			this->bar1->DockRow = 1;
			this->bar1->DockStyle = DevExpress::XtraBars::BarDockStyle::Top;
			this->bar1->FloatLocation = System::Drawing::Point(80, 157);
			this->bar1->LinksPersistInfo->AddRange(gcnew cli::array< DevExpress::XtraBars::LinkPersistInfo^  >(8) {
				(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem58,
					true)), (gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem59)), (gcnew DevExpress::XtraBars::LinkPersistInfo(this->Toolbar_Save)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->Toolbar_SaveAll)), (gcnew DevExpress::XtraBars::LinkPersistInfo(this->BuildMode,
						true)), (gcnew DevExpress::XtraBars::LinkPersistInfo(this->BuildTarget)), (gcnew DevExpress::XtraBars::LinkPersistInfo(this->ToolbarBuildProject)),
						(gcnew DevExpress::XtraBars::LinkPersistInfo(this->ToolbarPSettings, true))
			});
			this->bar1->Text = L"Custom 4";
			// 
			// barButtonItem58
			// 
			this->barButtonItem58->Caption = L"New Project";
			this->barButtonItem58->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"barButtonItem58.Glyph")));
			this->barButtonItem58->Id = 90;
			this->barButtonItem58->Name = L"barButtonItem58";
			this->barButtonItem58->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem58_ItemClick);
			// 
			// barButtonItem59
			// 
			this->barButtonItem59->Caption = L"Open Project";
			this->barButtonItem59->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"barButtonItem59.Glyph")));
			this->barButtonItem59->Id = 91;
			this->barButtonItem59->Name = L"barButtonItem59";
			this->barButtonItem59->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem59_ItemClick);
			// 
			// Toolbar_Save
			// 
			this->Toolbar_Save->Caption = L"Save File";
			this->Toolbar_Save->Enabled = false;
			this->Toolbar_Save->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Toolbar_Save.Glyph")));
			this->Toolbar_Save->Id = 88;
			this->Toolbar_Save->Name = L"Toolbar_Save";
			this->Toolbar_Save->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::Toolbar_Save_ItemClick);
			// 
			// Toolbar_SaveAll
			// 
			this->Toolbar_SaveAll->Caption = L"Save All";
			this->Toolbar_SaveAll->Enabled = false;
			this->Toolbar_SaveAll->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Toolbar_SaveAll.Glyph")));
			this->Toolbar_SaveAll->Id = 89;
			this->Toolbar_SaveAll->Name = L"Toolbar_SaveAll";
			this->Toolbar_SaveAll->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::Toolbar_SaveAll_ItemClick);
			// 
			// BuildMode
			// 
			this->BuildMode->Caption = L"Build Mode";
			this->BuildMode->Edit = this->BuildModeCombo;
			this->BuildMode->Enabled = false;
			this->BuildMode->Id = 77;
			this->BuildMode->Name = L"BuildMode";
			this->BuildMode->Width = 74;
			// 
			// BuildModeCombo
			// 
			this->BuildModeCombo->AutoComplete = false;
			this->BuildModeCombo->AutoHeight = false;
			this->BuildModeCombo->Buttons->AddRange(gcnew cli::array< DevExpress::XtraEditors::Controls::EditorButton^  >(1) { (gcnew DevExpress::XtraEditors::Controls::EditorButton(DevExpress::XtraEditors::Controls::ButtonPredefines::Combo)) });
			this->BuildModeCombo->CloseUpKey = (gcnew DevExpress::Utils::KeyShortcut(System::Windows::Forms::Keys::None));
			this->BuildModeCombo->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Debug", L"Release" });
			this->BuildModeCombo->Name = L"BuildModeCombo";
			this->BuildModeCombo->TextEditStyle = DevExpress::XtraEditors::Controls::TextEditStyles::DisableTextEditor;
			// 
			// BuildTarget
			// 
			this->BuildTarget->Caption = L"Platform";
			this->BuildTarget->Edit = this->BuildTargetCombo;
			this->BuildTarget->Enabled = false;
			this->BuildTarget->Id = 93;
			this->BuildTarget->Name = L"BuildTarget";
			this->BuildTarget->Width = 101;
			// 
			// BuildTargetCombo
			// 
			this->BuildTargetCombo->AutoHeight = false;
			this->BuildTargetCombo->Buttons->AddRange(gcnew cli::array< DevExpress::XtraEditors::Controls::EditorButton^  >(1) { (gcnew DevExpress::XtraEditors::Controls::EditorButton(DevExpress::XtraEditors::Controls::ButtonPredefines::Combo)) });
			this->BuildTargetCombo->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Console", L"PC", L"Package" });
			this->BuildTargetCombo->Name = L"BuildTargetCombo";
			this->BuildTargetCombo->TextEditStyle = DevExpress::XtraEditors::Controls::TextEditStyles::DisableTextEditor;
			// 
			// ToolbarBuildProject
			// 
			this->ToolbarBuildProject->Caption = L"Build Project";
			this->ToolbarBuildProject->Enabled = false;
			this->ToolbarBuildProject->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ToolbarBuildProject.Glyph")));
			this->ToolbarBuildProject->Id = 86;
			this->ToolbarBuildProject->Name = L"ToolbarBuildProject";
			this->ToolbarBuildProject->PaintStyle = DevExpress::XtraBars::BarItemPaintStyle::CaptionGlyph;
			this->ToolbarBuildProject->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::ToolbarBuildProject_ItemClick);
			// 
			// ToolbarPSettings
			// 
			this->ToolbarPSettings->Caption = L"Project Settings";
			this->ToolbarPSettings->Enabled = false;
			this->ToolbarPSettings->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ToolbarPSettings.Glyph")));
			this->ToolbarPSettings->Id = 95;
			this->ToolbarPSettings->Name = L"ToolbarPSettings";
			this->ToolbarPSettings->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::ToolbarPSettings_ItemClick);
			// 
			// barDockControlTop
			// 
			this->barDockControlTop->CausesValidation = false;
			this->barDockControlTop->Dock = System::Windows::Forms::DockStyle::Top;
			this->barDockControlTop->Location = System::Drawing::Point(0, 0);
			this->barDockControlTop->Size = System::Drawing::Size(984, 52);
			// 
			// barDockControlBottom
			// 
			this->barDockControlBottom->CausesValidation = false;
			this->barDockControlBottom->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->barDockControlBottom->Location = System::Drawing::Point(0, 555);
			this->barDockControlBottom->Size = System::Drawing::Size(984, 26);
			// 
			// barDockControlLeft
			// 
			this->barDockControlLeft->CausesValidation = false;
			this->barDockControlLeft->Dock = System::Windows::Forms::DockStyle::Left;
			this->barDockControlLeft->Location = System::Drawing::Point(0, 52);
			this->barDockControlLeft->Size = System::Drawing::Size(0, 503);
			// 
			// barDockControlRight
			// 
			this->barDockControlRight->CausesValidation = false;
			this->barDockControlRight->Dock = System::Windows::Forms::DockStyle::Right;
			this->barDockControlRight->Location = System::Drawing::Point(984, 52);
			this->barDockControlRight->Size = System::Drawing::Size(0, 503);
			// 
			// dockManager1
			// 
			this->dockManager1->Form = this;
			this->dockManager1->MenuManager = this->Toolbars;
			this->dockManager1->RootPanels->AddRange(gcnew cli::array< DevExpress::XtraBars::Docking::DockPanel^  >(3) {
				this->panelContainer1,
					this->ProjectPanel, this->dockPanel2
			});
			this->dockManager1->TopZIndexControls->AddRange(gcnew cli::array< System::String^  >(9) {
				L"DevExpress.XtraBars.BarDockControl",
					L"DevExpress.XtraBars.StandaloneBarDockControl", L"System.Windows.Forms.StatusBar", L"System.Windows.Forms.MenuStrip", L"System.Windows.Forms.StatusStrip",
					L"DevExpress.XtraBars.Ribbon.RibbonStatusBar", L"DevExpress.XtraBars.Ribbon.RibbonControl", L"DevExpress.XtraBars.Navigation.OfficeNavigationBar",
					L"DevExpress.XtraBars.Navigation.TileNavPane"
			});
			// 
			// panelContainer1
			// 
			this->panelContainer1->Controls->Add(this->ErrorPanel);
			this->panelContainer1->Controls->Add(this->OutputPanel);
			this->panelContainer1->Dock = DevExpress::XtraBars::Docking::DockingStyle::Bottom;
			this->panelContainer1->FloatVertical = true;
			this->panelContainer1->ID = System::Guid(L"89e852f3-c187-4fa6-bd62-ebed63e042f1");
			this->panelContainer1->Location = System::Drawing::Point(0, 381);
			this->panelContainer1->Name = L"panelContainer1";
			this->panelContainer1->OriginalSize = System::Drawing::Size(200, 174);
			this->panelContainer1->Size = System::Drawing::Size(984, 174);
			this->panelContainer1->Text = L"panelContainer1";
			// 
			// ErrorPanel
			// 
			this->ErrorPanel->Controls->Add(this->dockPanel3_Container);
			this->ErrorPanel->Dock = DevExpress::XtraBars::Docking::DockingStyle::Fill;
			this->ErrorPanel->FloatVertical = true;
			this->ErrorPanel->ID = System::Guid(L"b8e78239-e295-4136-b505-67fcc7a8f67d");
			this->ErrorPanel->Location = System::Drawing::Point(0, 0);
			this->ErrorPanel->Name = L"ErrorPanel";
			this->ErrorPanel->Options->ShowCloseButton = false;
			this->ErrorPanel->OriginalSize = System::Drawing::Size(200, 200);
			this->ErrorPanel->Size = System::Drawing::Size(492, 174);
			this->ErrorPanel->Text = L"Error List";
			// 
			// dockPanel3_Container
			// 
			this->dockPanel3_Container->Controls->Add(this->ErrorConsole);
			this->dockPanel3_Container->Location = System::Drawing::Point(3, 25);
			this->dockPanel3_Container->Name = L"dockPanel3_Container";
			this->dockPanel3_Container->Size = System::Drawing::Size(486, 146);
			this->dockPanel3_Container->TabIndex = 0;
			// 
			// ErrorConsole
			// 
			this->ErrorConsole->BorderStyle = DevExpress::XtraEditors::Controls::BorderStyles::NoBorder;
			this->ErrorConsole->Columns->AddRange(gcnew cli::array< DevExpress::XtraTreeList::Columns::TreeListColumn^  >(5) {
				this->treeListColumn5,
					this->treeListColumn2, this->treeListColumn3, this->treeListColumn6, this->treeListColumn4
			});
			this->ErrorConsole->Dock = System::Windows::Forms::DockStyle::Fill;
			this->ErrorConsole->Location = System::Drawing::Point(0, 0);
			this->ErrorConsole->LookAndFeel->SkinName = L"Visual Studio 2013 Dark";
			this->ErrorConsole->LookAndFeel->UseDefaultLookAndFeel = false;
			this->ErrorConsole->Name = L"ErrorConsole";
			this->ErrorConsole->OptionsBehavior->AllowExpandOnDblClick = false;
			this->ErrorConsole->OptionsBehavior->AutoChangeParent = false;
			this->ErrorConsole->OptionsBehavior->AutoSelectAllInEditor = false;
			this->ErrorConsole->OptionsBehavior->CopyToClipboardWithColumnHeaders = false;
			this->ErrorConsole->OptionsBehavior->CopyToClipboardWithNodeHierarchy = false;
			this->ErrorConsole->OptionsBehavior->Editable = false;
			this->ErrorConsole->OptionsBehavior->ImmediateEditor = false;
			this->ErrorConsole->OptionsBehavior->KeepSelectedOnClick = false;
			this->ErrorConsole->OptionsBehavior->PopulateServiceColumns = true;
			this->ErrorConsole->OptionsCustomization->AllowBandMoving = false;
			this->ErrorConsole->OptionsCustomization->AllowColumnMoving = false;
			this->ErrorConsole->OptionsCustomization->AllowQuickHideColumns = false;
			this->ErrorConsole->OptionsCustomization->ShowBandsInCustomizationForm = false;
			this->ErrorConsole->OptionsFilter->AllowColumnMRUFilterList = false;
			this->ErrorConsole->OptionsFilter->AllowFilterEditor = false;
			this->ErrorConsole->OptionsFilter->AllowMRUFilterList = false;
			this->ErrorConsole->OptionsLayout->AddNewColumns = false;
			this->ErrorConsole->OptionsMenu->EnableColumnMenu = false;
			this->ErrorConsole->OptionsMenu->EnableFooterMenu = false;
			this->ErrorConsole->OptionsMenu->ShowAutoFilterRowItem = false;
			this->ErrorConsole->OptionsSelection->EnableAppearanceFocusedCell = false;
			this->ErrorConsole->OptionsSelection->SelectNodesOnRightClick = true;
			this->ErrorConsole->OptionsView->ShowRoot = false;
			this->ErrorConsole->RepositoryItems->AddRange(gcnew cli::array< DevExpress::XtraEditors::Repository::RepositoryItem^  >(1) { this->repositoryItemPictureEdit1 });
			this->ErrorConsole->Size = System::Drawing::Size(486, 146);
			this->ErrorConsole->TabIndex = 0;
			this->ErrorConsole->FocusedNodeChanged += gcnew DevExpress::XtraTreeList::FocusedNodeChangedEventHandler(this, &MyForm::ErrorConsole_FocusedNodeChanged);
			// 
			// treeListColumn5
			// 
			this->treeListColumn5->ColumnEdit = this->repositoryItemPictureEdit1;
			this->treeListColumn5->Name = L"treeListColumn5";
			this->treeListColumn5->OptionsColumn->AllowEdit = false;
			this->treeListColumn5->Visible = true;
			this->treeListColumn5->VisibleIndex = 0;
			this->treeListColumn5->Width = 20;
			// 
			// repositoryItemPictureEdit1
			// 
			this->repositoryItemPictureEdit1->Name = L"repositoryItemPictureEdit1";
			// 
			// treeListColumn2
			// 
			this->treeListColumn2->Caption = L"Code";
			this->treeListColumn2->FieldName = L"Code";
			this->treeListColumn2->Name = L"treeListColumn2";
			this->treeListColumn2->Visible = true;
			this->treeListColumn2->VisibleIndex = 1;
			this->treeListColumn2->Width = 24;
			// 
			// treeListColumn3
			// 
			this->treeListColumn3->Caption = L"Description";
			this->treeListColumn3->FieldName = L"Description";
			this->treeListColumn3->Name = L"treeListColumn3";
			this->treeListColumn3->Visible = true;
			this->treeListColumn3->VisibleIndex = 2;
			this->treeListColumn3->Width = 281;
			// 
			// treeListColumn6
			// 
			this->treeListColumn6->Caption = L"File";
			this->treeListColumn6->FieldName = L"File";
			this->treeListColumn6->Name = L"treeListColumn6";
			this->treeListColumn6->Visible = true;
			this->treeListColumn6->VisibleIndex = 3;
			this->treeListColumn6->Width = 89;
			// 
			// treeListColumn4
			// 
			this->treeListColumn4->Caption = L"Line";
			this->treeListColumn4->FieldName = L"Line";
			this->treeListColumn4->Name = L"treeListColumn4";
			this->treeListColumn4->Visible = true;
			this->treeListColumn4->VisibleIndex = 4;
			this->treeListColumn4->Width = 53;
			// 
			// OutputPanel
			// 
			this->OutputPanel->Controls->Add(this->dockPanel4_Container);
			this->OutputPanel->Dock = DevExpress::XtraBars::Docking::DockingStyle::Fill;
			this->OutputPanel->ID = System::Guid(L"21f65035-ef2e-4a7f-9c5b-bc8aaadc1c66");
			this->OutputPanel->Location = System::Drawing::Point(492, 0);
			this->OutputPanel->Name = L"OutputPanel";
			this->OutputPanel->Options->ShowCloseButton = false;
			this->OutputPanel->OriginalSize = System::Drawing::Size(978, 121);
			this->OutputPanel->Size = System::Drawing::Size(492, 174);
			this->OutputPanel->Text = L"Output";
			this->OutputPanel->Click += gcnew System::EventHandler(this, &MyForm::dockPanel4_Click);
			// 
			// dockPanel4_Container
			// 
			this->dockPanel4_Container->Controls->Add(this->Output);
			this->dockPanel4_Container->Location = System::Drawing::Point(3, 25);
			this->dockPanel4_Container->Name = L"dockPanel4_Container";
			this->dockPanel4_Container->Size = System::Drawing::Size(486, 146);
			this->dockPanel4_Container->TabIndex = 0;
			// 
			// Output
			// 
			this->Output->ActiveViewType = DevExpress::XtraRichEdit::RichEditViewType::Simple;
			this->Output->Appearance->Text->Font = (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Output->Appearance->Text->Options->UseFont = true;
			this->Output->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Output->EnableToolTips = true;
			this->Output->Location = System::Drawing::Point(0, 0);
			this->Output->LookAndFeel->SkinName = L"Visual Studio 2013 Dark";
			this->Output->LookAndFeel->UseDefaultLookAndFeel = false;
			this->Output->MenuManager = this->Toolbars;
			this->Output->Name = L"Output";
			this->Output->Options->Behavior->ShowPopupMenu = DevExpress::XtraRichEdit::DocumentCapability::Disabled;
			this->Output->Options->Bookmarks->AllowNameResolution = false;
			this->Output->Options->DocumentCapabilities->Bookmarks = DevExpress::XtraRichEdit::DocumentCapability::Disabled;
			this->Output->Options->DocumentCapabilities->CharacterFormatting = DevExpress::XtraRichEdit::DocumentCapability::Enabled;
			this->Output->Options->DocumentCapabilities->EndNotes = DevExpress::XtraRichEdit::DocumentCapability::Disabled;
			this->Output->Options->DocumentCapabilities->FloatingObjects = DevExpress::XtraRichEdit::DocumentCapability::Disabled;
			this->Output->ReadOnly = true;
			this->Output->Size = System::Drawing::Size(486, 146);
			this->Output->TabIndex = 7;
			this->Output->Views->SimpleView->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(37)),
				static_cast<System::Int32>(static_cast<System::Byte>(37)), static_cast<System::Int32>(static_cast<System::Byte>(38)));
			this->Output->Click += gcnew System::EventHandler(this, &MyForm::Output_Click);
			// 
			// ProjectPanel
			// 
			this->ProjectPanel->Controls->Add(this->dockPanel1_Container);
			this->ProjectPanel->Dock = DevExpress::XtraBars::Docking::DockingStyle::Left;
			this->ProjectPanel->ID = System::Guid(L"8756d4fd-d028-4641-853f-c06b6762460e");
			this->ProjectPanel->Location = System::Drawing::Point(0, 52);
			this->ProjectPanel->Name = L"ProjectPanel";
			this->ProjectPanel->Options->ShowCloseButton = false;
			this->ProjectPanel->OriginalSize = System::Drawing::Size(200, 200);
			this->ProjectPanel->Size = System::Drawing::Size(200, 329);
			this->ProjectPanel->Text = L"Project Explorer";
			// 
			// dockPanel1_Container
			// 
			this->dockPanel1_Container->Controls->Add(this->ProjectExplorer);
			this->dockPanel1_Container->Location = System::Drawing::Point(3, 25);
			this->dockPanel1_Container->Name = L"dockPanel1_Container";
			this->dockPanel1_Container->Size = System::Drawing::Size(194, 301);
			this->dockPanel1_Container->TabIndex = 0;
			// 
			// ProjectExplorer
			// 
			this->ProjectExplorer->Appearance->FocusedCell->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(5)),
				static_cast<System::Int32>(static_cast<System::Byte>(117)), static_cast<System::Int32>(static_cast<System::Byte>(196)));
			this->ProjectExplorer->Appearance->FocusedCell->Options->UseBackColor = true;
			this->ProjectExplorer->Appearance->FocusedRow->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(5)),
				static_cast<System::Int32>(static_cast<System::Byte>(117)), static_cast<System::Int32>(static_cast<System::Byte>(196)));
			this->ProjectExplorer->Appearance->FocusedRow->Options->UseBackColor = true;
			this->ProjectExplorer->Appearance->HideSelectionRow->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(5)),
				static_cast<System::Int32>(static_cast<System::Byte>(117)), static_cast<System::Int32>(static_cast<System::Byte>(196)));
			this->ProjectExplorer->Appearance->HideSelectionRow->Options->UseBackColor = true;
			this->ProjectExplorer->Appearance->SelectedRow->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(5)),
				static_cast<System::Int32>(static_cast<System::Byte>(117)), static_cast<System::Int32>(static_cast<System::Byte>(196)));
			this->ProjectExplorer->Appearance->SelectedRow->Options->UseBackColor = true;
			this->ProjectExplorer->Columns->AddRange(gcnew cli::array< DevExpress::XtraTreeList::Columns::TreeListColumn^  >(1) { this->treeListColumn1 });
			this->ProjectExplorer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->ProjectExplorer->Location = System::Drawing::Point(0, 0);
			this->ProjectExplorer->LookAndFeel->SkinName = L"Visual Studio 2013 Dark";
			this->ProjectExplorer->LookAndFeel->UseDefaultLookAndFeel = false;
			this->ProjectExplorer->Name = L"ProjectExplorer";
			this->ProjectExplorer->BeginUnboundLoad();
			this->ProjectExplorer->AppendNode(gcnew cli::array< System::Object^  >(1) { L"README" }, -1);
			this->ProjectExplorer->EndUnboundLoad();
			this->ProjectExplorer->OptionsBehavior->AutoChangeParent = false;
			this->ProjectExplorer->OptionsBehavior->Editable = false;
			this->ProjectExplorer->OptionsCustomization->AllowBandMoving = false;
			this->ProjectExplorer->OptionsCustomization->AllowColumnMoving = false;
			this->ProjectExplorer->OptionsCustomization->AllowQuickHideColumns = false;
			this->ProjectExplorer->OptionsFilter->AllowFilterEditor = false;
			this->ProjectExplorer->OptionsLayout->AddNewColumns = false;
			this->ProjectExplorer->OptionsMenu->EnableColumnMenu = false;
			this->ProjectExplorer->OptionsMenu->EnableFooterMenu = false;
			this->ProjectExplorer->OptionsMenu->ShowAutoFilterRowItem = false;
			this->ProjectExplorer->OptionsSelection->SelectNodesOnRightClick = true;
			this->ProjectExplorer->Size = System::Drawing::Size(194, 301);
			this->ProjectExplorer->TabIndex = 0;
			this->ProjectExplorer->FocusedNodeChanged += gcnew DevExpress::XtraTreeList::FocusedNodeChangedEventHandler(this, &MyForm::treeList1_FocusedNodeChanged);
			// 
			// treeListColumn1
			// 
			this->treeListColumn1->Caption = L"GSC Scripts";
			this->treeListColumn1->FieldName = L"GSC_Name";
			this->treeListColumn1->MinWidth = 88;
			this->treeListColumn1->Name = L"treeListColumn1";
			this->treeListColumn1->Visible = true;
			this->treeListColumn1->VisibleIndex = 0;
			this->treeListColumn1->Width = 88;
			// 
			// dockPanel2
			// 
			this->dockPanel2->Controls->Add(this->dockPanel2_Container);
			this->dockPanel2->Dock = DevExpress::XtraBars::Docking::DockingStyle::Float;
			this->dockPanel2->DockedAsTabbedDocument = true;
			this->dockPanel2->FloatLocation = System::Drawing::Point(612, 346);
			this->dockPanel2->ID = System::Guid(L"5fc036f9-3aec-44c8-94e1-61544f73c388");
			this->dockPanel2->Location = System::Drawing::Point(0, 0);
			this->dockPanel2->Name = L"dockPanel2";
			this->dockPanel2->OriginalSize = System::Drawing::Size(200, 200);
			this->dockPanel2->Size = System::Drawing::Size(778, 302);
			this->dockPanel2->Text = L"README";
			this->dockPanel2->Click += gcnew System::EventHandler(this, &MyForm::dockPanel2_Click);
			// 
			// dockPanel2_Container
			// 
			this->dockPanel2_Container->Location = System::Drawing::Point(0, 0);
			this->dockPanel2_Container->Name = L"dockPanel2_Container";
			this->dockPanel2_Container->Size = System::Drawing::Size(778, 302);
			this->dockPanel2_Container->TabIndex = 0;
			// 
			// barButtonItem1
			// 
			this->barButtonItem1->Caption = L"Connect";
			this->barButtonItem1->Id = 1;
			this->barButtonItem1->Name = L"barButtonItem1";
			// 
			// barButtonItem2
			// 
			this->barButtonItem2->Caption = L"Project";
			this->barButtonItem2->Id = 2;
			this->barButtonItem2->Name = L"barButtonItem2";
			// 
			// barButtonItem3
			// 
			this->barButtonItem3->Caption = L"Build";
			this->barButtonItem3->Id = 3;
			this->barButtonItem3->Name = L"barButtonItem3";
			// 
			// barSubItem4
			// 
			this->barSubItem4->Caption = L"Settings";
			this->barSubItem4->Id = 7;
			this->barSubItem4->Name = L"barSubItem4";
			// 
			// barButtonItem6
			// 
			this->barButtonItem6->Caption = L"XBOX 360";
			this->barButtonItem6->Id = 12;
			this->barButtonItem6->Name = L"barButtonItem6";
			// 
			// barButtonItem7
			// 
			this->barButtonItem7->Caption = L"XBOX 360";
			this->barButtonItem7->Id = 13;
			this->barButtonItem7->Name = L"barButtonItem7";
			// 
			// barSubItem7
			// 
			this->barSubItem7->Caption = L"Redacted";
			this->barSubItem7->Id = 14;
			this->barSubItem7->Name = L"barSubItem7";
			// 
			// barButtonItem14
			// 
			this->barButtonItem14->Caption = L"Add New Script";
			this->barButtonItem14->Id = 23;
			this->barButtonItem14->Name = L"barButtonItem14";
			// 
			// barButtonItem15
			// 
			this->barButtonItem15->Caption = L"Check Script Syntax";
			this->barButtonItem15->Id = 24;
			this->barButtonItem15->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut(System::Windows::Forms::Keys::F5));
			this->barButtonItem15->Name = L"barButtonItem15";
			this->barButtonItem15->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem15_ItemClick);
			// 
			// barButtonItem16
			// 
			this->barButtonItem16->Caption = L"Compile";
			this->barButtonItem16->Id = 25;
			this->barButtonItem16->Name = L"barButtonItem16";
			// 
			// barSubItem10
			// 
			this->barSubItem10->Caption = L"Compile to GSC";
			this->barSubItem10->Id = 26;
			this->barSubItem10->Name = L"barSubItem10";
			// 
			// barCheckItem1
			// 
			this->barCheckItem1->BindableChecked = true;
			this->barCheckItem1->Caption = L"Auto-Update";
			this->barCheckItem1->Checked = true;
			this->barCheckItem1->Id = 34;
			this->barCheckItem1->Name = L"barCheckItem1";
			// 
			// barButtonItem28
			// 
			this->barButtonItem28->Caption = L"barButtonItem28";
			this->barButtonItem28->Id = 40;
			this->barButtonItem28->Name = L"barButtonItem28";
			// 
			// barButtonItem29
			// 
			this->barButtonItem29->Caption = L"Import";
			this->barButtonItem29->Id = 41;
			this->barButtonItem29->Name = L"barButtonItem29";
			this->barButtonItem29->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem29_ItemClick);
			// 
			// barSubItem12
			// 
			this->barSubItem12->Caption = L"Import";
			this->barSubItem12->Id = 42;
			this->barSubItem12->Name = L"barSubItem12";
			// 
			// barButtonItem31
			// 
			this->barButtonItem31->Caption = L"Export to GSC Studio Project";
			this->barButtonItem31->Id = 44;
			this->barButtonItem31->Name = L"barButtonItem31";
			// 
			// barCheckItem2
			// 
			this->barCheckItem2->BindableChecked = true;
			this->barCheckItem2->Caption = L"Protect My Source";
			this->barCheckItem2->Checked = true;
			this->barCheckItem2->Id = 45;
			this->barCheckItem2->Name = L"barCheckItem2";
			this->barCheckItem2->CheckedChanged += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barCheckItem2_CheckedChanged);
			// 
			// barSubItem14
			// 
			this->barSubItem14->Caption = L"Output Window";
			this->barSubItem14->Id = 48;
			this->barSubItem14->Name = L"barSubItem14";
			// 
			// barButtonItem33
			// 
			this->barButtonItem33->Caption = L"Clear Console";
			this->barButtonItem33->Id = 49;
			this->barButtonItem33->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Alt)
				| System::Windows::Forms::Keys::O)));
			this->barButtonItem33->Name = L"barButtonItem33";
			this->barButtonItem33->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem33_ItemClick);
			// 
			// barStaticItem2
			// 
			this->barStaticItem2->Caption = L"barStaticItem2";
			this->barStaticItem2->Id = 51;
			this->barStaticItem2->Name = L"barStaticItem2";
			this->barStaticItem2->TextAlignment = System::Drawing::StringAlignment::Near;
			// 
			// barButtonItem35
			// 
			this->barButtonItem35->Caption = L"Rename";
			this->barButtonItem35->Id = 52;
			this->barButtonItem35->Name = L"barButtonItem35";
			this->barButtonItem35->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem35_ItemClick);
			// 
			// barButtonItem36
			// 
			this->barButtonItem36->Caption = L"Delete Script";
			this->barButtonItem36->Id = 53;
			this->barButtonItem36->Name = L"barButtonItem36";
			this->barButtonItem36->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem36_ItemClick);
			// 
			// barButtonItem37
			// 
			this->barButtonItem37->Caption = L"Delete File";
			this->barButtonItem37->Id = 54;
			this->barButtonItem37->Name = L"barButtonItem37";
			this->barButtonItem37->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem37_ItemClick);
			// 
			// barButtonItem38
			// 
			this->barButtonItem38->Caption = L"Edit File Name";
			this->barButtonItem38->Id = 55;
			this->barButtonItem38->Name = L"barButtonItem38";
			this->barButtonItem38->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem38_ItemClick);
			// 
			// barButtonItem39
			// 
			this->barButtonItem39->Caption = L"Add New File";
			this->barButtonItem39->Id = 56;
			this->barButtonItem39->Name = L"barButtonItem39";
			this->barButtonItem39->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem39_ItemClick);
			// 
			// barCheckItem3
			// 
			this->barCheckItem3->Caption = L"Zombies Project";
			this->barCheckItem3->Id = 57;
			this->barCheckItem3->Name = L"barCheckItem3";
			// 
			// barButtonItem40
			// 
			this->barButtonItem40->Caption = L"Toggle Zombies Project";
			this->barButtonItem40->Id = 58;
			this->barButtonItem40->Name = L"barButtonItem40";
			// 
			// ZombiesToggle
			// 
			this->ZombiesToggle->Caption = L"Zombies Project";
			this->ZombiesToggle->Id = 59;
			this->ZombiesToggle->Name = L"ZombiesToggle";
			// 
			// barSubItem15
			// 
			this->barSubItem15->Caption = L"Project Options";
			this->barSubItem15->Id = 60;
			this->barSubItem15->LinksPersistInfo->AddRange(gcnew cli::array< DevExpress::XtraBars::LinkPersistInfo^  >(1) { (gcnew DevExpress::XtraBars::LinkPersistInfo(this->ZombiesToggle)) });
			this->barSubItem15->Name = L"barSubItem15";
			// 
			// barButtonItem42
			// 
			this->barButtonItem42->Caption = L"barButtonItem42";
			this->barButtonItem42->Id = 62;
			this->barButtonItem42->Name = L"barButtonItem42";
			// 
			// barStaticItem3
			// 
			this->barStaticItem3->Caption = L"GSX Studio by Serious";
			this->barStaticItem3->Id = 66;
			this->barStaticItem3->Name = L"barStaticItem3";
			this->barStaticItem3->TextAlignment = System::Drawing::StringAlignment::Near;
			// 
			// barButtonItem45
			// 
			this->barButtonItem45->Caption = L"Clear Output Window";
			this->barButtonItem45->Id = 67;
			this->barButtonItem45->Name = L"barButtonItem45";
			this->barButtonItem45->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem45_ItemClick);
			// 
			// barButtonItem46
			// 
			this->barButtonItem46->Caption = L"Delete Subgroup";
			this->barButtonItem46->Id = 68;
			this->barButtonItem46->Name = L"barButtonItem46";
			this->barButtonItem46->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem46_ItemClick);
			// 
			// barButtonItem47
			// 
			this->barButtonItem47->Caption = L"Set Project Name";
			this->barButtonItem47->Id = 70;
			this->barButtonItem47->Name = L"barButtonItem47";
			// 
			// barButtonItem48
			// 
			this->barButtonItem48->Caption = L"Set Creator Name";
			this->barButtonItem48->Id = 71;
			this->barButtonItem48->Name = L"barButtonItem48";
			// 
			// barButtonItem49
			// 
			this->barButtonItem49->Caption = L"New Script File";
			this->barButtonItem49->Id = 72;
			this->barButtonItem49->Name = L"barButtonItem49";
			this->barButtonItem49->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem49_ItemClick);
			// 
			// barButtonItem51
			// 
			this->barButtonItem51->Caption = L"Check File Syntax";
			this->barButtonItem51->Id = 74;
			this->barButtonItem51->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut((System::Windows::Forms::Keys::Alt | System::Windows::Forms::Keys::S)));
			this->barButtonItem51->Name = L"barButtonItem51";
			this->barButtonItem51->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem51_ItemClick);
			// 
			// DebugToggleSwitch
			// 
			this->DebugToggleSwitch->BindableChecked = true;
			this->DebugToggleSwitch->Caption = L"Debug Mode";
			this->DebugToggleSwitch->Checked = true;
			this->DebugToggleSwitch->Id = 75;
			this->DebugToggleSwitch->Name = L"DebugToggleSwitch";
			// 
			// barToggleSwitchItem1
			// 
			this->barToggleSwitchItem1->Caption = L"hhhh";
			this->barToggleSwitchItem1->Id = 76;
			this->barToggleSwitchItem1->Name = L"barToggleSwitchItem1";
			// 
			// barEditItem2
			// 
			this->barEditItem2->Caption = L"Inline";
			this->barEditItem2->Edit = this->repositoryItemComboBox2;
			this->barEditItem2->Enabled = false;
			this->barEditItem2->Id = 78;
			this->barEditItem2->Name = L"barEditItem2";
			this->barEditItem2->Width = 87;
			this->barEditItem2->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barEditItem2_ItemClick);
			// 
			// repositoryItemComboBox2
			// 
			this->repositoryItemComboBox2->AutoHeight = false;
			this->repositoryItemComboBox2->Buttons->AddRange(gcnew cli::array< DevExpress::XtraEditors::Controls::EditorButton^  >(1) { (gcnew DevExpress::XtraEditors::Controls::EditorButton(DevExpress::XtraEditors::Controls::ButtonPredefines::Combo)) });
			this->repositoryItemComboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Inline on", L"Smart inline", L"Inline off" });
			this->repositoryItemComboBox2->Name = L"repositoryItemComboBox2";
			this->repositoryItemComboBox2->TextEditStyle = DevExpress::XtraEditors::Controls::TextEditStyles::DisableTextEditor;
			// 
			// barStaticItem4
			// 
			this->barStaticItem4->Caption = L"Inline";
			this->barStaticItem4->Id = 79;
			this->barStaticItem4->Name = L"barStaticItem4";
			this->barStaticItem4->TextAlignment = System::Drawing::StringAlignment::Near;
			this->barStaticItem4->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barStaticItem4_ItemClick);
			// 
			// barLargeButtonItem1
			// 
			this->barLargeButtonItem1->Caption = L"barLargeButtonItem1";
			this->barLargeButtonItem1->Id = 80;
			this->barLargeButtonItem1->Name = L"barLargeButtonItem1";
			// 
			// barEditItem3
			// 
			this->barEditItem3->Caption = L"barEditItem3";
			this->barEditItem3->Edit = this->repositoryItemTextEdit1;
			this->barEditItem3->Id = 81;
			this->barEditItem3->Name = L"barEditItem3";
			// 
			// repositoryItemTextEdit1
			// 
			this->repositoryItemTextEdit1->AutoHeight = false;
			this->repositoryItemTextEdit1->Name = L"repositoryItemTextEdit1";
			// 
			// barButtonItem52
			// 
			this->barButtonItem52->Caption = L"barButtonItem52";
			this->barButtonItem52->Id = 82;
			this->barButtonItem52->Name = L"barButtonItem52";
			// 
			// barEditItem4
			// 
			this->barEditItem4->Caption = L"barEditItem4";
			this->barEditItem4->Edit = this->repositoryItemTextEdit2;
			this->barEditItem4->Id = 83;
			this->barEditItem4->Name = L"barEditItem4";
			// 
			// repositoryItemTextEdit2
			// 
			this->repositoryItemTextEdit2->AutoHeight = false;
			this->repositoryItemTextEdit2->Name = L"repositoryItemTextEdit2";
			// 
			// barEditItem5
			// 
			this->barEditItem5->Caption = L"typestrict";
			this->barEditItem5->Edit = this->repositoryItemComboBox3;
			this->barEditItem5->Id = 84;
			this->barEditItem5->Name = L"barEditItem5";
			this->barEditItem5->Width = 75;
			// 
			// repositoryItemComboBox3
			// 
			this->repositoryItemComboBox3->AutoHeight = false;
			this->repositoryItemComboBox3->Buttons->AddRange(gcnew cli::array< DevExpress::XtraEditors::Controls::EditorButton^  >(1) { (gcnew DevExpress::XtraEditors::Controls::EditorButton(DevExpress::XtraEditors::Controls::ButtonPredefines::Combo)) });
			this->repositoryItemComboBox3->Name = L"repositoryItemComboBox3";
			// 
			// barButtonItem53
			// 
			this->barButtonItem53->Caption = L"Build";
			this->barButtonItem53->Id = 85;
			this->barButtonItem53->ImageUri->Uri = L"Zoom2";
			this->barButtonItem53->Name = L"barButtonItem53";
			// 
			// barButtonItem55
			// 
			this->barButtonItem55->Caption = L"Save File";
			this->barButtonItem55->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"barButtonItem55.Glyph")));
			this->barButtonItem55->Id = 87;
			this->barButtonItem55->Name = L"barButtonItem55";
			// 
			// barEditItem6
			// 
			this->barEditItem6->Caption = L"barEditItem6";
			this->barEditItem6->Edit = this->repositoryItemComboBox4;
			this->barEditItem6->Id = 92;
			this->barEditItem6->Name = L"barEditItem6";
			// 
			// repositoryItemComboBox4
			// 
			this->repositoryItemComboBox4->AutoHeight = false;
			this->repositoryItemComboBox4->Buttons->AddRange(gcnew cli::array< DevExpress::XtraEditors::Controls::EditorButton^  >(1) { (gcnew DevExpress::XtraEditors::Controls::EditorButton(DevExpress::XtraEditors::Controls::ButtonPredefines::Combo)) });
			this->repositoryItemComboBox4->Name = L"repositoryItemComboBox4";
			// 
			// barEditItem1
			// 
			this->barEditItem1->Caption = L"Progress";
			this->barEditItem1->Edit = this->repositoryItemProgressBar1;
			this->barEditItem1->Id = 96;
			this->barEditItem1->Name = L"barEditItem1";
			// 
			// repositoryItemProgressBar1
			// 
			this->repositoryItemProgressBar1->Name = L"repositoryItemProgressBar1";
			// 
			// Bar_BuildSettings
			// 
			this->Bar_BuildSettings->Caption = L"Build Settings";
			this->Bar_BuildSettings->Id = 98;
			this->Bar_BuildSettings->Name = L"Bar_BuildSettings";
			// 
			// BuildSettingsButton
			// 
			this->BuildSettingsButton->Caption = L"Build Settings";
			this->BuildSettingsButton->Glyph = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"BuildSettingsButton.Glyph")));
			this->BuildSettingsButton->Id = 99;
			this->BuildSettingsButton->ItemShortcut = (gcnew DevExpress::XtraBars::BarShortcut((System::Windows::Forms::Keys::Alt | System::Windows::Forms::Keys::P)));
			this->BuildSettingsButton->Name = L"BuildSettingsButton";
			this->BuildSettingsButton->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::BuildSettingsButton_ItemClick);
			// 
			// barButtonItem13
			// 
			this->barButtonItem13->Caption = L"Optimize Child Variables";
			this->barButtonItem13->Id = 102;
			this->barButtonItem13->Name = L"barButtonItem13";
			this->barButtonItem13->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem13_ItemClick_2);
			// 
			// barButtonItem17
			// 
			this->barButtonItem17->Caption = L"barButtonItem17";
			this->barButtonItem17->Id = 103;
			this->barButtonItem17->Name = L"barButtonItem17";
			// 
			// barButtonItem18
			// 
			this->barButtonItem18->Caption = L"Connect Using JRPC";
			this->barButtonItem18->Id = 106;
			this->barButtonItem18->Name = L"barButtonItem18";
			// 
			// barSubItem18
			// 
			this->barSubItem18->Caption = L"Share";
			this->barSubItem18->Id = 107;
			this->barSubItem18->Name = L"barSubItem18";
			// 
			// barButtonItem19
			// 
			this->barButtonItem19->Caption = L"Publish Project";
			this->barButtonItem19->Id = 108;
			this->barButtonItem19->Name = L"barButtonItem19";
			// 
			// barSubItem19
			// 
			this->barSubItem19->Caption = L"Share";
			this->barSubItem19->Id = 109;
			this->barSubItem19->LinksPersistInfo->AddRange(gcnew cli::array< DevExpress::XtraBars::LinkPersistInfo^  >(3) {
				(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem32)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem34)), (gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem41))
			});
			this->barSubItem19->Name = L"barSubItem19";
			// 
			// barButtonItem32
			// 
			this->barButtonItem32->Caption = L"Share Project Source";
			this->barButtonItem32->Id = 110;
			this->barButtonItem32->Name = L"barButtonItem32";
			// 
			// barButtonItem34
			// 
			this->barButtonItem34->Caption = L"Share Package";
			this->barButtonItem34->Id = 111;
			this->barButtonItem34->Name = L"barButtonItem34";
			// 
			// barButtonItem41
			// 
			this->barButtonItem41->Caption = L"Share Project as Library";
			this->barButtonItem41->Id = 112;
			this->barButtonItem41->Name = L"barButtonItem41";
			// 
			// barButtonItem43
			// 
			this->barButtonItem43->Caption = L"Fast Files";
			this->barButtonItem43->Id = 114;
			this->barButtonItem43->Name = L"barButtonItem43";
			this->barButtonItem43->ItemClick += gcnew DevExpress::XtraBars::ItemClickEventHandler(this, &MyForm::barButtonItem43_ItemClick);
			// 
			// barButtonItem44
			// 
			this->barButtonItem44->Caption = L"Manage Your Libraries";
			this->barButtonItem44->Id = 115;
			this->barButtonItem44->Name = L"barButtonItem44";
			// 
			// barSubItem21
			// 
			this->barSubItem21->Caption = L"Manage";
			this->barSubItem21->Id = 116;
			this->barSubItem21->Name = L"barSubItem21";
			// 
			// barButtonItem54
			// 
			this->barButtonItem54->Caption = L"Project";
			this->barButtonItem54->Id = 117;
			this->barButtonItem54->Name = L"barButtonItem54";
			// 
			// barButtonItem57
			// 
			this->barButtonItem57->Caption = L"Share Project";
			this->barButtonItem57->Id = 119;
			this->barButtonItem57->Name = L"barButtonItem57";
			// 
			// barSubItem22
			// 
			this->barSubItem22->Caption = L"Manage";
			this->barSubItem22->Id = 120;
			this->barSubItem22->LinksPersistInfo->AddRange(gcnew cli::array< DevExpress::XtraBars::LinkPersistInfo^  >(3) {
				(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem60)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem61)), (gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem62))
			});
			this->barSubItem22->Name = L"barSubItem22";
			// 
			// barButtonItem60
			// 
			this->barButtonItem60->Caption = L"Import Libraries";
			this->barButtonItem60->Id = 121;
			this->barButtonItem60->Name = L"barButtonItem60";
			// 
			// barButtonItem61
			// 
			this->barButtonItem61->Caption = L"Reload Libraries";
			this->barButtonItem61->Id = 122;
			this->barButtonItem61->Name = L"barButtonItem61";
			// 
			// barButtonItem62
			// 
			this->barButtonItem62->Caption = L"Library Manager";
			this->barButtonItem62->Id = 123;
			this->barButtonItem62->Name = L"barButtonItem62";
			// 
			// barButtonItem66
			// 
			this->barButtonItem66->Caption = L"Platform Tools";
			this->barButtonItem66->Id = 128;
			this->barButtonItem66->Name = L"barButtonItem66";
			// 
			// Toolbarsmanager
			// 
			this->Toolbarsmanager->Controller->LookAndFeel->SkinName = L"Visual Studio 2013 Dark";
			this->Toolbarsmanager->Controller->LookAndFeel->UseDefaultLookAndFeel = false;
			this->Toolbarsmanager->Controller->PaintStyleName = L"Skin";
			this->Toolbarsmanager->Controller->PropertiesBar->DefaultGlyphSize = System::Drawing::Size(16, 16);
			this->Toolbarsmanager->Controller->PropertiesBar->DefaultLargeGlyphSize = System::Drawing::Size(32, 32);
			// 
			// documentManager1
			// 
			this->documentManager1->ContainerControl = this;
			this->documentManager1->View = this->tabbedView1;
			this->documentManager1->ViewCollection->AddRange(gcnew cli::array< DevExpress::XtraBars::Docking2010::Views::BaseView^  >(1) { this->tabbedView1 });
			// 
			// tabbedView1
			// 
			this->tabbedView1->DocumentGroupProperties->HeaderButtons = DevExpress::XtraTab::TabButtons::None;
			this->tabbedView1->DocumentGroupProperties->HeaderButtonsShowMode = DevExpress::XtraTab::TabButtonShowMode::Never;
			this->tabbedView1->DocumentGroups->AddRange(gcnew cli::array< DevExpress::XtraBars::Docking2010::Views::Tabbed::DocumentGroup^  >(1) { this->documentGroup1 });
			this->tabbedView1->Documents->AddRange(gcnew cli::array< DevExpress::XtraBars::Docking2010::Views::BaseDocument^  >(1) { this->document1 });
			// 
			// documentGroup1
			// 
			this->documentGroup1->Items->AddRange(gcnew cli::array< DevExpress::XtraBars::Docking2010::Views::Tabbed::Document^  >(1) { this->document1 });
			// 
			// document1
			// 
			this->document1->Caption = L"README";
			this->document1->ControlName = L"dockPanel2";
			this->document1->FloatLocation = System::Drawing::Point(612, 346);
			this->document1->FloatSize = System::Drawing::Size(200, 200);
			this->document1->Properties->AllowClose = DevExpress::Utils::DefaultBoolean::True;
			this->document1->Properties->AllowFloat = DevExpress::Utils::DefaultBoolean::True;
			this->document1->Properties->AllowFloatOnDoubleClick = DevExpress::Utils::DefaultBoolean::True;
			// 
			// SRightClick
			// 
			this->SRightClick->LinksPersistInfo->AddRange(gcnew cli::array< DevExpress::XtraBars::LinkPersistInfo^  >(3) {
				(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem39)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem35)), (gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem36))
			});
			this->SRightClick->Manager = this->Toolbars;
			this->SRightClick->MenuCaption = L"Edit Script";
			this->SRightClick->Name = L"SRightClick";
			// 
			// PRightClick
			// 
			this->PRightClick->LinksPersistInfo->AddRange(gcnew cli::array< DevExpress::XtraBars::LinkPersistInfo^  >(2) {
				(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem38)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem37))
			});
			this->PRightClick->Manager = this->Toolbars;
			this->PRightClick->Name = L"PRightClick";
			// 
			// OutputPopup
			// 
			this->OutputPopup->LinksPersistInfo->AddRange(gcnew cli::array< DevExpress::XtraBars::LinkPersistInfo^  >(1) { (gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem45)) });
			this->OutputPopup->Manager = this->Toolbars;
			this->OutputPopup->Name = L"OutputPopup";
			// 
			// SubgroupPopup
			// 
			this->SubgroupPopup->LinksPersistInfo->AddRange(gcnew cli::array< DevExpress::XtraBars::LinkPersistInfo^  >(2) {
				(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem49)),
					(gcnew DevExpress::XtraBars::LinkPersistInfo(this->barButtonItem46))
			});
			this->SubgroupPopup->Manager = this->Toolbars;
			this->SubgroupPopup->Name = L"SubgroupPopup";
			// 
			// ColorTool
			// 
			this->ColorTool->FullOpen = true;
			// 
			// SyntaxTimer
			// 
			this->SyntaxTimer->Interval = 1500;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(984, 581);
			this->Controls->Add(this->ProjectPanel);
			this->Controls->Add(this->panelContainer1);
			this->Controls->Add(this->barDockControlLeft);
			this->Controls->Add(this->barDockControlRight);
			this->Controls->Add(this->barDockControlBottom);
			this->Controls->Add(this->barDockControlTop);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->LookAndFeel->SkinName = L"Visual Studio 2013 Dark";
			this->LookAndFeel->UseDefaultLookAndFeel = false;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Black Ops II - GSX Studio";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Toolbars))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BuildModeCombo))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->BuildTargetCombo))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dockManager1))->EndInit();
			this->panelContainer1->ResumeLayout(false);
			this->ErrorPanel->ResumeLayout(false);
			this->dockPanel3_Container->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ErrorConsole))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->repositoryItemPictureEdit1))->EndInit();
			this->OutputPanel->ResumeLayout(false);
			this->dockPanel4_Container->ResumeLayout(false);
			this->ProjectPanel->ResumeLayout(false);
			this->dockPanel1_Container->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ProjectExplorer))->EndInit();
			this->dockPanel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->repositoryItemComboBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->repositoryItemTextEdit1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->repositoryItemTextEdit2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->repositoryItemComboBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->repositoryItemComboBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->repositoryItemProgressBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Toolbarsmanager->Controller))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->documentManager1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tabbedView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->documentGroup1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->document1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SRightClick))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PRightClick))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->OutputPopup))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SubgroupPopup))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void barButtonItem29_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
	}
	private: System::Void treeList1_FocusedNodeChanged(System::Object^  sender, DevExpress::XtraTreeList::FocusedNodeChangedEventArgs^  e) 
	{
	}
	private: System::Void barButtonItem4_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		Manager->ConnectToPlatform(GSXCompilerLib::XPlatformType::PLATFORM_PS3_CCAPI);
	}
	private: System::Void barButtonItem19_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		Manager->BuildProject(BuildMode->EditValue->ToString() == "Debug", GSXCompilerLib::PlatformTarget::Package);
	}
	private: System::Void barButtonItem11_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) //New Project
	{
		Manager->NewProject();
	}
	private: System::Void barCheckItem2_CheckedChanged(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		if (!barCheckItem2->Checked)
		{
			IDE::Print("Disabling source protection will allow other users to obtain your work without permission. If this is a release build, please consider re-enabling this option.", "Warning", Output);
		}
	}
private: System::Void dockPanel4_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void dockPanel2_Click(System::Object^  sender, System::EventArgs^  e) {
}
	private: System::Void barButtonItem12_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) //Open Project
	{
		Manager->OpenProject();
	}
	private: System::Void barButtonItem33_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) //Clear Console
	{
		IDE::ClearConsole(Output);
	}
	private: System::Void barButtonItem35_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) //Rename Script
	{ 
		Manager->RenameScriptFired();
	}
	private: System::Void barButtonItem38_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) //Rename File
	{
		Manager->RenameFileFired();
	}
	private: System::Void barButtonItem13_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) //Save Project
	{
		Manager->SaveProject();
	}
	private: System::Void barButtonItem39_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) //New File
	{
		Manager->AddScriptFile();
	}
	private: System::Void barButtonItem41_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		Manager->AddNewScript();
	}
	private: System::Void barButtonItem34_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		Manager->UnloadProject();
	}
	private: System::Void barButtonItem36_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		Manager->DeleteScriptFired();
	}
	private: System::Void barButtonItem37_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		Manager->DeleteFileFired();
	}
			 void OnOutputMouseClick(System::Object ^sender, System::Windows::Forms::MouseEventArgs ^e);
	private: System::Void barButtonItem45_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		IDE::ClearConsole(Output);
	}
	private: System::Void barButtonItem46_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		Manager->DeleteSubgroupFired();
	}
	private: System::Void barButtonItem30_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		Manager->LoadImportsWindow();
	}
	private: System::Void ReportClicked(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e)
	{
		Manager->ReportClicked();
	}
	private: System::Void barButtonItem32_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		Manager->SaveActiveFile();
	}
			 void OnThisClosing(System::Object ^sender, System::ComponentModel::CancelEventArgs ^e);
	private: System::Void barButtonItem49_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		Manager->AddNewScript();
	}
	private: System::Void barButtonItem50_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		ColorTool->ShowDialog();
		IDE::Print("(" + Decimal::Round((Decimal)(ColorTool->Color.R / 255.0), 3) + ", " + Decimal::Round((Decimal)(ColorTool->Color.G / 255.0), 3) + ", " + Decimal::Round((Decimal)(ColorTool->Color.B / 255.0), 3) + ")", "Color Picked", Output);
	}
	private: System::Void Output_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void barButtonItem15_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		Manager->CheckScriptSyntax();
	}
	private: System::Void barButtonItem51_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		Manager->CheckCurrentFileSyntax();
	}
	private: System::Void ErrorConsole_FocusedNodeChanged(System::Object^  sender, DevExpress::XtraTreeList::FocusedNodeChangedEventArgs^  e) 
	{
		
	}
	void OnGClick(System::Object ^sender, System::EventArgs ^e);
	private: System::Void barStaticItem4_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) {
	}
	private: System::Void barEditItem2_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) {
	}
	private: System::Void barButtonItem58_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		Manager->NewProject();
	}
	private: System::Void barButtonItem59_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		Manager->OpenProject();
	}
			 void OnBuildEditValueChanged(System::Object ^sender, System::EventArgs ^e);
			 void OnBuildSelectedValueChanged(System::Object ^sender, System::EventArgs ^e);
	private: System::Void Toolbar_Save_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		Manager->SaveActiveFile();
	}
	private: System::Void Toolbar_SaveAll_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		Manager->SaveProject();
	}
	private: System::Void ToolbarPSettings_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) {
		Manager->ProjectSettingsWindow();
	}
	private: System::Void DropDown_PSettings_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		Manager->ProjectSettingsWindow();
	}
	private: System::Void ToolbarBuildProject_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		if (BuildTarget->EditValue->ToString() == "Console")
		{
			Manager->BuildProject(BuildMode->EditValue->ToString() == "Debug", GSXCompilerLib::PlatformTarget::Console);
		}
		if (BuildTarget->EditValue->ToString() == "PC")
		{
			Manager->BuildProject(BuildMode->EditValue->ToString() == "Debug", GSXCompilerLib::PlatformTarget::PC);
		}
		if (BuildTarget->EditValue->ToString() == "Package")
		{
			Manager->BuildProject(BuildMode->EditValue->ToString() == "Debug", GSXCompilerLib::PlatformTarget::Package);
		}
	}
	private: System::Void DropDown_BuildC_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		Manager->BuildProject(BuildMode->EditValue->ToString() == "Debug", GSXCompilerLib::PlatformTarget::Console);
	}
	private: System::Void DropDown_BuildPC_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		Manager->BuildProject(BuildMode->EditValue->ToString() == "Debug", GSXCompilerLib::PlatformTarget::PC);
	}
	private: System::Void barButtonItem13_ItemClick_1(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) 
	{
		Manager->RepairProjectWrapper();
	}
private: System::Void BuildSettingsButton_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) {
	Manager->DisplayBuildSettings();
}
private: System::Void barCheckItem4_CheckedChanged(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) {
	Manager->OptimizeScripts = true;//Build_Scripts->Checked;
	Manager->GSXStudioRegistryKey->SetValue("Optimize", Manager->OptimizeScripts, Microsoft::Win32::RegistryValueKind::DWord);
}
private: System::Void barButtonItem13_ItemClick_2(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) {
}
private: System::Void barCheckItem5_CheckedChanged(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) {
	Manager->OptimizeChildren = Build_Children->Checked;
	Manager->GSXStudioRegistryKey->SetValue("OptimizeChildren", Manager->OptimizeChildren, Microsoft::Win32::RegistryValueKind::DWord);
}
private: System::Void barCheckItem6_CheckedChanged(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) {
	Manager->Symbolize = Build_Symbolize->Checked;
	Manager->GSXStudioRegistryKey->SetValue("Symbolize", Manager->Symbolize, Microsoft::Win32::RegistryValueKind::DWord);
}
private: System::Void barButtonItem5_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) {
	Manager->ConnectToPlatform(GSXCompilerLib::XPlatformType::PLATFORM_PS3_TMAPI);
}
private: System::Void barButtonItem8_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) {
	Manager->ConnectToPlatform(GSXCompilerLib::XPlatformType::PLATFORM_XBOX360);
}
private: System::Void barButtonItem9_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) {
	Manager->ConnectToPlatform(GSXCompilerLib::XPlatformType::PLATFORM_PC_REDACTED);
}
private: System::Void barButtonItem10_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) {
	Manager->ConnectToPlatform(GSXCompilerLib::XPlatformType::PLATFORM_PC_STEAM);
}

	private: System::Void InjectPackage(System::Object^ sender, DevExpress::XtraBars::ItemClickEventArgs^ e)
	{
		Manager->InjectPackage();
	}
	private: System::Void InjectCurrentProject(System::Object^ sender, DevExpress::XtraBars::ItemClickEventArgs^ e)
	{
		Manager->InjectCurrentProject(BuildMode->EditValue->ToString() == "Debug");
	}
	private: System::Void InjectGSX(System::Object^ sender, DevExpress::XtraBars::ItemClickEventArgs^ e)
	{
		Manager->InjectExternalScripts();
	}

	private: System::Void barButtonItem43_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) {
	}
private: System::Void barButtonItem67_ItemClick(System::Object^  sender, DevExpress::XtraBars::ItemClickEventArgs^  e) {
	Manager->PlatformMemClicked();
}
};
}


void GSX_Studio::MyForm::OnGClick(System::Object ^sender, System::EventArgs ^e)
{
	Manager->NavigateToSyntaxError(ErrorConsole->FocusedNode);
}
