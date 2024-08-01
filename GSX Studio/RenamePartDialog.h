#pragma once

namespace GSX_Studio {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for RenamePartDialog
	/// </summary>
	public ref class RenamePartDialog : DevExpress::XtraEditors::XtraForm
	{
	public:
		RenamePartDialog(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~RenamePartDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: DevExpress::XtraEditors::LabelControl^  labelControl1;
	public: DevExpress::XtraEditors::TextEdit^  CValue;
	private:
	private: DevExpress::XtraEditors::SimpleButton^  simpleButton1;
	public:
	private: DevExpress::XtraEditors::SimpleButton^  simpleButton2;
	protected:

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
			this->labelControl1 = (gcnew DevExpress::XtraEditors::LabelControl());
			this->CValue = (gcnew DevExpress::XtraEditors::TextEdit());
			this->simpleButton1 = (gcnew DevExpress::XtraEditors::SimpleButton());
			this->simpleButton2 = (gcnew DevExpress::XtraEditors::SimpleButton());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CValue->Properties))->BeginInit();
			this->SuspendLayout();
			// 
			// labelControl1
			// 
			this->labelControl1->Appearance->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelControl1->Location = System::Drawing::Point(12, 12);
			this->labelControl1->Name = L"labelControl1";
			this->labelControl1->Size = System::Drawing::Size(62, 16);
			this->labelControl1->TabIndex = 0;
			this->labelControl1->Text = L"File Name:";
			// 
			// CValue
			// 
			this->CValue->EditValue = L"main.gsx";
			this->CValue->Location = System::Drawing::Point(119, 12);
			this->CValue->Name = L"CValue";
			this->CValue->Properties->Mask->EditMask = L"[^\\.]+\\.gsx";
			this->CValue->Properties->Mask->MaskType = DevExpress::XtraEditors::Mask::MaskType::RegEx;
			this->CValue->Properties->Mask->ShowPlaceHolders = false;
			this->CValue->Size = System::Drawing::Size(214, 20);
			this->CValue->TabIndex = 1;
			// 
			// simpleButton1
			// 
			this->simpleButton1->Location = System::Drawing::Point(119, 38);
			this->simpleButton1->Name = L"simpleButton1";
			this->simpleButton1->Size = System::Drawing::Size(104, 29);
			this->simpleButton1->TabIndex = 2;
			this->simpleButton1->Text = L"OK";
			this->simpleButton1->Click += gcnew System::EventHandler(this, &RenamePartDialog::simpleButton1_Click);
			// 
			// simpleButton2
			// 
			this->simpleButton2->Location = System::Drawing::Point(229, 38);
			this->simpleButton2->Name = L"simpleButton2";
			this->simpleButton2->Size = System::Drawing::Size(104, 29);
			this->simpleButton2->TabIndex = 3;
			this->simpleButton2->Text = L"Cancel";
			this->simpleButton2->Click += gcnew System::EventHandler(this, &RenamePartDialog::simpleButton2_Click);
			// 
			// RenamePartDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(352, 83);
			this->Controls->Add(this->simpleButton2);
			this->Controls->Add(this->simpleButton1);
			this->Controls->Add(this->CValue);
			this->Controls->Add(this->labelControl1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->LookAndFeel->SkinName = L"Visual Studio 2013 Dark";
			this->LookAndFeel->UseDefaultLookAndFeel = false;
			this->Name = L"RenamePartDialog";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Rename File";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CValue->Properties))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void simpleButton1_Click(System::Object^  sender, System::EventArgs^  e) {
		DialogResult = System::Windows::Forms::DialogResult::OK;
		Close();
	}
private: System::Void simpleButton2_Click(System::Object^  sender, System::EventArgs^  e) {
	Close();
}
};
}
