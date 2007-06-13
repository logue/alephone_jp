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
bool VisualDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Visual"));

    return result;
}

void VisualDialog::OnClose()
{
}
