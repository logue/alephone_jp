#ifndef _PHYSICS_EDITOR_ONE_WX_
#define _PHYSICS_EDITOR_ONE_WX_

#include "Common.h"
class PhysicsEditorOneWX: public wxApp{
private:

public:
private:
	void OnInit();

	/**
		wxWidgetsに依存しない初期設定
	*/
	void init();
public:

};

DECLARE_APP(PhysicsEditorOneWX)

#endif
