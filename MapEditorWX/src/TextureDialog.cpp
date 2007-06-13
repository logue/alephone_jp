#include "TextureDialog.h"
#include "MapEditorWX.h"
BEGIN_EVENT_TABLE(TextureDialog, wxDialog)
END_EVENT_TABLE()
TextureDialog::TextureDialog()
{
}
TextureDialog::~TextureDialog()
{
}
bool TextureDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Texture"));

    return result;
}
