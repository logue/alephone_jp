#include "SidePropDialog.h"
#include "MapEditorWX.h"
BEGIN_EVENT_TABLE(SidePropDialog, wxDialog)
END_EVENT_TABLE()
SidePropDialog::SidePropDialog()
{
}
SidePropDialog::~SidePropDialog()
{
}
bool SidePropDialog::Create(wxWindow* parent, wxWindowID id, const wxString& title)
{
    bool result = wxDialog::Create(parent, id, title);

    return result;
}
