#pragma once
#include "XLState.h"

namespace XParserLib
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace DevExpress;

	public ref class XLNonTerminal
	{

	public:
		System::String^ Name;

		XLNonTerminal()
		{
			Name = "unknown";
		}
		XLNonTerminal(System::String^ name)
		{
			Name = name;
		}

		XLState^ Rule;

		static XLNonTerminal^ GetDefaultProgram();
	};
}