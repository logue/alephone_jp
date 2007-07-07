/*
MapEditorOne
Marathon and AlephOne's Map file editor
Copyright (C) 2007  Koji Koizumi(HN:HogePiyo)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#pragma once

#include <wx/wxprec.h>
#include <wx/bitmap.h>
#include <wx/dcbuffer.h>
#include <wx/bmpbuttn.h>
#include <wx/sizer.h>
#include <wx/cursor.h>
#include <wx/xrc/xmlres.h>
#include <wx/filedlg.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
// Include your minimal set of headers here, or wx.h
#include <wx/wx.h>
#endif
#include "wx/settings.h"


#include <HPLLib/HPLAlephLib.h>
#include <MapEditorOneSetting.h>
#include <MapEditorOneInnerSetting.h>


#include <vector>
#include <string>

static wxString TITLE_TEXT_BASE = wxString(_T("Map Editor One"));

class MapEditorMainFrame;

//�I���������̂̎��
enum{
    _no_selected,
    _selected_point,
    _selected_line,
    _selected_polygon,
    _selected_object,
};

/**
    �A�v���P�[�V�����̃��C���N���X
*/
class MapEditorWX: public wxApp
{
public:

    //////////////////////////////////////////////
    ////// Level names
    //level names stock
    std::vector<std::string> levelNameList;

    //editing level index
    int editLevelIndex;

    //color for polygon type
    int polygonTypeColors[NUMBER_OF_POLYGON_TYPE][3];
    
    //color for height(variables)
    //TODO height �p�r
    int heightColorList[2][3];

    ///////////////////////
    //�I�u�W�F�N�g�֘A
    //�I�u�W�F�N�g�^�C�v
    hpl::aleph::Information objectTypeInfo[NUMBER_OF_MAP_OBJECT_TYPES];
        //�����X�^�[
        hpl::aleph::Information monsterTypeInfo[NUMBER_OF_MONSTER_TYPES];
        //�I�u�W�F
        hpl::aleph::Information sceneryTypeInfo[NUMBER_OF_SCENERY_DEFINITIONS];
        //�A�C�e��
        hpl::aleph::Information itemTypeInfo[NUMBER_OF_DEFINED_ITEMS];
        //��
        hpl::aleph::Information soundSourceTypeInfo[NUMBER_OF_AMBIENT_SOUND_DEFINITIONS];
        //�N��
        hpl::aleph::Information activateTypeInfo[NUMBER_OF_ACTIVATE_TYPES];

    //�t���O
    hpl::aleph::InformationBinded flagInfo[NUMBER_OF_OBJECT_FLAGS];

    ////////////////////////
    //�}�b�v�֘A
    //��
    hpl::aleph::Information envInfo[NUMBER_OF_ENVIRONMENTS];
    //�w�i
    hpl::aleph::Information landscapeInfo[NUMBER_OF_LANDSPACES];
    //TODO �Q�[���^�C�v
    //NUMBER_OF_GAME_TYPES
    //���^�C�v
    hpl::aleph::InformationBinded envTypeInfo[NUMBER_OF_ENV_TYPES];
    //�~�b�V�����^�C�v
    hpl::aleph::InformationBinded missionTypeInfo[NUMBER_OF_MISSION_TYPES];

    //�^�[�~�i���^�C�v
    hpl::aleph::Information terminalTypeInfo[NUMBER_OF_GROUP_TYPES];

    //�|���S���^�C�v
    hpl::aleph::Information polygonTypeInfo[NUMBER_OF_POLYGON_TYPE];

    //���͉��y
    hpl::aleph::Information ambientSoundTypeInfo[NUMBER_OF_AMBIENT_SOUND_DEFINITIONS];
    //�����_���T�E���h
    hpl::aleph::Information randomSoundTypeInfo[NUMBER_OF_RANDOM_SOUND_DEFINITIONS];

    ////////////////////////
    //�I�����
    //�I��Ώۂ�ID
    hpl::aleph::map::HPLSelectData selectData;

    //�R�s�y�ŕێ�����f�[�^
    hpl::aleph::map::HPLRealMapData storedMapData;
    //���炷�ʒu
    int storedDataDiffPointDelta[2];

/*    //�A�C�e���A�C�R��
    wxBitmap itemIconBitmaps[NUMBER_OF_DEFINED_ITEMS];
    wxBitmap hilightedItemIconBitmaps[NUMBER_OF_DEFINED_ITEMS];

    //�}�b�v�A�C�R��
    wxBitmap mapIconBitmaps[NUMBER_OF_MAP_ICONS];
    wxBitmap hilightedMapIconBitmaps[NUMBER_OF_MAP_ICONS];
*/

