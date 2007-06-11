#include "VisualDialog.h"
#include "MapEditorWX.h"
BEGIN_EVENT_TABLE(VisualDialog, wxDialog)
END_EVENT_TABLE()
VisualDialog::VisualDialog()
{
}
VisualDialog::~VisualDialog()
{
}
bool VisualDialog::Create(wxWindow* parent, wxWindowID id, const wxString& title)
{
    bool result = wxDialog::Create(parent, id, title);

    return result;
}

void VisualDialog::OnClose()
{
}
