#include "WaitForm1.h"

void GSX_Studio::WaitForm1::InitializeComponent()
{
	this->progressPanel1 = gcnew DevExpress::XtraWaitForm::ProgressPanel();
	this->tableLayoutPanel1 = gcnew System::Windows::Forms::TableLayoutPanel();
	this->tableLayoutPanel1->SuspendLayout();
	this->SuspendLayout();
	// 
	// progressPanel1
	// 
	this->progressPanel1->Appearance->BackColor = System::Drawing::Color::Transparent;
	this->progressPanel1->Appearance->Options->UseBackColor = true;
	this->progressPanel1->AppearanceCaption->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 12);
	this->progressPanel1->AppearanceCaption->ForeColor = System::Drawing::SystemColors::Menu;
	this->progressPanel1->AppearanceCaption->Options->UseFont = true;
	this->progressPanel1->AppearanceCaption->Options->UseForeColor = true;
	this->progressPanel1->AppearanceDescription->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 8.25);
	this->progressPanel1->AppearanceDescription->ForeColor = System::Drawing::SystemColors::Menu;
	this->progressPanel1->AppearanceDescription->Options->UseFont = true;
	this->progressPanel1->AppearanceDescription->Options->UseForeColor = true;
	this->progressPanel1->BorderStyle = DevExpress::XtraEditors::Controls::BorderStyles::NoBorder;
	this->progressPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
	this->progressPanel1->ImageHorzOffset = 20;
	this->progressPanel1->Location = System::Drawing::Point(0, 17);
	this->progressPanel1->LookAndFeel->SkinName = "Visual Studio 2013 Dark";
	this->progressPanel1->LookAndFeel->UseDefaultLookAndFeel = false;
	this->progressPanel1->Margin = System::Windows::Forms::Padding(0, 3, 0, 3);
	this->progressPanel1->Name = "progressPanel1";
	this->progressPanel1->Size = System::Drawing::Size(246, 39);
	this->progressPanel1->TabIndex = 0;
	this->progressPanel1->Text = "progressPanel1";
	// 
	// tableLayoutPanel1
	// 
	this->tableLayoutPanel1->AutoSize = true;
	this->tableLayoutPanel1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
	this->tableLayoutPanel1->BackColor = System::Drawing::Color::Transparent;
	this->tableLayoutPanel1->ColumnCount = 1;
	this->tableLayoutPanel1->ColumnStyles->Add(gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100));
	this->tableLayoutPanel1->Controls->Add(this->progressPanel1, 0, 0);
	this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
	this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
	this->tableLayoutPanel1->Name = "tableLayoutPanel1";
	this->tableLayoutPanel1->Padding = System::Windows::Forms::Padding(0, 14, 0, 14);
	this->tableLayoutPanel1->RowCount = 1;
	this->tableLayoutPanel1->RowStyles->Add(gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100));
	this->tableLayoutPanel1->Size = System::Drawing::Size(246, 73);
	this->tableLayoutPanel1->TabIndex = 1;
	// 
	// WaitForm1
	// 
	this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->AutoSize = true;
	this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
	this->ClientSize = System::Drawing::Size(246, 73);
	this->Controls->Add(this->tableLayoutPanel1);
	this->DoubleBuffered = true;
	this->Name = "WaitForm1";
	this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
	this->Text = "Form1";
	this->tableLayoutPanel1->ResumeLayout(false);
	this->ResumeLayout(false);
	this->PerformLayout();
}

void GSX_Studio::WaitForm1::SetCaption(System::String ^ caption)
{
	WaitForm::SetCaption(caption);
	this->progressPanel1->Caption = caption;
}

void GSX_Studio::WaitForm1::SetDescription(System::String ^ description)
{
	WaitForm::SetDescription(description);
	this->progressPanel1->Description = description;
}

void GSX_Studio::WaitForm1::ProcessCommand(System::Enum^ cmd, System::String ^ arg)
{
	WaitForm::ProcessCommand(cmd, arg);
}