#pragma once

namespace GSX_Studio {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for LIBMGR
	/// </summary>
	public ref class LIBMGR : public DevExpress::XtraEditors::XtraForm
	{
	public:
		LIBMGR(System::String^ TargetMode)
		{
			DevExpress::Skins::SkinManager::EnableFormSkins();
			DevExpress::UserSkins::BonusSkins::Register();
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		void ExplorerOnMouseClick(System::Object ^sender, System::Windows::Forms::MouseEventArgs ^e);
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~LIBMGR()
		{
			if (components)
			{
				delete components;
			}
		}
	private: DevExpress::XtraTab::XtraTabControl^  xtraTabControl1;
	private: DevExpress::XtraTab::XtraTabPage^  LibList;
	private: DevExpress::XtraTab::XtraTabPage^  LibCreator;
	private: DevExpress::XtraTab::XtraTabPage^  DownloadLibs;
	protected:



	private: DevExpress::XtraTreeList::TreeList^  ProjectsList;
	private: DevExpress::XtraTreeList::Columns::TreeListColumn^  treeListColumn1;
	private: DevExpress::XtraTreeList::Columns::TreeListColumn^  treeListColumn2;
	private: DevExpress::XtraTreeList::Columns::TreeListColumn^  treeListColumn3;

	private: DevExpress::XtraBars::PopupMenu^  InstallRightClickMenu;
	private: DevExpress::XtraBars::BarManager^  barManager1;
	private: DevExpress::XtraBars::BarDockControl^  barDockControlTop;
	private: DevExpress::XtraBars::BarDockControl^  barDockControlBottom;
	private: DevExpress::XtraBars::BarDockControl^  barDockControlLeft;
	private: DevExpress::XtraBars::BarDockControl^  barDockControlRight;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem1;
	private: DevExpress::XtraTreeList::Columns::TreeListColumn^  treeListColumn4;
	private: DevExpress::XtraBars::BarButtonItem^  barButtonItem2;
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
			this->xtraTabControl1 = (gcnew DevExpress::XtraTab::XtraTabControl());
			this->LibList = (gcnew DevExpress::XtraTab::XtraTabPage());
			this->LibCreator = (gcnew DevExpress::XtraTab::XtraTabPage());
			this->DownloadLibs = (gcnew DevExpress::XtraTab::XtraTabPage());
			this->ProjectsList = (gcnew DevExpress::XtraTreeList::TreeList());
			this->treeListColumn1 = (gcnew DevExpress::XtraTreeList::Columns::TreeListColumn());
			this->treeListColumn2 = (gcnew DevExpress::XtraTreeList::Columns::TreeListColumn());
			this->treeListColumn3 = (gcnew DevExpress::XtraTreeList::Columns::TreeListColumn());
			this->InstallRightClickMenu = (gcnew DevExpress::XtraBars::PopupMenu(this->components));
			this->barManager1 = (gcnew DevExpress::XtraBars::BarManager(this->components));
			this->barDockControlTop = (gcnew DevExpress::XtraBars::BarDockControl());
			this->barDockControlBottom = (gcnew DevExpress::XtraBars::BarDockControl());
			this->barDockControlLeft = (gcnew DevExpress::XtraBars::BarDockControl());
			this->barDockControlRight = (gcnew DevExpress::XtraBars::BarDockControl());
			this->barButtonItem1 = (gcnew DevExpress::XtraBars::BarButtonItem());
			this->treeListColumn4 = (gcnew DevExpress::XtraTreeList::Columns::TreeListColumn());
			this->barButtonItem2 = (gcnew DevExpress::XtraBars::BarButtonItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->xtraTabControl1))->BeginInit();
			this->xtraTabControl1->SuspendLayout();
			this->LibList->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ProjectsList))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->InstallRightClickMenu))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barManager1))->BeginInit();
			this->SuspendLayout();
			// 
			// xtraTabControl1
			// 
			this->xtraTabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->xtraTabControl1->Location = System::Drawing::Point(0, 0);
			this->xtraTabControl1->Name = L"xtraTabControl1";
			this->xtraTabControl1->SelectedTabPage = this->LibList;
			this->xtraTabControl1->Size = System::Drawing::Size(764, 461);
			this->xtraTabControl1->TabIndex = 0;
			this->xtraTabControl1->TabPages->AddRange(gcnew cli::array< DevExpress::XtraTab::XtraTabPage^  >(3) {
				this->LibList, this->LibCreator,
					this->DownloadLibs
			});
			// 
			// LibList
			// 
			this->LibList->Controls->Add(this->ProjectsList);
			this->LibList->Name = L"LibList";
			this->LibList->Size = System::Drawing::Size(762, 434);
			this->LibList->Text = L"Installed Libraries";
			// 
			// LibCreator
			// 
			this->LibCreator->Name = L"LibCreator";
			this->LibCreator->Size = System::Drawing::Size(762, 434);
			this->LibCreator->Text = L"Library Editor";
			// 
			// DownloadLibs
			// 
			this->DownloadLibs->Name = L"DownloadLibs";
			this->DownloadLibs->Size = System::Drawing::Size(762, 434);
			this->DownloadLibs->Text = L"Get New Libraries";
			// 
			// ProjectsList
			// 
			this->ProjectsList->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->ProjectsList->Columns->AddRange(gcnew cli::array< DevExpress::XtraTreeList::Columns::TreeListColumn^  >(4) {
				this->treeListColumn1,
					this->treeListColumn2, this->treeListColumn3, this->treeListColumn4
			});
			this->ProjectsList->Location = System::Drawing::Point(10, 10);
			this->ProjectsList->Name = L"ProjectsList";
			this->ProjectsList->OptionsBehavior->Editable = false;
			this->ProjectsList->OptionsBehavior->ImmediateEditor = false;
			this->ProjectsList->OptionsBehavior->KeepSelectedOnClick = false;
			this->ProjectsList->OptionsCustomization->AllowBandMoving = false;
			this->ProjectsList->OptionsCustomization->AllowColumnMoving = false;
			this->ProjectsList->OptionsCustomization->AllowQuickHideColumns = false;
			this->ProjectsList->OptionsCustomization->ShowBandsInCustomizationForm = false;
			this->ProjectsList->OptionsLayout->AddNewColumns = false;
			this->ProjectsList->OptionsMenu->EnableColumnMenu = false;
			this->ProjectsList->OptionsMenu->EnableFooterMenu = false;
			this->ProjectsList->OptionsMenu->ShowAutoFilterRowItem = false;
			this->ProjectsList->OptionsSelection->SelectNodesOnRightClick = true;
			this->ProjectsList->Size = System::Drawing::Size(740, 413);
			this->ProjectsList->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &GSX_Studio::LIBMGR::ExplorerOnMouseClick);
			this->ProjectsList->TabIndex = 13;
			this->ProjectsList->FocusedNodeChanged += gcnew DevExpress::XtraTreeList::FocusedNodeChangedEventHandler(this, &LIBMGR::ProjectsList_FocusedNodeChanged);
			// 
			// treeListColumn1
			// 
			this->treeListColumn1->Caption = L"Library Title";
			this->treeListColumn1->FieldName = L"Project Name";
			this->treeListColumn1->MinWidth = 34;
			this->treeListColumn1->Name = L"treeListColumn1";
			this->treeListColumn1->OptionsColumn->AllowEdit = false;
			this->treeListColumn1->OptionsColumn->AllowMove = false;
			this->treeListColumn1->OptionsColumn->AllowMoveToCustomizationForm = false;
			this->treeListColumn1->OptionsColumn->AllowSort = false;
			this->treeListColumn1->OptionsColumn->ReadOnly = true;
			this->treeListColumn1->OptionsColumn->ShowInCustomizationForm = false;
			this->treeListColumn1->OptionsColumn->ShowInExpressionEditor = false;
			this->treeListColumn1->Visible = true;
			this->treeListColumn1->VisibleIndex = 0;
			// 
			// treeListColumn2
			// 
			this->treeListColumn2->Caption = L"Library Name";
			this->treeListColumn2->FieldName = L"Library Name";
			this->treeListColumn2->Name = L"treeListColumn2";
			this->treeListColumn2->OptionsColumn->AllowEdit = false;
			this->treeListColumn2->OptionsColumn->AllowMove = false;
			this->treeListColumn2->OptionsColumn->AllowMoveToCustomizationForm = false;
			this->treeListColumn2->OptionsColumn->AllowSort = false;
			this->treeListColumn2->OptionsColumn->ReadOnly = true;
			this->treeListColumn2->OptionsColumn->ShowInCustomizationForm = false;
			this->treeListColumn2->OptionsColumn->ShowInExpressionEditor = false;
			this->treeListColumn2->Visible = true;
			this->treeListColumn2->VisibleIndex = 1;
			// 
			// treeListColumn3
			// 
			this->treeListColumn3->Caption = L"Creator Name";
			this->treeListColumn3->FieldName = L"Creator Name";
			this->treeListColumn3->Name = L"treeListColumn3";
			this->treeListColumn3->OptionsColumn->AllowEdit = false;
			this->treeListColumn3->OptionsColumn->AllowMove = false;
			this->treeListColumn3->OptionsColumn->AllowMoveToCustomizationForm = false;
			this->treeListColumn3->OptionsColumn->AllowSort = false;
			this->treeListColumn3->OptionsColumn->ReadOnly = true;
			this->treeListColumn3->OptionsColumn->ShowInCustomizationForm = false;
			this->treeListColumn3->OptionsColumn->ShowInExpressionEditor = false;
			this->treeListColumn3->Visible = true;
			this->treeListColumn3->VisibleIndex = 2;
			// 
			// InstallRightClickMenu
			// 
			this->InstallRightClickMenu->Name = L"InstallRightClickMenu";
			// 
			// barManager1
			// 
			this->barManager1->DockControls->Add(this->barDockControlTop);
			this->barManager1->DockControls->Add(this->barDockControlBottom);
			this->barManager1->DockControls->Add(this->barDockControlLeft);
			this->barManager1->DockControls->Add(this->barDockControlRight);
			this->barManager1->Form = this;
			this->barManager1->Items->AddRange(gcnew cli::array< DevExpress::XtraBars::BarItem^  >(2) { this->barButtonItem1, this->barButtonItem2 });
			this->barManager1->MaxItemId = 2;
			// 
			// barDockControlTop
			// 
			this->barDockControlTop->CausesValidation = false;
			this->barDockControlTop->Dock = System::Windows::Forms::DockStyle::Top;
			this->barDockControlTop->Location = System::Drawing::Point(0, 0);
			this->barDockControlTop->Size = System::Drawing::Size(764, 0);
			// 
			// barDockControlBottom
			// 
			this->barDockControlBottom->CausesValidation = false;
			this->barDockControlBottom->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->barDockControlBottom->Location = System::Drawing::Point(0, 461);
			this->barDockControlBottom->Size = System::Drawing::Size(764, 0);
			// 
			// barDockControlLeft
			// 
			this->barDockControlLeft->CausesValidation = false;
			this->barDockControlLeft->Dock = System::Windows::Forms::DockStyle::Left;
			this->barDockControlLeft->Location = System::Drawing::Point(0, 0);
			this->barDockControlLeft->Size = System::Drawing::Size(0, 461);
			// 
			// barDockControlRight
			// 
			this->barDockControlRight->CausesValidation = false;
			this->barDockControlRight->Dock = System::Windows::Forms::DockStyle::Right;
			this->barDockControlRight->Location = System::Drawing::Point(764, 0);
			this->barDockControlRight->Size = System::Drawing::Size(0, 461);
			// 
			// barButtonItem1
			// 
			this->barButtonItem1->Caption = L"Import New Library";
			this->barButtonItem1->Id = 0;
			this->barButtonItem1->Name = L"barButtonItem1";
			// 
			// treeListColumn4
			// 
			this->treeListColumn4->Caption = L"Type of Library";
			this->treeListColumn4->FieldName = L"Type of Library";
			this->treeListColumn4->Name = L"treeListColumn4";
			this->treeListColumn4->Visible = true;
			this->treeListColumn4->VisibleIndex = 3;
			// 
			// barButtonItem2
			// 
			this->barButtonItem2->Caption = L"Delete Selected Library";
			this->barButtonItem2->Id = 1;
			this->barButtonItem2->Name = L"barButtonItem2";
			// 
			// LIBMGR
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(764, 461);
			this->Controls->Add(this->xtraTabControl1);
			this->Controls->Add(this->barDockControlLeft);
			this->Controls->Add(this->barDockControlRight);
			this->Controls->Add(this->barDockControlBottom);
			this->Controls->Add(this->barDockControlTop);
			this->LookAndFeel->SkinName = L"Visual Studio 2013 Dark";
			this->LookAndFeel->UseDefaultLookAndFeel = false;
			this->Name = L"LIBMGR";
			this->Text = L"Library Manager";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->xtraTabControl1))->EndInit();
			this->xtraTabControl1->ResumeLayout(false);
			this->LibList->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ProjectsList))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->InstallRightClickMenu))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->barManager1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ProjectsList_FocusedNodeChanged(System::Object^  sender, DevExpress::XtraTreeList::FocusedNodeChangedEventArgs^  e) {
	}
};
}
