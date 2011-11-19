/*  DefaultStringSets.cpp - support for compiled-in 

	Copyright (C) 2002 and beyond by the "Aleph One" developers.
 
	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	This license is contained in the file "COPYING",
	which is included with this source code; it is available online at
	http://www.gnu.org/licenses/gpl.html

	Default text StringSets, in case no MML provides them.
	by Woody Zenfell, III
	June 3, 2002

    June 3, 2002: captured text_strings.mml into C++ form for this file.
*/

#include    "cseries.h"

#include    "TextStrings.h"

// This works through what may seem like some weird voodoo.  Static objects are instantiated
// (despite the fact they have no storage); this results in the creation of StringSets in the
// normal StringSet storage area.  Nobody outside this file needs to know it exists; you just
// compile and link it, and the C++ runtime takes care of the instantiations.

class AutoStringSetBuilder {
public:
    AutoStringSetBuilder(short inStringSetID, const char** inStrings, short inNumStrings) {
        for(int i = 0; i < inNumStrings; i++)
            TS_PutCString(inStringSetID, i, inStrings[i]);
    }
};

#define NUMBER_OF_STRINGS(sa)   (sizeof(sa) / sizeof((sa)[0]))

#define BUILD_STRINGSET(id, strs)   static AutoStringSetBuilder (strs ## Builder) (id, strs, NUMBER_OF_STRINGS(strs))



// StringSets from original Bungie resources
// -----------------------------------------------------------------------------------------
// <!-- STR# Resource: "Errors" -->
static const char* sStringSetNumber128[] = {
	"AlephOne�ɂ�68040�ȏ�̃v���Z�b�T���K�v�ł��B",
	"���̒ʒm�́A�V�����o�[�W������AlephOne�����ɍ���Ă���A�v���C�ł��Ȃ��ꍇ�ɕ\\������܂��BAlephOne���A�b�v�O���[�h���Ă��������B",
	"�X�N���[���z�C�[���́A����̐؂�ւ��Ŏg�p����Ă��܂��B",
};

// STR# Resource: "Filenames"
static const char* sStringSetNumber129[] = {
    "Shapes",
    "Shapes.16",
    "Sounds",
    "Sounds.16",
    "Aleph One Preferences",
    "Map",
    "Untitled Game",
    "Marathon",
    "Aleph One Recording",
    "Physics Model",
    "Music",
    "Images",
    "Movie",
    "Default",
};

// STR# Resource: "Top-Level Interface Items"
static const char* sStringSetNumber130[] = {
	"�V�K�Q�[��",
	"�����̃Q�[�����J��",
	"",
	"�Ō�̃Q�[�����Đ�",
	"�t�B�������J��",
	"�t�B�����̕ۑ�",
	"",
	"�l�b�g�Q�[���W��",
	"�l�b�g�Q�[���Q��",
	"",
	"�ݒ�",
	"�f���J�n",
	"�I��",
};

// STR# Resource: "Prompts"
static const char* sStringSetNumber131[] = {
    "�Q�[���ۑ�",
    "�f��̕ۑ�",
    "�f��̑I���F",
    "�f�t�H���g",
};

