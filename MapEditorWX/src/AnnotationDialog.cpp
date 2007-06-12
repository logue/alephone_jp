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
    //アイテム貼り付け

    //縦置きサイザー
    wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer);

    //タイプ選択
    //横置きサイザー
    wxBoxSizer* typeBox = new wxBoxSizer(wxHORIZONTAL);
        //スタティックテキスト
        wxStaticText* typeSt = new wxStaticText(_T("Type"));
        //チョイス

    //テキストボックス
    this->textArea = new wxTextCtrl(this, ID_ANNOTATION_TEXT_AREA);
    boxSizer->Add(textArea);

    //依存ポリゴン指定
    //最後にNONEを付加

    //OKボタン
    boxSizer->Add(new wxButton(_T("OK")));
    boxSizer->Add(new wxButton(_T("Cancel")));
    return result;
}
