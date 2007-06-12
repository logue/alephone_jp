#include "HeightPalletDialog.h"
#include "MapEditorWX.h"
BEGIN_EVENT_TABLE(HeightPalletDialog, wxDialog)
END_EVENT_TABLE()
HeightPalletDialog::HeightPalletDialog()
{
}
HeightPalletDialog::~HeightPalletDialog()
{
}
bool HeightPalletDialog::Create(wxWindow* parent, wxWindowID id, const wxString& title)
{
    bool result = wxDialog::Create(parent, id, title);

    return result;
}
