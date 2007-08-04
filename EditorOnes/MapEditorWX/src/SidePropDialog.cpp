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
bool SidePropDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Side Properties"));

    return result;
}
void SidePropDialog::setIndex(int ind)
{
    this->index = ind;
}
int SidePropDialog::getIndex()
{
    return this->index;
}
