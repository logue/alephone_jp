#include "TextureSelectDialog.h"

TextureSelectDialog::TextureSelectDialog()
{
}
TextureSelectDialog::~TextureSelectDialog()
{
}
bool TextureSelectDialog::Create(wxWindow* parent, wxWindowID id,
								 int defaultShapesDescriptor)
{
    bool result = wxDialog::Create(parent, id, _T("Texture select"));
	wxASSERT(result);
	return result;
}
