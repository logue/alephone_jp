/*  DefaultStringSets.cpp - support for compiled-in 

	Copyright (C) 2002 and beyond by the "Aleph One" developers.
 
	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
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
/*
	"Sorry, Aleph One requires a 68040 processor or higher.",
	"Sorry, Aleph One requires Color QuickDraw.",
	"Sorry, Aleph One requires System Software 7.0 or higher.",
	"Sorry, Aleph One requires at least 3000k of free RAM.",
	"Sorry, Aleph One requires a 13ﾓ monitor (640x480) or larger which can be set to at least 256 colors or grays.",
	"Please be sure the files 'Map', 'Shapes', 'Images' and 'Sounds' are correctly installed and try again.",
	"Aleph One couldn't initialize the sound.",
	"Aleph One has encountered a file system error.  Check to make sure you have enough disk space and that you are not trying to save to a locked volume.",
	"This copy of Aleph One has been modified, perhaps by a virus.  Please re-install it from the original disks.",
	"This beta copy of Aleph One has expired and is no longer functional. Call Bungie at (312) 563-6200 ext. 21 for more information.",
	"Sorry, that key is already used to adjust the sound volume.",
	"Sorry, that key is already used for zooming in the overhead map view.",
	"Sorry, that key is already used for scrolling the inventory.",
	"Sorry, that key is already used for a special game function.",
	"Aleph One has used up all available RAM and cannot continue.  Trying giving it more memory, switching to a lower bit-depth or turning off sounds and try again.",
	"Aleph One is about to load an external physics model.  This could result in erratic performance, inexplicable crashes, corrupted saved games, and inconsistent network games (just a warning).",
	"Aleph One is using maps which were not created with Bungie tools.  This could result in poor performance, inexplicable crashes and corrupted saved games (proceed at your own risk).",
	"A game related error occurred while attempting to read from your map or saved game file.",
	"A system error occurred while attempting to read from your map or saved game file.",
	"An error occurred while saving your game (maybe your hard drive is full, or you tried to save to a locked volume?)",
	"That serial number is invalid.  Please try again.",
	"Sorry, you can't start a network game with more than one copy of the same serial number.  Call 1-800-295-0060 to order more network serial numbers by fax.",
	"Sorry, this copy of Aleph One has been serialized with a network-only serial number.  You cannot play the single-player game with a network-only serial number.",
	"The map you are trying to load has been corrupted.  Please reinstall from a backup copy.",
	"Checkpoint %d was not found!",
	"Picture %d was not found!",
	"This preview copy of Aleph One does not support networking.  A full demo will be available on-line or from Bungie shortly which includes networking (and a whole lot of other cool features).",
	"The gathering computer has quit the game, leaving everyone stranded without the next level.  Perhaps you should tar and feather him.",
	"Sorry, Aleph One was unable to gracefully exit from the network game.  As a result, your romp through the levels has been prematurely halted.",
	"The scenario file that this saved game was from cannot be found.  When you switch levels you will revert to the default map.",
	"Aleph One was unable to find the map that this film was recorded on, so the film cannot be replayed.",
	"Sorry, Aleph One needs 6000k free to play in a networked game.  Give Aleph One more memory and try again.",
	"There appears to be a script conflict.  Perhaps mml and netscript are having differences over who gets to control lua.  Don't be surprised if you get unexpected script behavior or out of sync.",
	"This replay was created with a newer version of Aleph One and cannot be played with this version. Upgrade Aleph One and try again.",
	"Sorry, the scroll wheel can only be used for switching weapons.",
*/
	"AlephOneには68040以上のプロセッサが必要です。",	"AlephOneには Color QuickDraw が必要です。",	"AlephOneには 漢字Talk 7.1 以降のシステムが必要です。",	"AlephOneには 3000k 以上の空きRAMが必要です。",	"AlephOneには13インチ以上(640x480)そして256色(またはグレー)が表示できるモニタが必要です。",	"Map, Shapes, Images, Sounds のファイルが Marathon アプリケーションと同じフォルダに入っているか確認してください。",	"システムメモリが少ないためサウンド用のメモリが割り当てられません(Marathonの割り当てメモリを減らしてください)。",	"AlephOneの実行中にファイルシステムエラーが発生しました。ディスク上の空要領とロックされていないか確認してください。",	"このAlephOneのコピーはウイルスなどによって変更されています。オリジナルのディスクから再度インストールしてください。",	"This beta copy of Marathon has expired and is no longer functional. Call Bungie at (312) 563-6200 ext. 21 for more information.",	"そのキーは既にボリューム調整に使われています。",	"そのキーは既に地図のズームに使われています。",	"そのキーは既にアイテムのスクロールに使われています。",	"そのキーは既にゲームの機能\に使われています。",	"AlephOneはこのマップをロードするためのメモリが足りません。メモリ量を増やしてもう一度実行してください。",	"AlephOneはこれから別の物理設定ファイルをロードします。そのため性能\が落ちたり、クラッシュしたり、保存ゲームファイルが悪化したり、ネットワークゲームが不安定になるおそれがあります。ご注意ください!",	"AlephOneは Bungie製以外の地図を使っています。そのため性能\が落ちたり、クラッシュしたり、保存ゲームファイルが悪化するおそれがあります。ご注意ください!",	"地図または保存ゲームファイルを読み込む際に致命的エラーが発生しました。",	"地図または保存ゲームファイルの読み込む際に致命的エラーが発生しました。",	"保存ゲームファイルの保存中にエラーが発生しました。ハードディスクが一杯か、ロックされているかもしれません。",	"シリアル番号が無効です。もう一度入力してください。",	"ネットワークゲームの際に同じシリアル番号を複数のマシンでご使用いただくことはできません。新たに製品をご購入いただく必要があります。詳しくは日本国内の販売代理店まで連絡してください。",	"このAlephOneのコピーはネットワーク専用のシリアル番号で登録されています。ネットワーク専用のシリアル番号では一人用のプレーはできません。",	"読み込もうとしている地図がこわれているぞ。バックアップコピーから再度インストールしよう。",	"チェックポイント %d は見つかりませんでした!",	"ピクチャー %d は見つかりませんでした!",	"このバージョンのAleph Oneはプレビュー版につき、ネットワークゲームをサポートしていません。Bungie社からは、まもなくネットワーク対応版が出ます。（この他多くのクールな特徴を持った）",	"プレーヤーを集めたプレーヤーが勝手にみんなをおいてゲームを終了してしまった。張本人を処罰した方がよいかも...。",	"すまん。AlephOneはネットワークゲームからの終了に失敗してしまった。その結果、このレベルでの君の努力は水の泡となってしまった。",	"この保存されたゲームのシナリオファイルが見つかりません。レベルを替えるとき、デフォルトの地図に戻ります。",	"この映画を記録した地図が見つかりません。映画は再生できません。",	"AlephOneをネットワーク上で遊ぶには 6000k 以上の空きRAMが必要です。メモリ量を増やしてもう一度実行してください。",	"スクリプト同士が競合を起こしているようです。MMLとネットスクリプトで誰をLuaでコントロールするか異なっていると思われます。予期しない動きや動機乱れが起こるかもしれません。",
	"この通知は、新しいバージョンのAlephOne向けに作られており、プレイできない場合に表示されます。AlephOneをアップグレードしてください。",
	"スクロールホイールは、武器の切り替えで使用されています。",
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
/*
	"BEGIN GAME",
    "OPEN SAVED GAME",
    "",
    "REPLAY LAST GAME",
    "REPLAY SAVED RECORDING",
    "SAVE LAST RECORDING",
    "",
    "GATHER NETWORK GAME",
    "JOIN NETWORK GAME",
    "",
    "PREFERENCES",
    "START DEMO",
    "QUIT",
*/
	"新規ゲーム",
	"既存のゲームを開く",
	"",
	"最後のゲームを再生",
	"映画を開く",
	"映画の保存",
	"",
	"ネットゲーム集合",
	"ネットゲーム参加",
	"",
	"設定",
	"デモ開始",
	"終了",
};

