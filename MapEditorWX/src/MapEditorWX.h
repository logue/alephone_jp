#pragma once

#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
// Include your minimal set of headers here, or wx.h
#include <wx/wx.h>
#endif
#include "wx/settings.h"

#include "AlephOne/header.h"
#include "AlephOne/extensions.h"
#include "AlephOne/FileHandler.h"
#include "AlephOne/map.h"
#include "AlephOne/game_wad.h"
#include "AlephOne/weapons.h"
#include "AlephOne/items.h"
#include "AlephOne/monsters.h"
#include "AlephOne/scenery_definitions.h"
#include "AlephOne/mysound.h"

#include <HPLLib/HPLAlephLib.h>

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
    vector<wxColor> polygonTypeColorList;
    
    //color for height(variables)
    vector<wxColor> heightColorList;

public:
    /**
        �r���[�O���b�h�̒����}�l�[�W���[���擾���܂�
    */
    hpl::aleph::view::HPLViewGridManager* getViewGridManager();

    virtual bool OnInit();
    bool initialize();
private:
    ///////////////////////
    // view grid
    /** �r���[���O���b�h�}�l�[�W���[ */
    hpl::aleph::view::HPLViewGridManager viewGridManager;

    /**
        �f�[�^��������擾���܂�
        load data strings from file
        @param filePath �t�@�C���p�X file path
        @param maxLines �ő�s��
    */
    void loadInfo(const char* filePath, int maxLines);
};

//wxString->char
///disabled

DECLARE_APP(MapEditorWX)

//void wxStringToChar(wxString& str, char* cstr);
