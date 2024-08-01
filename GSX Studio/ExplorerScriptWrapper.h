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

	public ref class ExplorerScriptWrapper
	{
	public:
		ExplorerScriptWrapper(System::String^ NameIdentifier, GSCScript^ script)
		{
			Name = NameIdentifier;
			Script = script;
		}
		virtual String^ ToString() override;

		System::String^ Name;
		GSCScript^ Script;
		DevExpress::XtraTreeList::Nodes::TreeListNode^ Node;
	};

}