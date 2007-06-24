#include "MediaPaletteDialog.h"
#include "MapEditorWX.h"
BEGIN_EVENT_TABLE(MediaPaletteDialog, wxDialog)
END_EVENT_TABLE()
MediaPaletteDialog::MediaPaletteDialog()
{
}
MediaPaletteDialog::~MediaPaletteDialog()
{
}
bool MediaPaletteDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Height Pallet"));

    return result;
}
