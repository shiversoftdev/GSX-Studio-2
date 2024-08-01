#pragma once
#include "GSXProject.h"

namespace GSX_Studio {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for EditProjectSettings
	/// </summary>
	public ref class EditProjectSettings : DevExpress::XtraEditors::XtraForm
	{
	public:
		EditProjectSettings(GSX_Studio::GSXProject^ project)
		{
			InitializeComponent();
			CreatorName->Text = project->CreatorName;
			Watermark->Text = project->Watermark;
			InlineMode->SelectedIndex = project->InlineState;
			TypestrictMode->SelectedIndex = project->TypeStrictState;
			Project = project;
		}
		GSX_Studio::GSXProject^ Project;
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~EditProjectSettings()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: DevExpress::XtraEditors::ComboBoxEdit^  InlineMode;
	private: DevExpress::XtraEditors::ComboBoxEdit^  TypestrictMode;
	protected:


	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: DevExpress::XtraEditors::TextEdit^  CreatorName;

	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::RichTextBox^  Watermark;

	private: DevExpress::XtraEditors::SimpleButton^  simpleButton1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->InlineMode = (gcnew DevExpress::XtraEditors::ComboBoxEdit());
			this->TypestrictMode = (gcnew DevExpress::XtraEditors::ComboBoxEdit());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->CreatorName = (gcnew DevExpress::XtraEditors::TextEdit());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->Watermark = (gcnew System::Windows::Forms::RichTextBox());
			this->simpleButton1 = (gcnew DevExpress::XtraEditors::SimpleButton());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->InlineMode->Properties))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TypestrictMode->Properties))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CreatorName->Properties))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 15);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(79, 16);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Inline Mode:";
			// 
			// InlineMode
			// 
			this->InlineMode->EditValue = L"Inline when possible";
			this->InlineMode->Location = System::Drawing::Point(154, 14);
			this->InlineMode->Name = L"InlineMode";
			this->InlineMode->Properties->Buttons->AddRange(gcnew cli::array< DevExpress::XtraEditors::Controls::EditorButton^  >(1) { (gcnew DevExpress::XtraEditors::Controls::EditorButton(DevExpress::XtraEditors::Controls::ButtonPredefines::Combo)) });
			this->InlineMode->Properties->Items->AddRange(gcnew cli::array< System::Object^  >(3) {
				L"Inline never", L"Inline when speficied",
					L"Inline when possible"
			});
			this->InlineMode->Properties->TextEditStyle = DevExpress::XtraEditors::Controls::TextEditStyles::DisableTextEditor;
			this->InlineMode->Size = System::Drawing::Size(253, 20);
			this->InlineMode->TabIndex = 1;
			// 
			// TypestrictMode
			// 
			this->TypestrictMode->EditValue = L"Context mode";
			this->TypestrictMode->Location = System::Drawing::Point(154, 40);
			this->TypestrictMode->Name = L"TypestrictMode";
			this->TypestrictMode->Properties->Buttons->AddRange(gcnew cli::array< DevExpress::XtraEditors::Controls::EditorButton^  >(1) { (gcnew DevExpress::XtraEditors::Controls::EditorButton(DevExpress::XtraEditors::Controls::ButtonPredefines::Combo)) });
			this->TypestrictMode->Properties->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"Never force types", L"Context Mode",
					L"All Returns", L"All Declarations"
			});
			this->TypestrictMode->Properties->TextEditStyle = DevExpress::XtraEditors::Controls::TextEditStyles::DisableTextEditor;
			this->TypestrictMode->Size = System::Drawing::Size(253, 20);
			this->TypestrictMode->TabIndex = 3;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(12, 41);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(104, 16);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Typestrict Mode:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(12, 67);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(93, 16);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Creator Name:";
			// 
			// CreatorName
			// 
			this->CreatorName->Location = System::Drawing::Point(154, 66);
			this->CreatorName->Name = L"CreatorName";
			this->CreatorName->Size = System::Drawing::Size(253, 20);
			this->CreatorName->TabIndex = 5;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(12, 93);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(77, 16);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Watermark:";
			// 
			// Watermark
			// 
			this->Watermark->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(30)));
			this->Watermark->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->Watermark->ForeColor = System::Drawing::Color::Gainsboro;
			this->Watermark->Location = System::Drawing::Point(154, 92);
			this->Watermark->Margin = System::Windows::Forms::Padding(9, 9, 3, 3);
			this->Watermark->Name = L"Watermark";
			this->Watermark->Size = System::Drawing::Size(253, 98);
			this->Watermark->TabIndex = 7;
			this->Watermark->Text = L"%projectname% by %creatorname%";
			// 
			// simpleButton1
			// 
			this->simpleButton1->Location = System::Drawing::Point(154, 197);
			this->simpleButton1->Name = L"simpleButton1";
			this->simpleButton1->Size = System::Drawing::Size(253, 28);
			this->simpleButton1->TabIndex = 8;
			this->simpleButton1->Text = L"Save Settings";
			this->simpleButton1->Click += gcnew System::EventHandler(this, &EditProjectSettings::simpleButton1_Click);
			// 
			// EditProjectSettings
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(419, 237);
			this->Controls->Add(this->simpleButton1);
			this->Controls->Add(this->Watermark);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->CreatorName);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->TypestrictMode);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->InlineMode);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->LookAndFeel->SkinName = L"Visual Studio 2013 Dark";
			this->LookAndFeel->UseDefaultLookAndFeel = false;
			this->Name = L"EditProjectSettings";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Project Settings";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->InlineMode->Properties))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TypestrictMode->Properties))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CreatorName->Properties))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void simpleButton1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		DialogResult = System::Windows::Forms::DialogResult::OK;
		Project->CreatorName = CreatorName->Text;
		Project->Watermark = Watermark->Text;
		Project->InlineState = InlineMode->SelectedIndex;
		Project->TypeStrictState = TypestrictMode->SelectedIndex;
		Close();
	}
};
}
