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
    ���̃e�[�V�����ǉ��E�ύX�_�C�A���O
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
        @param annotation �I�������A�m�e�[�V�����f�[�^�A���邢�͐V�K�쐬�̈ʒu���|���S���ԍ�
    */
    bool Create(wxWindow* parent, wxWindowID id,
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
