#pragma once
#include "GSCScript.h"

namespace GSX_Studio
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace DevExpress;

	public ref class GSXProject
	{
	public:

		GSXProject()
		{
		}

		String^ ProjectName;
		String^ CreatorName;
		String^ SourceLocation;
		Byte NumberOfScripts;
		Generic::List<GSCScript^> ^ProjectFiles = gcnew Generic::List<GSCScript^>();
		bool Unsaved = false;
		void UpdateModified(void);
		System::Byte TypeStrictState;
		System::Byte InlineState;
		bool Debug;
		System::String^ Watermark;

	public:
		static System::String^ GetDefaultProjectCode(System::String^ Creator, System::String^ ProjectName);
		static GSXProject^ LoadProject(System::String^ FileName);
		static GSXProject^ CreateProject(System::String^ ProjectName, System::String^ CreatorName, System::String^ Description, System::String^ PathLocation, System::String^ ScriptName);
	};
}