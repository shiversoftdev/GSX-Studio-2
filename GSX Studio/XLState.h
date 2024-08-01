#pragma once
#include "XLNonTerminal.h"

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

	public ref class XLState
	{

	public:
		Generic::List<XLState^>^ Terms = gcnew Generic::List<XLState^>();
		bool Match(System::String^);

		XLState(int Type) //Identifier|Number|Comment
		{
			UsingStaticValue = false;
			IsTerminal = true;
			TerminalType = Type;
		}

		XLState(System::String^ staticvalue) //Keyword|Operator
		{
			UsingStaticValue = true;
			StaticValue = staticvalue;
			IsTerminal = true;
			TerminalType = KEYWORD;
		}

		XLState(Generic::List<XLState^>^ SubTerms) //Conditional
		{
			Terms = SubTerms;
			IsTerminal = false;
			UsingStaticValue = false;
		}

		static XLState^ operator +(XLState^, XLState^);
		static XLState^ operator |(XLState^, XLState^);
		static XLState^ operator &(XLState^, XLState^);
		static XLState^ operator +(XLState^, System::String^);
		static operator XLState^ (System::String^ str);
		//static operator XLState^ (XLNonTerminal^ xnonterminal);

	private:
		System::String^ StaticValue;
		bool UsingStaticValue;
		bool IsTerminal;
		int TerminalType;
		const int IDENTIFIER = 0x0;
		const int NUMBER = 0x1;
		const int COMMENT = 0x2;
		const int KEYWORD = 0x3;
		const int UNKNOWNTERMINAL = 0xFF;

	};
}