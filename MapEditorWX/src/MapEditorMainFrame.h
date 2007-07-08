#pragma once

//dialogues
//modal
#include "AnnotationDialog.h"
#include "ColorCustomizeDialog.h"
#include "EditorPreferencesDialog.h"
#include "LevelInfoDialog.h"
#include "PlacementDialog.h"
#include "PlatformDialog.h"
#include "PolygonNumDialog.h"
#include "SelectLevelDialog.h"
#include "TerminalDialog.h"
#include "VisualDialog.h"

//modeless
//tool
#include "ToolDialog.h"
//height
#include "HeightDialog.h"
//palettes
#include "HeightPaletteDialog.h"
#include "LightPaletteDialog.h"
#include "MediaPaletteDialog.h"
#include "SoundPaletteDialog.h"
#include "TextureDialog.h"
//properties
#include "ObjectPropDialog.h"
#include "LinePropDialog.h"
#include "PointPropDialog.h"
#include "PolygonPropDialog.h"
#include "PolygonTypeDialog.h"
#include "SidePropDialog.h"


#include "MapEditorWX.h"
#include "HPLLib/HPLAlephLib.h"

/**
    event id
*/
enum
{
    ID_New = wxID_NEW,
    ID_Open = wxID_OPEN,
    ID_Save = wxID_SAVE,
    ID_SaveAs = wxID_SAVEAS,
    ID_Print = wxID_PRINT,
    ID_PrintPreview = wxID_PREVIEW,
    ID_PrintSetup = wxID_PRINT_SETUP,
    ID_Quit = wxID_EXIT,
    ID_About = wxID_ABOUT,

    ID_Undo = wxID_UNDO,
    ID_Redo = wxID_REDO,
    ID_Cut = wxID_CUT,
    ID_Copy = wxID_COPY,
    ID_Paste = wxID_PASTE,
    ID_Preference = wxID_PREFERENCES,

    ID_Merge = 1,
    //show
    ID_ToolDialog,
    ID_ZoomIn,
    ID_ZoomOut,
    ID_ZoomDefault,
    ID_MoveToCenter,
//    ID_ObjectPropDialog,
    ID_HeightDialog,

    //mode
    ID_DrawPolygonMode,
    ID_VisualMode,
    ID_PolygonTypeMode,
    ID_FloorHeightMode,
    ID_CeilingHeightMode,
    ID_FloorLightMode,
    ID_CeilingLightMode,
    ID_MediaMode,
    ID_FloorTextureMode,
    ID_CeilingTextureMode,

    //Special
    ID_JumpLevel,
    ID_LevelInfo,
    ID_ObjectPlacement,
    ID_TerminalViewer,

    //popup menu
    ID_LineProp,
    ID_ClockwiseSideProp,
    ID_CounterclockwiseSideProp,
    ID_PointProp,
};  

//���\�[�XID
enum{
    ID_ANNOTATION_DIALOG,

};

/**
    editor's main frame
*/
class MapEditorMainFrame: public wxFrame
{
public:
    //�v���p�e�B�� <en> properties
    ObjectPropDialog objPropDialog;
    LinePropDialog linePropDialog;
    PointPropDialog pointPropDialog;
    PolygonTypeDialog polyTypeDialog;
    PolygonPropDialog polyPropDialog;
    SidePropDialog sidePropDialog;
private:
    //�_�u���o�b�t�@�����O�pBitmap
    wxBitmap doubleBufferingBitmap;
    //wxMemoryDC doubleBufferingDC;
//    wxBufferedPaintDC bufferedPainDC

    /////////////////////
    //�_�C�A���O(���[�h���X)
    //tool
    ToolDialog toolDialog;
    //���� <en> height
    HeightDialog heightDialog;
    //�p���b�g�� <en> palettes
    HeightPaletteDialog heightPaletteDialog;
    LightPaletteDialog lightPaletteDialog;
    MediaPaletteDialog mediaPaletteDialog;
    TextureDialog textureDialog;

    SoundPaletteDialog soundPaletteDialog;

