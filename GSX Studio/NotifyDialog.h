#pragma once

namespace GSX_Studio {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for NotifyDialog
	/// </summary>
	public ref class NotifyDialog : DevExpress::XtraEditors::XtraForm
	{
	public:
		NotifyDialog(void)
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
		~NotifyDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::RichTextBox^  Message;
	protected:

	private: DevExpress::XtraEditors::SimpleButton^  simpleButton1;
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
			this->Message = (gcnew System::Windows::Forms::RichTextBox());
			this->simpleButton1 = (gcnew DevExpress::XtraEditors::SimpleButton());
			this->SuspendLayout();
			// 
			// Message
			// 
			this->Message->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->Message->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->Message->Font = (gcnew System::Drawing::Font(L"Tahoma", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Message->ForeColor = System::Drawing::SystemColors::Window;
			this->Message->Location = System::Drawing::Point(12, 12);
			this->Message->Name = L"Message";
			this->Message->ReadOnly = true;
			this->Message->Size = System::Drawing::Size(354, 137);
			this->Message->TabIndex = 0;
			this->Message->Text = L"";
			// 
			// simpleButton1
			// 
			this->simpleButton1->Location = System::Drawing::Point(136, 155);
			this->simpleButton1->Name = L"simpleButton1";
			this->simpleButton1->Size = System::Drawing::Size(106, 34);
			this->simpleButton1->TabIndex = 1;
			this->simpleButton1->Text = L"OK";
			this->simpleButton1->Click += gcnew System::EventHandler(this, &NotifyDialog::simpleButton1_Click);
			// 
			// NotifyDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(378, 201);
			this->Controls->Add(this->simpleButton1);
			this->Controls->Add(this->Message);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->LookAndFeel->SkinName = L"Visual Studio 2013 Dark";
			this->LookAndFeel->UseDefaultLookAndFeel = false;
			this->Name = L"NotifyDialog";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Message";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void simpleButton1_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		Close();
	}
	};
}
