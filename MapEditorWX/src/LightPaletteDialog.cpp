#include "LightPaletteDialog.h"
#include "MapEditorWX.h"
BEGIN_EVENT_TABLE(LightPaletteDialog, wxDialog)
END_EVENT_TABLE()
LightPaletteDialog::LightPaletteDialog()
{
}
LightPaletteDialog::~LightPaletteDialog()
{
}
bool LightPaletteDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Height Pallet"));

    return result;
}
