#include "EditorPreferencesDialog.h"
#include "MapEditorWX.h"
BEGIN_EVENT_TABLE(EditorPreferencesDialog, wxDialog)
END_EVENT_TABLE()
EditorPreferencesDialog::EditorPreferencesDialog()
{
}
EditorPreferencesDialog::~EditorPreferencesDialog()
{
}
bool EditorPreferencesDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Editor Preferences"));

    return result;
}
