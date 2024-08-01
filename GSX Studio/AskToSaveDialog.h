#pragma once

namespace GSX_Studio {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for AskToSaveDialog
	/// </summary>
	public ref class AskToSaveDialog : DevExpress::XtraEditors::XtraForm
	{
	public:
		AskToSaveDialog(void)
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
		~AskToSaveDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: DevExpress::XtraEditors::LabelControl^  labelControl1;
	protected:
	private: DevExpress::XtraEditors::SimpleButton^  simpleButton1;
	private: DevExpress::XtraEditors::SimpleButton^  simpleButton2;
	private: DevExpress::XtraEditors::SimpleButton^  simpleButton3;

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
			this->simpleButton1 = (gcnew DevExpress::XtraEditors::SimpleButton());
			this->simpleButton2 = (gcnew DevExpress::XtraEditors::SimpleButton());
			this->simpleButton3 = (gcnew DevExpress::XtraEditors::SimpleButton());
			this->SuspendLayout();
			// 
			// labelControl1
			// 
			this->labelControl1->Appearance->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelControl1->Location = System::Drawing::Point(12, 25);
			this->labelControl1->Name = L"labelControl1";
			this->labelControl1->Size = System::Drawing::Size(315, 16);
			this->labelControl1->TabIndex = 0;
			this->labelControl1->Text = L"Save current project\? All unsaved progress will be lost!";
			// 
			// simpleButton1
			// 
			this->simpleButton1->Location = System::Drawing::Point(12, 73);
			this->simpleButton1->Name = L"simpleButton1";
			this->simpleButton1->Size = System::Drawing::Size(104, 32);
			this->simpleButton1->TabIndex = 1;
			this->simpleButton1->Text = L"Yes";
			this->simpleButton1->Click += gcnew System::EventHandler(this, &AskToSaveDialog::simpleButton1_Click);
			// 
			// simpleButton2
			// 
			this->simpleButton2->Location = System::Drawing::Point(122, 73);
			this->simpleButton2->Name = L"simpleButton2";
			this->simpleButton2->Size = System::Drawing::Size(104, 32);
			this->simpleButton2->TabIndex = 2;
			this->simpleButton2->Text = L"No";
			this->simpleButton2->Click += gcnew System::EventHandler(this, &AskToSaveDialog::simpleButton2_Click);
			// 
			// simpleButton3
			// 
			this->simpleButton3->Location = System::Drawing::Point(232, 73);
			this->simpleButton3->Name = L"simpleButton3";
			this->simpleButton3->Size = System::Drawing::Size(104, 32);
			this->simpleButton3->TabIndex = 3;
			this->simpleButton3->Text = L"Cancel";
			this->simpleButton3->Click += gcnew System::EventHandler(this, &AskToSaveDialog::simpleButton3_Click);
			// 
			// AskToSaveDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(348, 117);
			this->Controls->Add(this->simpleButton3);
			this->Controls->Add(this->simpleButton2);
			this->Controls->Add(this->simpleButton1);
			this->Controls->Add(this->labelControl1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->LookAndFeel->SkinName = L"Visual Studio 2013 Dark";
			this->LookAndFeel->UseDefaultLookAndFeel = false;
			this->Name = L"AskToSaveDialog";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Save Current Project\?";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void simpleButton1_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		DialogResult = System::Windows::Forms::DialogResult::Yes;
		Close();
	}
	private: System::Void simpleButton2_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		DialogResult = System::Windows::Forms::DialogResult::No;
		Close();
	}
	private: System::Void simpleButton3_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		Close();
	}
};
}
