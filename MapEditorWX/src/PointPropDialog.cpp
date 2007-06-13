#include "PointPropDialog.h"
#include "MapEditorWX.h"
BEGIN_EVENT_TABLE(PointPropDialog, wxDialog)
END_EVENT_TABLE()
PointPropDialog::PointPropDialog()
{
}
PointPropDialog::~PointPropDialog()
{
}
bool PointPropDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Point Properties"));

    return result;
}
