#include "HeightPaletteDialog.h"
#include "MapEditorWX.h"
BEGIN_EVENT_TABLE(HeightPaletteDialog, wxDialog)
END_EVENT_TABLE()
HeightPaletteDialog::HeightPaletteDialog()
{
}
HeightPaletteDialog::~HeightPaletteDialog()
{
}
bool HeightPaletteDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Height Pallet"));

    return result;
}
