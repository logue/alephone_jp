#include "MapEditorMainFrame.h"

const int LARGE_PEN_SIZE = 2;

/**
    マップデータの表示
*/
void MapEditorMainFrame::drawBackground(wxPaintDC* dc)
{
    wxSize size = wxFrame::GetClientSize();
    //色設定
    int back[] = wxGetApp().setting.getColorSetting()->background;
    wxColor col = wxColor(back[0], back[1], back[2]);
    wxPen pen(col);
    wxBrush brush(col);

    //背景
    dc->SetPen(pen);
    dc->SetBrush(brush);
    int left = 0;
    int top = 0;
    int width = size.GetWidth();
    int height = size.GetHeight();
    dc->DrawRectangle(left, top, width, height);

    int gridCol[] = wxGetApp().setting.getColorSetting()->grid;
    wxColor edgeCol(gridCol[0], gridCol[1], gridCol[2]);
    pen = wxPen(edgeCol);
    wxPen largePen(edgeCol, LARGE_PEN_SIZE);
    wxBrush nullBrush(wxNullBrush);

    //グリッド
    int grid = wxGetApp().getViewGridManager()->getGridInterval();
    int voffset[2];
    wxGetApp().getViewGridManager()->getOffset(voffset);
    int DIV = wxGetApp().getViewGridManager()->getZoomDivision();
    //TODO
    //SHRT_MAXはgridの倍数ではない！
    //中心から右、下の方向
    for(int i = OFFSET_X_WORLD: i <= OFFSET_X_WORLD * 2; i += grid){
        if(i == OFFSET_X_WORLD){
            //中心＝太線
            dc->setPen(largePen);
        }else{
            dc->setPen(pen);
        }
        int x0 = offset[0] + i / DIV;
        int y0 = offset[1] + i / DIV;

        dc->DrawLine(x0, offset[1], x0, offset[1] + OFFSET_Y_WORLD * 2 / DIV);
        dc->DrawLine(offset[0], y0, offset[0] + OFFSET_X_WORLD * 2 / DIV, y0);

        //左＆上
        int j = OFFSET_X_WORLD * 2 - i;
        int x1 = offset[0] + j / DIV;
        int y1 = offset[1] + j / DIV;
        dc->DrawLine(x1, offset[1], x1, offset[1] + OFFSET_Y_WORLD * 2 / DIV);
        dc->DrawLine(offset[0], y1, offset[0] + OFFSET_X_WORLD * 2 / DIV, y1);
        
    }
    //枠描画
    dc->setPen(largePen);
    dc->setBrush(wxNullBrush);
    left = offset[0];
    top = offset[1];
    width = OFFSET_X_WORLD * 2 / DIV;
    height = OFFSET_Y_WORLD * 2 / DIV;
    dc->DrawRectangle(left, top, width, height);

}
void MapEditorMainFrame::drawPolygons(wxPaintDC* dc)
{
}
void MapEditorMainFrame::drawLines(wxPaintDC* dc)
{
}
void MapEditorMainFrame::drawSides(wxPaintDC* dc)
{
}
void MapEditorMainFrame::drawPoints(wxPaintDC* dc)
{
}
void MapEditorMainFrame::drawObjects(wxPaintDC* dc)
{
}
