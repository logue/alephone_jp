#include "AnnotationDialog.h"
#include "MapEditorWX.h"

const int BUF_MAX = 1024;

//EVT_BUTTON(id, func)
BEGIN_EVENT_TABLE(AnnotationDialog, wxDialog)
//EVT_BUTTON(, func)
    //チェックボックス変更
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
    label_12 = new wxStaticText(this, wxID_ANY, wxT("Type"));
    const wxString choice_8_choices[] = {
        wxT("Normal")
    };
    choice_8 = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 1, choice_8_choices, 0);
    text_ctrl_7 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxHSCROLL);
    label_11 = new wxStaticText(this, wxID_ANY, wxT("Dependency polygon index"));
    choice_7 = new wxChoice(this, wxID_ANY);
    button_3 = new wxButton(this, wxID_OK, wxT("OK"));
    button_4 = new wxButton(this, wxID_CANCEL, wxT("Cancel"));

    //setup
    choice_8->SetSelection(0);
    text_ctrl_7->SetMinSize(wxSize(250, 60));

    //layout
    wxFlexGridSizer* sizer_33 = new wxFlexGridSizer(4, 1, 0, 0);
    wxBoxSizer* sizer_34 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_35 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_36 = new wxBoxSizer(wxHORIZONTAL);
    sizer_36->Add(label_12, 0, 0, 0);
    sizer_36->Add(choice_8, 0, 0, 0);
    sizer_33->Add(sizer_36, 1, wxEXPAND, 0);
    sizer_33->Add(text_ctrl_7, 0, wxEXPAND, 0);
    sizer_35->Add(label_11, 0, 0, 0);
    sizer_35->Add(choice_7, 0, 0, 0);
    sizer_33->Add(sizer_35, 1, wxEXPAND, 0);
    sizer_34->Add(button_3, 0, 0, 0);
    sizer_34->Add(button_4, 0, 0, 0);
    sizer_33->Add(sizer_34, 1, wxEXPAND, 0);
    SetSizer(sizer_33);
    sizer_33->Fit(this);
    Layout();

    //値設定
    choice_8->SetSelection(annotation.type);
    text_ctrl_7->SetValue(wxConvertMB2WX(annotation.text));
    this->wpoint.x = annotation.location.x;
    this->wpoint.y = annotation.location.y;
    //ポリゴン情報を代入
    //TODO
    for(int i = 0; i < (int)PolygonList.size(); i ++){
        char buf[BUF_MAX];
        sprintf(buf, "%d", i);
        choice_7->Insert(wxConvertMB2WX(buf), i);
    }
    //最後にNONE
    choice_7->Insert(_T("NONE"), (int)PolygonList.size());
    if(annotation.polygon_index == NONE){
        choice_7->SetSelection((int)PolygonList.size());
    }else{
        choice_7->SetSelection(annotation.polygon_index);
    }
    return result;
}
/**
    設定した値でデータを取得する
*/
map_annotation AnnotationDialog::getAnnotation()
{
    map_annotation annotation = {NULL};
    annotation.location.x = this->wpoint.x;
    annotation.location.y = this->wpoint.y;
    //長さチェック
    wxString str = wxString(text_ctrl_7->GetValue());
    if(str.Length() > MAXIMUM_ANNOTATION_TEXT_LENGTH){
        hpl::error::caution("annotation text is too long (over %d). ignored after limit.",
            MAXIMUM_ANNOTATION_TEXT_LENGTH);
        str = str.Mid(0, MAXIMUM_ANNOTATION_TEXT_LENGTH);
    }
    strcpy(annotation.text, str.mb_str());
    annotation.type = choice_8->GetSelection();
    annotation.polygon_index = choice_7->GetSelection();
    if(annotation.polygon_index == PolygonList.size()){
        annotation.polygon_index = NONE;
    }
    return annotation;
}
//OKボタン押した時
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

