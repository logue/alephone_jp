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
    //アイテム貼り付け

    //縦置きサイザー
    wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer);

    //タイプ選択
    //横置きサイザー
    wxBoxSizer* typeBox = new wxBoxSizer(wxHORIZONTAL);
    boxSizer->Add(typeBox);
//    typeBox->Fit(boxSizer);
        //スタティックテキスト
        wxStaticText* typeSt = new wxStaticText(this, wxID_ANY, _T("Type"));
        typeBox->Add(typeSt);
        //チョイス
        this->typeChoice = new wxChoice(this, ID_TYPE_CHOICE);
        typeBox->Add(this->typeChoice);
        //タイプ項目追加
        this->typeChoice->Insert(wxString(_T("Normal")), 0 );
        
    //テキストボックス
    this->textArea = new wxTextCtrl(this, ID_ANNOTATION_TEXT_AREA);
    boxSizer->Add(textArea);

    //依存ポリゴン指定
    wxBoxSizer* polygonBox = new wxBoxSizer(wxHORIZONTAL);
    boxSizer->Add(polygonBox);
//    polygonBox->Fit(boxSizer);
        wxStaticText* polySt = new wxStaticText(this, wxID_ANY, wxString(_T("Depend polygon")));
        polygonBox->Add(polySt);
        //ポリゴンチョイス
        this->polyChoice = new wxChoice();
        //現存するポリゴン番号を追加
        //最後にNONEを付加
        int n = (int)PolygonList.size();
        for(int i = 0; i < n; i ++){
            char buf[BUF_MAX];
            sprintf(buf, "%d", i);
            polyChoice->Insert(wxConvCurrent->cMB2WX(buf), i);
        }
        polyChoice->Insert(wxString(_T("NONE")), n);
        polygonBox->Add(polyChoice);

    //ボタンは横置き！
    wxBoxSizer* btnBox = new wxBoxSizer(wxHORIZONTAL);
        //OKボタン
        btnBox->Add(new wxButton(this, wxID_OK, _T("OK")));
        btnBox->Add(new wxButton(this, wxID_CANCEL, _T("Cancel")));
        boxSizer->Add(btnBox);
    boxSizer->Fit(this);
    Layout();
    return result;
}
/**
    設定した値でデータを取得する
*/
map_annotation AnnotationDialog::getAnnotation()
{
    //TODO
    map_annotation annotation;
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

