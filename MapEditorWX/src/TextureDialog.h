#ifndef _TEXTURE_DIALOG_
#define _TEXTURE_DIALOG_

#include "DlgCommon.h"

class TextureDialog: public wxDialog{
    wxStaticText* label_75;
    wxChoice* choice_30;
    wxScrolledWindow* panel_13;

	wxChoice* choice_collection;
	wxChoice* choice_clut;

    bool isFloor_;
public:
    TextureDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~TextureDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
    void OnType(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnCollection(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnCLUT(wxCommandEvent &event); // wxGlade: <event_handler>

public:
    void setFloor(bool floor);
	void drawPanel(int collection, int clut, std::map<int, wxImage>* imgMap);
	void setupDialog(int collection);
//    bool isFloor();
};

#endif
