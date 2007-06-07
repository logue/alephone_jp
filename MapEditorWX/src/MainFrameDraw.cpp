#include "MapEditorMainFrame.h"

/**
    マップデータの表示
*/
void MapEditorMainFrame::drawBackground(wxPaintDC dc)
{
    //範囲
    //黒
    dc.SetPen(*wxBLACK_PEN);
    //中抜き
    dc.SetBrush(wxNullBrush);
    int left = OFFSET_X_VIEW;
    int top = OFFSET_Y_VIEW;
    int width = (2 * OFFSET_X_WORLD) / DIV;
    int height = (2 * OFFSET_Y_WORLD) / DIV;
    dc.DrawRectangle(left, top, width, height);

    //グリッド
    //TODO
}
void MapEditorMainFrame::drawPolygons(wxPaintDC dc)
{
}
void MapEditorMainFrame::drawLines(wxPaintDC dc)
{
}
void MapEditorMainFrame::drawSides(wxPaintDC dc)
{
}
void MapEditorMainFrame::drawPoints(wxPaintDC dc)
{
}
void MapEditorMainFrame::drawObjects(wxPaintDC dc)
{
}