// STR# Resource: "Network Errors"
static const char* sStringSetNumber132[] = {
	"���̃v���[���[�̓l�b�g���[�N��Ō�����܂���B�Q�[���Q���̃_�C�A���O����L�����Z��������������܂���B",

	"�������̃v���[���[���l�b�g���[�N��Ō�����Ȃ����߁A"
	"�Q�[�������f����܂����B",

	"�z�X�g�����Ă���R���s���[�^����̉���������܂���B"
	"�t�@�C���[�E�H�[�����K�؂ɐݒ肳��Ă��邩�A�A�h���X���Ԉ���Ă��Ȃ������m�F���ĉ������B",

	"Sorry, the gathering computer has cancelled the game (you should all gang up on him next game).",

	"The map was not received in its entirety, so the game has been canceled.",

	"�Ăяo�����̃R���s���[�^���n�}�𑗂�Ȃ��������߁A�Q�[�����L�����Z������܂����B���̃R���s���[�^�̐ڑ����؂ꂽ��������܂���B",
	"AlephOne�́A�Q�[�����J�n�ł��܂���B���̃R���s���[�^�̐ڑ����؂ꂽ��������܂���B",
	"�Q�[���̎Q�����ɃG���[���������܂���(�A�v���P�[�V�����̃o�[�W�������Ⴄ��������܂���)�B������x�����Ă݂Ă��������B",
	"�l�b�g���[�N�G���[�̂���AlephOne�͑��s�ł��܂���B",

	"�o�[�W�������قȂ邽�߂��̃v���[���[�̓Q�[���ɎQ���ł��܂���ł����B",

	"���̃v���C���[�́A���ݕ�W�������Ă���Q�[���̂������̊g���@�\\���g�p�ł��Ȃ��Â��o�[�W������AlephOne���g�p���Ă���悤�ł��B���̂��߁A���̃Q�[�����J�n���邱�Ƃ��ł��܂���B",
	"���ݕ�W�������Ă���Q�[���ɁA�g���@�\\�ɑΉ����Ă��Ȃ�AlephOne���g���Ă���v���C���[���Q�����悤�Ƃ��܂����B",
	"AlephOne�́A���̃��x���̃}�b�v�t�@�C���������邱�Ƃ��ł��܂���ł����B�������̃^�[�~�i��������ɕ\\������Ȃ���������܂���B�܂��A���̃R���s���[�^�[��ŃQ�[����ۑ����邱�Ƃ͐����ł��܂���B",
	"��W�������Ă����l�����Ȃ��Ȃ�܂����B",

	"��W�������Ă���l�������邱�Ƃ��ł��܂���B�A�h���X�����������͂���Ă��邩���m�F���������B",

	"�T�[�o�[����}�b�v�𑗂�Ƃ��ɃG���[���������܂����B�Q�[���I�����܂��B",

	"The gatherer is using the star protocol, but your configuration is set to ring. You will not appear in the list of available players.",

	"The gatherer is using the ring protocol, but your configuration is set to star. You will not appear in the list of available players.",

	"The gatherer is using a Lua netscript, but this version was built without Lua support. You will not appear in the list of available players.",

	"There was a problem connecting to the server that tracks Internet games.  Please try again later.",

	"Your game could not be advertised on the Internet.  Please distribute your public IP address by other means or try again later.",

	"Aleph One�́A�t�@�C���[�E�H�[���⃋�[�^�[�̐ݒ��ύX���邱�Ƃ��ł��܂���ł����B�v���C���[���W���邱�Ƃ��ł��܂���B"
	
};

// STR# Resource: "Key Codes To Names"
static const char* sStringSetNumber133[] = {
    "A",
    "S",
    "D",
    "F",
    "H",
    "G",
    "Z",
    "X",
    "C",
    "V",
    "0x0A",
    "B",
    "Q",
    "W",
    "E",
    "R",
    "Y",
    "T",
    "1",
    "2",
    "3",
    "4",
    "6",
    "5",
    "=",
    "9",
    "7",
    "-",
    "8",
    "0",
    "]",
    "O",
    "U",
    "[",
    "I",
    "P",
    "Return",
    "L",
    "J",
    "'",
    "K",
    ";",
    "\\",
    ",",
    "/",
    "N",
    "M",
    ".",
    "Tab",
    "Space",
    "`",
    "Delete",
    "0x34",
    "Escape",
    "0x35",
    "?",
    "Shift",
    "Caps Lock",
    "Option",
    "Control",
    "0x3c",
    "0x3d",
    "0x3e",
    "0x3f",
    "0x40",
    "Keypad .",
    "0x42",
    "Keypad *",
    "0x44",
    "Keypad +",
    "0x46",
    "Clear",
    "0x48",
    "0x49",
    "0x4a",
    "Keypad /",
    "Enter",
    "0x4d",
    "Keypad -",
    "0x4f",
    "0x50",
    "Keypad =",
    "Keypad 0",
    "Keypad 1",
    "Keypad 2",
    "Keypad 3",
    "Keypad 4",
    "Keypad 5",
    "Keypad 6",
    "Keypad 7",
    "0x5a",
    "Keypad 8",
    "Keypad 9",
    "0x5d",
    "0x5e",
    "0x5f",
    "F5",
    "F6",
    "F7",
    "F3",
    "F8",
    "F9",
    "0x66",
    "F11",
    "0x68",
    "F13",
    "0x6a",
    "F14",
    "0x6c",
    "F10",
    "0x6e",
    "F12",
    "0x70",
    "F15",
    "Help",
    "Home",
    "Page Up",
    "Forw. Del.",
    "F4",
    "End",
    "F2",
    "��",
    "F1",
    "��",
    "��",
    "��",
    "��",
    "Power",
};