// STR# Resource: "Prompts"
static const char* sStringSetNumber131[] = {
    "ゲーム保存：",
    "映画の保存：",
    "映画の選択：",
    "デフォルト",
};

// STR# Resource: "Network Errors"
static const char* sStringSetNumber132[] = {
//	"Sorry, that player could not be found on the network.  He may have cancelled his Join Game dialog.",
	"そのプレーヤーはネットワーク上で見つかりません。ゲーム参加のダイアログからキャンセルしたかもしれません。",

//	"One or more of the players in the game could not be found to receive the "
//	"map.  The game has been canceled.",
	"いくつかのプレーヤーがネットワーク上で見つからないため、ゲームが中断されました。",

	"The gatherering computer is not responding."
	" It may be behind a firewall, or you may have mistyped the address.",

	"Sorry, the gathering computer has cancelled the game (you should all gang up on him next game).",

	"The map was not received in its entirety, so the game has been canceled.",

	"The gathering computer never sent the map, so the game has been cancelled.  Maybe one of the other machines in the game went down.",
	"Aleph One was unable to start the game.  Maybe one of the other machines in the game went down.",
	"An error ocurred while trying to join a game (an incompatible version of Aleph One may have tried to gather you).  Try again.",
	"Sorry, a network error ocurred and Aleph One is unable to continue.",

	"An error occurred while trying to join a game (the gatherer is using an incompatible version).",

	"The player you just added is using an older version of Aleph One that does not support some advanced features required by the game you're trying to gather.  You will not be allowed to start the game.",
	"The player you just attempted to add is using a version of Aleph One that does not support some advanced features required by the game you're trying to gather.",
	"Aleph One was unable to locate the Map file this level came from.  Some terminals may not display properly, and saving this game on this computer is not recommended.",
	"The connection to the gatherer was lost.",

	"Unable to look up the gatherer. Maybe you typed the address in wrong.",

	"An error occurred receiving the map from the server. Game over.",

	"The gatherer is using the star protocol, but your configuration is set to ring. You will not appear in the list of available players.",

	"The gatherer is using the ring protocol, but your configuration is set to star. You will not appear in the list of available players.",

	"The gatherer is using a Lua netscript, but this version was built without Lua support. You will not appear in the list of available players.",

	"There was a problem connecting to the server that tracks Internet games.  Please try again later.",

	"Your game could not be advertised on the Internet.  Please distribute your public IP address by other means or try again later.",

	"Aleph One failed to configure the firewall/router. You may be unable to gather."
	
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
    "↓",
    "F1",
    "←",
    "→",
    "↓",
    "↑",
    "Power",
};