    //TODO ���[�_�������ASide�I���_�C�A���O����낤
    //TODO JumpLevel, LevelInfo

    //�N�����ƁA�F�ݒ�ύX���ɂ�����ύX���邱��
    //TODO �ݒ�ύX�R�[�h
    //�O���b�h���א�
    wxPen gridPen;
    //�O���b�h������
    wxPen gridLargePen;
    //�w�i�y��
    wxPen backgroundPen;
    //�w�i�u���V
    wxBrush backgroundBrush;
    //�^�C�v�ʃ|���S���F
    wxBrush polyTypeBrushes[NUMBER_OF_POLYGON_TYPE];
    //�|���S���I��Ԋ|���u���V
    wxBrush polySelNetBrush;
    //�C�����@���b�h�ȃ|���S��
    wxBrush invalidBrush;
    //�I��F
    wxPen selectedLinePen;
    //�ʏ��
    wxPen linePen;
    //�ʏ�_
    wxPen pointPen;
    wxBrush pointBrush;
    //�ʏ�|���S��
    wxBrush polyBrush;

    //���������̐��F
    wxPen sameHeightLinePen;
    //�i���̂�����F
    wxPen stairLinePen;

    //�A�C�e���r�b�g�}�b�v
    wxImage itemBitmaps[NUMBER_OF_DEFINED_ITEMS];
    //�n�C���C�g��
    wxImage hilightedItemBitmaps[NUMBER_OF_DEFINED_ITEMS];

    //�}�b�v�v�f�r�b�g�}�b�v�i����j
    wxImage mapItemBitmaps[NUMBER_OF_MAP_ICONS];
    //�n�C���C�g��
    wxImage hilightedMapItemBitmaps[NUMBER_OF_MAP_ICONS];

    //
//    wxBitmap 
    //�����X�^�[�y��
    wxPen monsterPen;
    wxPen selectedMonsterPen;
    wxBrush monsterBrush;
    wxBrush selectedMonsterBrush;
    //�v���C���[�y���E�u���V
    wxPen playerPen;
    wxPen selectedPlayerPen;
    wxBrush playerBrush;
    wxBrush selectedPlayerBrush;
    //�����y���E�u���V <en> ally
    wxPen allyPen;
    wxPen selectedAllyPen;
    wxBrush allyBrush;
    wxBrush selectedAllyBrush;

    //�͈͑I��\��
    wxPen selectingPen;

    wxImage texture;
public:
    MapEditorMainFrame(const wxString& title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize);
    virtual ~MapEditorMainFrame();

    //���j���[<en> menu
    //�t�@�C�����j���[ <en>Files menu
    void OnNew(wxCommandEvent& ev);
    void OnOpen(wxCommandEvent& ev);
    void OnSave(wxCommandEvent& ev);
    void OnSaveAs(wxCommandEvent& ev);
    void OnPrint(wxCommandEvent& ev);
    void OnPrintPreview(wxCommandEvent& ev);
    void OnPrintSetup(wxCommandEvent& ev);
    void OnQuit(wxCommandEvent& ev);
    void OnAbout(wxCommandEvent& ev);
    void OnMerge(wxCommandEvent& ev);

    //�ҏW���j���[<en>Edit menus
    void OnUndo(wxCommandEvent& ev);
    void OnRedo(wxCommandEvent& ev);
    void OnCut(wxCommandEvent& ev);
    void OnCopy(wxCommandEvent& ev);
    void OnPaste(wxCommandEvent& ev);
    void OnPreference(wxCommandEvent& ev);

    //�\�����j���[<en>show
    void OnToolDialog(wxCommandEvent& ev);
    void OnZoomIn(wxCommandEvent& ev);
    void OnZoomOut(wxCommandEvent& ev);
    void OnZoomDefault(wxCommandEvent& ev);
    void OnMoveToCenter(wxCommandEvent& ev);
//    void OnObjectPropDialog(wxCommandEvent& ev);
    void OnHeightDialog(wxCommandEvent& ev);

