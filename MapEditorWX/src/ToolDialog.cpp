#include "ToolDialog.h"
#include "MapEditorWX.h"

#include <string>
#include "PolygonNumDialog.h"

BEGIN_EVENT_TABLE(ToolDialog, wxDialog)
    EVT_PAINT(ToolDialog::OnPaint)
    EVT_LEFT_DOWN(ToolDialog::OnLeftDown)
END_EVENT_TABLE()

ToolDialog::ToolDialog():wxDialog()
{
    //�C���[�W�����X�g�ǂݍ���
    hpl::aleph::Information infos[NUMBER_OF_TOOL_BAR_ICON_FILES];
    {
        std::string path = std::string(DATA_DIR_NAME) + std::string(TOOL_BAR_ICONS_IMAGE_LIST_FILE_NAME);
        hpl::aleph::loadInformation(path.c_str(), NUMBER_OF_TOOL_BAR_ICON_FILES,
            infos);
    }

    //
    for(int i = 0; i < ToolType::NUMBER_OF_TOOLS * 2; i ++){
        std::string imgPath = std::string(DATA_DIR_NAME) + std::string(TOOL_BAR_ICONS_DIR_NAMR);
        //�ŏ����ʏ탂�[�h�B�㔼�͑I�����̃C���[�W�t�@�C�����ɂȂ��Ă���
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
    //�c�[���A�C�R���\��
    wxPaintDC dc(this);
    PrepareDC(dc);

    for(int i = 0; i < ToolType::NUMBER_OF_TOOLS; i ++){
#ifdef MAP_VIEWER
        //�}�b�v�r���[�A�[�d�l
        if(i % 2 == 1 || i >= 6){
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
    //�I�������c�[���ɐݒ肷��
    for(int i = 0; i < ToolType::NUMBER_OF_TOOLS; i ++){
        int left = (i % 2) * TOOL_WIDTH;
        int top = (i / 2) * TOOL_HEIGHT;
        int right = left + TOOL_WIDTH;
        int bottom = top + TOOL_HEIGHT;

        if(hpl::math::isPointInRect<int>(ev.m_x, ev.m_y,
            left, top, right, bottom))
        {
            //�ω�
            wxGetApp().getEventManager()->setToolType(i);

            if(i == ToolType::TI_SKULL){
                //�I�u�W�F�N�g�c�[��
                //�v���p�e�B��\������
                //TODO wxGetApp().objectPropDialog.Show();

            }else if(i == ToolType::TI_POLYGON){
                //�|���S���c�[��
                //�K��̃|���S���ǉ��c�[��
                //TODO Preset polygons
                PolygonNumDialog polyNumDialog;
                
            }
            Refresh();
            //�J�[�\���ω�
            //TODO cursor
            wxGetApp().setCursor();
        }
    }
}
