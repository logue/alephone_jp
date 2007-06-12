#ifndef _ANNOTATION_DIALOG_
#define _ANNOTATION_DIALOG_

#include "map.h"

#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/textctrl.h>

/*
struct map_annotation
{
	int16 type; //* turns into color, font, size, style, etc... *
	
	world_point2d location; //* where to draw this (lower left) *
	int16 polygon_index; //* only displayed if this polygon is in the automap *
	
	char text[MAXIMUM_ANNOTATION_TEXT_LENGTH];
};
*/

/**
    あのテーション追加・変更ダイアログ
*/
class AnnotationDialog: public wxDialog{
private:
//    wxBoxSizer* boxSizer;
    //テキストデータ
    wxTextCtrl* textArea;

    //タイプ選択
    wxChoice* typeChoice;

    //ワールド座標
    wxTextCtrl* worldX;
    wxTextCtrl* worldY;

    //ビュー座標
    wxTextCtrl* viewX;
    wxTextCtrl* viewY;

public:
    AnnotationDialog();
    /**
        @param annotation 選択したアノテーションデータ、あるいは新規作成の位置＆ポリゴン番号
    */
    bool Create(wxWindow* parent, wxWindowID id, const wxString& title,
        map_annotation& annotation);

    virtual ~AnnotationDialog();

    //OKボタン押した時
    void OnOk(wxCommandEvent& wv);
    void OnCancel(wxCommandEvent &ev);

    /**
        設定した値でデータを取得する
    */
    map_annotation getAnnotation();

    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
};

#endif