    ///////////////////////
    // ���ǉ�
    //���ǉ��ɂ�����ŏ��̓_�w�肩�H
    bool isFirstOfLineToAdd;
    //�O��I�������_�̃C���f�b�N�X
    int prevPointIndex;
    
    //�ҏW�ݒ�
    MapEditorOneSetting setting;

    //Shapes���[�h���H
    bool isLoadedShapesFile;

    //�v���Z�b�g�Œǉ�����|���S���̒��_��
    int nPolygonPoints;

    //�e�N�X�`���f�[�^
    //TODO texture
    std::vector<std::vector<wxBitmap> > textureBitmaps;

    //�ҏW���[�h�ƃ��j���[ID�̑Ή�
    //TODO menu
    std::map<int, int> menuIDMap;

    //���\�[�X�t�@�C��
    wxXmlResource xrc;

    //�������͈͊O�̐���\�����邩�ǂ���(�f�t�H���g:false)
    bool isRevealHiddenLines;

    //�}�b�v���ύX���ꂽ��
    bool isChanged;
    //�t�@�C���p�X
    wxString filePath;

    //�v���Z�b�g�Œǉ�����|���S���̒��_��
    int presetPolygonVertexCount;

    //���݂̃|�C���g�͓_�̏�ɂ��邩�H
    //�������A�����͈͂̊O�ɂ���ꍇ�l�����Ȃ�
    bool isNowOnThePoint;
    bool isNowOnTheLine;

    wxMenu linePopupMenu;
    wxMenu pointPopupMenu;

    //popup�p�C���f�b�N�X�o��
    int popupEndpointIndex;
    int popupLineIndex;
    //public �����o�ϐ� �����܂�
private:
    
    ///////////////////////
    // view grid
    /** �r���[���O���b�h�}�l�[�W���[ */
    hpl::aleph::view::HPLViewGridManager viewGridManager;

    //�C�x���g�Ǘ�
    hpl::aleph::HPLEventManager eventManager;

    //�X�g�b�N���Ǘ�
    hpl::aleph::HPLStockManager stockManager;

    //Shapes�}�l�[�W���[
    hpl::shapes::HPLShapesManager shapesManager;

    //�c�[�����Ƃ̃J�[�\��
    wxCursor cursors[ToolType::NUMBER_OF_TOOLS];

    //�I�����C���J�[�\��
    wxCursor onLineCursor;
    //�I���|�C���g�J�[�\��
    wxCursor onPointCursor;
    //�ʏ탉�C���J�[�\��
    //wxCursor lineToolCursor;

    //�ǉ����J�[�\��
    wxCursor onLineCursorAdding;
    wxCursor onPointCursorAdding;
    wxCursor lineToolCursorAdding;

    //�o�P�c
    wxCursor fillCursor;
    //���ዾ
    wxCursor magCursor;

    //�E�C���h�E�t���[��
    MapEditorMainFrame *frame;
public:
    ///////////////////////////////////
    ///////////////////////////////////
    // �֐�

    /**
        �r���[�O���b�h�̒����}�l�[�W���[���擾���܂�
    */
    hpl::aleph::view::HPLViewGridManager* getViewGridManager();

    //Shapes�}�l�[�W���[�擾
    hpl::shapes::HPLShapesManager* getShapesManager();

    virtual bool OnInit();
    /**
        ��ʓI�ȏ�����
    */
    bool initialize();


    //�C�x���g�}�l�[�W���[���擾���܂�
    hpl::aleph::HPLEventManager* getEventManager();

    //�X�g�b�N�}�l�[�W�����擾���܂�
    hpl::aleph::HPLStockManager* getStockManager();

    //�r���[���W�����[���h���W�ɒ�������̊ȈՔ�
    world_point2d getWorldPointFromViewPoint(int vx, int vy);
    //
    void getViewPointFromWorldPoint(world_point2d& wpoint, int vpoint[2]);
    void getViewPointFromWorldPoint(int x, int y, int vpoint[2])
    {
        world_point2d wpoint = {x,y};
        this->getViewPointFromWorldPoint(wpoint, vpoint);
    }

    /**
        �r�b�g�}�b�v�̓ǂݍ��݁i�ȈՔŁj
    */
    void loadBitmap(const char* fname, wxImage* bitmap);
    void loadImage(const char* fname, wxImage* bitmap);
    /**
        �J���[�}�X�N�t���œǂݍ���
    */
    void loadImage(const char* fname, wxImage* img, int r, int g, int b);

    /**
        ���݂̃��[�h�E�c�[���ɂ��킹�ăJ�[�\����ύX���܂�
    */
    void setCursor();

    /**
        ���ҏW�������������܂�
    */
    void resetLineEditInfo();

    void getShapesImage(wxImage* img, int collection, int clut, int index);
private:

};

//���̂��������܂�
DECLARE_APP(MapEditorWX)

//char->wx
wxString getString(const char* format, ...);
