#include "SelectLevelDialog.h"
#include "MapEditorWX.h"
BEGIN_EVENT_TABLE(SelectLevelDialog, wxDialog)
END_EVENT_TABLE()
SelectLevelDialog::SelectLevelDialog()
{
}
SelectLevelDialog::~SelectLevelDialog()
{
}
bool SelectLevelDialog::Create(wxWindow* parent, wxWindowID id, const wxString& title)
{
    bool result = wxDialog::Create(parent, id, title);

    return result;
}
