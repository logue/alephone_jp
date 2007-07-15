#include "VisualDialog.h"
#include "MapEditorWX.h"
const int VISUAL_MODE_DIALOG_WIDTH = 640;
const int VISUAL_MODE_DIALOG_HEIGHT = 480;

BEGIN_EVENT_TABLE(VisualDialog, wxDialog)
	EVT_PAINT(VisualDialog::OnPaint)
END_EVENT_TABLE()
VisualDialog::VisualDialog()
{
	wxGetApp().getVisualModeManager()->init();
}
VisualDialog::~VisualDialog()
{
}
bool VisualDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Visual"), wxPoint(-1,-1),
		wxSize(VISUAL_MODE_DIALOG_WIDTH, VISUAL_MODE_DIALOG_HEIGHT));
	
    return result;
}

void VisualDialog::OnClose()
{
}
void VisualDialog::OnPaint(wxPaintEvent &ev)
{
	wxPaintDC dc(this);
	
	wxSize clientSize = this->GetClientSize();
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.DrawRectangle(clientSize);

	if(wxGetApp().getShapesManager()->isLoadedShapesFile()){
		//プレイヤーの位置に設定
		render_screen(0);
		//スクリーンからコピー

	}
}
