#pragma once

#include <wx/wxprec.h>
#include <wx/bitmap.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
// Include your minimal set of headers here, or wx.h
#include <wx/wx.h>
#endif
#include "wx/settings.h"

#include "header.h"
#include "extensions.h"
#include "FileHandler.h"
#include "map.h"
#include "game_wad.h"
#include "weapons.h"
#include "items.h"
#include "monsters.h"
#include "scenery_definitions.h"
#include "mysound.h"
#include "computer_interface.h"

#include <HPLLib/HPLAlephLib.h>
#include <MapEditorOneSetting.h>
#include <MapEditorOneInnerSetting.h>

#include <vector>
#include <string>

static wxString TITLE_TEXT_BASE = wxString(_T("Map Editor One"));

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

    //�A�C�e���A�C�R��
    wxBitmap itemIconBitmaps[NUMBER_OF_DEFINED_ITEMS];
    wxBitmap hilightedItemIconBitmaps[NUMBER_OF_DEFINED_ITEMS];

    //�}�b�v�A�C�R��
    wxBitmap mapIconBitmaps[NUMBER_OF_MAP_ICONS];
    wxBitmap hilightedMapIconBitmaps[NUMBER_OF_MAP_ICONS];

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
    std::vector<std::vector<wxBitmap> > textureBitmaps;

    //�ҏW���[�h�ƃ��j���[ID�̑Ή�
    std::map<int, int> menuIDMap;

private:
    
    ///////////////////////
    // view grid
    /** �r���[���O���b�h�}�l�[�W���[ */
    hpl::aleph::view::HPLViewGridManager viewGridManager;

    //�}�b�v���ύX���ꂽ��
    bool isChanged;

    //�C�x���g�Ǘ�
    hpl::aleph::HPLEventManager eventManager;

public:
    ///////////////////////////////////
    ///////////////////////////////////
    // �֐�

    /**
        �r���[�O���b�h�̒����}�l�[�W���[���擾���܂�
    */
    hpl::aleph::view::HPLViewGridManager* getViewGridManager();

    virtual bool OnInit();
    /**
        ��ʓI�ȏ�����
    */
    bool initialize();

    //////////////////////////
    // �|���S��������
    //�|���S�������������ǂ������������܂�(������)
    bool isPolygonValidityStored(int polyIndex);

    //�|���S�������������X�V���܂�
    void updatePolygonValidityStored();

    //�C�x���g�}�l�[�W���[���擾���܂�
    hpl::aleph::HPLEventManager* getEventManager();

    //�r���[���W�����[���h���W�ɒ�������̊ȈՔ�
    world_point2d getWorldPointFromViewPoint(int vx, int vy);
    //
    void getViewPointFromWorldPoint(world_point2d& wpoint, int vpoint[2]);

private:
    /**
        �A�C�R���p�̃r�b�g�}�b�v�t�@�C����ǂݍ��݂܂�
    */
    void loadIconBitmaps(const char* baseDirPath);

    /**
        �r�b�g�}�b�v�̓ǂݍ��݁i�ȈՔŁj
    */
    void loadBitmap(const char* fname, wxBitmap* bitmap);
};

//���̂��������܂�
DECLARE_APP(MapEditorWX)
