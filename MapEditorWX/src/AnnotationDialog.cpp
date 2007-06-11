#include "AnnotationDialog.h"
#include "MapEditorWX.h"

//EVT_BUTTON(id, func)
BEGIN_EVENT_TABLE(AnnotationDialog, wxDialog)
END_EVENT_TABLE()

enum{
    ID_ANNOTATION_TEXT_AREA = 1000,
    ID_ANNOTATION_CHECK_BOX,

};

AnnotationDialog::AnnotationDialog()
{
}
AnnotationDialog::~AnnotationDialog()
{
}
bool AnnotationDialog::Create(wxWindow* parent, wxWindowID id, const wxString& title)
{
    bool result = wxDialog::Create(parent, id, title);
    //�A�C�e���\��t��

    //�c�u���T�C�U�[
    wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer);

    //�e�L�X�g�{�b�N�X
    wxTextCtrl* textArea = new wxTextCtrl(this, ID_ANNOTATION_TEXT_AREA);
    boxSizer->Add(textArea);

    //�`�F�b�N�{�b�N�X
    wxCheckBox* check = new wxCheckBox(this, ID_ANNOTATION_CHECK_BOX);
    boxSizer->Add(check);

    return result;
}