// STR# Resource: "Preferences Advice"
static const char* sStringSetNumber134[] = {
	"�O���X�s�[�J�[���̓w�b�h�t�H�����ڑ�����A�T�E���h�̃R���g���[���p�l���ŃX�e���I�o�͂��I���ɂȂ��Ă��邱�Ƃ��m�F���Ă��������B",
};

// STR# Resource: "Computer Interface"
static const char* sStringSetNumber135[] = {
    "U.E.S.C. Marathon",
//    "Opening Connection to b.4.5-23",
	"��.4.5-23 �Ɛڑ��J�n��",
    "CAS.qterm//CyberAcme Systems Inc.",
    "<931.461.60231.14.vt920>",
//    "UESCTerm 802.11 (remote override)",
	"UESC�^�[�~�i�� 802.11�i�����[�g�I�[�o�[�h���C�u�j",
//    "PgUp/PgDown/Arrows To Scroll",
	"PgUp/PgDown/���L�[�ŃX�N���[��",
//    "Return/Enter To Acknowledge",
	"Return/Enter�L�[�ŗ���",
//    "Disconnecting...",
	"�ڑ��ؒf",
//    "Connection Terminated.",
	"�ڑ��I��",
    "%H%M %m.%d.%Y",
};

// STR# Resource: "Join Dialog Messages"
static const char* sStringSetNumber136[] = {
	"�u�Q���v���N���b�N����ƃl�b�g���[�N�Q�[���ɎQ���ł��܂��B",
	"�T�[�o�[����l�b�g���[�N�Q�[���ɌĂяo�����̂�҂��Ă��܂��B�u�L�����Z���v���N���b�N����ƒ��f���܂��B",
	"�l�b�g���[�N�Q�[���ɎQ�����܂����B�T�[�o�[�͑��̃v���[���[���W�߂Ă��܂�..."
};

// STR# Resource: "Weapon Names"
static const char* sStringSetNumber137[] = {
	"����",
	".44 �}�O�i���E���K�� A1",
	"�[�E�X���j�Z���s�X�g��",
	"MA-75B �@�֏e/�O���l�[�h�C",
	"SPNKR-X18�^�~�T�C�������`���[",
	"TOZT-7 �Ή����ˋ@",
	"����ޕs�� �V�X�e���G���[ 0xfded",
	"WSTE-M �퓬�p�V���b�g�K��",
	"(somehow related to time of applicability)",
	"KKV-7 10MM�t���`�G�b�g���^�y�@�֏e",
};

// STR# Resource: "file search path"
static const char* sStringSetNumber138[] = {
    "Marathon Trilogy:Marathon Infinity:Marathon Infinity:",
};

// STR# Resource: "Preferences Groupings"
static const char* sStringSetNumber139[] = {
	"�O���t�B�b�N",
	"�v���C���[",
	"�T�E���h",
	"�R���g���[��",
	"��"
};

// STR# Resource: "Postgame network game stats"
static const char* sStringSetNumber140[] = {
	"%d ��",
	"%d:%02d",
	"%d �_",
	"�`�[��",
	"�{�[���̕ێ�����",
	"���̕ߊl",
	"����",
	"�S�[��",
	"�w�n�ɂ�������",
	"�w�n�ɂ�������",
	"�|�C���g",
	"����"
};

// STR# Resource: "Net Game Setup"
static const char* sStringSetNumber141[] = {
	"�E������",
	"�E��",
	"�ߊl����",
	"��",
	"�_������",
	"�_��",
	"�w�n�ɂ�������",
	"��",
	"�|�C���g",
	"����"
};

