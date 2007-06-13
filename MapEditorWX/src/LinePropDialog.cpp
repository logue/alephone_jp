#include "LinePropDialog.h"
#include "MapEditorWX.h"
BEGIN_EVENT_TABLE(LinePropDialog, wxDialog)
END_EVENT_TABLE()
LinePropDialog::LinePropDialog()
{
}
LinePropDialog::~LinePropDialog()
{
}
bool LinePropDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Line Properties"));

    return result;
}
