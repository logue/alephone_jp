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
bool SelectLevelDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Select Level"));

    return result;
}