// STR# Resource: "New Join Dialog Messages"
static const char* sStringSetNumber142[] = {
	"�N�́u%s�v�Q�[���Ɏ󂯓�����܂����B�T�[�o�[���c��̃v���[���[��ǉ�����܂ŏ��X���܂����������c",
	"�l�ΐ�"
	"�N�́u�����ΐ�v�Q�[���Ɏ󂯓�����܂����B�T�[�o�[���c��̃v���[���[��ǉ�����܂ŏ��X���܂����������c",
	"�����",
	"�w�n���",
	"�{�[���̎�荇��",
	"�h�q��",
	"���O�r�[",
	"�S������",
	"�N�̓J�X�^���Q�[���Ɏ󂯓�����܂����B�T�[�o�[���c��̃v���[���[��ǉ�����܂ŏ��X���܂����������c",
};

// STR# Resource: "Progress strings for networking"
static const char* sStringSetNumber143[] = {
	"�v���C���[�֒n�}��]�����ł��B",
	"�v���C���[�֒n�}��]�����ł��B",
	"�T�[�o�[����n�}��]�����Ă��܂��B",
	"�T�[�o�[����n�}�̓]�������҂����������B",
	"���f�[�^�𑼂̃v���C���[�֓]�����ł��B",
	"���f�[�^�𑼂̃v���C���[�֓]�����ł��B",
	"���f�[�^���T�[�o�[����]�����Ă��܂��B",
	"�ǂݍ��ݒ��c"
	"���[�^�[�̃|�[�g���J���Ă��܂��c",
	"���[�^�[�̃|�[�g����Ă��܂��c",
	"�A�b�v�f�[�g���m�F���ł��c"
};

BUILD_STRINGSET(128, sStringSetNumber128);
BUILD_STRINGSET(129, sStringSetNumber129);
BUILD_STRINGSET(130, sStringSetNumber130);
BUILD_STRINGSET(131, sStringSetNumber131);
BUILD_STRINGSET(132, sStringSetNumber132);
BUILD_STRINGSET(133, sStringSetNumber133);
BUILD_STRINGSET(134, sStringSetNumber134);
BUILD_STRINGSET(135, sStringSetNumber135);
BUILD_STRINGSET(136, sStringSetNumber136);
BUILD_STRINGSET(137, sStringSetNumber137);
BUILD_STRINGSET(138, sStringSetNumber138);
BUILD_STRINGSET(139, sStringSetNumber139);
BUILD_STRINGSET(140, sStringSetNumber140);
BUILD_STRINGSET(141, sStringSetNumber141);
BUILD_STRINGSET(142, sStringSetNumber142);
BUILD_STRINGSET(143, sStringSetNumber143);



// Stringsets for SDL w_select widgets.
// -----------------------------------------------------------------------------------------
#include    "network_dialogs.h"  // for stringset ID's

static const char*    sDifficultyLevelsStrings[] = {
	"���т��q",
	"�ȒP",
	"����",
	"���",
	"�s�E"
};

static const char*    sNetworkGameTypesStrings[] = {
	"�l�ΐ�",
	"�`�[���v���C",
	"�����",
	"�w�n���",
	"�S������",
	"���O�r�[",
	"�^�O",
	"�l�b�g�X�N���v�g"
};

static const char*    sEndConditionTypeStrings[] = {
//    "No Limit (Alt+Q to quit)",
	"������",
	"���Ԑ���",
	"�X�R�A���"
};

static const char*	sSingleOrNetworkStrings[] = {
	"�\\���ŃQ�[��",
	"�l�b�g���[�N�ŃQ�[��"
};


BUILD_STRINGSET(kDifficultyLevelsStringSetID,   sDifficultyLevelsStrings);
BUILD_STRINGSET(kNetworkGameTypesStringSetID,   sNetworkGameTypesStrings);
BUILD_STRINGSET(kEndConditionTypeStringSetID,   sEndConditionTypeStrings);
BUILD_STRINGSET(kSingleOrNetworkStringSetID,	sSingleOrNetworkStrings);


