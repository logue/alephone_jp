#include "AnnotationDialog.h"
#include "MapEditorWX.h"

const int BUF_MAX = 1024;

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
    ID_POLY_INDEX,
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
//    typeBox->Fit(boxSizer);
        //�X�^�e�B�b�N�e�L�X�g
        wxStaticText* typeSt = new wxStaticText(this, wxID_ANY, _T("Type"));
        typeBox->Add(typeSt);
        //�`���C�X
        this->typeChoice = new wxChoice(this, ID_TYPE_CHOICE);
        typeBox->Add(this->typeChoice);
        //�^�C�v���ڒǉ�
        this->typeChoice->Insert(wxString(_T("Normal")), 0 );
        
    //�e�L�X�g�{�b�N�X
    this->textArea = new wxTextCtrl(this, ID_ANNOTATION_TEXT_AREA);
    boxSizer->Add(textArea);

    //�ˑ��|���S���w��
    wxBoxSizer* polygonBox = new wxBoxSizer(wxHORIZONTAL);
    boxSizer->Add(polygonBox);
//    polygonBox->Fit(boxSizer);
        wxStaticText* polySt = new wxStaticText(this, wxID_ANY, wxString(_T("Depend polygon")));
        polygonBox->Add(polySt);
        //�|���S���`���C�X
        this->polyChoice = new wxChoice();
        //��������|���S���ԍ���ǉ�
        //�Ō��NONE��t��
        int n = (int)PolygonList.size();
        for(int i = 0; i < n; i ++){
            char buf[BUF_MAX];
            sprintf(buf, "%d", i);
            polyChoice->Insert(wxConvCurrent->cMB2WX(buf), i);
        }
        polyChoice->Insert(wxString(_T("NONE")), n);
        polygonBox->Add(polyChoice);

    //�{�^���͉��u���I
    wxBoxSizer* btnBox = new wxBoxSizer(wxHORIZONTAL);
        //OK�{�^��
        btnBox->Add(new wxButton(this, wxID_OK, _T("OK")));
        btnBox->Add(new wxButton(this, wxID_CANCEL, _T("Cancel")));
        boxSizer->Add(btnBox);
    boxSizer->Fit(this);
    Layout();
    return result;
}
/**
    �ݒ肵���l�Ńf�[�^���擾����
*/
map_annotation AnnotationDialog::getAnnotation()
{
    //TODO
    map_annotation annotation;
    return annotation;
}
//OK�{�^����������
void AnnotationDialog::OnOk(wxCommandEvent& wv)
{
    SetReturnCode(wxID_OK);
    Destroy();
}
void AnnotationDialog::OnCancel(wxCommandEvent &ev)
{
    SetReturnCode(wxID_CANCEL);
    Destroy();
}

