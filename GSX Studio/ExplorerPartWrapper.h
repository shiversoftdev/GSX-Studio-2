#pragma once
#pragma once
#include "GSCPart.h"

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

	public ref class ExplorerPartWrapper
	{
	public:
		ExplorerPartWrapper(System::String^ NameIdentifier, GSCPart^ script)
		{
			Name = NameIdentifier;
			Script = script;
		}
		virtual String^ ToString() override;

		System::String^ Name;
		GSCPart^ Script;
	};

}