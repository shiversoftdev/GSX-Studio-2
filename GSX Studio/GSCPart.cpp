#include "GSCPart.h"

void GSX_Studio::GSCPart::LoadCache(Irony::Parsing::Parser^ Parser)
{
	Tree = Parser->Parse(Contents);
}

void GSX_Studio::GSCPart::SetCache(Irony::Parsing::Parser^ Parser, System::String^ filename, System::String^ cts)
{
	Tree = Parser->Parse(cts, filename);
}

System::Collections::Generic::List<FastColoredTextBoxNS::AutocompleteItem^>^ GSX_Studio::GSCPart::GetFunctionsList()
{
	FunctionsACList->Clear();
	if (!Tree || Tree->ParserMessages->Count > 0)
		return FunctionsACList;
	for each (ParseTreeNode^ node in GSXCompilerLib::Intellisense::CollectFunctionNodes(Tree))
	{
		FastColoredTextBoxNS::AutocompleteItem^ item = gcnew FastColoredTextBoxNS::AutocompleteItem();
		item->Text = GSXCompilerLib::Intellisense::FindFunctionHeader(node);
		item->ToolTipText = GSXCompilerLib::Intellisense::FindFunctionDescription(node);
		item->ToolTipTitle = GSXCompilerLib::Intellisense::FindFunctionHeader(node);
		item->ImageIndex = 0;
		FunctionsACList->Add(item);
	}
	return FunctionsACList;
}