    //���[�h<en>Mode
    void OnDrawPolygonMode(wxCommandEvent& ev);
    void OnVisualMode(wxCommandEvent& ev);
    void OnPolygonTypeMode(wxCommandEvent& ev);
    void OnFloorHeightMode(wxCommandEvent& ev);
    void OnCeilingHeightMode(wxCommandEvent& ev);
    void OnFloorLightMode(wxCommandEvent& ev);
    void OnCeilingLightMode(wxCommandEvent& ev);
    void OnMediaMode(wxCommandEvent& ev);
    void OnFloorTextureMode(wxCommandEvent& ev);
    void OnCeilingTextureMode(wxCommandEvent& ev);

    //���ʃ��j���[<en>Special!
    void OnJumpLevel(wxCommandEvent& ev);
    void OnLevelInfo(wxCommandEvent& ev);
    void OnObjectPlacement(wxCommandEvent& ev);
    void OnTerminalViewer(wxCommandEvent& ev);

    //�|�b�v�A�b�v���j���[ <en> popup menu
    void OnLineProp(wxCommandEvent& ev);
    void OnClockwiseSide(wxCommandEvent& ev);
    void OnCounterclockwiseSide(wxCommandEvent& ev);
    void OnPointProp(wxCommandEvent& ev);

    void OnPaint(wxPaintEvent& ev);

    void OnLeftDown(wxMouseEvent& ev);
    void OnLeftUp(wxMouseEvent& ev);
    void OnRightDown(wxMouseEvent& ev);
    void OnRightUp(wxMouseEvent& ev);
    void OnMotion(wxMouseEvent& ev);
    void OnMouseWheel(wxMouseEvent& ev);
    void OnLeftDoubleClick(wxMouseEvent& ev);

    //�T�C�Y�ύX<en>change window size event
    void OnSize(wxSizeEvent& ev);
    //�_�u���o�b�t�@�����O���̔w�i�폜��~�p<en>to disable erasing backgroud for double buffering
    void OnEraseBackground(wxEraseEvent& ev);

    //
    //�C�x���g�e�[�u���쐬<en>declare
    DECLARE_EVENT_TABLE()

private:
    /**
        �_�u���o�b�t�@�����O����
        �N�����ƃE�C���h�E�T�C�Y�ύX���ɌĂ�
        <en> setup buffer for double buffering
        call this when (1)starting and (2)resizing window
    */
    void createDoubleBuffer();
    /**
        ���j���[�̃Z�b�g�A�b�v
        <en> setup menu items
    */
    void setupMenus();

    /**
        �}�b�v�f�[�^�̕\��
        <en> draw map items
    */
    /**
        �w�i�`��
        <en> draw background, drawable area, and grid
        @param dc �f�o�C�X�R���e�L�X�g <en> device context
    */
    void drawBackground(wxDC* dc);
    void drawPolygons(wxDC* dc);
    void drawLines(wxDC* dc);
    void drawSides(wxDC* dc);
    void drawPoints(wxDC* dc);
    void drawObjects(wxDC* dc);
    void drawAnnotations(wxDC* dc);

    //////////////////////////////////
    // ���̋K��FdoLButtonOn[�ҏW���[�h��]
    //           doLButtonOn[�h���[���[�h�̃c�[����]
    // <en>     :doLButtonOn[name of Edit Mode]
    //          :doLButtonOn[name of tool in Draw Mode]
    /**
        �}�E�X�C�x���g����
    */
    void doLButtonOnDrawMode(wxMouseEvent& ev);
        void doLButtonOnArrowTool(wxMouseEvent& ev);
        void doLButtonOnFillTool(wxMouseEvent& ev);
        void doLButtonOnHandTool(wxMouseEvent& ev);
        void doLButtonOnLineTool(wxMouseEvent& ev);
        void doLButtonOnMagnifyTool(wxMouseEvent& ev);
        void doLButtonOnSkullTool(wxMouseEvent& ev);
        void doLButtonOnTextTool(wxMouseEvent& ev);
        void doLButtonOnPolygonTool(wxMouseEvent& ev);
    void doLButtonOnPolygonMode(wxMouseEvent& ev);
    void doLButtonOnFloorHeightMode(wxMouseEvent& ev);
    void doLButtonOnCeilingHeightMode(wxMouseEvent& ev);
    void doLButtonOnFloorLightMode(wxMouseEvent& ev);
    void doLButtonOnCeilingLightMode(wxMouseEvent& ev);
    void doLButtonOnMediaMode(wxMouseEvent& ev);
    void doLButtonOnFloorTextureMode(wxMouseEvent& ev);
    void doLButtonOnCeilingTextureMode(wxMouseEvent& ev);

