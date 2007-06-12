#include "AnnotationDialog.h"
#include "MapEditorWX.h"

//EVT_BUTTON(id, func)
BEGIN_EVENT_TABLE(AnnotationDialog, wxDialog)
//EVT_BUTTON(, func)
    //�`�F�b�N�{�b�N�X�ύX
    EVT_BUTTON(wxID_OK, AnnotationDialog::OnOk)
    EVT_BUTTON(wxID_CANCEL, AnnotationDialog::OnCancel)
END_EVENT_TABLE()

enum{
    ID_ANNOTATION_TEXT_AREA = 0,
    ID_ANNOTATION_CHECK_BOX,
    
};

AnnotationDialog::AnnotationDialog():wxDialog()
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

    //�^�C�v�I��
    //���u���T�C�U�[
    wxBoxSizer* typeBox = new wxBoxSizer(wxHORIZONTAL);
        //�X�^�e�B�b�N�e�L�X�g
        wxStaticText* typeSt = new wxStaticText(_T("Type"));
        //�`���C�X

    //�e�L�X�g�{�b�N�X
    this->textArea = new wxTextCtrl(this, ID_ANNOTATION_TEXT_AREA);
    boxSizer->Add(textArea);

    //�ˑ��|���S���w��
    //�Ō��NONE��t��

    //OK�{�^��
    boxSizer->Add(new wxButton(_T("OK")));
    boxSizer->Add(new wxButton(_T("Cancel")));
    return result;
}
