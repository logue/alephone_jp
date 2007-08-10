#ifndef _TEXTURE_SELECT_DIALOG_
#define _TEXTURE_SELECT_DIALOG_

#include "DlgCommon.h"

class TextureSelectDialog: public wxDialog{
public:
	TextureSelectDialog();
	virtual ~TextureSelectDialog();
	bool Create(wxWindow* parent, wxWindowID id, int defaultShapesDescriptor);
};

#endif
