#pragma once
#include "XParseLanguage.h"
#include "XParseNode.h"

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


	public ref class XParseTree
	{

	public:
		XParseNode^ Root;
		XParseLanguage^ Language;

		XParseTree(XParseNode^ root, XParseLanguage^ language)
		{
			Root = root;
			Language = language;
		}
	};

}