// STR# Resource: "Preferences Advice"
static const char* sStringSetNumber134[] = {
//    "Be sure your external speakers or headphones are connected properly, and that you have enabled stereo output from the Sound Control Panel.",
//    "Be sure that your Cybermaxx helmet is properly hooked up to the serial port and turned on.",
//    "Please check to be sure you have the file ﾒQuickTime[TM] Musical Instrumentsﾓ in your ﾒExtensionsﾓ folder, because Aleph One's background music will sound really, really stupid without it.",
	"外部スピーカー又はヘッドフォンが接続され、サウンドのコントロールパネルでステレオ出力がオンになっていることを確認してください。",	"Cybermaxx ヘルメットがシリアルポートに接続され、オンになっていることを確認してください。",	"機能\拡張フォルダに QuickTime Musical Instruments ファイルが入っていることを確認してくさい。入っていないとBGMはすごくバカらしく聞こえるぞ..."
};

// STR# Resource: "Computer Interface"
static const char* sStringSetNumber135[] = {
    "U.E.S.C. Marathon",
//    "Opening Connection to b.4.5-23",
	"β.4.5-23 と接続開始中",
    "CAS.qterm//CyberAcme Systems Inc.",
    "<931.461.60231.14.vt920>",
//    "UESCTerm 802.11 (remote override)",
	"UESCターミナル 802.11（リモートオーバードライブ）",
//    "PgUp/PgDown/Arrows To Scroll",
	"PgUp/PgDown/矢印キーでスクロール",
//    "Return/Enter To Acknowledge",
	"Return/Enterキーで了解",
//    "Disconnecting...",
	"接続切断",
//    "Connection Terminated.",
	"接続終了",
    "%H%M %m.%d.%Y",
};

