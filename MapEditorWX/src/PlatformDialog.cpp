#include "PlatformDialog.h"
#include "MapEditorWX.h"
BEGIN_EVENT_TABLE(PlatformDialog, wxDialog)
END_EVENT_TABLE()
PlatformDialog::PlatformDialog()
{
}
PlatformDialog::~PlatformDialog()
{
}
bool PlatformDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Platform"));

    return result;
}
