#include "ToolDialog.h"
#include "MapEditorWX.h"

#include <string>
#include "PolygonNumDialog.h"
#include "MapEditorMainFrame.h"

BEGIN_EVENT_TABLE(ToolDialog, wxDialog)
    EVT_PAINT(ToolDialog::OnPaint)
    EVT_LEFT_DOWN(ToolDialog::OnLeftDown)
END_EVENT_TABLE()

ToolDialog::ToolDialog():wxDialog()
{
    
    //イメージ名リスト読み込み
    hpl::aleph::Information infos[NUMBER_OF_TOOL_BAR_ICON_FILES];
    {
        std::string path = std::string(DATA_DIR_NAME) + std::string(TOOL_BAR_ICONS_IMAGE_LIST_FILE_NAME);
        hpl::aleph::loadInformation(path.c_str(), NUMBER_OF_TOOL_BAR_ICON_FILES,
            infos);
    }

    //
    for(int i = 0; i < ToolType::NUMBER_OF_TOOLS * 2; i ++){
        std::string imgPath = std::string(DATA_DIR_NAME) + std::string(TOOL_BAR_ICONS_DIR_NAMR);
        //最初が通常モード。後半は選択時のイメージファイル名になっている
        bool select = (i >= ToolType::NUMBER_OF_TOOLS);
        if(select){
            imgPath += std::string(SELECTED_ICONS_DIR_NAME);
        }
        int index = i % ToolType::NUMBER_OF_TOOLS;
        imgPath += infos[index].jname;
        if(select){
            wxGetApp().loadBitmap(imgPath.c_str(), &this->selectedToolBitmaps[index]);
        }else{
            wxGetApp().loadBitmap(imgPath.c_str(), &this->toolBitmaps[index]);
        }
    }

}
ToolDialog::~ToolDialog()
{
    
}
bool ToolDialog::Create(wxWindow* parent, wxWindowID id)
{
    //wxTHICK_FRAME wxSTAY_ON_TOP
    long style = wxCAPTION;
    bool result = wxDialog::Create(parent, id, _T("Tool"), wxDefaultPosition//);
    ,        wxSize(TOOL_DIALOG_W, TOOL_DIALOG_H), style);

/*    wxBitmapButton *bmpBtn = new wxBitmapButton(this, -1, toolBitmaps[0]);
    wxGridSizer *boxSizer = new wxGridSizer(2);
    this->SetSizer(boxSizer);
    boxSizer->Add(bmpBtn);
*/
    return result;
}

//paint
void ToolDialog::OnPaint(wxPaintEvent& ev)
{
    //ツールアイコン表示
    wxPaintDC dc(this);
    PrepareDC(dc);

    for(int i = 0; i < ToolType::NUMBER_OF_TOOLS; i ++){
#ifdef MAPVIEWER
		if(i == ToolType::TI_FILL ||
			i == ToolType::TI_LINE ||
//			i == ToolType::TI_SKULL ||
			i == ToolType::TI_TEXT ||
			i == ToolType::TI_POLYGON)
		{
			continue;
		}
#endif
        int x = (i % 2) * TOOL_WIDTH;
        int y = (i / 2) * TOOL_HEIGHT;

        bool select = (wxGetApp().getEventManager()->getToolType() == i);
        wxImage* bmp = &this->toolBitmaps[i];
        if(select){
            bmp = &this->selectedToolBitmaps[i];
        }
        dc.DrawBitmap(*bmp, x, y);
    }
}

void ToolDialog::OnLeftDown(wxMouseEvent& ev)
{
    hpl::aleph::HPLEventManager* emgr = wxGetApp().getEventManager();
    int oldIndex = emgr->getToolType();
    //選択したツールに設定する
    for(int i = 0; i < ToolType::NUMBER_OF_TOOLS; i ++){
#ifdef MAPVIEWER
		if(i == ToolType::TI_FILL ||
			i == ToolType::TI_LINE ||
//			i == ToolType::TI_SKULL ||
			i == ToolType::TI_TEXT ||
			i == ToolType::TI_POLYGON)
		{
			continue;
		}
#endif
        int left = (i % 2) * TOOL_WIDTH;
        int top = (i / 2) * TOOL_HEIGHT;
        int right = left + TOOL_WIDTH;
        int bottom = top + TOOL_HEIGHT;

        if(hpl::math::isPointInRect<int>(ev.m_x, ev.m_y,
            left, top, right, bottom))
        {
            //変化
            emgr->setToolType(i);

            //線追加ツールの初期化
            wxGetApp().resetLineEditInfo();

            if(i == ToolType::TI_SKULL){
                //オブジェクトツール
                //プロパティを表示する
                ((MapEditorMainFrame*)GetParent())->objPropDialog.setObjIndex(NONE);
                ((MapEditorMainFrame*)GetParent())->objPropDialog.Show();

            }else if(i == ToolType::TI_POLYGON){
                //ポリゴンツール
                //規定のポリゴン追加ツール
                //TODO Preset polygons
                PolygonNumDialog polyNumDialog;
                polyNumDialog.Create(this, wxID_ANY);
                int num = polyNumDialog.ShowModal();
                if(num >= 3 && num <= 8){
                    //値を設定
                    wxGetApp().presetPolygonVertexCount = num;
                }
                
            }
            if(i != oldIndex){
                //TODO
                //範囲選択モードを解除
                emgr->exitSelectingGroup();
                //選択情報を解除
                //wxGetApp().selectData.clear();
            }
            Refresh();
            //カーソル変化
            //TODO cursor
            wxGetApp().setCursor();
        }
    }
}
