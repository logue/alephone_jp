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
bool ObjectPropDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Object Properties"));

    return result;
}
void ObjectPropDialog::setObjIndex(int index)
{
    this->objIndex = index;
    setupDialog();
}
int ObjectPropDialog::getObjIndex()
{
    return this->objIndex;
}
void ObjectPropDialog::setupDialog()
{
}
