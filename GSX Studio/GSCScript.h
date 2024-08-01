#pragma once
#include "GSCPart.h"
#include "XParser.h"
#include "XEditor.h"

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

	public ref class GSCScript
	{
	public:

		GSCScript()
		{
		}
		String^ Name;
		Byte NumberOfScriptFiles;
		DevExpress::XtraTreeList::Nodes::TreeListNode^ Node;
		Generic::List<GSCPart^> ^ScriptFiles = gcnew Generic::List<GSCPart^>();
		Generic::Dictionary<GSCPart^, XEditor^>^ Links = gcnew Generic::Dictionary<GSCPart^, XEditor^>();
		Generic::Dictionary<XEditor^, GSCPart^>^ EditorLinks = gcnew Generic::Dictionary<XEditor^, GSCPart^>();
		Generic::Dictionary<GSCPart^, DevExpress::XtraBars::Docking::DockPanel^>^ WindowLinks = gcnew Generic::Dictionary<GSCPart^, DevExpress::XtraBars::Docking::DockPanel^>();
		bool Linked = false;
		void SyncEditorContents(void);
		void RefreshParseTrees(Irony::Parsing::Parser^ parser);
		GSXCompilerLib::Intellisense::ScriptInfo^ ScriptInfo = gcnew GSXCompilerLib::Intellisense::ScriptInfo();
		System::Collections::Generic::List<FastColoredTextBoxNS::AutocompleteItem^>^ Autos = gcnew System::Collections::Generic::List<FastColoredTextBoxNS::AutocompleteItem^>();
	};
}