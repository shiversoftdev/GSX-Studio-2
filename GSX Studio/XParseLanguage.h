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

	public ref class XParseLanguage
	{

	public:
		System::String^ Language;
		bool IsComplete(void);
		XLNonTerminal^ GetProgram(void);
		delegate XParserLib::XLNonTerminal^ DefineLanguage(void);
		void SealLanguage(DefineLanguage^);
		
		XParseLanguage(System::String^ LanguageName)
		{
			Language = LanguageName;
		}



	private:
		bool LSealed;
		XParserLib::XLNonTerminal ^ XProgram;
		
	};
}