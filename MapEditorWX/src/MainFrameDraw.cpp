#include "MapEditorMainFrame.h"

/**
    �}�b�v�f�[�^�̕\��
*/
void MapEditorMainFrame::drawBackground(wxPaintDC dc)
{
    //�͈�
    //��
    dc.SetPen(*wxBLACK_PEN);
    //������
    dc.SetBrush(wxNullBrush);
    int left = OFFSET_X_VIEW;
    int top = OFFSET_Y_VIEW;
    int width = (2 * OFFSET_X_WORLD) / DIV;
    int height = (2 * OFFSET_Y_WORLD) / DIV;
    dc.DrawRectangle(left, top, width, height);

    //�O���b�h
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
