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
bool PolygonPropDialog::Create(wxWindow* parent, wxWindowID id, const wxString& title)
{
    bool result = wxDialog::Create(parent, id, title);

    return result;
}
