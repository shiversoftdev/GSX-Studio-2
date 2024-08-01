#include "LIBMGR.h"

void GSX_Studio::LIBMGR::ExplorerOnMouseClick(System::Object ^sender, System::Windows::Forms::MouseEventArgs ^e)
{
	if (e->Button == System::Windows::Forms::MouseButtons::Right)
	{
		if (ProjectsList->Selection[0] && ProjectsList->Selection[0]->GetValue(0)->GetType() == GSXCompilerLib::GSXLibraries::GSXLibraryConfig::typeid)
		{
			InstallRightClickMenu->ShowPopup(((System::Windows::Forms::Control^)sender)->PointToScreen(e->Location));
		}
	}
}