#ifndef _TEXTURE_DIALOG_
#define _TEXTURE_DIALOG_

#include "DlgCommon.h"

class TextureArea: public wxScrolledWindow{
public:
	TextureArea(wxWindow* parent, wxWindowID id);
	virtual ~TextureArea();
protected:
    DECLARE_EVENT_TABLE()
    void OnScroll(wxScrollWinEvent &event);
	void OnDraw();
};

class TextureDialog: public wxDialog{
    wxStaticText* label_75;
    wxChoice* choice_30;
    wxScrolledWindow* panel_13;

	wxChoice* choice_collection;
	wxChoice* choice_clut;

    bool isFloor_;
    int indexSelected;

    //コレクションチョイスと実際のコレクション番号との対応リスト
    std::vector<int> collectionIndexTable;
public:
    TextureDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~TextureDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
    void OnType(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnCollection(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnCLUT(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnPaint(wxPaintEvent &event);
    void OnScroll(wxScrollWinEvent &event);

public:
    void setFloor(bool floor);
	void drawPanel(int collection, int clut, std::map<int, wxImage>* imgMap, wxDC* dc);
	void setupDialog(int collection);

    int getIndexSelected();
//    bool isFloor();
};

#endif
