#include "GSCScript.h"
#include "GSCPart.h"

void GSX_Studio::GSCScript::SyncEditorContents(void)
{
	for (int i = 0; i < ScriptFiles->Count; i++)
	{
		ScriptFiles[i]->Contents = Links[ScriptFiles[i]]->Editor->Text;
	}
}

void GSX_Studio::GSCScript::RefreshParseTrees(Irony::Parsing::Parser^ parser)
{
	for each (GSCPart^ script in ScriptFiles)
	{
		script->LoadCache(parser);
	}
}