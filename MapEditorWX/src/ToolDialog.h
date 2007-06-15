#ifndef _TOOL_DIALOG_
#define _TOOL_DIALOG_

#include "DlgCommon.h"

/**
    �c�[���I���_�C�A���O
*/
class ToolDialog: public wxDialog{
private:
    //�C���[�W�r�b�g�}�b�v
    wxImage toolBitmaps[ToolType::NUMBER_OF_TOOLS];
    wxImage selectedToolBitmaps[ToolType::NUMBER_OF_TOOLS];
public:
    /**
        @param parent �e�E�C���h�ENULL�ł��\
        @param wxWindowID ����ID�B-1�Ȃ�f�t�H���g
    */
    ToolDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~ToolDialog();

    //�C�x���g�e�[�u���쐬<en>declare
    DECLARE_EVENT_TABLE()

    //paint
    void OnPaint(wxPaintEvent& ev);
    //mouse
    void OnLeftDown(wxMouseEvent& ev);
};

#endif