// STR# Resource: "Join Dialog Messages"
static const char* sStringSetNumber136[] = {
//    "Click 'Join' to wait for an invitation into a network game of Aleph One.",
//    "Now waiting to be gathered into a network game by a server.  Click 'Cancel' to give up.",
//    "You have been accepted into a game.  Now waiting for the server to add the remaining playersﾉ ",
	"「参加」をクリックするとネットワークゲームに参加できます。",
	"サーバーからネットワークゲームに呼び出されるのを待っています。「キャンセル」をクリックすると中断します。",
	"ネットワークゲームに参加しました。サーバーは他のプレーヤーを集めています..."
};

// STR# Resource: "Weapon Names"
static const char* sStringSetNumber137[] = {
/*
	"FISTS",
    ".44 MAGNUM MEGA CLASS A1",
    "ZEUS-CLASS FUSION PISTOL",
    "MA-75B ASSAULT RIFLE/ GRENADE LAUNCHER",
    "SPNKR-X18 SSM LAUNCHER",
    "TOZT-7 BACKPACK NAPALM UNIT",
    "UNKNOWN WEAPON CLASS system error 0xfded",
    "WSTE-M COMBAT SHOTGUN",
    "(somehow related to time of applicability)",
    "KKV-7 10MM FLECHETTE SMG",
*/
	"拳骨",
	".44 マグナム・メガ級 A1",
	"ゼウス級核融合ピストル",
	"MA-75B 機関銃/グレネード砲",
	"SPNKR-X18型ミサイルランチャー",
	"TOZT-7 火炎放射機",
	"武器類不明 システムエラー 0xfded",
	"WSTE-M 戦闘用ショットガン",
	"(somehow related to time of applicability)",
	"KKV-7 10MMフルチエット小型軽機関銃",
};

// STR# Resource: "file search path"
static const char* sStringSetNumber138[] = {
    "Marathon Trilogy:Marathon Infinity ﾄ:Marathon Infinity:",
};

// STR# Resource: "Preferences Groupings"
static const char* sStringSetNumber139[] = {
/*
	"Graphics",
    "Player",
    "Sound",
    "Controls",
    "Environment",
*/
	"グラフィック",
	"プレイヤー",
	"サウンド",
	"コントロール",
	"環境"
};

// STR# Resource: "Postgame network game stats"
static const char* sStringSetNumber140[] = {
/*
	"%d flags",
    "%d:%02d",
    "%d points",
    "Team",
    "Time With Ball",
    "Flags Captured",
    "Time 'It'",
    "Goals",
    "Time On Hill",
    "Time On Hill",
    "Points",
    "Time",
*/
	"%d 旗",
	"%d:%02d",
	"%d 点",
	"チーム",
	"ボールの保持時間",
	"旗の捕獲",
	"時間",
	"ゴール",
	"陣地にいた時間",
	"陣地にいた時間",
	"ポイント",
	"時間"
};

// STR# Resource: "Net Game Setup"
static const char* sStringSetNumber141[] = {
/*
	"Kill Limit",
    "kills",
    "Capture Limit",
    "flags",
    "Point Limit",
    "points",
    "Time On Hill:",
    "minutes",
    "Points",
    "Time",
*/
	"殺傷制限",
	"殺傷",
	"捕獲制限",
	"旗",
	"点数制限",
	"点数",
	"陣地にいた時間",
	"分",
	"ポイント",
	"時間"
};

