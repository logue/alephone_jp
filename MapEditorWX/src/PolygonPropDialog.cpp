#include "PolygonPropDialog.h"
#include "MapEditorWX.h"
BEGIN_EVENT_TABLE(PolygonPropDialog, wxDialog)
END_EVENT_TABLE()
PolygonPropDialog::PolygonPropDialog()
{
}
PolygonPropDialog::~PolygonPropDialog()
{
}
bool PolygonPropDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Polygon Properties"));

    return result;
}
