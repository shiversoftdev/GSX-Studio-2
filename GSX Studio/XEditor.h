#pragma once

namespace GSX_Studio {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace FastColoredTextBoxNS;
	using namespace System::Reflection;

	/// <summary>
	/// Summary for XEditor
	/// </summary>
	public ref class XEditor : DevExpress::XtraEditors::XtraUserControl
	{
	public:
		void AdjustScrollbars(void);
		void AdjustHScrollbar(DevExpress::XtraEditors::HScrollBar^ scrollBar, int max, int value, int clientSize);
		void AdjustVScrollbar(DevExpress::XtraEditors::VScrollBar^ scrollBar, int max, int value, int clientSize);
		void fctb_ScrollbarsUpdated(System::Object^ sender, System::EventArgs^ e);
		void VScrollBar_Scroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e);
		void HScrollBar_Scroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e);

		XEditor(System::Windows::Forms::ImageList^ images, System::Collections::Generic::List<AutocompleteItem^>^ items)
		{
			InitializeComponent();
			Editor->ScrollbarsUpdated += gcnew System::EventHandler(this, &GSX_Studio::XEditor::fctb_ScrollbarsUpdated);
			Editor->SelectionColor = System::Drawing::Color::FromArgb(51, 153, 255);
			VScroller->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &GSX_Studio::XEditor::VScrollBar_Scroll);
			HScroller->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &GSX_Studio::XEditor::HScrollBar_Scroll);
			documentMap1->MouseEnter += gcnew System::EventHandler(this, &GSX_Studio::XEditor::OnDMMouseEnter);
			documentMap1->MouseLeave += gcnew System::EventHandler(this, &GSX_Studio::XEditor::OnDMMouseLeave);
			Editor->BracketsStyle->BackgroundBrush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(100, 51, 153, 255));
			Editor->BracketsStyle2->BackgroundBrush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(100, 51, 153, 255));
			ACM = gcnew FastColoredTextBoxNS::AutocompleteMenu(Editor);
			Editor->Click += gcnew System::EventHandler(this, &GSX_Studio::XEditor::OnEClick);
			ACM->ForeColor = Color::FromArgb(220,220,220);
			ACM->AllowTabKey = true;
			ACM->BackColor = Color::FromArgb(37,37,37);
			ACM->SelectedColor = Color::FromArgb(60, 149, 253);
			ACM->Font = gcnew System::Drawing::Font("Tahoma", 10);
			ACM->HoveredColor = Color::FromArgb(37, 37, 37);
			ACM->ToolTipDuration = Int32::MaxValue;
			ACM->ImageList = images;
			ACM->ToolTip->OwnerDraw = true;
			ACM->ToolTip->Draw += gcnew System::Windows::Forms::DrawToolTipEventHandler(this, &GSX_Studio::XEditor::OnTTDraw);
			ACM->ToolTip->BackColor = Color::FromArgb(66, 65, 70);
			ACM->ToolTip->ForeColor = Color::FromArgb(220, 220, 220);
			ACM->AppearInterval = 100;
			//ACM->SelectedColor = Color::FromArgb(.5, 148, 186, 222);
			ACM->SearchPattern = "[\\w\\.\\\\\:]";
			ACM->Items->SetAutocompleteItems(items);
			ACM->MinFragmentLength = 1;
			//
			//TODO: Add the constructor code here
			//
		}
		FastColoredTextBoxNS::AutocompleteMenu^ ACM;
		void SetAutoCompleteItems(System::Collections::Generic::List<AutocompleteItem^>^ items);
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~XEditor()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:

	protected:

	protected:
	private: DevExpress::XtraEditors::VScrollBar^  VScroller;
	private: DevExpress::XtraEditors::HScrollBar^  HScroller;
	private: DevExpress::XtraEditors::XtraUserControl^  CornerBlock;
	private:
		bool MovingVScrollBar = false;
	public: FastColoredTextBoxNS::FastColoredTextBox^  Editor;
	private: FastColoredTextBoxNS::DocumentMap^  documentMap1;
	public:
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(XEditor::typeid));
			this->VScroller = (gcnew DevExpress::XtraEditors::VScrollBar());
			this->HScroller = (gcnew DevExpress::XtraEditors::HScrollBar());
			this->CornerBlock = (gcnew DevExpress::XtraEditors::XtraUserControl());
			this->Editor = (gcnew FastColoredTextBoxNS::FastColoredTextBox());
			this->documentMap1 = (gcnew FastColoredTextBoxNS::DocumentMap());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Editor))->BeginInit();
			this->SuspendLayout();
			// 
			// VScroller
			// 
			this->VScroller->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->VScroller->Location = System::Drawing::Point(758, 0);
			this->VScroller->Name = L"VScroller";
			this->VScroller->Size = System::Drawing::Size(17, 583);
			this->VScroller->TabIndex = 1;
			this->VScroller->Click += gcnew System::EventHandler(this, &XEditor::VScroller_Click);
			// 
			// HScroller
			// 
			this->HScroller->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->HScroller->Location = System::Drawing::Point(0, 583);
			this->HScroller->Name = L"HScroller";
			this->HScroller->Size = System::Drawing::Size(758, 17);
			this->HScroller->TabIndex = 2;
			this->HScroller->Click += gcnew System::EventHandler(this, &XEditor::HScroller_Click);
			// 
			// CornerBlock
			// 
			this->CornerBlock->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->CornerBlock->Appearance->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(62)),
				static_cast<System::Int32>(static_cast<System::Byte>(62)), static_cast<System::Int32>(static_cast<System::Byte>(66)));
			this->CornerBlock->Appearance->Options->UseBackColor = true;
			this->CornerBlock->Location = System::Drawing::Point(758, 583);
			this->CornerBlock->Name = L"CornerBlock";
			this->CornerBlock->Size = System::Drawing::Size(17, 17);
			this->CornerBlock->TabIndex = 3;
			// 
			// Editor
			// 
			this->Editor->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Editor->AutoCompleteBrackets = true;
			this->Editor->AutoCompleteBracketsList = gcnew cli::array< System::Char >(10) {
				'(', ')', '{', '}', '[', ']', '\"', '\"', '\'',
					'\''
			};
			this->Editor->AutoScrollMinSize = System::Drawing::Size(70, 15);
			this->Editor->BackBrush = nullptr;
			this->Editor->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(30)));
			this->Editor->CaretColor = System::Drawing::Color::White;
			this->Editor->ChangedLineColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(30)));
			this->Editor->CharHeight = 15;
			this->Editor->CharWidth = 7;
			this->Editor->CurrentLineColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(6)), static_cast<System::Int32>(static_cast<System::Byte>(6)),
				static_cast<System::Int32>(static_cast<System::Byte>(6)));
			this->Editor->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->Editor->DescriptionFile = L"C:\\Users\\A\\Desktop\\GSX Studio\\GSX Studio\\GSXStyling.xml";
			this->Editor->DisabledColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(180)),
				static_cast<System::Int32>(static_cast<System::Byte>(180)), static_cast<System::Int32>(static_cast<System::Byte>(180)));
			this->Editor->FoldingIndicatorColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)),
				static_cast<System::Int32>(static_cast<System::Byte>(15)), static_cast<System::Int32>(static_cast<System::Byte>(15)));
			this->Editor->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F));
			this->Editor->ForeColor = System::Drawing::Color::Gainsboro;
			this->Editor->HighlightingRangeType = FastColoredTextBoxNS::HighlightingRangeType::VisibleRange;
			this->Editor->Hotkeys = resources->GetString(L"Editor.Hotkeys");
			this->Editor->IndentBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(30)));
			this->Editor->IsReplaceMode = false;
			this->Editor->LeftBracket = '{';
			this->Editor->LeftBracket2 = '(';
			this->Editor->LeftPadding = 30;
			this->Editor->LineNumberColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(43)), static_cast<System::Int32>(static_cast<System::Byte>(145)),
				static_cast<System::Int32>(static_cast<System::Byte>(175)));
			this->Editor->Location = System::Drawing::Point(0, 0);
			this->Editor->Name = L"Editor";
			this->Editor->Paddings = System::Windows::Forms::Padding(15, 0, 0, 0);
			this->Editor->RightBracket = '}';
			this->Editor->RightBracket2 = ')';
			this->Editor->SelectionColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(51)),
				static_cast<System::Int32>(static_cast<System::Byte>(153)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->Editor->ServiceColors = (cli::safe_cast<FastColoredTextBoxNS::ServiceColors^>(resources->GetObject(L"Editor.ServiceColors")));
			this->Editor->ShowFoldingLines = true;
			this->Editor->ShowScrollBars = false;
			this->Editor->Size = System::Drawing::Size(583, 583);
			this->Editor->TabIndex = 4;
			this->Editor->Zoom = 100;
			// 
			// documentMap1
			// 
			this->documentMap1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->documentMap1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(30)));
			this->documentMap1->Font = (gcnew System::Drawing::Font(L"Consolas", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->documentMap1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(30)));
			this->documentMap1->Location = System::Drawing::Point(583, 0);
			this->documentMap1->Name = L"documentMap1";
			this->documentMap1->ScrollbarVisible = false;
			this->documentMap1->Size = System::Drawing::Size(175, 583);
			this->documentMap1->TabIndex = 5;
			this->documentMap1->Target = this->Editor;
			// 
			// XEditor
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->documentMap1);
			this->Controls->Add(this->Editor);
			this->Controls->Add(this->CornerBlock);
			this->Controls->Add(this->HScroller);
			this->Controls->Add(this->VScroller);
			this->LookAndFeel->SkinName = L"Visual Studio 2013 Dark";
			this->LookAndFeel->UseDefaultLookAndFeel = false;
			this->Name = L"XEditor";
			this->Size = System::Drawing::Size(775, 600);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Editor))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void VScroller_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void HScroller_Click(System::Object^  sender, System::EventArgs^  e) {
	}
			 void OnDMMouseEnter(System::Object ^sender, System::EventArgs ^e);
			 void OnDMMouseLeave(System::Object ^sender, System::EventArgs ^e);
			 void OnTTDraw(System::Object ^sender, System::Windows::Forms::DrawToolTipEventArgs ^e);
			 void OnEClick(System::Object ^sender, System::EventArgs ^e);
};
}