// STR# Resource: "New Join Dialog Messages"
static const char* sStringSetNumber142[] = {
/*
	"You have been accepted into a game of '%s'.  Now waiting for the server to add the remaining players...",
    "Every Man For Himself",
    "You have been accepted into a cooperative game.  Now waiting for the server to add the remaining players...",
    "Capture the Flag",
    "King of the Hill",
    "Kill the Man With the Ball",
    "Defense",
    "Rugby",
    "Tag",
    "You have been accepted into a custom game. Now waiting for the server to add the remaining players...",
*/
	"君は「%s」ゲームに受け入れられました。サーバーが残りのプレーヤーを追加するまで少々おまちください…",
	"個人対戦"
	"君は「共同対戦」ゲームに受け入れられました。サーバーが残りのプレーヤーを追加するまで少々おまちください…",
	"旗取り",
	"陣地取り",
	"ボールの取り合い",
	"防衛戦",
	"ラグビー",
	"鬼ごっこ",
	"君はカスタムゲームに受け入れられました。サーバーが残りのプレーヤーを追加するまで少々おまちください…",
};

// STR# Resource: "Progress strings for networking"
static const char* sStringSetNumber143[] = {
/*
	"Sending map to remote player.",
    "Sending map to remote players.",
    "Receiving map from server.",
    "Waiting for server to send map.",
    "Sending environment information to the other player.",
    "Sending environment information to the other players.",
    "Receiving environment information from server.",
    "Loading...",
    "Attempting to open router ports...",
    "Closing router ports...",
    "Checking for updates..."
*/
	"プレイヤーへ地図を転送中です。",
	"プレイヤーへ地図を転送中です。",
	"サーバーから地図を転送しています。",
	"サーバーから地図の転送をお待ちください。",
	"環境データを他のプレイヤーへ転送中です。",
	"環境データを他のプレイヤーへ転送中です。",
	"環境データをサーバーから転送しています。",
	"読み込み中…"
	"ルーターのポートを開いています…",
	"ルーターのポートを閉じています…",
	"アップデートを確認中です…"
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
/*
	"Kindergarten",
    "Easy",
    "Normal",
    "Major Damage",
    "Total Carnage"
*/
	"ちびっ子",
	"簡単",
	"普通",
	"難しい",
	"虐殺"
};

static const char*    sNetworkGameTypesStrings[] = {
/*
	"Every Man for Himself",
    "Cooperative Play",
    "Capture the Flag",
    "King of the Hill",
    "Kill the Man With the Ball",
    "Rugby",
    "Tag",
    "Netscript",
*/
	"個人対戦",
	"チームプレイ",
	"旗取り",
	"陣地取り",
	"鬼ごっこ",
	"ラグビー",
	"タグ",
	"ネットスクリプト"
};

static const char*    sEndConditionTypeStrings[] = {
//    "No Limit (Alt+Q to quit)",
/*
	"Unlimited",
    "Time Limit",
    "Score Limit",
*/
	"無制限",
	"時間制限",
	"スコア上限"
};

static const char*	sSingleOrNetworkStrings[] = {
/*
	"Single-player game",
    "Network game"
*/
	"ソ\ロでゲーム",
	"ネットワークでゲーム"
};


BUILD_STRINGSET(kDifficultyLevelsStringSetID,   sDifficultyLevelsStrings);
BUILD_STRINGSET(kNetworkGameTypesStringSetID,   sNetworkGameTypesStrings);
BUILD_STRINGSET(kEndConditionTypeStringSetID,   sEndConditionTypeStrings);
BUILD_STRINGSET(kSingleOrNetworkStringSetID,	sSingleOrNetworkStrings);


