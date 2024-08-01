#pragma once
namespace GSX_Studio
{
	using namespace System;
	using namespace System::Collections::Generic;
	using namespace System::ComponentModel;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text;
	using namespace System::Windows::Forms;
	using namespace DevExpress::XtraWaitForm;

	public ref class WaitForm1 : WaitForm
	{
	public:
		void InitializeComponent();

		WaitForm1()
		{
			InitializeComponent();

			this->progressPanel1->AutoHeight = true;
		}

		virtual void SetCaption(System::String^ caption) override;

		virtual void SetDescription(System::String^ description) override;
		
		virtual void ProcessCommand(System::Enum^, System::String^ arg) override;
	

		DevExpress::LookAndFeel::UserLookAndFeel^ mlookAndFeel;
	protected:
		property DevExpress::LookAndFeel::UserLookAndFeel^ TargetLookAndFeel
		{
			DevExpress::LookAndFeel::UserLookAndFeel^ get() override
			{
				if (!mlookAndFeel)
				{
					mlookAndFeel = gcnew DevExpress::LookAndFeel::UserLookAndFeel(this);
					mlookAndFeel->UseDefaultLookAndFeel = false;
					mlookAndFeel->SkinName = "Visual Studio 2013 Dark";
				}
				return mlookAndFeel;
			}
		}
		~WaitForm1()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::IContainer^ components = nullptr;
		DevExpress::XtraWaitForm::ProgressPanel^ progressPanel1;
		System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;


	};
}