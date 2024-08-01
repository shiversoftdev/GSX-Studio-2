#pragma once
#include "XParseTree.h"
#include "XParseLanguage.h"

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

	public ref class XParser
	{
	public:
		XParseTree^ FullParse(System::String^);

		XParser(XParseLanguage^ language)
		{
			Language = language;
		}
	private:
		XParseLanguage^ Language;
	};

}