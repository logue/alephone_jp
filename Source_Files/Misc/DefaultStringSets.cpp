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
	"AlephOne�ɂ� Color QuickDraw ���K�v�ł��B",
	"AlephOne�ɂ� ����Talk 7.1 �ȍ~�̃V�X�e�����K�v�ł��B",
	"AlephOne�ɂ� 3000k �ȏ�̋�RAM���K�v�ł��B",
	"AlephOne�ɂ�13�C���`�ȏ�(640x480)������256�F(�܂��̓O���[)���\\���ł��郂�j�^���K�v�ł��B",
	"Map, Shapes, Images, Sounds �̃t�@�C���� Marathon �A�v���P�[�V�����Ɠ����t�H���_�ɓ����Ă��邩�m�F���Ă��������B",
	"�V�X�e�������������Ȃ����߃T�E���h�p�̃����������蓖�Ă��܂���(Marathon�̊��蓖�ă����������炵�Ă�������)�B",
	"AlephOne�̎��s���Ƀt�@�C���V�X�e���G���[���������܂����B�f�B�X�N��̋�v�̂ƃ��b�N����Ă��Ȃ����m�F���Ă��������B",
	"����AlephOne�̃R�s�[�̓E�C���X�Ȃǂɂ���ĕύX����Ă��܂��B�I���W�i���̃f�B�X�N����ēx�C���X�g�[�����Ă��������B",
	"This beta copy of Marathon has expired and is no longer functional. Call Bungie at (312) 563-6200 ext. 21 for more information.",
	"���̃L�[�͊��Ƀ{�����[�������Ɏg���Ă��܂��B",
	"���̃L�[�͊��ɒn�}�̃Y�[���Ɏg���Ă��܂��B",
	"���̃L�[�͊��ɃA�C�e���̃X�N���[���Ɏg���Ă��܂��B",
	"���̃L�[�͊��ɃQ�[���̋@�\\�Ɏg���Ă��܂��B",
	"AlephOne�͂��̃}�b�v�����[�h���邽�߂̃�����������܂���B�������ʂ𑝂₵�Ă�����x���s���Ă��������B",
	"AlephOne�͂��ꂩ��ʂ̕����ݒ�t�@�C�������[�h���܂��B���̂��ߐ��\\����������A�N���b�V��������A�ۑ��Q�[���t�@�C��������������A�l�b�g���[�N�Q�[�����s����ɂȂ邨���ꂪ����܂��B�����ӂ�������!",
	"AlephOne�� Bungie���ȊO�̒n�}���g���Ă��܂��B���̂��ߐ��\\����������A�N���b�V��������A�ۑ��Q�[���t�@�C�����������邨���ꂪ����܂��B�����ӂ�������!",
	"�n�}�܂��͕ۑ��Q�[���t�@�C����ǂݍ��ލۂɒv���I�G���[���������܂����B",
	"�Z�[�u�t�@�C������}�b�v��ǂݍ��ނƂ��ɃV�X�e���G���[���������܂����B",
	"�ۑ��Q�[���t�@�C���̕ۑ����ɃG���[���������܂����B�n�[�h�f�B�X�N����t���A���b�N����Ă��邩������܂���B",
	"�V���A���ԍ��������ł��B������x���͂��Ă��������B",
	"�l�b�g���[�N�Q�[���̍ۂɓ����V���A���ԍ��𕡐��̃}�V���ł��g�p�����������Ƃ͂ł��܂���B�V���ɐ��i�����w�����������K�v������܂��B�ڂ����͓��{�����̔̔��㗝�X�܂ŘA�����Ă��������B",
	"����AlephOne�̃R�s�[�̓l�b�g���[�N��p�̃V���A���ԍ��œo�^����Ă��܂��B�l�b�g���[�N��p�̃V���A���ԍ��ł͈�l�p�̃v���[�͂ł��܂���B",
	"�ǂݍ������Ƃ��Ă���n�}�������Ă��邼�B�o�b�N�A�b�v�R�s�[����ēx�C���X�g�[�����悤�B",
	"�`�F�b�N�|�C���g %d �͌�����܂���ł���!",
	"�s�N�`���[ %d �͌�����܂���ł���!",
	"���̃o�[�W������Aleph One�̓v���r���[�łɂ��A�l�b�g���[�N�Q�[�����T�|�[�g���Ă��܂���BBungie�Ђ���́A�܂��Ȃ��l�b�g���[�N�Ή��ł��o�܂��B�i���̑������̃N�[���ȓ������������j",
	"�v���[���[���W�߂��v���[���[������ɂ݂�Ȃ������ăQ�[�����I�����Ă��܂����B���{�l���������������悢����...�B",
	"���܂�BAlephOne�̓l�b�g���[�N�Q�[������̏I���Ɏ��s���Ă��܂����B���̌��ʁA���̃��x���ł̌N�̓w�͂͐��̖A�ƂȂ��Ă��܂����B",
	"���̕ۑ����ꂽ�Q�[���̃V�i���I�t�@�C����������܂���B���x����ւ���Ƃ��A�f�t�H���g�̒n�}�ɖ߂�܂��B",
	"���̉f����L�^�����n�}��������܂���B�f��͍Đ��ł��܂���B",
	"AlephOne���l�b�g���[�N��ŗV�Ԃɂ� 6000k �ȏ�̋�RAM���K�v�ł��B�������ʂ𑝂₵�Ă�����x���s���Ă��������B",
	"�X�N���v�g���m���������N�����Ă���悤�ł��BMML�ƃl�b�g�X�N���v�g�ŒN��Lua�ŃR���g���[�����邩���قȂ��Ă���Ǝv���܂��B�\\�����Ȃ������⓯�����ꂪ�N���邩������܂���B",
	"���̒ʒm�́A�V�����o�[�W������AlephOne�����ɍ���Ă���A�v���C�ł��Ȃ��ꍇ�ɕ\\������܂��BAlephOne���A�b�v�O���[�h���Ă��������B",
	"�X�N���[���z�C�[���́A����̐؂�ւ��Ŏg�p����Ă��܂��B",
};

