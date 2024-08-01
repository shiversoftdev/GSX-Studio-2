#include "XLNonTerminal.h"

XParserLib::XLNonTerminal ^ XParserLib::XLNonTerminal::GetDefaultProgram()
{
	XLNonTerminal^ default_program = gcnew XLNonTerminal();
	default_program->Name = "program";
	return default_program;
}
