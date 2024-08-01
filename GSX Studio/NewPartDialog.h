#pragma once

namespace GSX_Studio {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for NewPartDialog
	/// </summary>
	public ref class NewPartDialog : DevExpress::XtraEditors::XtraForm
	{
	public:
		NewPartDialog(void)
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
		~NewPartDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	public: DevExpress::XtraEditors::TextEdit^  FileName;
	private:
	public: DevExpress::XtraEditors::TextEdit^  Description;


	protected:


	private: System::Windows::Forms::Label^  label2;
	private: DevExpress::XtraEditors::SimpleButton^  simpleButton1;
	public: DevExpress::XtraEditors::CheckEdit^  DefaultCode;
	private:




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
			this->FileName = (gcnew DevExpress::XtraEditors::TextEdit());
			this->Description = (gcnew DevExpress::XtraEditors::TextEdit());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->simpleButton1 = (gcnew DevExpress::XtraEditors::SimpleButton());
			this->DefaultCode = (gcnew DevExpress::XtraEditors::CheckEdit());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->FileName->Properties))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Description->Properties))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DefaultCode->Properties))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 15);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(57, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"File Name:";
			this->label1->Click += gcnew System::EventHandler(this, &NewPartDialog::label1_Click);
			// 
			// FileName
			// 
			this->FileName->Location = System::Drawing::Point(102, 12);
			this->FileName->Name = L"FileName";
			this->FileName->Size = System::Drawing::Size(273, 20);
			this->FileName->TabIndex = 1;
			this->FileName->EditValueChanged += gcnew System::EventHandler(this, &NewPartDialog::textEdit1_EditValueChanged);
			// 
			// Description
			// 
			this->Description->Location = System::Drawing::Point(102, 38);
			this->Description->Name = L"Description";
			this->Description->Size = System::Drawing::Size(273, 20);
			this->Description->TabIndex = 3;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 41);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(64, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Description:";
			// 
			// simpleButton1
			// 
			this->simpleButton1->Location = System::Drawing::Point(102, 64);
			this->simpleButton1->Name = L"simpleButton1";
			this->simpleButton1->Size = System::Drawing::Size(113, 36);
			this->simpleButton1->TabIndex = 4;
			this->simpleButton1->Text = L"Create";
			this->simpleButton1->Click += gcnew System::EventHandler(this, &NewPartDialog::simpleButton1_Click);
			// 
			// DefaultCode
			// 
			this->DefaultCode->EditValue = true;
			this->DefaultCode->Location = System::Drawing::Point(236, 72);
			this->DefaultCode->Name = L"DefaultCode";
			this->DefaultCode->Properties->Caption = L"Include Default Code";
			this->DefaultCode->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->DefaultCode->Size = System::Drawing::Size(129, 19);
			this->DefaultCode->TabIndex = 5;
			this->DefaultCode->CheckedChanged += gcnew System::EventHandler(this, &NewPartDialog::checkEdit1_CheckedChanged);
			// 
			// NewPartDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(387, 112);
			this->Controls->Add(this->DefaultCode);
			this->Controls->Add(this->simpleButton1);
			this->Controls->Add(this->Description);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->FileName);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->LookAndFeel->SkinName = L"Visual Studio 2013 Dark";
			this->LookAndFeel->UseDefaultLookAndFeel = false;
			this->Name = L"NewPartDialog";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"New Script File";
			this->Load += gcnew System::EventHandler(this, &NewPartDialog::NewPartDialog_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->FileName->Properties))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Description->Properties))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DefaultCode->Properties))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void NewPartDialog_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textEdit1_EditValueChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void checkEdit1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void simpleButton1_Click(System::Object^  sender, System::EventArgs^  e) {
	DialogResult = System::Windows::Forms::DialogResult::OK;
	Close();
}
};
}