// STR# Resource: "Filenames"
static const char* sStringSetNumber129[] = {
    "Shapes",
    "Shapes.16",
    "Sounds",
    "Sounds.16",
    "$appName$ Preferences",
    "Map",
    "Untitled Game",
    "Marathon",
    "$appName$ Recording",
    "Physics Model",
    "Music",
    "Images",
    "Movie",
    "Default",
    "Marathon.appl",
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

	"�v���[���[���W�߂Ă����v���[���[���A����ɂ݂�Ȃ������ăQ�[�����I�����Ă��܂����B�i���{�l���������������悢�����c�B�j",

	"�}�b�v��S���ɑ��邱�Ƃ��o���Ȃ��������߁A�Q�[�����L�����Z������܂����B",

	"�Ăяo�����̃R���s���[�^���n�}�𑗂�Ȃ��������߁A�Q�[�����L�����Z������܂����B���̃R���s���[�^�̐ڑ����؂ꂽ��������܂���B",
	"$appName$�́A�Q�[�����J�n�ł��܂���B���̃R���s���[�^�̐ڑ����؂ꂽ��������܂���B",
	"�Q�[���̎Q�����ɃG���[���������܂����i�A�v���P�[�V�����̃o�[�W�������Ⴄ��������܂���j�B������x�����Ă݂Ă��������B",
	"�l�b�g���[�N�G���[�̂���$appName$�͑��s�ł��܂���B",

	"�o�[�W�������قȂ邽�߂��̃v���[���[�̓Q�[���ɎQ���ł��܂���ł����B",

	"���̃v���C���[�́A���ݕ�W�������Ă���Q�[���̂������̊g���@�\\���g�p�ł��Ȃ��Â��o�[�W������$appName$���g�p���Ă���悤�ł��B���̂��߁A���̃Q�[�����J�n���邱�Ƃ��ł��܂���B",
	"���ݕ�W�������Ă���Q�[���ɁA�g���@�\\�ɑΉ����Ă��Ȃ�AlephOne���g���Ă���v���C���[���Q�����悤�Ƃ��܂����B",
	"$appName$�́A���̃��x���̃}�b�v�t�@�C���������邱�Ƃ��ł��܂���ł����B�������̃^�[�~�i��������ɕ\\������Ȃ���������܂���B�܂��A���̃R���s���[�^�[��ŃQ�[����ۑ����邱�Ƃ͐����ł��܂���B",
	"��W�������Ă����l�����Ȃ��Ȃ�܂����B",

	"��W�������Ă���l�������邱�Ƃ��ł��܂���B�A�h���X�����������͂���Ă��邩���m�F���������B",

	"�T�[�o�[����}�b�v�𑗂�Ƃ��ɃG���[���������܂����B�Q�[���I�����܂��B",

	"��W�������Ă���l�́A�X�^�[�v���g�R�����g�p���Ă��܂����A���Ȃ��̐ݒ�̓����O�ɂȂ��Ă��܂��B���̂��߁A�ΐ�\\�ȑ��̃v���C���[�̃��X�g�ɕ\\������܂���B",

	"��W�������Ă���l�́A�����O�v���g�R�����g�p���Ă��܂����A���Ȃ��̐ݒ�̓X�^�[�ɂȂ��Ă��܂��B���̂��߁A�ΐ�\\�ȑ��̃v���C���[�̃��X�g�ɕ\\������܂���B",

	"��W�������Ă���l��Lua�̃l�b�g�X�N���v�g���g�p���Ă��܂����A���̃o�[�W�����́A�r���h����Lua���L���ɂȂ��Ă��܂���B���̂��߁A�ΐ�\\�ȑ��̃v���C���[�̃��X�g�ɕ\\������܂���B",

	"�C���^�[�l�b�g��̃Q�[�����W���Ă���T�[�o�[�ւ̐ڑ��ɖ�肪�������܂����B���萔�ł����A������x��蒼���Ă��������B",

	"���Ȃ�����W���悤�Ƃ��Ă���Q�[���́A�C���^�[�l�b�g��ɒʒm���邱�Ƃ��ł��܂���ł����B���̕��@�ŁA���Ȃ���IP�A�h���X��m�点�邩�A������x��蒼���Ă��������B",

	"$appName$�́A�t�@�C���[�E�H�[���⃋�[�^�[�̐ݒ��ύX���邱�Ƃ��ł��܂���ł����B�v���C���[���W���邱�Ƃ��ł��܂���B"
	
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
	"���^�[��",
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
	"�X�y�[�X",
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
	"�e���L�[��.",
	"0x42",
	"�e���L�[��*",
	"0x44",
	"�e���L�[��+",
	"0x46",
	"Clear",
	"0x48",
	"0x49",
	"0x4a",
	"�e���L�[��/",
	"Enter",
	"0x4d",
	"�e���L�[��-",
	"0x4f",
	"0x50",
	"�e���L�[��=",
	"�e���L�[��0",
	"�e���L�[��1",
	"�e���L�[��2",
	"�e���L�[��3",
	"�e���L�[��4",
	"�e���L�[��5",
	"�e���L�[��6",
	"�e���L�[��7",
	"0x5a",
	"�e���L�[��8",
	"�e���L�[��9",
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
	"Cybermaxx �w�����b�g���V���A���|�[�g�ɐڑ�����A�I���ɂȂ��Ă��邱�Ƃ��m�F���Ă��������B",
	"�@�\\�g���t�H���_�� QuickTime Musical Instruments �t�@�C���������Ă��邱�Ƃ��m�F���Ă������B�����Ă��Ȃ���BGM�͂������o�J�炵���������邼..."
};

