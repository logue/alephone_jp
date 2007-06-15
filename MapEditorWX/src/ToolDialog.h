#ifndef _TOOL_DIALOG_
#define _TOOL_DIALOG_

#include "DlgCommon.h"

/**
    ツール選択ダイアログ
*/
class ToolDialog: public wxDialog{
private:
    //イメージビットマップ
    wxImage toolBitmaps[ToolType::NUMBER_OF_TOOLS];
    wxImage selectedToolBitmaps[ToolType::NUMBER_OF_TOOLS];
public:
    /**
        @param parent 親ウインドウNULLでも可能
        @param wxWindowID 識別ID。-1ならデフォルト
    */
    ToolDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~ToolDialog();

    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()

    //paint
    void OnPaint(wxPaintEvent& ev);
    //mouse
    void OnLeftDown(wxMouseEvent& ev);
};

#endif
