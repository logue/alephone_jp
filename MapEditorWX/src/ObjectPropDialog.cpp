#include "ObjectPropDialog.h"
#include "MapEditorWX.h"
BEGIN_EVENT_TABLE(ObjectPropDialog, wxDialog)
END_EVENT_TABLE()
ObjectPropDialog::ObjectPropDialog()
{
}
ObjectPropDialog::~ObjectPropDialog()
{
}
bool ObjectPropDialog::Create(wxWindow* parent, wxWindowID id, const wxString& title)
{
    bool result = wxDialog::Create(parent, id, title);

    return result;
}