// STR# Resource: "Computer Interface"
static const char* sStringSetNumber135[] = {
	"U.E.S.C. Marathon",
	"��.4.5-23 �Ɛڑ��J�n��",
	"CAS.qterm//CyberAcme Systems Inc.",
	"<931.461.60231.14.vt920>",
	"UESC�^�[�~�i�� 802.11�i�����[�g�I�[�o�[�h���C�u�j",
	"PgUp/PgDown/���L�[�ŃX�N���[��",
	"Return/Enter�L�[�ŗ���",
	"�ڑ��ؒf���c",
	"�ڑ��I��",
	"%H%M %m.%d.%Y",
};

// STR# Resource: "Join Dialog Messages"
static const char* sStringSetNumber136[] = {
	"�u�Q���v���N���b�N����ƃl�b�g���[�N�Q�[���ɎQ���ł��܂��B",
	"�T�[�o�[����l�b�g���[�N�Q�[���ɌĂяo�����̂�҂��Ă��܂��B�u�L�����Z���v���N���b�N����ƒ��f���܂��B",
	"�l�b�g���[�N�Q�[���ɎQ�����܂����B�T�[�o�[�͑��̃v���[���[���W�߂Ă��܂��c�B"
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
	"�i�K�p�\\�Ȏ��ԂɊ֘A���鉽���j",
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
	"�ǂݍ��ݒ��c�B",
	"���[�^�[�̃|�[�g���J���Ă��܂��c�B",
	"���[�^�[�̃|�[�g����Ă��܂��c�B",
	"�A�b�v�f�[�g���m�F���ł��c�B"
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