// More Mac OS string-resource stringsets.
// -----------------------------------------------------------------------------------------
// STR# Resource: "Item names"
static const char* sStringSetNumber150[] = {
    "����",
    ".44 �}�O�i���E���K��",
    ".44 �}�O�i���E���K��",
    ".44 �e�� (x8)",
    ".44 �e�� (x8)",
    "�[�E�X���j�Z���s�X�g��",
    "�j�Z���o�b�e��",
    "�j�Z���o�b�e��",
    "MA-75B �@�֏e",
    "MA-75B �e�� (x52)",
    "MA-75B �e�� (x52)",
    "MA-75B �O���l�[�h (x7)",
    "MA-75B �O���l�[�h (x7)",
    "SPNKR-X18 SSM �~�T�C�����ˋ@",
    "SSM �~�T�C�� (x2)",
    "SSM �~�T�C�� (x2)",
    "�G�C���A���̕���",
    "�V���b�g�K���e�� (x2)",
    "�V���b�g�K���e�� (x2)",
    "TOZT-7 �w�������Ή����ˋ@",
    "�i�p�[���U�e",
    "�i�p�[���U�e",
    "POWERPC 620 �`�b�v",
    "POWERPC 620 �`�b�v",
    "�G�C���A���̃G�l���M�[�ϊ��@",
    "�g���C",
    "�݌v�}",
    "WSTE-M �퓬�p�V���b�g�K��",
    "WSTE-M �퓬�p�V���b�g�K��",
    "�X�t�g�J�[�h�L�[",
    "�X�t�g�J�[�h�L�[",
    "�A�b�v�����N�`�b�v",
    "�A�b�v�����N�`�b�v",
    "���F�̃{�[��",
    "���W��",
    "���F�̃{�[��",
    "���F�̃{�[��",
    "���F�̃{�[��",
    "��F�̃{�[��",
    "�F�̃{�[��",
    "�ΐF�̃{�[��",
    "KKV-7 10MM �t���`�F�b�g���^�y�@�֏e",
    "10MM �t���`�F�b�g�e�q",
    "10MM �t���`�F�b�g�e�q",
};

// STR# Resource: "Item types"
static const char* sStringSetNumber151[] = {
    "����",
    "�e��",
    "�p���[�A�b�v",
    "����",
    "����^�p���[�A�b�v",
    "�{�[��",
    "�l�b�g���[�N��",
};

// STR# Resource: "Net Statistics Strings"
static const char* sStringSetNumber153[] = {
    "�E��: %d�l",
    "���S: %d�l",
    "���E: %d�l",
    "���v",
    "�G",
    "�E���̍��v: %d (�ꕪ������ %.2f�l)",
    "���S�̍��v: %d (�ꕪ������ %.2f�l)",
    " - ���E %d�l���܂�",
    "�`�[���s�E�̍��v",
    " - ���m���� %d�l���܂�",
    "����",
    "�`�[���̐���",
    // ZZZ: added for team vs. team carnage in postgame report
    "%s�̃`�[��",
    // ZZZ: added for legend/key in SDL postgame report
    "�E��",
    "���S",
    "����",
    "����",
};

// STR# Resource: "OpenGL-Option Color-Picker Prompts"
static const char* sStringSetNumber200[] = {
    "�����Ȃ���Ԃ̐F�́H",
    "�����̒n�ʂ̐F�́H",
    "�����̋�̐F�́H",
    "��Ԃ̒n�ʂ̐F�́H",
    "��Ԃ̋�̐F�́H",
    "���̒n�ʂ̐F�́H",
    "���̋�̐F�́H",
    "�F����Ԃ̒n�ʂ̐F�́H",
    "�F����Ԃ̋�̐F�́H",
    "�t�H�b�O�̐F�́H",
};

BUILD_STRINGSET(150, sStringSetNumber150);
BUILD_STRINGSET(151, sStringSetNumber151);
BUILD_STRINGSET(153, sStringSetNumber153);
BUILD_STRINGSET(200, sStringSetNumber200);


#include "player.h" // for kTeamColorsStringSetID

static const char* sTeamColorNamesStrings[] = {
    "�D",
    "��",
    "��",
    "��",
    "��",
    "��",
    "��",
    "��",
};

BUILD_STRINGSET(kTeamColorsStringSetID, sTeamColorNamesStrings);
