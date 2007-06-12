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
    ID_TYPE_CHOICE,
    
};

AnnotationDialog::AnnotationDialog():wxDialog()
{
}

AnnotationDialog::~AnnotationDialog()
{
}
bool AnnotationDialog::Create(wxWindow* parent, wxWindowID id, map_annotation& annotation)
{
    bool result = wxDialog::Create(parent, id, _T("Annotation"));
    //�A�C�e���\��t��

    //�c�u���T�C�U�[
    wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer);

    //�^�C�v�I��
    //���u���T�C�U�[
    wxBoxSizer* typeBox = new wxBoxSizer(wxHORIZONTAL);
    boxSizer->Add(typeBox);
        //�X�^�e�B�b�N�e�L�X�g
        wxStaticText* typeSt = new wxStaticText(_T("Type"));
        typeBox->Add(typeSt);
        //�`���C�X
        this->typeChoice = new wxChoice(this, ID_TYPE_CHOICE);
        typeBox->Add(this->typeChoice);
        //�^�C�v���ڒǉ�
        this->typeChoice->Insert(wxString(_T("Normal")));
        
    //�e�L�X�g�{�b�N�X
    this->textArea = new wxTextCtrl(this, ID_ANNOTATION_TEXT_AREA);
    boxSizer->Add(textArea);

    //�ˑ��|���S���w��
    wxBoxSizer* polygonBox = new wxBoxSizer(wxHORIZONTAL);
    boxSizer->Add(polygonBox);
        wxStaticText* polySt = new wxStaticText(_T("Depend polygon"));
        polygonBox->Add(polySt);
        //�|���S���`���C�X
        this->polyChoice = new wxChoice();
        //��������|���S���ԍ���ǉ�
        //�Ō��NONE��t��
        for(int i = 0; i < (int)PolygonList.size(); i ++){
            wxString str(i);
            this->polyChoice->Insert(str);
        }
        this->polyChoice->Insert(wxString(_T("NONE")));
        polygonBox->Add(polyChoice);

    //OK�{�^��
    boxSizer->Add(new wxButton(_T("OK"), wxID_OK));
    boxSizer->Add(new wxButton(_T("Cancel", wxID_CANCEL)));
    return result;
}
