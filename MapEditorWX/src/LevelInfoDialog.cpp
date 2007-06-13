#include "LevelInfoDialog.h"
#include "MapEditorWX.h"
BEGIN_EVENT_TABLE(LevelInfoDialog, wxDialog)
END_EVENT_TABLE()
LevelInfoDialog::LevelInfoDialog()
{
}
LevelInfoDialog::~LevelInfoDialog()
{
}
bool LevelInfoDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Level Information"));

    return result;
}
