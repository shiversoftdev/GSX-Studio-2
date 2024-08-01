#pragma once

namespace GSX_Studio {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for DeleteConfirmationDialog
	/// </summary>
	public ref class DeleteConfirmationDialog : DevExpress::XtraEditors::XtraForm
	{
	public:
		DeleteConfirmationDialog(void)
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
		~DeleteConfirmationDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	public: DevExpress::XtraEditors::LabelControl^  Message;
	protected:

	public: DevExpress::XtraEditors::CheckEdit^  DeleteFile;
	private:
	private: DevExpress::XtraEditors::SimpleButton^  simpleButton1;
	public:
	private: DevExpress::XtraEditors::SimpleButton^  simpleButton2;
	private: DevExpress::XtraEditors::SimpleButton^  simpleButton3;
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
			this->Message = (gcnew DevExpress::XtraEditors::LabelControl());
			this->DeleteFile = (gcnew DevExpress::XtraEditors::CheckEdit());
			this->simpleButton1 = (gcnew DevExpress::XtraEditors::SimpleButton());
			this->simpleButton2 = (gcnew DevExpress::XtraEditors::SimpleButton());
			this->simpleButton3 = (gcnew DevExpress::XtraEditors::SimpleButton());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DeleteFile->Properties))->BeginInit();
			this->SuspendLayout();
			// 
			// Message
			// 
			this->Message->Appearance->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Message->Location = System::Drawing::Point(12, 12);
			this->Message->Name = L"Message";
			this->Message->Size = System::Drawing::Size(339, 16);
			this->Message->TabIndex = 0;
			this->Message->Text = L"Are you sure you want to remove this file from the project\?";
			// 
			// DeleteFile
			// 
			this->DeleteFile->EditValue = true;
			this->DeleteFile->Location = System::Drawing::Point(276, 91);
			this->DeleteFile->Name = L"DeleteFile";
			this->DeleteFile->Properties->Caption = L"Delete File";
			this->DeleteFile->Size = System::Drawing::Size(75, 19);
			this->DeleteFile->TabIndex = 1;
			// 
			// simpleButton1
			// 
			this->simpleButton1->Location = System::Drawing::Point(26, 49);
			this->simpleButton1->Name = L"simpleButton1";
			this->simpleButton1->Size = System::Drawing::Size(98, 36);
			this->simpleButton1->TabIndex = 2;
			this->simpleButton1->Text = L"Yes";
			this->simpleButton1->Click += gcnew System::EventHandler(this, &DeleteConfirmationDialog::simpleButton1_Click);
			// 
			// simpleButton2
			// 
			this->simpleButton2->Location = System::Drawing::Point(130, 49);
			this->simpleButton2->Name = L"simpleButton2";
			this->simpleButton2->Size = System::Drawing::Size(98, 36);
			this->simpleButton2->TabIndex = 3;
			this->simpleButton2->Text = L"No";
			this->simpleButton2->Click += gcnew System::EventHandler(this, &DeleteConfirmationDialog::simpleButton2_Click);
			// 
			// simpleButton3
			// 
			this->simpleButton3->Location = System::Drawing::Point(234, 49);
			this->simpleButton3->Name = L"simpleButton3";
			this->simpleButton3->Size = System::Drawing::Size(98, 36);
			this->simpleButton3->TabIndex = 4;
			this->simpleButton3->Text = L"Cancel";
			this->simpleButton3->Click += gcnew System::EventHandler(this, &DeleteConfirmationDialog::simpleButton3_Click);
			// 
			// DeleteConfirmationDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(365, 120);
			this->Controls->Add(this->simpleButton3);
			this->Controls->Add(this->simpleButton2);
			this->Controls->Add(this->simpleButton1);
			this->Controls->Add(this->DeleteFile);
			this->Controls->Add(this->Message);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->LookAndFeel->SkinName = L"Visual Studio 2013 Dark";
			this->LookAndFeel->UseDefaultLookAndFeel = false;
			this->Name = L"DeleteConfirmationDialog";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Confirm";
			this->Load += gcnew System::EventHandler(this, &DeleteConfirmationDialog::DeleteConfirmationDialog_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DeleteFile->Properties))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void DeleteConfirmationDialog_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void simpleButton1_Click(System::Object^  sender, System::EventArgs^  e) {
		DialogResult = System::Windows::Forms::DialogResult::Yes;
		Close();
	}
private: System::Void simpleButton2_Click(System::Object^  sender, System::EventArgs^  e) {
	Close();
}
private: System::Void simpleButton3_Click(System::Object^  sender, System::EventArgs^  e) {
	Close();
}
};
}
