#ifndef _TOOL_DIALOG_
#define _TOOL_DIALOG_

#include <wx/dialog.h>
#include <wx/bitmap.h>
#include <wx/bmpbuttn.h>
#include "HPLLib/HPLEventManager.h"
#include <string>
/**
    ツール選択ダイアログ
*/
class ToolDialog: public wxDialog{
private:
    //イメージビットマップ
    wxBitmap toolBitmaps[ToolType::NUMBER_OF_TOOLS];
    wxBitmap selectedToolBitmaps[ToolType::NUMBER_OF_TOOLS];
public:
    /**
        @param parent 親ウインドウNULLでも可能
        @param wxWindowID 識別ID。-1ならデフォルト
    */
    ToolDialog();
    bool Create(wxWindow* parent, wxWindowID id, const wxString& title);
    virtual ~ToolDialog();

    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()

    //paint
    void OnPaint(wxPaintEvent& ev);
    //mouse
    void OnLeftDown(wxMouseEvent& ev);
};

#endif
