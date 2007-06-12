#include "LinePropDialog.h"
#include "MapEditorWX.h"
BEGIN_EVENT_TABLE(LinePropDialog, wxDialog)
END_EVENT_TABLE()
LinePropDialog::LinePropDialog()
{
}
LinePropDialog::~LinePropDialog()
{
}
bool LinePropDialog::Create(wxWindow* parent, wxWindowID id, const wxString& title)
{
    bool result = wxDialog::Create(parent, id, title);

    return result;
}
