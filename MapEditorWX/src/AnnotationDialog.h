#ifndef _ANNOTATION_DIALOG_
#define _ANNOTATION_DIALOG_

#include "DlgCommon.h"

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
    wxStaticText* label_12;
    wxChoice* choice_8;
    wxTextCtrl* text_ctrl_7;
    wxStaticText* label_11;
    wxChoice* choice_7;
    wxButton* button_3;
    wxButton* button_4;
public:
    AnnotationDialog();
    /**
        @param annotation 選択したアノテーションデータ、あるいは新規作成の位置＆ポリゴン番号
    */
    bool Create(wxWindow* parent, wxWindowID id,
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
