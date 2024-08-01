#pragma once

namespace GSX_Studio {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for XPlatformMemory
	/// </summary>
	public ref class XPlatformMemory : public DevExpress::XtraEditors::XtraForm
	{
	public:
		XPlatformMemory(void)
		{
			DevExpress::Skins::SkinManager::EnableFormSkins();
			DevExpress::UserSkins::BonusSkins::Register();
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~XPlatformMemory()
		{
			if (components)
			{
				delete components;
			}
		}
	private: DevExpress::XtraEditors::GroupControl^  groupControl1;
	protected:
	private: DevExpress::XtraEditors::GroupControl^  groupControl2;
	private: DevExpress::XtraEditors::TextEdit^  SetTarget;

	private: DevExpress::XtraEditors::LabelControl^  labelControl1;
	private: DevExpress::XtraEditors::TextEdit^  textEdit2;
	private: DevExpress::XtraEditors::LabelControl^  labelControl2;
	private: DevExpress::XtraEditors::ComboBoxEdit^  SetType;

	private: DevExpress::XtraEditors::TextEdit^  SetTargetValue;

	private: DevExpress::XtraEditors::LabelControl^  labelControl3;
	private: DevExpress::XtraEditors::LabelControl^  labelControl4;
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
			this->groupControl1 = (gcnew DevExpress::XtraEditors::GroupControl());
			this->groupControl2 = (gcnew DevExpress::XtraEditors::GroupControl());
			this->SetTarget = (gcnew DevExpress::XtraEditors::TextEdit());
			this->labelControl1 = (gcnew DevExpress::XtraEditors::LabelControl());
			this->textEdit2 = (gcnew DevExpress::XtraEditors::TextEdit());
			this->labelControl2 = (gcnew DevExpress::XtraEditors::LabelControl());
			this->SetTargetValue = (gcnew DevExpress::XtraEditors::TextEdit());
			this->SetType = (gcnew DevExpress::XtraEditors::ComboBoxEdit());
			this->labelControl3 = (gcnew DevExpress::XtraEditors::LabelControl());
			this->labelControl4 = (gcnew DevExpress::XtraEditors::LabelControl());
			this->simpleButton1 = (gcnew DevExpress::XtraEditors::SimpleButton());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->groupControl1))->BeginInit();
			this->groupControl1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->groupControl2))->BeginInit();
			this->groupControl2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SetTarget->Properties))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->textEdit2->Properties))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SetTargetValue->Properties))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SetType->Properties))->BeginInit();
			this->SuspendLayout();
			// 
			// groupControl1
			// 
			this->groupControl1->Controls->Add(this->textEdit2);
			this->groupControl1->Controls->Add(this->labelControl2);
			this->groupControl1->Location = System::Drawing::Point(12, 12);
			this->groupControl1->Name = L"groupControl1";
			this->groupControl1->Size = System::Drawing::Size(560, 222);
			this->groupControl1->TabIndex = 1;
			this->groupControl1->Text = L"Get";
			// 
			// groupControl2
			// 
			this->groupControl2->Controls->Add(this->simpleButton1);
			this->groupControl2->Controls->Add(this->labelControl4);
			this->groupControl2->Controls->Add(this->labelControl3);
			this->groupControl2->Controls->Add(this->SetType);
			this->groupControl2->Controls->Add(this->SetTargetValue);
			this->groupControl2->Controls->Add(this->SetTarget);
			this->groupControl2->Controls->Add(this->labelControl1);
			this->groupControl2->Location = System::Drawing::Point(12, 240);
			this->groupControl2->Name = L"groupControl2";
			this->groupControl2->Size = System::Drawing::Size(560, 109);
			this->groupControl2->TabIndex = 2;
			this->groupControl2->Text = L"Set";
			// 
			// SetTarget
			// 
			this->SetTarget->Location = System::Drawing::Point(159, 21);
			this->SetTarget->Name = L"SetTarget";
			this->SetTarget->Properties->AllowNullInput = DevExpress::Utils::DefaultBoolean::False;
			this->SetTarget->Properties->Appearance->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->SetTarget->Properties->Appearance->Options->UseFont = true;
			this->SetTarget->Properties->Appearance->Options->UseTextOptions = true;
			this->SetTarget->Properties->Appearance->TextOptions->HAlignment = DevExpress::Utils::HorzAlignment::Center;
			this->SetTarget->Properties->Appearance->TextOptions->VAlignment = DevExpress::Utils::VertAlignment::Center;
			this->SetTarget->Properties->DisplayFormat->FormatString = L"0x[0-9A-F]{8}";
			this->SetTarget->Properties->DisplayFormat->FormatType = DevExpress::Utils::FormatType::Custom;
			this->SetTarget->Properties->EditFormat->FormatString = L"0x[0-9A-F]{8}";
			this->SetTarget->Properties->EditFormat->FormatType = DevExpress::Utils::FormatType::Custom;
			this->SetTarget->Properties->Mask->BeepOnError = true;
			this->SetTarget->Properties->Mask->EditMask = L"0x[0-9A-Fa-f]{8}";
			this->SetTarget->Properties->Mask->MaskType = DevExpress::XtraEditors::Mask::MaskType::RegEx;
			this->SetTarget->Properties->MaxLength = 10;
			this->SetTarget->Properties->NullText = L"0x00000000";
			this->SetTarget->Properties->ValidateOnEnterKey = true;
			this->SetTarget->Size = System::Drawing::Size(152, 22);
			this->SetTarget->TabIndex = 1;
			// 
			// labelControl1
			// 
			this->labelControl1->Appearance->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelControl1->Location = System::Drawing::Point(16, 24);
			this->labelControl1->Name = L"labelControl1";
			this->labelControl1->Size = System::Drawing::Size(98, 15);
			this->labelControl1->TabIndex = 0;
			this->labelControl1->Text = L"Target Address";
			// 
			// textEdit2
			// 
			this->textEdit2->Location = System::Drawing::Point(18, 45);
			this->textEdit2->Name = L"textEdit2";
			this->textEdit2->Properties->AllowNullInput = DevExpress::Utils::DefaultBoolean::False;
			this->textEdit2->Properties->Appearance->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->textEdit2->Properties->Appearance->Options->UseFont = true;
			this->textEdit2->Properties->Appearance->Options->UseTextOptions = true;
			this->textEdit2->Properties->Appearance->TextOptions->HAlignment = DevExpress::Utils::HorzAlignment::Center;
			this->textEdit2->Properties->Appearance->TextOptions->VAlignment = DevExpress::Utils::VertAlignment::Center;
			this->textEdit2->Properties->DisplayFormat->FormatString = L"0x[0-9A-F]{8}";
			this->textEdit2->Properties->DisplayFormat->FormatType = DevExpress::Utils::FormatType::Custom;
			this->textEdit2->Properties->EditFormat->FormatString = L"0x[0-9A-F]{8}";
			this->textEdit2->Properties->EditFormat->FormatType = DevExpress::Utils::FormatType::Custom;
			this->textEdit2->Properties->Mask->BeepOnError = true;
			this->textEdit2->Properties->Mask->EditMask = L"0x[0-9A-Fa-f]{8}";
			this->textEdit2->Properties->Mask->MaskType = DevExpress::XtraEditors::Mask::MaskType::RegEx;
			this->textEdit2->Properties->MaxLength = 10;
			this->textEdit2->Properties->NullText = L"0x00000000";
			this->textEdit2->Properties->ValidateOnEnterKey = true;
			this->textEdit2->Size = System::Drawing::Size(100, 22);
			this->textEdit2->TabIndex = 3;
			// 
			// labelControl2
			// 
			this->labelControl2->Appearance->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelControl2->Location = System::Drawing::Point(20, 24);
			this->labelControl2->Name = L"labelControl2";
			this->labelControl2->Size = System::Drawing::Size(98, 15);
			this->labelControl2->TabIndex = 2;
			this->labelControl2->Text = L"Target Address";
			// 
			// SetTargetValue
			// 
			this->SetTargetValue->EditValue = L"0x0000000000000000";
			this->SetTargetValue->Location = System::Drawing::Point(159, 49);
			this->SetTargetValue->Name = L"SetTargetValue";
			this->SetTargetValue->Properties->AllowNullInput = DevExpress::Utils::DefaultBoolean::False;
			this->SetTargetValue->Properties->Appearance->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->SetTargetValue->Properties->Appearance->Options->UseFont = true;
			this->SetTargetValue->Properties->Appearance->Options->UseTextOptions = true;
			this->SetTargetValue->Properties->Appearance->TextOptions->HAlignment = DevExpress::Utils::HorzAlignment::Center;
			this->SetTargetValue->Properties->Appearance->TextOptions->VAlignment = DevExpress::Utils::VertAlignment::Center;
			this->SetTargetValue->Properties->DisplayFormat->FormatString = L"0x[0-9A-F]{8}";
			this->SetTargetValue->Properties->DisplayFormat->FormatType = DevExpress::Utils::FormatType::Custom;
			this->SetTargetValue->Properties->EditFormat->FormatString = L"0x[0-9A-F]{8}";
			this->SetTargetValue->Properties->EditFormat->FormatType = DevExpress::Utils::FormatType::Custom;
			this->SetTargetValue->Properties->Mask->BeepOnError = true;
			this->SetTargetValue->Properties->Mask->EditMask = L"0x[0-9A-Fa-f]{8}";
			this->SetTargetValue->Properties->Mask->MaskType = DevExpress::XtraEditors::Mask::MaskType::RegEx;
			this->SetTargetValue->Properties->MaxLength = 10;
			this->SetTargetValue->Properties->NullText = L"0x00000000";
			this->SetTargetValue->Properties->ValidateOnEnterKey = true;
			this->SetTargetValue->Size = System::Drawing::Size(152, 22);
			this->SetTargetValue->TabIndex = 2;
			// 
			// SetType
			// 
			this->SetType->EditValue = L"DWORD";
			this->SetType->Location = System::Drawing::Point(159, 77);
			this->SetType->Name = L"SetType";
			this->SetType->Properties->Appearance->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F));
			this->SetType->Properties->Appearance->Options->UseFont = true;
			this->SetType->Properties->Appearance->Options->UseTextOptions = true;
			this->SetType->Properties->Appearance->TextOptions->HAlignment = DevExpress::Utils::HorzAlignment::Center;
			this->SetType->Properties->Appearance->TextOptions->VAlignment = DevExpress::Utils::VertAlignment::Center;
			this->SetType->Properties->Buttons->AddRange(gcnew cli::array< DevExpress::XtraEditors::Controls::EditorButton^  >(1) { (gcnew DevExpress::XtraEditors::Controls::EditorButton(DevExpress::XtraEditors::Controls::ButtonPredefines::Combo)) });
			this->SetType->Properties->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"BYTE", L"WORD", L"DWORD", L"QWORD",
					L"LOAD"
			});
			this->SetType->Properties->TextEditStyle = DevExpress::XtraEditors::Controls::TextEditStyles::DisableTextEditor;
			this->SetType->Size = System::Drawing::Size(152, 22);
			this->SetType->TabIndex = 3;
			this->SetType->SelectedIndexChanged += gcnew System::EventHandler(this, &XPlatformMemory::comboBoxEdit1_SelectedIndexChanged);
			// 
			// labelControl3
			// 
			this->labelControl3->Appearance->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelControl3->Location = System::Drawing::Point(16, 52);
			this->labelControl3->Name = L"labelControl3";
			this->labelControl3->Size = System::Drawing::Size(84, 15);
			this->labelControl3->TabIndex = 4;
			this->labelControl3->Text = L"Target Value";
			// 
			// labelControl4
			// 
			this->labelControl4->Appearance->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelControl4->Location = System::Drawing::Point(16, 80);
			this->labelControl4->Name = L"labelControl4";
			this->labelControl4->Size = System::Drawing::Size(77, 15);
			this->labelControl4->TabIndex = 5;
			this->labelControl4->Text = L"Target Type";
			// 
			// simpleButton1
			// 
			this->simpleButton1->Location = System::Drawing::Point(480, 76);
			this->simpleButton1->Name = L"simpleButton1";
			this->simpleButton1->Size = System::Drawing::Size(75, 23);
			this->simpleButton1->TabIndex = 6;
			this->simpleButton1->Text = L"simpleButton1";
			// 
			// XPlatformMemory
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(584, 361);
			this->Controls->Add(this->groupControl2);
			this->Controls->Add(this->groupControl1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->LookAndFeel->SkinName = L"Visual Studio 2013 Dark";
			this->LookAndFeel->UseDefaultLookAndFeel = false;
			this->Name = L"XPlatformMemory";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Memory Editing";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->groupControl1))->EndInit();
			this->groupControl1->ResumeLayout(false);
			this->groupControl1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->groupControl2))->EndInit();
			this->groupControl2->ResumeLayout(false);
			this->groupControl2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SetTarget->Properties))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->textEdit2->Properties))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SetTargetValue->Properties))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SetType->Properties))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void comboBoxEdit1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	}
};
}
