#ifndef _HEIGHT_PALLET_DIALOG_
#define _HEIGHT_PALLET_DIALOG_

#include "DlgCommon.h"

class HeightPaletteDialog: public wxDialog{
    wxButton* button_24;
    wxButton* button_25;
    wxListCtrl* list_ctrl_3;

    bool isFloor_;

public:
    HeightPaletteDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~HeightPaletteDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
    void OnAdd(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnDelete(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnEdit(wxListEvent &event); // wxGlade: <event_handler>

public:
    /**
        現在のマップの高さ情報を代入します
        今までのものは削除されます
    */
    void updateHeights();

    /**
        床なのか天井なのか
        <en>Floor or Ceiling
    */
    void setFloor(bool floor);
    bool isFloor();
    wxColor getColorFromHeight(double heightPerOne);
};

#endif
