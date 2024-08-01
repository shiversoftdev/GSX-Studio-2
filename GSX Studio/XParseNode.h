#pragma once

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

	public ref class XParseNode
	{

	public:
		System::String^ TypeIdentity;
		property System::String^ Value;
		Generic::List<XParseNode^>^ Children = gcnew Generic::List<XParseNode^>();

		XParseNode(System::String^ TypeOfGNode)
		{
			TypeIdentity = TypeOfGNode;
		}

	};

}