#include "PolygonTypeDialog.h"
#include "MapEditorWX.h"
BEGIN_EVENT_TABLE(PolygonTypeDialog, wxDialog)
END_EVENT_TABLE()
PolygonTypeDialog::PolygonTypeDialog()
{
}
PolygonTypeDialog::~PolygonTypeDialog()
{
}
bool PolygonTypeDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Polygon Type"));

    return result;
}