// More Mac OS string-resource stringsets.
// -----------------------------------------------------------------------------------------
// STR# Resource: "Item names"
static const char* sStringSetNumber150[] = {
    "FISTS",
    ".44 MAGNUM MEGA CLASS",
    ".44 MAGNUM MEGA CLASS",
    ".44 CLIP (x8)",
    ".44 CLIPS (x8)",
    "ZEUS-CLASS FUSION PISTOL",
    "FUSION BATTERY",
    "FUSION BATTERIES",
    "MA-75B ASSAULT RIFLE",
    "MA-75B CLIP (x52)",
    "MA-75B CLIPS (x52)",
    "MA-75B GRENADES (x7)",
    "MA-75B GRENADES (x7)",
    "SPNKR-X18 SSM LAUNCHER",
    "SSM MISSILE (x2)",
    "SSM MISSILES (x2)",
    "ALIEN WEAPON",
    "SHOTGUN SHELL (x2)",
    "SHOTGUN SHELLS (x2)",
    "TOZT-7 NAPALM UNIT",
    "NAPALM CANISTER",
    "NAPALM CANISTERS",
    "POWERPC 620 CHIP",
    "POWERPC 620 CHIPS",
    "ALIEN ENERGY CONVERTER",
    "WAVE MOTION CANNON",
    "THE PLANS",
    "WSTE-M COMBAT SHOTGUN",
    "WSTE-M COMBAT SHOTGUNS",
    "SﾕPHT CARD KEY",
    "SﾕPHT CARD KEYS",
    "UPLINK CHIP",
    "UPLINK CHIPS",
    "Ryanﾕs Light Blue Ball",
    "SKULL",
    "Violet Ball",
    "Yellow Ball",
    "Brown Ball",
    "Orange Ball",
    "Blue Ball",
    "Green Ball",
    "KKV-7 10MM FLECHETTE SMG",
    "10MM FLECHETTE MAGAZINE",
    "10MM FLECHETTE MAGAZINES",
};

// STR# Resource: "Item types"
static const char* sStringSetNumber151[] = {
    "WEAPONS",
    "AMMUNITION",
    "POWERUPS",
    "ITEMS",
    "WEAPON POWERUPS",
    "BALLS",
    "NETWORK STATISTICS",
};

// STR# Resource: "Net Statistics Strings"
static const char* sStringSetNumber153[] = {
    "%d kills",
    "%d deaths",
    "%d suicides",
    "Total Carnage",
    "Monsters",
    "Total Kills: %d (%.2f kpm)",
    "Total Deaths: %d (%.2f dpm)",
    " including %d suicides",
    "Total Team Carnage",
    " including %d friendly-fire kills",
    "Total Scores",
    "Total Team Scores",
    // ZZZ: added for team vs. team carnage in postgame report
    "%s's team",
    // ZZZ: added for legend/key in SDL postgame report
    "kills",
    "deaths",
    "suicides",
    "friendly-fire kills",
};

// STR# Resource: "OpenGL-Option Color-Picker Prompts"
static const char* sStringSetNumber200[] = {
    "What color for the Void?",
    "What day ground color?",
    "What day sky color?",
    "What night ground color?",
    "What night sky color?",
    "What moon ground color?",
    "What moon sky color?",
    "What space ground color?",
    "What space sky color?",
    "What fog color?",
};

BUILD_STRINGSET(150, sStringSetNumber150);
BUILD_STRINGSET(151, sStringSetNumber151);
BUILD_STRINGSET(153, sStringSetNumber153);
BUILD_STRINGSET(200, sStringSetNumber200);


#include "player.h" // for kTeamColorsStringSetID

static const char* sTeamColorNamesStrings[] = {
    "Slate",
    "Red",
    "Violet",
    "Yellow",
    "White",
    "Orange",
    "Blue",
    "Green",
};

BUILD_STRINGSET(kTeamColorsStringSetID, sTeamColorNamesStrings);

