#ifndef _POLYGON_NUM_DIALOG_
#define _POLYGON_NUM_DIALOG_

#include "DlgCommon.h"

class PolygonNumDialog: public wxDialog{
public:
    PolygonNumDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~PolygonNumDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
private:

    wxBitmapButton* bitmap_button_1;
    wxBitmapButton* bitmap_button_2;
    wxBitmapButton* bitmap_button_3;
    wxBitmapButton* bitmap_button_4;
    wxBitmapButton* bitmap_button_5;
    wxBitmapButton* bitmap_button_6;
public:
    void OnPoly3(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnPoly4(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnPoly5(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnPoly6(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnPoly7(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnPoly8(wxCommandEvent &event); // wxGlade: <event_handler>

};
#endif
