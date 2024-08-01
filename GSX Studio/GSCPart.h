#pragma once
#include "XParseTree.h"
#include "XParser.h"

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
	using namespace Irony::Parsing;
	public ref class GSCPart
	{
	public:

		GSCPart(System::String^ Code, System::String^ name)
		{
			Contents = Code;
			Name = name;
		}
		void LoadCache(Irony::Parsing::Parser^ Parser);
		void SetCache(Irony::Parsing::Parser^ Parser, System::String^ filename, System::String^ cts);
		System::Collections::Generic::List<FastColoredTextBoxNS::AutocompleteItem^>^ GetFunctionsList();
		bool Modified;
		String^ Name;
		String^ Contents;
		ParseTree^ Tree;
		System::Collections::Generic::List<FastColoredTextBoxNS::AutocompleteItem^>^ FunctionsACList = gcnew System::Collections::Generic::List<FastColoredTextBoxNS::AutocompleteItem^>();
	};
}