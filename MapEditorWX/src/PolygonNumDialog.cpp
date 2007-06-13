#include "PolygonNumDialog.h"
#include "MapEditorWX.h"
BEGIN_EVENT_TABLE(PolygonNumDialog, wxDialog)
END_EVENT_TABLE()
PolygonNumDialog::PolygonNumDialog()
{
}
PolygonNumDialog::~PolygonNumDialog()
{
}
bool PolygonNumDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Polygon Num"));

    return result;
}
