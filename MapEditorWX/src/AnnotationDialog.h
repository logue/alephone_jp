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
    ���̃e�[�V�����ǉ��E�ύX�_�C�A���O
*/
class AnnotationDialog: public wxDialog{
private:
//    wxBoxSizer* boxSizer;
    //�e�L�X�g�f�[�^
    wxTextCtrl* textArea;

    //�^�C�v�I��
    wxChoice* typeChoice;

    //���[���h���W
    wxTextCtrl* worldX;
    wxTextCtrl* worldY;

    //�r���[���W
    wxTextCtrl* viewX;
    wxTextCtrl* viewY;

public:
    AnnotationDialog();
    /**
        @param annotation �I�������A�m�e�[�V�����f�[�^�A���邢�͐V�K�쐬�̈ʒu���|���S���ԍ�
    */
    bool Create(wxWindow* parent, wxWindowID id, const wxString& title,
        map_annotation& annotation);

    virtual ~AnnotationDialog();

    //OK�{�^����������
    void OnOk(wxCommandEvent& wv);
    void OnCancel(wxCommandEvent &ev);

    /**
        �ݒ肵���l�Ńf�[�^���擾����
    */
    map_annotation getAnnotation();

    //�C�x���g�e�[�u���쐬<en>declare
    DECLARE_EVENT_TABLE()
};

#endif
