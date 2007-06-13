#include "ColorCustomizeDialog.h"
#include "MapEditorWX.h"
BEGIN_EVENT_TABLE(ColorCustomizeDialog, wxDialog)
END_EVENT_TABLE()
ColorCustomizeDialog::ColorCustomizeDialog()
{
}
ColorCustomizeDialog::~ColorCustomizeDialog()
{
}
bool ColorCustomizeDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, wxT("Color Customize"));

    return result;
}
