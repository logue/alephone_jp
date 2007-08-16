#ifndef _MAIN_FRAME_
#define _MAIN_FRAME_

#include "Common.h"

class MainFrame: public wxFrame{
public:
	void Create(wxWindow* parent, wxWindowID id);
protected:
	void OnNew(wxCommandEvent& ev);
	void OnOpen(wxCommandEvent& ev);
	void OnSave(wxCommandEvent& ev);
	void OnSaveAs(wxCommandEvent& ev);
	void OnQuit(wxCommandEvent& ev);

    DECLARE_EVENT_TABLE()
private:
	/**
		�����ҏW���ł���Γ��e��j�����邩�A���̑O�ɕۑ����邩�A�L�����Z�����邩
		�ǂ����₢�������܂��B
		@return 
			wxYES:	�j������O�ɕۑ�����
			wxNO:	�ۑ������ɔj������
			wxCANCEL:�L�����Z�����ď������s��Ȃ�
	*/
	int askDestroy();


public:
};

#endif
