#pragma once
#include "XParser.h"
#include "XLNonTerminal.h"
#include "XParseLanguage.h"
#include "XParseNode.h"
#include "XLState.h"
#include "XParseTree.h"


XParserLib::XParseTree^ XParserLib::XParser::FullParse(System::String^ Code)
{
	if (!Language)
	{
		throw gcnew System::Exception("No Language was defined to parse");
		return nullptr;
	}
	if (!Code)
	{
		return nullptr; //No exception, an empty parser is valid. TODO: Should a user be able to define NullCodeAllowed?
	}
	//TODO Implement
	//Expected implementation:
	//
	return nullptr;
}

bool XParserLib::XLState::Match(System::String^ value)
{
	//TODO Implement
	return false;
}

XParserLib::XLState^  XParserLib::XLState::operator +(XParserLib::XLState^ xstate1, XParserLib::XLState^ xstate2)
{
	Generic::List<XLState^>^ terms = gcnew Generic::List<XLState^>();
	terms->AddRange(xstate1->Terms);
	terms->AddRange(xstate2->Terms);
	XParserLib::XLState^ newstate = gcnew XParserLib::XLState(terms);
	return newstate;
}

XParserLib::XLState^ XParserLib::XLState::operator |(XParserLib::XLState^ xstate1, XParserLib::XLState^ xstate2)
{
	//TODO Implement
	return nullptr;
}

XParserLib::XLState^ XParserLib::XLState::operator &(XParserLib::XLState^ xstate1, XParserLib::XLState^ xstate2)
{
	return xstate1 + xstate2;
}
XParserLib::XLState^ XParserLib::XLState::operator +(XParserLib::XLState^ xstate1, System::String^ str)
{
	return xstate1 + (XLState^)str;
}

XParserLib::XLState::operator XLState ^ (System::String^ str)
{
	XParserLib::XLState^ NewState = (gcnew XParserLib::XLState(str));
	return NewState;
}
/*
XParserLib::XLState::operator XLState ^ (XLNonTerminal^ xnonterminal)
{
	return xnonterminal->Rule;
}
*/
void XParserLib::XParseLanguage::SealLanguage(DefineLanguage^ Func)
{
	XProgram = Func();
	LSealed = true;
}


bool XParserLib::XParseLanguage::IsComplete()
{
	return LSealed;
}

XParserLib::XLNonTerminal^ XParserLib::XParseLanguage::GetProgram(void)
{
	return XProgram;
}