    /**
        �}�E�X���{�^�����������Ƃ�
    */
    void doLUpOnArrowTool(wxMouseEvent& ev);
    void doLUpOnPolygonTool(wxMouseEvent& ev);

    // �I�t�Z�b�g���w�肵���}�E�X�|�C���g�ɂ���Ĉړ������܂�
    void moveMapOffset(int x, int y);

    /////////////////////////////////////
    // ���̋K��FdoMouseMotionOn[]
    /**
        ���c�[��@�h���[���[�h��D&D
    */
    void doMouseMotionOnDrawMode(wxMouseEvent& ev);
        void doMouseMotionOnArrowTool(wxMouseEvent& ev);
        void doMouseMotionOnFillTool(wxMouseEvent& ev);
        void doMouseMotionOnHandTool(wxMouseEvent& ev);
        void doMouseMotionOnLineTool(wxMouseEvent& ev);
        void doMouseMotionOnMagnifyTool(wxMouseEvent& ev);
        void doMouseMotionOnSkullTool(wxMouseEvent& ev);
        void doMouseMotionOnTextTool(wxMouseEvent& ev);
        void doMouseMotionOnPolygonTool(wxMouseEvent& ev);
    void doMouseMotionOnPolygonMode(wxMouseEvent& ev);
    void doMouseMotionOnFloorHeightMode(wxMouseEvent& ev);
    void doMouseMotionOnCeilingHeightMode(wxMouseEvent& ev);
    void doMouseMotionOnFloorLightMode(wxMouseEvent& ev);
    void doMouseMotionOnCeilingLightMode(wxMouseEvent& ev);
    void doMouseMotionOnMediaMode(wxMouseEvent& ev);
    void doMouseMotionOnFloorTextureMode(wxMouseEvent& ev);
    void doMouseMotionOnCeilingTextureMode(wxMouseEvent& ev);

    /**
        �}�b�v�`��p�u���V�E�y���̃Z�b�g�A�b�v
        @param setting �J���[�ݒ�f�[�^ <en> setting data for color
    */
    void setupPenAndBrush(ColorSettings* setting);

    /**
        �A�C�R���p�̃r�b�g�}�b�v�t�@�C����ǂݍ��݂܂�
    */
    void loadIconBitmaps(const char* baseDirPath);

    /**
        �ҏW���[�h���j���[�̃`�F�b�N��S�Ă͂����܂�
    */
    void uncheckModesOnMenu();

    /**
        �I�t�Z�b�g��ݒ肵�܂�
        @param mx,my �r���[���W�̊�_�ʒu
    */
    void setupSelectDataGroupOffsets(int mx, int my);

    /**
        @param ev
        @return �I���ɐ��������ꍇ�^
    */
    bool tryToSelectOneItem(wxMouseEvent& ev);

    /**
        �V�������[�h�ɐ؂�ւ��܂�
    */
    void changeEditMode(int mode);

    void closeAllModelessDialogs();

    void initLevel();

    /**
        �_�C�A���O���o���ĕҏW���̃}�b�v��j�󂵂Ă悢���𕷂��o���܂��B
        
        @param ���[�U����OK���o��ΐ^�B�o�Ȃ���΋U�B
            �܂��A�ҏW����ĂȂ���ΐ^���Ԃ�
    */
    bool askDestructMap();
};
