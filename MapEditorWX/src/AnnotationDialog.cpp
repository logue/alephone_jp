#include "AnnotationDialog.h"
#include "MapEditorWX.h"

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
        //スタティックテキスト
        wxStaticText* typeSt = new wxStaticText(_T("Type"));
        typeBox->Add(typeSt);
        //チョイス
        this->typeChoice = new wxChoice(this, ID_TYPE_CHOICE);
        typeBox->Add(this->typeChoice);
        //タイプ項目追加
        this->typeChoice->Insert(wxString(_T("Normal")));
        
    //テキストボックス
    this->textArea = new wxTextCtrl(this, ID_ANNOTATION_TEXT_AREA);
    boxSizer->Add(textArea);

    //依存ポリゴン指定
    wxBoxSizer* polygonBox = new wxBoxSizer(wxHORIZONTAL);
    boxSizer->Add(polygonBox);
        wxStaticText* polySt = new wxStaticText(_T("Depend polygon"));
        polygonBox->Add(polySt);
        //ポリゴンチョイス
        this->polyChoice = new wxChoice();
        //現存するポリゴン番号を追加
        //最後にNONEを付加
        for(int i = 0; i < (int)PolygonList.size(); i ++){
            wxString str(i);
            this->polyChoice->Insert(str);
        }
        this->polyChoice->Insert(wxString(_T("NONE")));
        polygonBox->Add(polyChoice);

    //OKボタン
    boxSizer->Add(new wxButton(_T("OK"), wxID_OK));
    boxSizer->Add(new wxButton(_T("Cancel", wxID_CANCEL)));
    return result;
}
