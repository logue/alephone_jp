#include "HeightDialog.h"
#include "MapEditorWX.h"
BEGIN_EVENT_TABLE(HeightDialog, wxDialog)
END_EVENT_TABLE()
HeightDialog::HeightDialog()
{
}
HeightDialog::~HeightDialog()
{
}
bool HeightDialog::Create(wxWindow* parent, wxWindowID id, const wxString& title)
{
    bool result = wxDialog::Create(parent, id, title);

    return result;
}
