#include "XEditor.h"

void GSX_Studio::XEditor::AdjustScrollbars(void)
{
	AdjustVScrollbar(VScroller, Editor->VerticalScroll->Maximum, Editor->VerticalScroll->Value, Editor->ClientSize.Height);
	AdjustHScrollbar(HScroller, Editor->HorizontalScroll->Maximum, Editor->HorizontalScroll->Value, Editor->ClientSize.Width);
}

void GSX_Studio::XEditor::AdjustHScrollbar(DevExpress::XtraEditors::HScrollBar ^ scrollBar, int max, int value, int clientSize)
{
	scrollBar->LargeChange = clientSize / 3;
	scrollBar->SmallChange = clientSize / 11;
	scrollBar->Maximum = max + scrollBar->LargeChange;
	scrollBar->Visible = max > 0;
	scrollBar->Value = Math::Min(scrollBar->Maximum, value);
}

void GSX_Studio::XEditor::AdjustVScrollbar(DevExpress::XtraEditors::VScrollBar ^ scrollBar, int max, int value, int clientSize)
{
	scrollBar->LargeChange = clientSize / 3;
	scrollBar->SmallChange = clientSize / 11;
	scrollBar->Maximum = max + scrollBar->LargeChange;
	scrollBar->Visible = max > 0;
	scrollBar->Value = Math::Min(scrollBar->Maximum, value);
}

void GSX_Studio::XEditor::fctb_ScrollbarsUpdated(System::Object ^ sender, System::EventArgs ^ e)
{
	AdjustScrollbars();
}

void GSX_Studio::XEditor::VScrollBar_Scroll(System::Object ^ sender, System::Windows::Forms::ScrollEventArgs ^ e)
{
	Editor->OnScroll(e, e->Type != ScrollEventType::ThumbTrack && e->Type != ScrollEventType::ThumbPosition, 2);
}

void GSX_Studio::XEditor::HScrollBar_Scroll(System::Object ^ sender, System::Windows::Forms::ScrollEventArgs ^ e)
{
	Editor->OnScroll(e , e->Type != ScrollEventType::ThumbTrack && e->Type != ScrollEventType::ThumbPosition, 1);
}

void GSX_Studio::XEditor::OnDMMouseEnter(System::Object ^sender, System::EventArgs ^e)
{
	documentMap1->ForeColor = System::Drawing::Color::FromArgb(170,170,170);
}

void GSX_Studio::XEditor::OnDMMouseLeave(System::Object ^sender, System::EventArgs ^e)
{
	documentMap1->ForeColor = System::Drawing::Color::FromArgb(30, 30, 30);
}

void GSX_Studio::XEditor::OnTTDraw(System::Object ^sender, System::Windows::Forms::DrawToolTipEventArgs ^e)
{
	e->DrawBackground();
	e->DrawBorder();
	e->DrawText();
}

void GSX_Studio::XEditor::OnEClick(System::Object ^sender, System::EventArgs ^e)
{
	Editor->SelectionColor = System::Drawing::Color::FromArgb(51, 153, 255);
}

void GSX_Studio::XEditor::SetAutoCompleteItems(System::Collections::Generic::List<FastColoredTextBoxNS::AutocompleteItem^>^ items)
{
	ACM->Items->SetAutocompleteItems(items);
}