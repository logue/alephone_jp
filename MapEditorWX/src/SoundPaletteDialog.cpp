#include "SoundPaletteDialog.h"
#include "MapEditorWX.h"
BEGIN_EVENT_TABLE(SoundPaletteDialog, wxDialog)
END_EVENT_TABLE()
SoundPaletteDialog::SoundPaletteDialog()
{
}
SoundPaletteDialog::~SoundPaletteDialog()
{
}
bool SoundPaletteDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Height Pallet"));

    return result;
}
