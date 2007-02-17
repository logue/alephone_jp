//----------------------------------------------------//
// MWT C++ Application Source File                    //
//      created by WideStudio Application Builder     //
//----------------------------------------------------//
#include <WScom.h>
#include <WSDappDev.h>

//--- OBJECT includes ---//
#include <WSCmainWindow.h>
#include <WSCmenuArea.h>
#include <WSCpulldownMenu.h>
#include <WSCvbtn.h>
#include <WSCform.h>
#include <WSClist.h>
#include <WSCindexForm.h>
#include <WSCvlabel.h>
#include <WSCvifield.h>
#include <WSCoption.h>
#include <WSCcheckGroup.h>
#include <WSCvradio.h>
#include <WSCtform.h>
#include <WSCdialog.h>

//--- OBJECT instance variable ---//
WSCmainWindow* MainWindow = NULL;
WSCmenuArea* MainMenu = NULL;
WSCpulldownMenu* Maipull_001 = NULL;
WSCvbtn* BtnMonster = NULL;
WSCvbtn* BtnEffect = NULL;
WSCvbtn* BtnProjectile = NULL;
WSCvbtn* BtnPhysics = NULL;
WSCvbtn* BtnWeapon = NULL;
WSCform* FrmMonster = NULL;
WSClist* ListMonsterTypes = NULL;
WSCindexForm* Maiinde_012 = NULL;
WSCvlabel* Maivlab_004 = NULL;
WSCvlabel* Maivlab_019 = NULL;
WSCvifield* PalletEdit = NULL;
WSCvlabel* Maivlab_022 = NULL;
WSCvlabel* Maivlab_024 = NULL;
WSCvifield* VitalityEdit = NULL;
WSCvlabel* Maivlab_037 = NULL;
WSCvlabel* Maivlab_038 = NULL;
WSCvifield* RadiusEdit = NULL;
WSCvifield* HeightEdit = NULL;
WSCvlabel* Maivlab_046 = NULL;
WSCvlabel* Maivlab_047 = NULL;
WSCvlabel* Maivlab_048 = NULL;
WSCvlabel* Maivlab_049 = NULL;
WSCvlabel* Maivlab_050 = NULL;
WSCvifield* HoverEdit = NULL;
WSCvifield* MinLedgeEdit = NULL;
WSCvifield* MaxLedgeEdit = NULL;
WSCvifield* ExtVelScaleEdit = NULL;
WSCvlabel* Maivlab_055 = NULL;
WSCvlabel* Maivlab_056 = NULL;
WSCvlabel* Maivlab_057 = NULL;
WSCvlabel* Maivlab_058 = NULL;
WSCvlabel* Maivlab_059 = NULL;
WSCvlabel* Maivlab_060 = NULL;
WSCvlabel* Maivlab_061 = NULL;
WSCvifield* SeqStationaly = NULL;
WSCvlabel* Maivlab_063 = NULL;
WSCvlabel* Maivlab_064 = NULL;
WSCvifield* SeqMoving = NULL;
WSCvifield* SeqHitting = NULL;
WSCvifield* SeqSoftDying = NULL;
WSCvifield* SeqSoftDead = NULL;
WSCvifield* SeqHardDying = NULL;
WSCvifield* SeqHardDead = NULL;
WSCvifield* SeqTeleportIn = NULL;
WSCvifield* SeqTeleportOut = NULL;
WSCvlabel* Maivlab_073 = NULL;
WSCvlabel* Maivlab_074 = NULL;
WSCvlabel* Maivlab_075 = NULL;
WSCvlabel* Maivlab_076 = NULL;
WSCvlabel* Maivlab_077 = NULL;
WSCvlabel* Maivlab_078 = NULL;
WSCvlabel* Maivlab_079 = NULL;
WSCvlabel* Maivlab_080 = NULL;
WSCvlabel* Maivlab_081 = NULL;
WSCvifield* SoundPitchEdit = NULL;
WSCvifield* RandomSndMaskEdit = NULL;
WSCvlabel* Maivlab_084 = NULL;
WSCvlabel* Maivlab_085 = NULL;
WSCvlabel* Maivlab_086 = NULL;
WSCvlabel* Maivlab_087 = NULL;
WSCvlabel* Maivlab_088 = NULL;
WSCvlabel* Maivlab_089 = NULL;
WSCvlabel* Maivlab_090 = NULL;
WSCvlabel* Maivlab_091 = NULL;
WSCvlabel* Maivlab_092 = NULL;
WSCvifield* HalfVisualArcEdit = NULL;
WSCvifield* VertVisualArcEdit = NULL;
WSCvifield* SpeedEdit = NULL;
WSCvifield* GravityEdit = NULL;
WSCvbtn* Maivbtn_106 = NULL;
WSCoption* SpeedCombo = NULL;
WSCoption* IntelligenceCombo = NULL;
WSCvbtn* CollectionBtn = NULL;
WSCvbtn* CarryItemBtn = NULL;
WSCvbtn* ActivationSndBtn = NULL;
WSCvbtn* FriendActSndBtn = NULL;
WSCvbtn* ClearSndBtn = NULL;
WSCvbtn* KillSndBtn = NULL;
WSCvbtn* ApologySndBtn = NULL;
WSCvbtn* FriendFireSndBtn = NULL;
WSCvbtn* FlamingSndBtn = NULL;
WSCvbtn* RandomSndBtn = NULL;
WSCoption* ClassCombo = NULL;
WSCvbtn* ImpactEffectBtn = NULL;
WSCvbtn* MeleeEffectBtn = NULL;
WSCvbtn* ContrailEffectBtn = NULL;
WSCvbtn* BtnDefaultMonster01 = NULL;
WSCcheckGroup* ListImmunities = NULL;
WSCcheckGroup* ListWeakness = NULL;
WSCcheckGroup* ListEnemies = NULL;
WSCcheckGroup* ListFriends = NULL;
WSCcheckGroup* ListFlags = NULL;
WSCvlabel* Maivlab_009 = NULL;
WSCvifield* ShapnelRadiusEdit = NULL;
WSCvlabel* Maivlab_012 = NULL;
WSCvlabel* Maivlab_013 = NULL;
WSCvlabel* Maivlab_014 = NULL;
WSCvlabel* Maaaa = NULL;
WSCvifield* ShapnelRndEdit = NULL;
WSCvifield* ShapnelScaleEdit = NULL;
WSCvifield* ShapnelBaseEdit = NULL;
WSCvbtn* ShapnelTypeBtn = NULL;
WSCvradio* ShapnelAlienCheck = NULL;
WSCvlabel* Maivlab_023 = NULL;
WSCvifield* FrequencyEdit = NULL;
WSCtform* Maitfor_025 = NULL;
WSCvifield* MeleedzEdit = NULL;
WSCvlabel* Maivlab_026 = NULL;
WSCvbtn* BtnMeleeType = NULL;
WSCvlabel* Maivlab_028 = NULL;
WSCvlabel* Maivlab_029 = NULL;
WSCvlabel* Maivlab_030 = NULL;
WSCvlabel* Maivlab_031 = NULL;
WSCvlabel* Maivlab_032 = NULL;
WSCvifield* MeleeRepetitionsEdit = NULL;
WSCvifield* MeleeErrorEdit = NULL;
WSCvifield* MeleeRangeEdit = NULL;
WSCvifield* MeleeSequenceEdit = NULL;
WSCvifield* MeleedxEdit = NULL;
WSCvifield* MeleedyEdit = NULL;
WSCvlabel* Maivlab_040 = NULL;
WSCvlabel* Maivlab_041 = NULL;
WSCvbtn* BtnMeleePreset = NULL;
WSCvbtn* BtnPresetThisAllEnemyOn = NULL;
WSCvbtn* BtnAllUncheck = NULL;
WSCtform* Maitfor_055 = NULL;
WSCvifield* RangeddzEdit = NULL;
WSCvlabel* Maivlab_062 = NULL;
WSCvbtn* BtnRangedType = NULL;
WSCvlabel* Maivlab_065 = NULL;
WSCvlabel* Maivlab_066 = NULL;
WSCvlabel* Maivlab_067 = NULL;
WSCvlabel* Maivlab_068 = NULL;
WSCvlabel* Maivlab_069 = NULL;
WSCvifield* RangedRepetitionsEdit = NULL;
WSCvifield* RangedErrorEdit = NULL;
WSCvifield* RangedRangeEdit = NULL;
WSCvifield* RangedSequenceEdit = NULL;
WSCvifield* RangeddxEdit = NULL;
WSCvifield* RangeddyEdit = NULL;
WSCvlabel* Maivlab_082 = NULL;
WSCvlabel* Maivlab_083 = NULL;
WSCvbtn* BtnRangedPreset = NULL;
WSCdialog* WndSelect = NULL;
WSClist* ListSelect = NULL;
WSCform* FrmEffect = NULL;
WSClist* ListEffect = NULL;
WSCvbtn* BtnEffectCollection = NULL;
WSCvlabel* Maivlab_093 = NULL;
WSCvlabel* Maivlab_094 = NULL;
WSCvlabel* Maivlab_095 = NULL;
WSCcheckGroup* EffectFlagsCheckGroup = NULL;
WSCvlabel* Maivlab_097 = NULL;
WSCvlabel* Maivlab_099 = NULL;
WSCvbtn* BtnEffectDelaySound = NULL;
WSCvifield* EffectSoundPitchEdit = NULL;
WSCvifield* EffectDelayEdit = NULL;
WSCvifield* EffectSequenceEdit = NULL;
WSCvlabel* Maivlab_104 = NULL;
WSCvifield* EffectPalletEdit = NULL;
WSCform* FrmProjectile = NULL;
WSClist* ListProjectile = NULL;
WSCvlabel* Maivlab_109 = NULL;
WSCvifield* ProjPalletEdit = NULL;
WSCvbtn* ProjCollectionBtn = NULL;
WSCvlabel* Maivlab_112 = NULL;
WSCvlabel* Maivlab_113 = NULL;
WSCvlabel* Maivlab_114 = NULL;
WSCvlabel* Maivlab_115 = NULL;
WSCvbtn* ProjContrailEfBtn = NULL;
WSCvbtn* ProjDetonationEfBtn = NULL;
WSCvbtn* ProjDetMediaEfBtn = NULL;
WSCvlabel* Maivlab_119 = NULL;
WSCvlabel* Maivlab_120 = NULL;
WSCvlabel* Maivlab_121 = NULL;
WSCvlabel* Maivlab_122 = NULL;
WSCvlabel* Maivlab_123 = NULL;
WSCvifield* ProjAreaOfEfEdit = NULL;
WSCvifield* ProjTicksBetContrailEdit = NULL;
WSCvifield* ProjMaxContrailEdit = NULL;
WSCvifield* ProjMediaPromoEdit = NULL;
WSCvifield* ProjRadiusEdit = NULL;
WSCtform* Maitfor_129 = NULL;
WSCvlabel* Maivlab_130 = NULL;
WSCvbtn* ProjDamageTypeBtn = NULL;
WSCvlabel* Maivlab_132 = NULL;
WSCvlabel* Maivlab_133 = NULL;
WSCvlabel* Maivlab_134 = NULL;
WSCvradio* ProjDamageFlags = NULL;
WSCvifield* ProjDamageBaseEdit = NULL;
WSCvifield* ProjDamageRandomEdit = NULL;
WSCvifield* ProjDamageScaleEdit = NULL;
WSCcheckGroup* ListProjFlags = NULL;
WSCvlabel* Maivlab_137 = NULL;
WSCvlabel* Maivlab_138 = NULL;
WSCvlabel* Maivlab_139 = NULL;
WSCvlabel* Maivlab_140 = NULL;
WSCvlabel* Maivlab_141 = NULL;
WSCvbtn* ProjFlyBySoundBtn = NULL;
WSCvbtn* ProjReboundSndBtn = NULL;
WSCvifield* ProjSpeedEdit = NULL;
WSCvifield* ProjMaxRangeEdit = NULL;
WSCvifield* ProjSoundPitchEdit = NULL;
WSCvlabel* Maivlab_147 = NULL;
WSCvifield* ProjSequenceEdit = NULL;
WSCvbtn* ProjPresetOtherProj = NULL;
WSCvbtn* Maivbtn_153 = NULL;
WSCform* FrmPhysics = NULL;
WSCoption* PhysicsTypeOpt = NULL;
WSCvlabel* Maivlab_158 = NULL;
WSCvifield* PhyMaxForwardEdit = NULL;
WSCvlabel* Maivlab_160 = NULL;
WSCvlabel* Maivlab_161 = NULL;
WSCvlabel* Maivlab_162 = NULL;
WSCvlabel* labne = NULL;
WSCvlabel* Maivlab_164 = NULL;
WSCvlabel* Maivlab_165 = NULL;
WSCvlabel* Maivlab_166 = NULL;
WSCvlabel* Maivlab_167 = NULL;
WSCvlabel* Maivlab_168 = NULL;
WSCvlabel* Maivlab_169 = NULL;
WSCvlabel* Maivlab_170 = NULL;
WSCvlabel* Maivlab_171 = NULL;
WSCvlabel* Maivlab_172 = NULL;
WSCvifield* PhyMaxBackwardEdit = NULL;
WSCvifield* PhyMaxPerpendEdit = NULL;
WSCvifield* PhyAccelEdit = NULL;
WSCvifield* PhyDecelEdit = NULL;
WSCvifield* PhyAirDecelEdit = NULL;
WSCvifield* PhyGravityAccelEdit = NULL;
WSCvifield* PhyClimbAccelEdit = NULL;
WSCvifield* PhyTerminalAccelEdit = NULL;
WSCvifield* PhyExtDecEdit = NULL;
WSCvifield* PhyAngularAccelEdit = NULL;
WSCvifield* PhyAngularDecelEdit = NULL;
WSCvifield* PhyMaxAngularVelEdit = NULL;
WSCvlabel* Maivlab_185 = NULL;
WSCvlabel* Maivlab_186 = NULL;
WSCvlabel* Maivlab_187 = NULL;
WSCvlabel* Maivlab_188 = NULL;
WSCvifield* PhyAngularRecenterEdit = NULL;
WSCvifield* PhyFastAngularVelEdit = NULL;
WSCvifield* PhyMaxElevationEdit = NULL;
WSCvifield* PhyExtAngularDecelEdit = NULL;
WSCvlabel* Maivlab_193 = NULL;
WSCvlabel* Maivlab_194 = NULL;
WSCvlabel* Maivlab_195 = NULL;
WSCvlabel* Maivlab_196 = NULL;
WSCvlabel* Maivlab_197 = NULL;
WSCvlabel* Maivlab_198 = NULL;
WSCvlabel* Maivlab_199 = NULL;
WSCvlabel* PhyHalfCameraSepEdit = NULL;
WSCvifield* PhyStepDeltaEdit = NULL;
WSCvifield* PhyStepAmpEdit = NULL;
WSCvifield* PhyRadiusEdit = NULL;
WSCvifield* PhyHeightEdit = NULL;
WSCvifield* PhyDeadHeightEdit = NULL;
WSCvifield* PhyCameraHeightEdit = NULL;
WSCvifield* PhySplashHeightEdit = NULL;
WSCvifield* Maivifi_208 = NULL;
WSCform* FrmWeapon = NULL;

//--- OBJECT src ---//

WSCbase* _create_win_MainWindow(){


  MainWindow = new  WSCmainWindow(NULL,"MainWindow");
      MainWindow->initialize();
  MainWindow->setPropertyV(WSNname,"MainWindow");
  MainWindow->setPropertyV(WSNtitleString,"PhysicsEditorWS");
  MainWindow->setPropertyV(WSNx,(short)100);
  MainWindow->setPropertyV(WSNy,(short)100);
  MainWindow->setPropertyV(WSNwidth,(unsigned short)787);
  MainWindow->setPropertyV(WSNheight,(unsigned short)502);
  MainWindow->setPropertyV(WSNvis,(WSCbool)1);
    extern void MainInitFunc(WSCbase*);
    MainWindow->addProcedureV("MainInit","MainInitFunc",MainInitFunc,0);
    extern void MainWindowExitFunc(WSCbase*);
    MainWindow->addProcedureV("MainWindowExit","MainWindowExitFunc",MainWindowExitFunc,32);
    extern void MainWindowCloseFunc(WSCbase*);
    MainWindow->addProcedureV("MainWindowClose","MainWindowCloseFunc",MainWindowCloseFunc,56);

  MainMenu = new  WSCmenuArea(MainWindow,"MainMenu");
      MainMenu->initialize();
  MainMenu->setPropertyV(WSNname,"MainMenu");
  MainMenu->setPropertyV(WSNx,(short)0);
  MainMenu->setPropertyV(WSNy,(short)0);
  MainMenu->setPropertyV(WSNwidth,(unsigned short)787);
  MainMenu->setPropertyV(WSNheight,(unsigned short)23);
  MainMenu->setPropertyV(WSNvis,(WSCbool)1);
  MainMenu->setPropertyV(WSNanchorLeftFlag,(WSCbool)1);
  MainMenu->setPropertyV(WSNanchorRightFlag,(WSCbool)1);

  Maipull_001 = new  WSCpulldownMenu(MainMenu,"Maipull_001");
      Maipull_001->initialize();
  Maipull_001->setPropertyV(WSNmenuItems,"New(N):FileNew:N,Open(O):open1:O,Save(S):FileSave:S,SP,Exit(X):exit1:X");
  Maipull_001->setPropertyV(WSNshortcut,"F");
  Maipull_001->setPropertyV(WSNlabelString,"File(F)");
  Maipull_001->setPropertyV(WSNname,"Maipull_001");
  Maipull_001->setPropertyV(WSNvis,(WSCbool)1);
  Maipull_001->setPropertyV(WSNwidth,(unsigned short)80);
  Maipull_001->setPropertyV(WSNheight,(unsigned short)21);
    extern void open1(WSCbase*);
    Maipull_001->addProcedureV("open1","open1",open1,-1);
    extern void close1(WSCbase*);
    Maipull_001->addProcedureV("close1","close1",close1,-1);
    extern void exit1(WSCbase*);
    Maipull_001->addProcedureV("exit1","exit1",exit1,-1);
    extern void FileNewFunc(WSCbase*);
    Maipull_001->addProcedureV("FileNew","FileNewFunc",FileNewFunc,-1);
    extern void FileSaveFunc(WSCbase*);
    Maipull_001->addProcedureV("FileSave","FileSaveFunc",FileSaveFunc,-1);

  BtnMonster = new  WSCvbtn(MainWindow,"BtnMonster");
      BtnMonster->initialize();
  BtnMonster->setPropertyV(WSNlabelString,"Monster");
  BtnMonster->setPropertyV(WSNname,"BtnMonster");
  BtnMonster->setPropertyV(WSNvis,(WSCbool)1);
  BtnMonster->setPropertyV(WSNx,(short)5);
  BtnMonster->setPropertyV(WSNy,(short)30);
  BtnMonster->setPropertyV(WSNwidth,(unsigned short)85);
  BtnMonster->setPropertyV(WSNheight,(unsigned short)65);
    extern void BtnMonsterPressFunc(WSCbase*);
    BtnMonster->addProcedureV("BtnMonsterPress","BtnMonsterPressFunc",BtnMonsterPressFunc,13);

  BtnEffect = new  WSCvbtn(MainWindow,"BtnEffect");
      BtnEffect->initialize();
  BtnEffect->setPropertyV(WSNlabelString,"Effect");
  BtnEffect->setPropertyV(WSNname,"BtnEffect");
  BtnEffect->setPropertyV(WSNvis,(WSCbool)1);
  BtnEffect->setPropertyV(WSNx,(short)5);
  BtnEffect->setPropertyV(WSNy,(short)95);
  BtnEffect->setPropertyV(WSNwidth,(unsigned short)85);
  BtnEffect->setPropertyV(WSNheight,(unsigned short)65);
    extern void BtnEffectDownFunc(WSCbase*);
    BtnEffect->addProcedureV("BtnEffectDown","BtnEffectDownFunc",BtnEffectDownFunc,13);

  BtnProjectile = new  WSCvbtn(MainWindow,"BtnProjectile");
      BtnProjectile->initialize();
  BtnProjectile->setPropertyV(WSNlabelString,"Projectile");
  BtnProjectile->setPropertyV(WSNname,"BtnProjectile");
  BtnProjectile->setPropertyV(WSNvis,(WSCbool)1);
  BtnProjectile->setPropertyV(WSNx,(short)5);
  BtnProjectile->setPropertyV(WSNy,(short)160);
  BtnProjectile->setPropertyV(WSNwidth,(unsigned short)85);
  BtnProjectile->setPropertyV(WSNheight,(unsigned short)65);
    extern void BtnProjectileDownFunc(WSCbase*);
    BtnProjectile->addProcedureV("BtnProjectileDown","BtnProjectileDownFunc",BtnProjectileDownFunc,13);

  BtnPhysics = new  WSCvbtn(MainWindow,"BtnPhysics");
      BtnPhysics->initialize();
  BtnPhysics->setPropertyV(WSNlabelString,"Physics");
  BtnPhysics->setPropertyV(WSNname,"BtnPhysics");
  BtnPhysics->setPropertyV(WSNvis,(WSCbool)1);
  BtnPhysics->setPropertyV(WSNx,(short)5);
  BtnPhysics->setPropertyV(WSNy,(short)225);
  BtnPhysics->setPropertyV(WSNwidth,(unsigned short)85);
  BtnPhysics->setPropertyV(WSNheight,(unsigned short)65);
    extern void BtnPhysicsDownFunc(WSCbase*);
    BtnPhysics->addProcedureV("BtnPhysicsDown","BtnPhysicsDownFunc",BtnPhysicsDownFunc,13);

  BtnWeapon = new  WSCvbtn(MainWindow,"BtnWeapon");
      BtnWeapon->initialize();
  BtnWeapon->setPropertyV(WSNlabelString,"Weapon");
  BtnWeapon->setPropertyV(WSNname,"BtnWeapon");
  BtnWeapon->setPropertyV(WSNvis,(WSCbool)1);
  BtnWeapon->setPropertyV(WSNx,(short)5);
  BtnWeapon->setPropertyV(WSNy,(short)290);
  BtnWeapon->setPropertyV(WSNwidth,(unsigned short)85);
  BtnWeapon->setPropertyV(WSNheight,(unsigned short)65);
    extern void BtnWeaponDownFunc(WSCbase*);
    BtnWeapon->addProcedureV("BtnWeaponDown","BtnWeaponDownFunc",BtnWeaponDownFunc,13);

  FrmMonster = new  WSCform(MainWindow,"FrmMonster");
      FrmMonster->initialize();
  FrmMonster->setPropertyV(WSNname,"FrmMonster");
  FrmMonster->setPropertyV(WSNx,(short)95);
  FrmMonster->setPropertyV(WSNy,(short)25);
  FrmMonster->setPropertyV(WSNwidth,(unsigned short)690);
  FrmMonster->setPropertyV(WSNheight,(unsigned short)470);

  ListMonsterTypes = new  WSClist(FrmMonster,"ListMonsterTypes");
      ListMonsterTypes->initialize();
  ListMonsterTypes->setPropertyV(WSNitemHeight,(unsigned char)10);
  ListMonsterTypes->setPropertyV(WSNtitleString,"");
  ListMonsterTypes->setPropertyV(WSNdataSource,(unsigned char)2);
  ListMonsterTypes->setPropertyV(WSNdataSourceName,"data/MonsterTypes.txt");
  ListMonsterTypes->setPropertyV(WSNworkWidth,(unsigned short)300);
  ListMonsterTypes->setPropertyV(WSNworkHeight,(unsigned short)470);
  ListMonsterTypes->setPropertyV(WSNhbarVisible,(WSCbool)1);
  ListMonsterTypes->setPropertyV(WSNname,"ListMonsterTypes");
  ListMonsterTypes->setPropertyV(WSNx,(short)10);
  ListMonsterTypes->setPropertyV(WSNy,(short)5);
  ListMonsterTypes->setPropertyV(WSNwidth,(unsigned short)105);
  ListMonsterTypes->setPropertyV(WSNheight,(unsigned short)450);
  ListMonsterTypes->setPropertyV(WSNvis,(WSCbool)1);
    extern void ListMonsterTypeItemSelFunc(WSCbase*);
    ListMonsterTypes->addProcedureV("ListMonsterTypeItemSel","ListMonsterTypeItemSelFunc",ListMonsterTypeItemSelFunc,35);

  Maiinde_012 = new  WSCindexForm(FrmMonster,"Maiinde_012");
      Maiinde_012->initialize();
  Maiinde_012->setPropertyV(WSNmenuItems,"Appearance,Flags1,Attack");
  Maiinde_012->setPropertyV(WSNvalue,(unsigned char)1);
  Maiinde_012->setPropertyV(WSNname,"Maiinde_012");
  Maiinde_012->setPropertyV(WSNx,(short)120);
  Maiinde_012->setPropertyV(WSNy,(short)10);
  Maiinde_012->setPropertyV(WSNwidth,(unsigned short)565);
  Maiinde_012->setPropertyV(WSNheight,(unsigned short)460);
  Maiinde_012->setPropertyV(WSNvis,(WSCbool)1);
    extern void MonsterTabsInitFunc(WSCbase*);
    Maiinde_012->addProcedureV("MonsterTabsInit","MonsterTabsInitFunc",MonsterTabsInitFunc,0);

  Maivlab_004 = new  WSCvlabel(Maiinde_012,"Maivlab_004");
      Maivlab_004->initialize();
  Maivlab_004->setPropertyV(WSNuserValue,(long)1);
  Maivlab_004->setPropertyV(WSNlabelString,"Collection");
  Maivlab_004->setPropertyV(WSNname,"Maivlab_004");
  Maivlab_004->setPropertyV(WSNx,(short)5);
  Maivlab_004->setPropertyV(WSNy,(short)30);
  Maivlab_004->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_004->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_019 = new  WSCvlabel(Maiinde_012,"Maivlab_019");
      Maivlab_019->initialize();
  Maivlab_019->setPropertyV(WSNuserValue,(long)1);
  Maivlab_019->setPropertyV(WSNlabelString,"Pallet");
  Maivlab_019->setPropertyV(WSNname,"Maivlab_019");
  Maivlab_019->setPropertyV(WSNx,(short)5);
  Maivlab_019->setPropertyV(WSNy,(short)55);
  Maivlab_019->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_019->setPropertyV(WSNheight,(unsigned short)25);

  PalletEdit = new  WSCvifield(Maiinde_012,"PalletEdit");
      PalletEdit->initialize();
  PalletEdit->setPropertyV(WSNuserValue,(long)1);
  PalletEdit->setPropertyV(WSNname,"PalletEdit");
  PalletEdit->setPropertyV(WSNx,(short)95);
  PalletEdit->setPropertyV(WSNy,(short)55);
  PalletEdit->setPropertyV(WSNwidth,(unsigned short)80);
  PalletEdit->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_022 = new  WSCvlabel(Maiinde_012,"Maivlab_022");
      Maivlab_022->initialize();
  Maivlab_022->setPropertyV(WSNuserValue,(long)1);
  Maivlab_022->setPropertyV(WSNlabelString,"Vitality");
  Maivlab_022->setPropertyV(WSNname,"Maivlab_022");
  Maivlab_022->setPropertyV(WSNx,(short)5);
  Maivlab_022->setPropertyV(WSNy,(short)80);
  Maivlab_022->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_022->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_024 = new  WSCvlabel(Maiinde_012,"Maivlab_024");
      Maivlab_024->initialize();
  Maivlab_024->setPropertyV(WSNuserValue,(long)1);
  Maivlab_024->setPropertyV(WSNlabelString,"Class");
  Maivlab_024->setPropertyV(WSNname,"Maivlab_024");
  Maivlab_024->setPropertyV(WSNx,(short)5);
  Maivlab_024->setPropertyV(WSNy,(short)105);
  Maivlab_024->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_024->setPropertyV(WSNheight,(unsigned short)25);

  VitalityEdit = new  WSCvifield(Maiinde_012,"VitalityEdit");
      VitalityEdit->initialize();
  VitalityEdit->setPropertyV(WSNuserValue,(long)1);
  VitalityEdit->setPropertyV(WSNname,"VitalityEdit");
  VitalityEdit->setPropertyV(WSNx,(short)95);
  VitalityEdit->setPropertyV(WSNy,(short)80);
  VitalityEdit->setPropertyV(WSNwidth,(unsigned short)80);
  VitalityEdit->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_037 = new  WSCvlabel(Maiinde_012,"Maivlab_037");
      Maivlab_037->initialize();
  Maivlab_037->setPropertyV(WSNuserValue,(long)1);
  Maivlab_037->setPropertyV(WSNlabelString,"Radius");
  Maivlab_037->setPropertyV(WSNname,"Maivlab_037");
  Maivlab_037->setPropertyV(WSNx,(short)5);
  Maivlab_037->setPropertyV(WSNy,(short)130);
  Maivlab_037->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_037->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_038 = new  WSCvlabel(Maiinde_012,"Maivlab_038");
      Maivlab_038->initialize();
  Maivlab_038->setPropertyV(WSNuserValue,(long)1);
  Maivlab_038->setPropertyV(WSNlabelString,"Height");
  Maivlab_038->setPropertyV(WSNname,"Maivlab_038");
  Maivlab_038->setPropertyV(WSNx,(short)5);
  Maivlab_038->setPropertyV(WSNy,(short)155);
  Maivlab_038->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_038->setPropertyV(WSNheight,(unsigned short)25);

  RadiusEdit = new  WSCvifield(Maiinde_012,"RadiusEdit");
      RadiusEdit->initialize();
  RadiusEdit->setPropertyV(WSNuserValue,(long)1);
  RadiusEdit->setPropertyV(WSNname,"RadiusEdit");
  RadiusEdit->setPropertyV(WSNx,(short)95);
  RadiusEdit->setPropertyV(WSNy,(short)130);
  RadiusEdit->setPropertyV(WSNwidth,(unsigned short)80);
  RadiusEdit->setPropertyV(WSNheight,(unsigned short)25);

  HeightEdit = new  WSCvifield(Maiinde_012,"HeightEdit");
      HeightEdit->initialize();
  HeightEdit->setPropertyV(WSNuserValue,(long)1);
  HeightEdit->setPropertyV(WSNname,"HeightEdit");
  HeightEdit->setPropertyV(WSNx,(short)95);
  HeightEdit->setPropertyV(WSNy,(short)155);
  HeightEdit->setPropertyV(WSNwidth,(unsigned short)80);
  HeightEdit->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_046 = new  WSCvlabel(Maiinde_012,"Maivlab_046");
      Maivlab_046->initialize();
  Maivlab_046->setPropertyV(WSNuserValue,(long)1);
  Maivlab_046->setPropertyV(WSNlabelString,"Hover");
  Maivlab_046->setPropertyV(WSNname,"Maivlab_046");
  Maivlab_046->setPropertyV(WSNx,(short)5);
  Maivlab_046->setPropertyV(WSNy,(short)180);
  Maivlab_046->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_046->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_047 = new  WSCvlabel(Maiinde_012,"Maivlab_047");
      Maivlab_047->initialize();
  Maivlab_047->setPropertyV(WSNuserValue,(long)1);
  Maivlab_047->setPropertyV(WSNlabelString,"Min Ledge");
  Maivlab_047->setPropertyV(WSNname,"Maivlab_047");
  Maivlab_047->setPropertyV(WSNx,(short)5);
  Maivlab_047->setPropertyV(WSNy,(short)205);
  Maivlab_047->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_047->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_048 = new  WSCvlabel(Maiinde_012,"Maivlab_048");
      Maivlab_048->initialize();
  Maivlab_048->setPropertyV(WSNuserValue,(long)1);
  Maivlab_048->setPropertyV(WSNlabelString,"Max Ledge");
  Maivlab_048->setPropertyV(WSNname,"Maivlab_048");
  Maivlab_048->setPropertyV(WSNx,(short)5);
  Maivlab_048->setPropertyV(WSNy,(short)230);
  Maivlab_048->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_048->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_049 = new  WSCvlabel(Maiinde_012,"Maivlab_049");
      Maivlab_049->initialize();
  Maivlab_049->setPropertyV(WSNuserValue,(long)1);
  Maivlab_049->setPropertyV(WSNlabelString,"ExtVelScale");
  Maivlab_049->setPropertyV(WSNname,"Maivlab_049");
  Maivlab_049->setPropertyV(WSNx,(short)5);
  Maivlab_049->setPropertyV(WSNy,(short)255);
  Maivlab_049->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_049->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_050 = new  WSCvlabel(Maiinde_012,"Maivlab_050");
      Maivlab_050->initialize();
  Maivlab_050->setPropertyV(WSNuserValue,(long)1);
  Maivlab_050->setPropertyV(WSNlabelString,"CarryItem");
  Maivlab_050->setPropertyV(WSNname,"Maivlab_050");
  Maivlab_050->setPropertyV(WSNx,(short)5);
  Maivlab_050->setPropertyV(WSNy,(short)280);
  Maivlab_050->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_050->setPropertyV(WSNheight,(unsigned short)25);

  HoverEdit = new  WSCvifield(Maiinde_012,"HoverEdit");
      HoverEdit->initialize();
  HoverEdit->setPropertyV(WSNuserValue,(long)1);
  HoverEdit->setPropertyV(WSNname,"HoverEdit");
  HoverEdit->setPropertyV(WSNx,(short)95);
  HoverEdit->setPropertyV(WSNy,(short)180);
  HoverEdit->setPropertyV(WSNwidth,(unsigned short)80);
  HoverEdit->setPropertyV(WSNheight,(unsigned short)25);

  MinLedgeEdit = new  WSCvifield(Maiinde_012,"MinLedgeEdit");
      MinLedgeEdit->initialize();
  MinLedgeEdit->setPropertyV(WSNuserValue,(long)1);
  MinLedgeEdit->setPropertyV(WSNname,"MinLedgeEdit");
  MinLedgeEdit->setPropertyV(WSNx,(short)95);
  MinLedgeEdit->setPropertyV(WSNy,(short)205);
  MinLedgeEdit->setPropertyV(WSNwidth,(unsigned short)80);
  MinLedgeEdit->setPropertyV(WSNheight,(unsigned short)25);

  MaxLedgeEdit = new  WSCvifield(Maiinde_012,"MaxLedgeEdit");
      MaxLedgeEdit->initialize();
  MaxLedgeEdit->setPropertyV(WSNuserValue,(long)1);
  MaxLedgeEdit->setPropertyV(WSNname,"MaxLedgeEdit");
  MaxLedgeEdit->setPropertyV(WSNx,(short)95);
  MaxLedgeEdit->setPropertyV(WSNy,(short)230);
  MaxLedgeEdit->setPropertyV(WSNwidth,(unsigned short)80);
  MaxLedgeEdit->setPropertyV(WSNheight,(unsigned short)25);

  ExtVelScaleEdit = new  WSCvifield(Maiinde_012,"ExtVelScaleEdit");
      ExtVelScaleEdit->initialize();
  ExtVelScaleEdit->setPropertyV(WSNuserValue,(long)1);
  ExtVelScaleEdit->setPropertyV(WSNname,"ExtVelScaleEdit");
  ExtVelScaleEdit->setPropertyV(WSNx,(short)95);
  ExtVelScaleEdit->setPropertyV(WSNy,(short)255);
  ExtVelScaleEdit->setPropertyV(WSNwidth,(unsigned short)80);
  ExtVelScaleEdit->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_055 = new  WSCvlabel(Maiinde_012,"Maivlab_055");
      Maivlab_055->initialize();
  Maivlab_055->setPropertyV(WSNuserValue,(long)1);
  Maivlab_055->setPropertyV(WSNlabelString,"Stationaly");
  Maivlab_055->setPropertyV(WSNname,"Maivlab_055");
  Maivlab_055->setPropertyV(WSNx,(short)205);
  Maivlab_055->setPropertyV(WSNy,(short)30);
  Maivlab_055->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_055->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_056 = new  WSCvlabel(Maiinde_012,"Maivlab_056");
      Maivlab_056->initialize();
  Maivlab_056->setPropertyV(WSNuserValue,(long)1);
  Maivlab_056->setPropertyV(WSNlabelString,"Moving");
  Maivlab_056->setPropertyV(WSNname,"Maivlab_056");
  Maivlab_056->setPropertyV(WSNx,(short)205);
  Maivlab_056->setPropertyV(WSNy,(short)55);
  Maivlab_056->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_056->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_057 = new  WSCvlabel(Maiinde_012,"Maivlab_057");
      Maivlab_057->initialize();
  Maivlab_057->setPropertyV(WSNuserValue,(long)1);
  Maivlab_057->setPropertyV(WSNlabelString,"Hitting");
  Maivlab_057->setPropertyV(WSNname,"Maivlab_057");
  Maivlab_057->setPropertyV(WSNx,(short)205);
  Maivlab_057->setPropertyV(WSNy,(short)80);
  Maivlab_057->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_057->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_058 = new  WSCvlabel(Maiinde_012,"Maivlab_058");
      Maivlab_058->initialize();
  Maivlab_058->setPropertyV(WSNuserValue,(long)1);
  Maivlab_058->setPropertyV(WSNlabelString,"Soft Dying");
  Maivlab_058->setPropertyV(WSNname,"Maivlab_058");
  Maivlab_058->setPropertyV(WSNx,(short)205);
  Maivlab_058->setPropertyV(WSNy,(short)105);
  Maivlab_058->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_058->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_059 = new  WSCvlabel(Maiinde_012,"Maivlab_059");
      Maivlab_059->initialize();
  Maivlab_059->setPropertyV(WSNuserValue,(long)1);
  Maivlab_059->setPropertyV(WSNlabelString,"Soft Dead");
  Maivlab_059->setPropertyV(WSNname,"Maivlab_059");
  Maivlab_059->setPropertyV(WSNx,(short)205);
  Maivlab_059->setPropertyV(WSNy,(short)130);
  Maivlab_059->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_059->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_060 = new  WSCvlabel(Maiinde_012,"Maivlab_060");
      Maivlab_060->initialize();
  Maivlab_060->setPropertyV(WSNuserValue,(long)1);
  Maivlab_060->setPropertyV(WSNlabelString,"Hard Dying");
  Maivlab_060->setPropertyV(WSNname,"Maivlab_060");
  Maivlab_060->setPropertyV(WSNx,(short)205);
  Maivlab_060->setPropertyV(WSNy,(short)155);
  Maivlab_060->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_060->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_061 = new  WSCvlabel(Maiinde_012,"Maivlab_061");
      Maivlab_061->initialize();
  Maivlab_061->setPropertyV(WSNuserValue,(long)1);
  Maivlab_061->setPropertyV(WSNlabelString,"Hard Dead");
  Maivlab_061->setPropertyV(WSNname,"Maivlab_061");
  Maivlab_061->setPropertyV(WSNx,(short)205);
  Maivlab_061->setPropertyV(WSNy,(short)180);
  Maivlab_061->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_061->setPropertyV(WSNheight,(unsigned short)25);

  SeqStationaly = new  WSCvifield(Maiinde_012,"SeqStationaly");
      SeqStationaly->initialize();
  SeqStationaly->setPropertyV(WSNuserValue,(long)1);
  SeqStationaly->setPropertyV(WSNname,"SeqStationaly");
  SeqStationaly->setPropertyV(WSNx,(short)295);
  SeqStationaly->setPropertyV(WSNy,(short)30);
  SeqStationaly->setPropertyV(WSNwidth,(unsigned short)55);
  SeqStationaly->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_063 = new  WSCvlabel(Maiinde_012,"Maivlab_063");
      Maivlab_063->initialize();
  Maivlab_063->setPropertyV(WSNuserValue,(long)1);
  Maivlab_063->setPropertyV(WSNlabelString,"Teleport In");
  Maivlab_063->setPropertyV(WSNname,"Maivlab_063");
  Maivlab_063->setPropertyV(WSNx,(short)205);
  Maivlab_063->setPropertyV(WSNy,(short)205);
  Maivlab_063->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_063->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_064 = new  WSCvlabel(Maiinde_012,"Maivlab_064");
      Maivlab_064->initialize();
  Maivlab_064->setPropertyV(WSNuserValue,(long)1);
  Maivlab_064->setPropertyV(WSNlabelString,"Teleport Out");
  Maivlab_064->setPropertyV(WSNname,"Maivlab_064");
  Maivlab_064->setPropertyV(WSNx,(short)205);
  Maivlab_064->setPropertyV(WSNy,(short)230);
  Maivlab_064->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_064->setPropertyV(WSNheight,(unsigned short)25);

  SeqMoving = new  WSCvifield(Maiinde_012,"SeqMoving");
      SeqMoving->initialize();
  SeqMoving->setPropertyV(WSNuserValue,(long)1);
  SeqMoving->setPropertyV(WSNname,"SeqMoving");
  SeqMoving->setPropertyV(WSNx,(short)295);
  SeqMoving->setPropertyV(WSNy,(short)55);
  SeqMoving->setPropertyV(WSNwidth,(unsigned short)55);
  SeqMoving->setPropertyV(WSNheight,(unsigned short)25);

  SeqHitting = new  WSCvifield(Maiinde_012,"SeqHitting");
      SeqHitting->initialize();
  SeqHitting->setPropertyV(WSNuserValue,(long)1);
  SeqHitting->setPropertyV(WSNname,"SeqHitting");
  SeqHitting->setPropertyV(WSNx,(short)295);
  SeqHitting->setPropertyV(WSNy,(short)80);
  SeqHitting->setPropertyV(WSNwidth,(unsigned short)55);
  SeqHitting->setPropertyV(WSNheight,(unsigned short)25);

  SeqSoftDying = new  WSCvifield(Maiinde_012,"SeqSoftDying");
      SeqSoftDying->initialize();
  SeqSoftDying->setPropertyV(WSNuserValue,(long)1);
  SeqSoftDying->setPropertyV(WSNname,"SeqSoftDying");
  SeqSoftDying->setPropertyV(WSNx,(short)295);
  SeqSoftDying->setPropertyV(WSNy,(short)105);
  SeqSoftDying->setPropertyV(WSNwidth,(unsigned short)55);
  SeqSoftDying->setPropertyV(WSNheight,(unsigned short)25);

  SeqSoftDead = new  WSCvifield(Maiinde_012,"SeqSoftDead");
      SeqSoftDead->initialize();
  SeqSoftDead->setPropertyV(WSNuserValue,(long)1);
  SeqSoftDead->setPropertyV(WSNname,"SeqSoftDead");
  SeqSoftDead->setPropertyV(WSNx,(short)295);
  SeqSoftDead->setPropertyV(WSNy,(short)130);
  SeqSoftDead->setPropertyV(WSNwidth,(unsigned short)55);
  SeqSoftDead->setPropertyV(WSNheight,(unsigned short)25);

  SeqHardDying = new  WSCvifield(Maiinde_012,"SeqHardDying");
      SeqHardDying->initialize();
  SeqHardDying->setPropertyV(WSNuserValue,(long)1);
  SeqHardDying->setPropertyV(WSNname,"SeqHardDying");
  SeqHardDying->setPropertyV(WSNx,(short)295);
  SeqHardDying->setPropertyV(WSNy,(short)155);
  SeqHardDying->setPropertyV(WSNwidth,(unsigned short)55);
  SeqHardDying->setPropertyV(WSNheight,(unsigned short)25);

  SeqHardDead = new  WSCvifield(Maiinde_012,"SeqHardDead");
      SeqHardDead->initialize();
  SeqHardDead->setPropertyV(WSNuserValue,(long)1);
  SeqHardDead->setPropertyV(WSNname,"SeqHardDead");
  SeqHardDead->setPropertyV(WSNx,(short)295);
  SeqHardDead->setPropertyV(WSNy,(short)180);
  SeqHardDead->setPropertyV(WSNwidth,(unsigned short)55);
  SeqHardDead->setPropertyV(WSNheight,(unsigned short)25);

  SeqTeleportIn = new  WSCvifield(Maiinde_012,"SeqTeleportIn");
      SeqTeleportIn->initialize();
  SeqTeleportIn->setPropertyV(WSNuserValue,(long)1);
  SeqTeleportIn->setPropertyV(WSNname,"SeqTeleportIn");
  SeqTeleportIn->setPropertyV(WSNx,(short)295);
  SeqTeleportIn->setPropertyV(WSNy,(short)205);
  SeqTeleportIn->setPropertyV(WSNwidth,(unsigned short)55);
  SeqTeleportIn->setPropertyV(WSNheight,(unsigned short)25);

  SeqTeleportOut = new  WSCvifield(Maiinde_012,"SeqTeleportOut");
      SeqTeleportOut->initialize();
  SeqTeleportOut->setPropertyV(WSNuserValue,(long)1);
  SeqTeleportOut->setPropertyV(WSNname,"SeqTeleportOut");
  SeqTeleportOut->setPropertyV(WSNx,(short)295);
  SeqTeleportOut->setPropertyV(WSNy,(short)230);
  SeqTeleportOut->setPropertyV(WSNwidth,(unsigned short)55);
  SeqTeleportOut->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_073 = new  WSCvlabel(Maiinde_012,"Maivlab_073");
      Maivlab_073->initialize();
  Maivlab_073->setPropertyV(WSNuserValue,(long)1);
  Maivlab_073->setPropertyV(WSNlabelString,"SoundPitch");
  Maivlab_073->setPropertyV(WSNname,"Maivlab_073");
  Maivlab_073->setPropertyV(WSNx,(short)350);
  Maivlab_073->setPropertyV(WSNy,(short)30);
  Maivlab_073->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_073->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_074 = new  WSCvlabel(Maiinde_012,"Maivlab_074");
      Maivlab_074->initialize();
  Maivlab_074->setPropertyV(WSNuserValue,(long)1);
  Maivlab_074->setPropertyV(WSNlabelString,"ActivationSnd");
  Maivlab_074->setPropertyV(WSNfont,(unsigned char)0);
  Maivlab_074->setPropertyV(WSNname,"Maivlab_074");
  Maivlab_074->setPropertyV(WSNx,(short)350);
  Maivlab_074->setPropertyV(WSNy,(short)55);
  Maivlab_074->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_075 = new  WSCvlabel(Maiinde_012,"Maivlab_075");
      Maivlab_075->initialize();
  Maivlab_075->setPropertyV(WSNuserValue,(long)1);
  Maivlab_075->setPropertyV(WSNlabelString,"FriendActSnd");
  Maivlab_075->setPropertyV(WSNname,"Maivlab_075");
  Maivlab_075->setPropertyV(WSNx,(short)350);
  Maivlab_075->setPropertyV(WSNy,(short)80);
  Maivlab_075->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_076 = new  WSCvlabel(Maiinde_012,"Maivlab_076");
      Maivlab_076->initialize();
  Maivlab_076->setPropertyV(WSNuserValue,(long)1);
  Maivlab_076->setPropertyV(WSNlabelString,"ClearSnd");
  Maivlab_076->setPropertyV(WSNname,"Maivlab_076");
  Maivlab_076->setPropertyV(WSNx,(short)350);
  Maivlab_076->setPropertyV(WSNy,(short)105);
  Maivlab_076->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_077 = new  WSCvlabel(Maiinde_012,"Maivlab_077");
      Maivlab_077->initialize();
  Maivlab_077->setPropertyV(WSNuserValue,(long)1);
  Maivlab_077->setPropertyV(WSNlabelString,"KillSnd");
  Maivlab_077->setPropertyV(WSNname,"Maivlab_077");
  Maivlab_077->setPropertyV(WSNx,(short)350);
  Maivlab_077->setPropertyV(WSNy,(short)130);
  Maivlab_077->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_078 = new  WSCvlabel(Maiinde_012,"Maivlab_078");
      Maivlab_078->initialize();
  Maivlab_078->setPropertyV(WSNuserValue,(long)1);
  Maivlab_078->setPropertyV(WSNlabelString,"ApologySnd");
  Maivlab_078->setPropertyV(WSNname,"Maivlab_078");
  Maivlab_078->setPropertyV(WSNx,(short)350);
  Maivlab_078->setPropertyV(WSNy,(short)155);
  Maivlab_078->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_079 = new  WSCvlabel(Maiinde_012,"Maivlab_079");
      Maivlab_079->initialize();
  Maivlab_079->setPropertyV(WSNuserValue,(long)1);
  Maivlab_079->setPropertyV(WSNlabelString,"FriendFireSnd");
  Maivlab_079->setPropertyV(WSNname,"Maivlab_079");
  Maivlab_079->setPropertyV(WSNx,(short)350);
  Maivlab_079->setPropertyV(WSNy,(short)180);
  Maivlab_079->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_080 = new  WSCvlabel(Maiinde_012,"Maivlab_080");
      Maivlab_080->initialize();
  Maivlab_080->setPropertyV(WSNuserValue,(long)1);
  Maivlab_080->setPropertyV(WSNlabelString,"FlamingSnd");
  Maivlab_080->setPropertyV(WSNname,"Maivlab_080");
  Maivlab_080->setPropertyV(WSNx,(short)350);
  Maivlab_080->setPropertyV(WSNy,(short)205);
  Maivlab_080->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_081 = new  WSCvlabel(Maiinde_012,"Maivlab_081");
      Maivlab_081->initialize();
  Maivlab_081->setPropertyV(WSNuserValue,(long)1);
  Maivlab_081->setPropertyV(WSNlabelString,"RandomSnd");
  Maivlab_081->setPropertyV(WSNname,"Maivlab_081");
  Maivlab_081->setPropertyV(WSNx,(short)350);
  Maivlab_081->setPropertyV(WSNy,(short)230);
  Maivlab_081->setPropertyV(WSNheight,(unsigned short)25);

  SoundPitchEdit = new  WSCvifield(Maiinde_012,"SoundPitchEdit");
      SoundPitchEdit->initialize();
  SoundPitchEdit->setPropertyV(WSNuserValue,(long)1);
  SoundPitchEdit->setPropertyV(WSNname,"SoundPitchEdit");
  SoundPitchEdit->setPropertyV(WSNx,(short)440);
  SoundPitchEdit->setPropertyV(WSNy,(short)30);
  SoundPitchEdit->setPropertyV(WSNwidth,(unsigned short)80);
  SoundPitchEdit->setPropertyV(WSNheight,(unsigned short)25);

  RandomSndMaskEdit = new  WSCvifield(Maiinde_012,"RandomSndMaskEdit");
      RandomSndMaskEdit->initialize();
  RandomSndMaskEdit->setPropertyV(WSNuserValue,(long)1);
  RandomSndMaskEdit->setPropertyV(WSNname,"RandomSndMaskEdit");
  RandomSndMaskEdit->setPropertyV(WSNx,(short)450);
  RandomSndMaskEdit->setPropertyV(WSNy,(short)255);
  RandomSndMaskEdit->setPropertyV(WSNwidth,(unsigned short)80);
  RandomSndMaskEdit->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_084 = new  WSCvlabel(Maiinde_012,"Maivlab_084");
      Maivlab_084->initialize();
  Maivlab_084->setPropertyV(WSNuserValue,(long)1);
  Maivlab_084->setPropertyV(WSNlabelString,"RandomSndMask");
  Maivlab_084->setPropertyV(WSNname,"Maivlab_084");
  Maivlab_084->setPropertyV(WSNx,(short)350);
  Maivlab_084->setPropertyV(WSNy,(short)255);
  Maivlab_084->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_085 = new  WSCvlabel(Maiinde_012,"Maivlab_085");
      Maivlab_085->initialize();
  Maivlab_085->setPropertyV(WSNuserValue,(long)1);
  Maivlab_085->setPropertyV(WSNlabelString,"ImpactEffect");
  Maivlab_085->setPropertyV(WSNname,"Maivlab_085");
  Maivlab_085->setPropertyV(WSNx,(short)345);
  Maivlab_085->setPropertyV(WSNy,(short)280);
  Maivlab_085->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_085->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_086 = new  WSCvlabel(Maiinde_012,"Maivlab_086");
      Maivlab_086->initialize();
  Maivlab_086->setPropertyV(WSNuserValue,(long)1);
  Maivlab_086->setPropertyV(WSNlabelString,"MeleeEffect");
  Maivlab_086->setPropertyV(WSNname,"Maivlab_086");
  Maivlab_086->setPropertyV(WSNx,(short)345);
  Maivlab_086->setPropertyV(WSNy,(short)305);
  Maivlab_086->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_086->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_087 = new  WSCvlabel(Maiinde_012,"Maivlab_087");
      Maivlab_087->initialize();
  Maivlab_087->setPropertyV(WSNuserValue,(long)1);
  Maivlab_087->setPropertyV(WSNlabelString,"ContrailEffect");
  Maivlab_087->setPropertyV(WSNname,"Maivlab_087");
  Maivlab_087->setPropertyV(WSNx,(short)345);
  Maivlab_087->setPropertyV(WSNy,(short)330);
  Maivlab_087->setPropertyV(WSNwidth,(unsigned short)110);
  Maivlab_087->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_088 = new  WSCvlabel(Maiinde_012,"Maivlab_088");
      Maivlab_088->initialize();
  Maivlab_088->setPropertyV(WSNuserValue,(long)1);
  Maivlab_088->setPropertyV(WSNlabelString,"HalfVisualArc");
  Maivlab_088->setPropertyV(WSNname,"Maivlab_088");
  Maivlab_088->setPropertyV(WSNx,(short)5);
  Maivlab_088->setPropertyV(WSNy,(short)305);
  Maivlab_088->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_089 = new  WSCvlabel(Maiinde_012,"Maivlab_089");
      Maivlab_089->initialize();
  Maivlab_089->setPropertyV(WSNuserValue,(long)1);
  Maivlab_089->setPropertyV(WSNlabelString,"VertVisualArc");
  Maivlab_089->setPropertyV(WSNname,"Maivlab_089");
  Maivlab_089->setPropertyV(WSNx,(short)5);
  Maivlab_089->setPropertyV(WSNy,(short)330);
  Maivlab_089->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_090 = new  WSCvlabel(Maiinde_012,"Maivlab_090");
      Maivlab_090->initialize();
  Maivlab_090->setPropertyV(WSNuserValue,(long)1);
  Maivlab_090->setPropertyV(WSNlabelString,"Intelligence");
  Maivlab_090->setPropertyV(WSNname,"Maivlab_090");
  Maivlab_090->setPropertyV(WSNx,(short)5);
  Maivlab_090->setPropertyV(WSNy,(short)355);
  Maivlab_090->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_090->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_091 = new  WSCvlabel(Maiinde_012,"Maivlab_091");
      Maivlab_091->initialize();
  Maivlab_091->setPropertyV(WSNuserValue,(long)1);
  Maivlab_091->setPropertyV(WSNlabelString,"Speed");
  Maivlab_091->setPropertyV(WSNname,"Maivlab_091");
  Maivlab_091->setPropertyV(WSNx,(short)5);
  Maivlab_091->setPropertyV(WSNy,(short)380);
  Maivlab_091->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_091->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_092 = new  WSCvlabel(Maiinde_012,"Maivlab_092");
      Maivlab_092->initialize();
  Maivlab_092->setPropertyV(WSNuserValue,(long)1);
  Maivlab_092->setPropertyV(WSNlabelString,"Gravity");
  Maivlab_092->setPropertyV(WSNname,"Maivlab_092");
  Maivlab_092->setPropertyV(WSNx,(short)5);
  Maivlab_092->setPropertyV(WSNy,(short)405);
  Maivlab_092->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_092->setPropertyV(WSNheight,(unsigned short)25);

  HalfVisualArcEdit = new  WSCvifield(Maiinde_012,"HalfVisualArcEdit");
      HalfVisualArcEdit->initialize();
  HalfVisualArcEdit->setPropertyV(WSNuserValue,(long)1);
  HalfVisualArcEdit->setPropertyV(WSNname,"HalfVisualArcEdit");
  HalfVisualArcEdit->setPropertyV(WSNx,(short)105);
  HalfVisualArcEdit->setPropertyV(WSNy,(short)305);
  HalfVisualArcEdit->setPropertyV(WSNwidth,(unsigned short)70);
  HalfVisualArcEdit->setPropertyV(WSNheight,(unsigned short)25);

  VertVisualArcEdit = new  WSCvifield(Maiinde_012,"VertVisualArcEdit");
      VertVisualArcEdit->initialize();
  VertVisualArcEdit->setPropertyV(WSNuserValue,(long)1);
  VertVisualArcEdit->setPropertyV(WSNname,"VertVisualArcEdit");
  VertVisualArcEdit->setPropertyV(WSNx,(short)105);
  VertVisualArcEdit->setPropertyV(WSNy,(short)330);
  VertVisualArcEdit->setPropertyV(WSNwidth,(unsigned short)70);
  VertVisualArcEdit->setPropertyV(WSNheight,(unsigned short)25);

  SpeedEdit = new  WSCvifield(Maiinde_012,"SpeedEdit");
      SpeedEdit->initialize();
  SpeedEdit->setPropertyV(WSNuserValue,(long)1);
  SpeedEdit->setPropertyV(WSNname,"SpeedEdit");
  SpeedEdit->setPropertyV(WSNx,(short)95);
  SpeedEdit->setPropertyV(WSNy,(short)380);
  SpeedEdit->setPropertyV(WSNwidth,(unsigned short)80);
  SpeedEdit->setPropertyV(WSNheight,(unsigned short)25);

  GravityEdit = new  WSCvifield(Maiinde_012,"GravityEdit");
      GravityEdit->initialize();
  GravityEdit->setPropertyV(WSNuserValue,(long)1);
  GravityEdit->setPropertyV(WSNname,"GravityEdit");
  GravityEdit->setPropertyV(WSNx,(short)95);
  GravityEdit->setPropertyV(WSNy,(short)405);
  GravityEdit->setPropertyV(WSNwidth,(unsigned short)80);
  GravityEdit->setPropertyV(WSNheight,(unsigned short)25);

  Maivbtn_106 = new  WSCvbtn(Maiinde_012,"Maivbtn_106");
      Maivbtn_106->initialize();
  Maivbtn_106->setPropertyV(WSNuserValue,(long)2);
  Maivbtn_106->setPropertyV(WSNlabelString,"Set as Default");
  Maivbtn_106->setPropertyV(WSNname,"Maivbtn_106");
  Maivbtn_106->setPropertyV(WSNvis,(WSCbool)1);
  Maivbtn_106->setPropertyV(WSNx,(short)270);
  Maivbtn_106->setPropertyV(WSNy,(short)430);
  Maivbtn_106->setPropertyV(WSNwidth,(unsigned short)115);
  Maivbtn_106->setPropertyV(WSNheight,(unsigned short)25);

  SpeedCombo = new  WSCoption(Maiinde_012,"SpeedCombo");
      SpeedCombo->initialize();
  SpeedCombo->setPropertyV(WSNuserValue,(long)1);
  SpeedCombo->setPropertyV(WSNvalue,(long)1);
  SpeedCombo->setPropertyV(WSNlabelString,"item1");
  SpeedCombo->setPropertyV(WSNfont,(unsigned char)0);
  SpeedCombo->setPropertyV(WSNname,"SpeedCombo");
  SpeedCombo->setPropertyV(WSNx,(short)175);
  SpeedCombo->setPropertyV(WSNy,(short)380);
  SpeedCombo->setPropertyV(WSNheight,(unsigned short)25);

  IntelligenceCombo = new  WSCoption(Maiinde_012,"IntelligenceCombo");
      IntelligenceCombo->initialize();
  IntelligenceCombo->setPropertyV(WSNuserValue,(long)1);
  IntelligenceCombo->setPropertyV(WSNmenuItems,"Low:1:ep1_name,Average:2:ep2_name,High:3:ep3_name");
  IntelligenceCombo->setPropertyV(WSNvalue,(long)1);
  IntelligenceCombo->setPropertyV(WSNlabelString,"Low");
  IntelligenceCombo->setPropertyV(WSNfont,(unsigned char)0);
  IntelligenceCombo->setPropertyV(WSNname,"IntelligenceCombo");
  IntelligenceCombo->setPropertyV(WSNx,(short)95);
  IntelligenceCombo->setPropertyV(WSNy,(short)355);
  IntelligenceCombo->setPropertyV(WSNwidth,(unsigned short)80);
  IntelligenceCombo->setPropertyV(WSNheight,(unsigned short)25);
    extern void IntelligenceValueChFunc(WSCbase*);
    IntelligenceCombo->addProcedureV("IntelligenceValueCh","IntelligenceValueChFunc",IntelligenceValueChFunc,3);

  CollectionBtn = new  WSCvbtn(Maiinde_012,"CollectionBtn");
      CollectionBtn->initialize();
  CollectionBtn->setPropertyV(WSNuserValue,(long)1);
  CollectionBtn->setPropertyV(WSNfont,(unsigned char)0);
  CollectionBtn->setPropertyV(WSNname,"CollectionBtn");
  CollectionBtn->setPropertyV(WSNx,(short)95);
  CollectionBtn->setPropertyV(WSNy,(short)30);
  CollectionBtn->setPropertyV(WSNwidth,(unsigned short)80);
  CollectionBtn->setPropertyV(WSNheight,(unsigned short)25);
    extern void CollectionBtnFunc(WSCbase*);
    CollectionBtn->addProcedureV("CollectionBtn","CollectionBtnFunc",CollectionBtnFunc,13);

  CarryItemBtn = new  WSCvbtn(Maiinde_012,"CarryItemBtn");
      CarryItemBtn->initialize();
  CarryItemBtn->setPropertyV(WSNuserValue,(long)1);
  CarryItemBtn->setPropertyV(WSNfont,(unsigned char)0);
  CarryItemBtn->setPropertyV(WSNname,"CarryItemBtn");
  CarryItemBtn->setPropertyV(WSNx,(short)95);
  CarryItemBtn->setPropertyV(WSNy,(short)280);
  CarryItemBtn->setPropertyV(WSNwidth,(unsigned short)110);
  CarryItemBtn->setPropertyV(WSNheight,(unsigned short)25);
    extern void CaarryItemBtnFunc(WSCbase*);
    CarryItemBtn->addProcedureV("CaarryItemBtn","CaarryItemBtnFunc",CaarryItemBtnFunc,13);

  ActivationSndBtn = new  WSCvbtn(Maiinde_012,"ActivationSndBtn");
      ActivationSndBtn->initialize();
  ActivationSndBtn->setPropertyV(WSNuserValue,(long)1);
  ActivationSndBtn->setPropertyV(WSNfont,(unsigned char)0);
  ActivationSndBtn->setPropertyV(WSNname,"ActivationSndBtn");
  ActivationSndBtn->setPropertyV(WSNx,(short)450);
  ActivationSndBtn->setPropertyV(WSNy,(short)55);
  ActivationSndBtn->setPropertyV(WSNwidth,(unsigned short)95);
  ActivationSndBtn->setPropertyV(WSNheight,(unsigned short)25);

  FriendActSndBtn = new  WSCvbtn(Maiinde_012,"FriendActSndBtn");
      FriendActSndBtn->initialize();
  FriendActSndBtn->setPropertyV(WSNuserValue,(long)1);
  FriendActSndBtn->setPropertyV(WSNfont,(unsigned char)0);
  FriendActSndBtn->setPropertyV(WSNname,"FriendActSndBtn");
  FriendActSndBtn->setPropertyV(WSNx,(short)450);
  FriendActSndBtn->setPropertyV(WSNy,(short)80);
  FriendActSndBtn->setPropertyV(WSNwidth,(unsigned short)95);
  FriendActSndBtn->setPropertyV(WSNheight,(unsigned short)25);

  ClearSndBtn = new  WSCvbtn(Maiinde_012,"ClearSndBtn");
      ClearSndBtn->initialize();
  ClearSndBtn->setPropertyV(WSNuserValue,(long)1);
  ClearSndBtn->setPropertyV(WSNfont,(unsigned char)0);
  ClearSndBtn->setPropertyV(WSNname,"ClearSndBtn");
  ClearSndBtn->setPropertyV(WSNx,(short)450);
  ClearSndBtn->setPropertyV(WSNy,(short)105);
  ClearSndBtn->setPropertyV(WSNwidth,(unsigned short)95);
  ClearSndBtn->setPropertyV(WSNheight,(unsigned short)25);

  KillSndBtn = new  WSCvbtn(Maiinde_012,"KillSndBtn");
      KillSndBtn->initialize();
  KillSndBtn->setPropertyV(WSNuserValue,(long)1);
  KillSndBtn->setPropertyV(WSNfont,(unsigned char)0);
  KillSndBtn->setPropertyV(WSNname,"KillSndBtn");
  KillSndBtn->setPropertyV(WSNx,(short)450);
  KillSndBtn->setPropertyV(WSNy,(short)130);
  KillSndBtn->setPropertyV(WSNwidth,(unsigned short)95);
  KillSndBtn->setPropertyV(WSNheight,(unsigned short)25);

  ApologySndBtn = new  WSCvbtn(Maiinde_012,"ApologySndBtn");
      ApologySndBtn->initialize();
  ApologySndBtn->setPropertyV(WSNuserValue,(long)1);
  ApologySndBtn->setPropertyV(WSNfont,(unsigned char)0);
  ApologySndBtn->setPropertyV(WSNname,"ApologySndBtn");
  ApologySndBtn->setPropertyV(WSNx,(short)450);
  ApologySndBtn->setPropertyV(WSNy,(short)155);
  ApologySndBtn->setPropertyV(WSNwidth,(unsigned short)95);
  ApologySndBtn->setPropertyV(WSNheight,(unsigned short)25);

  FriendFireSndBtn = new  WSCvbtn(Maiinde_012,"FriendFireSndBtn");
      FriendFireSndBtn->initialize();
  FriendFireSndBtn->setPropertyV(WSNuserValue,(long)1);
  FriendFireSndBtn->setPropertyV(WSNfont,(unsigned char)0);
  FriendFireSndBtn->setPropertyV(WSNname,"FriendFireSndBtn");
  FriendFireSndBtn->setPropertyV(WSNx,(short)450);
  FriendFireSndBtn->setPropertyV(WSNy,(short)180);
  FriendFireSndBtn->setPropertyV(WSNwidth,(unsigned short)95);
  FriendFireSndBtn->setPropertyV(WSNheight,(unsigned short)25);

  FlamingSndBtn = new  WSCvbtn(Maiinde_012,"FlamingSndBtn");
      FlamingSndBtn->initialize();
  FlamingSndBtn->setPropertyV(WSNuserValue,(long)1);
  FlamingSndBtn->setPropertyV(WSNfont,(unsigned char)0);
  FlamingSndBtn->setPropertyV(WSNname,"FlamingSndBtn");
  FlamingSndBtn->setPropertyV(WSNx,(short)450);
  FlamingSndBtn->setPropertyV(WSNy,(short)205);
  FlamingSndBtn->setPropertyV(WSNwidth,(unsigned short)95);
  FlamingSndBtn->setPropertyV(WSNheight,(unsigned short)25);

  RandomSndBtn = new  WSCvbtn(Maiinde_012,"RandomSndBtn");
      RandomSndBtn->initialize();
  RandomSndBtn->setPropertyV(WSNuserValue,(long)1);
  RandomSndBtn->setPropertyV(WSNfont,(unsigned char)0);
  RandomSndBtn->setPropertyV(WSNname,"RandomSndBtn");
  RandomSndBtn->setPropertyV(WSNx,(short)450);
  RandomSndBtn->setPropertyV(WSNy,(short)230);
  RandomSndBtn->setPropertyV(WSNwidth,(unsigned short)95);
  RandomSndBtn->setPropertyV(WSNheight,(unsigned short)25);

  ClassCombo = new  WSCoption(Maiinde_012,"ClassCombo");
      ClassCombo->initialize();
  ClassCombo->setPropertyV(WSNuserValue,(long)1);
  ClassCombo->setPropertyV(WSNvalue,(long)1);
  ClassCombo->setPropertyV(WSNlabelString,"item1");
  ClassCombo->setPropertyV(WSNfont,(unsigned char)0);
  ClassCombo->setPropertyV(WSNname,"ClassCombo");
  ClassCombo->setPropertyV(WSNx,(short)95);
  ClassCombo->setPropertyV(WSNy,(short)105);
  ClassCombo->setPropertyV(WSNwidth,(unsigned short)110);
  ClassCombo->setPropertyV(WSNheight,(unsigned short)25);

  ImpactEffectBtn = new  WSCvbtn(Maiinde_012,"ImpactEffectBtn");
      ImpactEffectBtn->initialize();
  ImpactEffectBtn->setPropertyV(WSNuserValue,(long)1);
  ImpactEffectBtn->setPropertyV(WSNfont,(unsigned char)0);
  ImpactEffectBtn->setPropertyV(WSNname,"ImpactEffectBtn");
  ImpactEffectBtn->setPropertyV(WSNx,(short)450);
  ImpactEffectBtn->setPropertyV(WSNy,(short)280);
  ImpactEffectBtn->setPropertyV(WSNwidth,(unsigned short)110);
  ImpactEffectBtn->setPropertyV(WSNheight,(unsigned short)25);

  MeleeEffectBtn = new  WSCvbtn(Maiinde_012,"MeleeEffectBtn");
      MeleeEffectBtn->initialize();
  MeleeEffectBtn->setPropertyV(WSNuserValue,(long)1);
  MeleeEffectBtn->setPropertyV(WSNfont,(unsigned char)0);
  MeleeEffectBtn->setPropertyV(WSNname,"MeleeEffectBtn");
  MeleeEffectBtn->setPropertyV(WSNx,(short)450);
  MeleeEffectBtn->setPropertyV(WSNy,(short)305);
  MeleeEffectBtn->setPropertyV(WSNwidth,(unsigned short)110);
  MeleeEffectBtn->setPropertyV(WSNheight,(unsigned short)25);

  ContrailEffectBtn = new  WSCvbtn(Maiinde_012,"ContrailEffectBtn");
      ContrailEffectBtn->initialize();
  ContrailEffectBtn->setPropertyV(WSNuserValue,(long)1);
  ContrailEffectBtn->setPropertyV(WSNfont,(unsigned char)0);
  ContrailEffectBtn->setPropertyV(WSNname,"ContrailEffectBtn");
  ContrailEffectBtn->setPropertyV(WSNx,(short)450);
  ContrailEffectBtn->setPropertyV(WSNy,(short)330);
  ContrailEffectBtn->setPropertyV(WSNwidth,(unsigned short)110);
  ContrailEffectBtn->setPropertyV(WSNheight,(unsigned short)25);

  BtnDefaultMonster01 = new  WSCvbtn(Maiinde_012,"BtnDefaultMonster01");
      BtnDefaultMonster01->initialize();
  BtnDefaultMonster01->setPropertyV(WSNuserValue,(long)1);
  BtnDefaultMonster01->setPropertyV(WSNlabelString,"SetAsDefault");
  BtnDefaultMonster01->setPropertyV(WSNname,"BtnDefaultMonster01");
  BtnDefaultMonster01->setPropertyV(WSNx,(short)460);
  BtnDefaultMonster01->setPropertyV(WSNy,(short)420);

  ListImmunities = new  WSCcheckGroup(Maiinde_012,"ListImmunities");
      ListImmunities->initialize();
  ListImmunities->setPropertyV(WSNuserValue,(long)2);
  ListImmunities->setPropertyV(WSNvalue,(unsigned long)4);
  ListImmunities->setPropertyV(WSNtitleString,"Immunities");
  ListImmunities->setPropertyV(WSNmenuItemHeight,(unsigned short)12);
  ListImmunities->setPropertyV(WSNfont,(unsigned char)0);
  ListImmunities->setPropertyV(WSNindicatorSize,(unsigned char)10);
  ListImmunities->setPropertyV(WSNname,"ListImmunities");
  ListImmunities->setPropertyV(WSNx,(short)5);
  ListImmunities->setPropertyV(WSNy,(short)25);
  ListImmunities->setPropertyV(WSNwidth,(unsigned short)105);
  ListImmunities->setPropertyV(WSNheight,(unsigned short)430);
  ListImmunities->setPropertyV(WSNvis,(WSCbool)1);

  ListWeakness = new  WSCcheckGroup(Maiinde_012,"ListWeakness");
      ListWeakness->initialize();
  ListWeakness->setPropertyV(WSNuserValue,(long)2);
  ListWeakness->setPropertyV(WSNtitleString,"Weakness");
  ListWeakness->setPropertyV(WSNmenuItemHeight,(unsigned short)12);
  ListWeakness->setPropertyV(WSNfont,(unsigned char)0);
  ListWeakness->setPropertyV(WSNindicatorSize,(unsigned char)10);
  ListWeakness->setPropertyV(WSNname,"ListWeakness");
  ListWeakness->setPropertyV(WSNx,(short)110);
  ListWeakness->setPropertyV(WSNy,(short)25);
  ListWeakness->setPropertyV(WSNwidth,(unsigned short)105);
  ListWeakness->setPropertyV(WSNheight,(unsigned short)430);
  ListWeakness->setPropertyV(WSNvis,(WSCbool)1);

  ListEnemies = new  WSCcheckGroup(Maiinde_012,"ListEnemies");
      ListEnemies->initialize();
  ListEnemies->setPropertyV(WSNuserValue,(long)2);
  ListEnemies->setPropertyV(WSNvalue,(unsigned long)1);
  ListEnemies->setPropertyV(WSNtitleString,"Enemies");
  ListEnemies->setPropertyV(WSNmenuItemHeight,(unsigned short)12);
  ListEnemies->setPropertyV(WSNfont,(unsigned char)0);
  ListEnemies->setPropertyV(WSNindicatorSize,(unsigned char)10);
  ListEnemies->setPropertyV(WSNname,"ListEnemies");
  ListEnemies->setPropertyV(WSNx,(short)220);
  ListEnemies->setPropertyV(WSNy,(short)25);
  ListEnemies->setPropertyV(WSNwidth,(unsigned short)105);
  ListEnemies->setPropertyV(WSNheight,(unsigned short)340);
  ListEnemies->setPropertyV(WSNvis,(WSCbool)1);

  ListFriends = new  WSCcheckGroup(Maiinde_012,"ListFriends");
      ListFriends->initialize();
  ListFriends->setPropertyV(WSNuserValue,(long)2);
  ListFriends->setPropertyV(WSNvalue,(unsigned long)1);
  ListFriends->setPropertyV(WSNtitleString,"Friends");
  ListFriends->setPropertyV(WSNmenuItemHeight,(unsigned short)12);
  ListFriends->setPropertyV(WSNfont,(unsigned char)0);
  ListFriends->setPropertyV(WSNindicatorSize,(unsigned char)10);
  ListFriends->setPropertyV(WSNname,"ListFriends");
  ListFriends->setPropertyV(WSNx,(short)325);
  ListFriends->setPropertyV(WSNy,(short)25);
  ListFriends->setPropertyV(WSNwidth,(unsigned short)110);
  ListFriends->setPropertyV(WSNheight,(unsigned short)340);
  ListFriends->setPropertyV(WSNvis,(WSCbool)1);

  ListFlags = new  WSCcheckGroup(Maiinde_012,"ListFlags");
      ListFlags->initialize();
  ListFlags->setPropertyV(WSNuserValue,(long)2);
  ListFlags->setPropertyV(WSNvalue,(unsigned long)1);
  ListFlags->setPropertyV(WSNtitleString,"Flags");
  ListFlags->setPropertyV(WSNmenuItemHeight,(unsigned short)11);
  ListFlags->setPropertyV(WSNfont,(unsigned char)0);
  ListFlags->setPropertyV(WSNindicatorSize,(unsigned char)10);
  ListFlags->setPropertyV(WSNname,"ListFlags");
  ListFlags->setPropertyV(WSNx,(short)435);
  ListFlags->setPropertyV(WSNy,(short)25);
  ListFlags->setPropertyV(WSNwidth,(unsigned short)105);
  ListFlags->setPropertyV(WSNheight,(unsigned short)430);
  ListFlags->setPropertyV(WSNvis,(WSCbool)1);

  Maivlab_009 = new  WSCvlabel(Maiinde_012,"Maivlab_009");
      Maivlab_009->initialize();
  Maivlab_009->setPropertyV(WSNuserValue,(long)1);
  Maivlab_009->setPropertyV(WSNlabelString,"ShrapnelR");
  Maivlab_009->setPropertyV(WSNname,"Maivlab_009");
  Maivlab_009->setPropertyV(WSNx,(short)205);
  Maivlab_009->setPropertyV(WSNy,(short)255);
  Maivlab_009->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_009->setPropertyV(WSNheight,(unsigned short)25);

  ShapnelRadiusEdit = new  WSCvifield(Maiinde_012,"ShapnelRadiusEdit");
      ShapnelRadiusEdit->initialize();
  ShapnelRadiusEdit->setPropertyV(WSNuserValue,(long)1);
  ShapnelRadiusEdit->setPropertyV(WSNname,"ShapnelRadiusEdit");
  ShapnelRadiusEdit->setPropertyV(WSNx,(short)295);
  ShapnelRadiusEdit->setPropertyV(WSNy,(short)255);
  ShapnelRadiusEdit->setPropertyV(WSNwidth,(unsigned short)55);
  ShapnelRadiusEdit->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_012 = new  WSCvlabel(Maiinde_012,"Maivlab_012");
      Maivlab_012->initialize();
  Maivlab_012->setPropertyV(WSNuserValue,(long)1);
  Maivlab_012->setPropertyV(WSNlabelString,"ShrapnelType");
  Maivlab_012->setPropertyV(WSNname,"Maivlab_012");
  Maivlab_012->setPropertyV(WSNx,(short)205);
  Maivlab_012->setPropertyV(WSNy,(short)355);
  Maivlab_012->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_012->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_013 = new  WSCvlabel(Maiinde_012,"Maivlab_013");
      Maivlab_013->initialize();
  Maivlab_013->setPropertyV(WSNuserValue,(long)1);
  Maivlab_013->setPropertyV(WSNlabelString,"ShrapnelScale");
  Maivlab_013->setPropertyV(WSNname,"Maivlab_013");
  Maivlab_013->setPropertyV(WSNx,(short)205);
  Maivlab_013->setPropertyV(WSNy,(short)330);
  Maivlab_013->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_013->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_014 = new  WSCvlabel(Maiinde_012,"Maivlab_014");
      Maivlab_014->initialize();
  Maivlab_014->setPropertyV(WSNuserValue,(long)1);
  Maivlab_014->setPropertyV(WSNlabelString,"ShrapnelBase");
  Maivlab_014->setPropertyV(WSNname,"Maivlab_014");
  Maivlab_014->setPropertyV(WSNx,(short)205);
  Maivlab_014->setPropertyV(WSNy,(short)280);
  Maivlab_014->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_014->setPropertyV(WSNheight,(unsigned short)25);

  Maaaa = new  WSCvlabel(Maiinde_012,"Maaaa");
      Maaaa->initialize();
  Maaaa->setPropertyV(WSNuserValue,(long)1);
  Maaaa->setPropertyV(WSNlabelString,"ShrapnelRnd");
  Maaaa->setPropertyV(WSNname,"Maaaa");
  Maaaa->setPropertyV(WSNx,(short)205);
  Maaaa->setPropertyV(WSNy,(short)305);
  Maaaa->setPropertyV(WSNwidth,(unsigned short)90);
  Maaaa->setPropertyV(WSNheight,(unsigned short)25);

  ShapnelRndEdit = new  WSCvifield(Maiinde_012,"ShapnelRndEdit");
      ShapnelRndEdit->initialize();
  ShapnelRndEdit->setPropertyV(WSNuserValue,(long)1);
  ShapnelRndEdit->setPropertyV(WSNname,"ShapnelRndEdit");
  ShapnelRndEdit->setPropertyV(WSNx,(short)295);
  ShapnelRndEdit->setPropertyV(WSNy,(short)305);
  ShapnelRndEdit->setPropertyV(WSNwidth,(unsigned short)55);
  ShapnelRndEdit->setPropertyV(WSNheight,(unsigned short)25);

  ShapnelScaleEdit = new  WSCvifield(Maiinde_012,"ShapnelScaleEdit");
      ShapnelScaleEdit->initialize();
  ShapnelScaleEdit->setPropertyV(WSNuserValue,(long)1);
  ShapnelScaleEdit->setPropertyV(WSNname,"ShapnelScaleEdit");
  ShapnelScaleEdit->setPropertyV(WSNx,(short)295);
  ShapnelScaleEdit->setPropertyV(WSNy,(short)330);
  ShapnelScaleEdit->setPropertyV(WSNwidth,(unsigned short)55);
  ShapnelScaleEdit->setPropertyV(WSNheight,(unsigned short)25);

  ShapnelBaseEdit = new  WSCvifield(Maiinde_012,"ShapnelBaseEdit");
      ShapnelBaseEdit->initialize();
  ShapnelBaseEdit->setPropertyV(WSNuserValue,(long)1);
  ShapnelBaseEdit->setPropertyV(WSNname,"ShapnelBaseEdit");
  ShapnelBaseEdit->setPropertyV(WSNx,(short)295);
  ShapnelBaseEdit->setPropertyV(WSNy,(short)280);
  ShapnelBaseEdit->setPropertyV(WSNwidth,(unsigned short)55);
  ShapnelBaseEdit->setPropertyV(WSNheight,(unsigned short)25);

  ShapnelTypeBtn = new  WSCvbtn(Maiinde_012,"ShapnelTypeBtn");
      ShapnelTypeBtn->initialize();
  ShapnelTypeBtn->setPropertyV(WSNuserValue,(long)1);
  ShapnelTypeBtn->setPropertyV(WSNfont,(unsigned char)0);
  ShapnelTypeBtn->setPropertyV(WSNname,"ShapnelTypeBtn");
  ShapnelTypeBtn->setPropertyV(WSNx,(short)295);
  ShapnelTypeBtn->setPropertyV(WSNy,(short)355);
  ShapnelTypeBtn->setPropertyV(WSNwidth,(unsigned short)110);
  ShapnelTypeBtn->setPropertyV(WSNheight,(unsigned short)25);
    extern void ShapnelTypeBtnDownFunc(WSCbase*);
    ShapnelTypeBtn->addProcedureV("ShapnelTypeBtnDown","ShapnelTypeBtnDownFunc",ShapnelTypeBtnDownFunc,13);

  ShapnelAlienCheck = new  WSCvradio(Maiinde_012,"ShapnelAlienCheck");
      ShapnelAlienCheck->initialize();
  ShapnelAlienCheck->setPropertyV(WSNuserValue,(long)1);
  ShapnelAlienCheck->setPropertyV(WSNlabelString,"Shrapnel is Alien");
  ShapnelAlienCheck->setPropertyV(WSNname,"ShapnelAlienCheck");
  ShapnelAlienCheck->setPropertyV(WSNx,(short)295);
  ShapnelAlienCheck->setPropertyV(WSNy,(short)380);
  ShapnelAlienCheck->setPropertyV(WSNwidth,(unsigned short)155);
  ShapnelAlienCheck->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_023 = new  WSCvlabel(Maiinde_012,"Maivlab_023");
      Maivlab_023->initialize();
  Maivlab_023->setPropertyV(WSNuserValue,(long)3);
  Maivlab_023->setPropertyV(WSNlabelString,"Frequency");
  Maivlab_023->setPropertyV(WSNname,"Maivlab_023");
  Maivlab_023->setPropertyV(WSNx,(short)5);
  Maivlab_023->setPropertyV(WSNy,(short)30);
  Maivlab_023->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_023->setPropertyV(WSNheight,(unsigned short)25);

  FrequencyEdit = new  WSCvifield(Maiinde_012,"FrequencyEdit");
      FrequencyEdit->initialize();
  FrequencyEdit->setPropertyV(WSNuserValue,(long)3);
  FrequencyEdit->setPropertyV(WSNname,"FrequencyEdit");
  FrequencyEdit->setPropertyV(WSNx,(short)100);
  FrequencyEdit->setPropertyV(WSNy,(short)30);
  FrequencyEdit->setPropertyV(WSNwidth,(unsigned short)80);
  FrequencyEdit->setPropertyV(WSNheight,(unsigned short)25);

  Maitfor_025 = new  WSCtform(Maiinde_012,"Maitfor_025");
      Maitfor_025->initialize();
  Maitfor_025->setPropertyV(WSNuserValue,(long)3);
  Maitfor_025->setPropertyV(WSNtitleString,"Melee");
  Maitfor_025->setPropertyV(WSNname,"Maitfor_025");
  Maitfor_025->setPropertyV(WSNx,(short)5);
  Maitfor_025->setPropertyV(WSNy,(short)60);
  Maitfor_025->setPropertyV(WSNwidth,(unsigned short)245);
  Maitfor_025->setPropertyV(WSNheight,(unsigned short)255);

  MeleedzEdit = new  WSCvifield(Maitfor_025,"MeleedzEdit");
      MeleedzEdit->initialize();
  MeleedzEdit->setPropertyV(WSNuserValue,(long)3);
  MeleedzEdit->setPropertyV(WSNname,"MeleedzEdit");
  MeleedzEdit->setPropertyV(WSNvis,(WSCbool)1);
  MeleedzEdit->setPropertyV(WSNx,(short)105);
  MeleedzEdit->setPropertyV(WSNy,(short)190);
  MeleedzEdit->setPropertyV(WSNwidth,(unsigned short)80);
  MeleedzEdit->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_026 = new  WSCvlabel(Maitfor_025,"Maivlab_026");
      Maivlab_026->initialize();
  Maivlab_026->setPropertyV(WSNuserValue,(long)3);
  Maivlab_026->setPropertyV(WSNlabelString,"Type");
  Maivlab_026->setPropertyV(WSNname,"Maivlab_026");
  Maivlab_026->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_026->setPropertyV(WSNx,(short)10);
  Maivlab_026->setPropertyV(WSNy,(short)15);
  Maivlab_026->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_026->setPropertyV(WSNheight,(unsigned short)25);

  BtnMeleeType = new  WSCvbtn(Maitfor_025,"BtnMeleeType");
      BtnMeleeType->initialize();
  BtnMeleeType->setPropertyV(WSNname,"BtnMeleeType");
  BtnMeleeType->setPropertyV(WSNvis,(WSCbool)1);
  BtnMeleeType->setPropertyV(WSNx,(short)105);
  BtnMeleeType->setPropertyV(WSNy,(short)15);
  BtnMeleeType->setPropertyV(WSNwidth,(unsigned short)130);
  BtnMeleeType->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_028 = new  WSCvlabel(Maitfor_025,"Maivlab_028");
      Maivlab_028->initialize();
  Maivlab_028->setPropertyV(WSNuserValue,(long)3);
  Maivlab_028->setPropertyV(WSNlabelString,"Repetitions");
  Maivlab_028->setPropertyV(WSNname,"Maivlab_028");
  Maivlab_028->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_028->setPropertyV(WSNx,(short)10);
  Maivlab_028->setPropertyV(WSNy,(short)40);
  Maivlab_028->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_028->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_029 = new  WSCvlabel(Maitfor_025,"Maivlab_029");
      Maivlab_029->initialize();
  Maivlab_029->setPropertyV(WSNuserValue,(long)3);
  Maivlab_029->setPropertyV(WSNlabelString,"Error");
  Maivlab_029->setPropertyV(WSNname,"Maivlab_029");
  Maivlab_029->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_029->setPropertyV(WSNx,(short)10);
  Maivlab_029->setPropertyV(WSNy,(short)65);
  Maivlab_029->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_029->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_030 = new  WSCvlabel(Maitfor_025,"Maivlab_030");
      Maivlab_030->initialize();
  Maivlab_030->setPropertyV(WSNuserValue,(long)3);
  Maivlab_030->setPropertyV(WSNlabelString,"Range");
  Maivlab_030->setPropertyV(WSNname,"Maivlab_030");
  Maivlab_030->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_030->setPropertyV(WSNx,(short)10);
  Maivlab_030->setPropertyV(WSNy,(short)90);
  Maivlab_030->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_030->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_031 = new  WSCvlabel(Maitfor_025,"Maivlab_031");
      Maivlab_031->initialize();
  Maivlab_031->setPropertyV(WSNuserValue,(long)3);
  Maivlab_031->setPropertyV(WSNlabelString,"Sequence");
  Maivlab_031->setPropertyV(WSNname,"Maivlab_031");
  Maivlab_031->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_031->setPropertyV(WSNx,(short)10);
  Maivlab_031->setPropertyV(WSNy,(short)115);
  Maivlab_031->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_031->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_032 = new  WSCvlabel(Maitfor_025,"Maivlab_032");
      Maivlab_032->initialize();
  Maivlab_032->setPropertyV(WSNuserValue,(long)3);
  Maivlab_032->setPropertyV(WSNlabelString,"dx");
  Maivlab_032->setPropertyV(WSNname,"Maivlab_032");
  Maivlab_032->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_032->setPropertyV(WSNx,(short)10);
  Maivlab_032->setPropertyV(WSNy,(short)140);
  Maivlab_032->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_032->setPropertyV(WSNheight,(unsigned short)25);

  MeleeRepetitionsEdit = new  WSCvifield(Maitfor_025,"MeleeRepetitionsEdit");
      MeleeRepetitionsEdit->initialize();
  MeleeRepetitionsEdit->setPropertyV(WSNuserValue,(long)3);
  MeleeRepetitionsEdit->setPropertyV(WSNname,"MeleeRepetitionsEdit");
  MeleeRepetitionsEdit->setPropertyV(WSNvis,(WSCbool)1);
  MeleeRepetitionsEdit->setPropertyV(WSNx,(short)105);
  MeleeRepetitionsEdit->setPropertyV(WSNy,(short)40);
  MeleeRepetitionsEdit->setPropertyV(WSNwidth,(unsigned short)80);
  MeleeRepetitionsEdit->setPropertyV(WSNheight,(unsigned short)25);

  MeleeErrorEdit = new  WSCvifield(Maitfor_025,"MeleeErrorEdit");
      MeleeErrorEdit->initialize();
  MeleeErrorEdit->setPropertyV(WSNuserValue,(long)3);
  MeleeErrorEdit->setPropertyV(WSNname,"MeleeErrorEdit");
  MeleeErrorEdit->setPropertyV(WSNvis,(WSCbool)1);
  MeleeErrorEdit->setPropertyV(WSNx,(short)105);
  MeleeErrorEdit->setPropertyV(WSNy,(short)65);
  MeleeErrorEdit->setPropertyV(WSNwidth,(unsigned short)80);
  MeleeErrorEdit->setPropertyV(WSNheight,(unsigned short)25);

  MeleeRangeEdit = new  WSCvifield(Maitfor_025,"MeleeRangeEdit");
      MeleeRangeEdit->initialize();
  MeleeRangeEdit->setPropertyV(WSNuserValue,(long)3);
  MeleeRangeEdit->setPropertyV(WSNname,"MeleeRangeEdit");
  MeleeRangeEdit->setPropertyV(WSNvis,(WSCbool)1);
  MeleeRangeEdit->setPropertyV(WSNx,(short)105);
  MeleeRangeEdit->setPropertyV(WSNy,(short)90);
  MeleeRangeEdit->setPropertyV(WSNwidth,(unsigned short)80);
  MeleeRangeEdit->setPropertyV(WSNheight,(unsigned short)25);

  MeleeSequenceEdit = new  WSCvifield(Maitfor_025,"MeleeSequenceEdit");
      MeleeSequenceEdit->initialize();
  MeleeSequenceEdit->setPropertyV(WSNuserValue,(long)3);
  MeleeSequenceEdit->setPropertyV(WSNname,"MeleeSequenceEdit");
  MeleeSequenceEdit->setPropertyV(WSNvis,(WSCbool)1);
  MeleeSequenceEdit->setPropertyV(WSNx,(short)105);
  MeleeSequenceEdit->setPropertyV(WSNy,(short)115);
  MeleeSequenceEdit->setPropertyV(WSNwidth,(unsigned short)80);
  MeleeSequenceEdit->setPropertyV(WSNheight,(unsigned short)25);

  MeleedxEdit = new  WSCvifield(Maitfor_025,"MeleedxEdit");
      MeleedxEdit->initialize();
  MeleedxEdit->setPropertyV(WSNuserValue,(long)3);
  MeleedxEdit->setPropertyV(WSNname,"MeleedxEdit");
  MeleedxEdit->setPropertyV(WSNvis,(WSCbool)1);
  MeleedxEdit->setPropertyV(WSNx,(short)105);
  MeleedxEdit->setPropertyV(WSNy,(short)140);
  MeleedxEdit->setPropertyV(WSNwidth,(unsigned short)80);
  MeleedxEdit->setPropertyV(WSNheight,(unsigned short)25);

  MeleedyEdit = new  WSCvifield(Maitfor_025,"MeleedyEdit");
      MeleedyEdit->initialize();
  MeleedyEdit->setPropertyV(WSNuserValue,(long)3);
  MeleedyEdit->setPropertyV(WSNname,"MeleedyEdit");
  MeleedyEdit->setPropertyV(WSNvis,(WSCbool)1);
  MeleedyEdit->setPropertyV(WSNx,(short)105);
  MeleedyEdit->setPropertyV(WSNy,(short)165);
  MeleedyEdit->setPropertyV(WSNwidth,(unsigned short)80);
  MeleedyEdit->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_040 = new  WSCvlabel(Maitfor_025,"Maivlab_040");
      Maivlab_040->initialize();
  Maivlab_040->setPropertyV(WSNuserValue,(long)3);
  Maivlab_040->setPropertyV(WSNlabelString,"dy");
  Maivlab_040->setPropertyV(WSNname,"Maivlab_040");
  Maivlab_040->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_040->setPropertyV(WSNx,(short)10);
  Maivlab_040->setPropertyV(WSNy,(short)165);
  Maivlab_040->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_040->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_041 = new  WSCvlabel(Maitfor_025,"Maivlab_041");
      Maivlab_041->initialize();
  Maivlab_041->setPropertyV(WSNuserValue,(long)3);
  Maivlab_041->setPropertyV(WSNlabelString,"dz");
  Maivlab_041->setPropertyV(WSNname,"Maivlab_041");
  Maivlab_041->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_041->setPropertyV(WSNx,(short)10);
  Maivlab_041->setPropertyV(WSNy,(short)190);
  Maivlab_041->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_041->setPropertyV(WSNheight,(unsigned short)25);

  BtnMeleePreset = new  WSCvbtn(Maitfor_025,"BtnMeleePreset");
      BtnMeleePreset->initialize();
  BtnMeleePreset->setPropertyV(WSNlabelString,"Preset From Other Monster");
  BtnMeleePreset->setPropertyV(WSNname,"BtnMeleePreset");
  BtnMeleePreset->setPropertyV(WSNvis,(WSCbool)1);
  BtnMeleePreset->setPropertyV(WSNx,(short)10);
  BtnMeleePreset->setPropertyV(WSNy,(short)220);
  BtnMeleePreset->setPropertyV(WSNwidth,(unsigned short)225);
    extern void BtnMeleePresetDownFunc(WSCbase*);
    BtnMeleePreset->addProcedureV("BtnMeleePresetDown","BtnMeleePresetDownFunc",BtnMeleePresetDownFunc,13);

  BtnPresetThisAllEnemyOn = new  WSCvbtn(Maiinde_012,"BtnPresetThisAllEnemyOn");
      BtnPresetThisAllEnemyOn->initialize();
  BtnPresetThisAllEnemyOn->setPropertyV(WSNuserValue,(long)2);
  BtnPresetThisAllEnemyOn->setPropertyV(WSNlabelString,"Set All Enemy Check For This");
  BtnPresetThisAllEnemyOn->setPropertyV(WSNname,"BtnPresetThisAllEnemyOn");
  BtnPresetThisAllEnemyOn->setPropertyV(WSNvis,(WSCbool)1);
  BtnPresetThisAllEnemyOn->setPropertyV(WSNx,(short)225);
  BtnPresetThisAllEnemyOn->setPropertyV(WSNy,(short)370);
  BtnPresetThisAllEnemyOn->setPropertyV(WSNwidth,(unsigned short)205);
  BtnPresetThisAllEnemyOn->setPropertyV(WSNheight,(unsigned short)25);
    extern void BtnPresetThisAllEnemyOnDownFunc(WSCbase*);
    BtnPresetThisAllEnemyOn->addProcedureV("BtnPresetThisAllEnemyOnDown","BtnPresetThisAllEnemyOnDownFunc",BtnPresetThisAllEnemyOnDownFunc,13);

  BtnAllUncheck = new  WSCvbtn(Maiinde_012,"BtnAllUncheck");
      BtnAllUncheck->initialize();
  BtnAllUncheck->setPropertyV(WSNuserValue,(long)2);
  BtnAllUncheck->setPropertyV(WSNlabelString,"Set All Enemy Unchk For This");
  BtnAllUncheck->setPropertyV(WSNname,"BtnAllUncheck");
  BtnAllUncheck->setPropertyV(WSNvis,(WSCbool)1);
  BtnAllUncheck->setPropertyV(WSNx,(short)225);
  BtnAllUncheck->setPropertyV(WSNy,(short)395);
  BtnAllUncheck->setPropertyV(WSNwidth,(unsigned short)205);
  BtnAllUncheck->setPropertyV(WSNheight,(unsigned short)25);
    extern void BtnAllUncheckDownFunc(WSCbase*);
    BtnAllUncheck->addProcedureV("BtnAllUncheckDown","BtnAllUncheckDownFunc",BtnAllUncheckDownFunc,13);

  Maitfor_055 = new  WSCtform(Maiinde_012,"Maitfor_055");
      Maitfor_055->initialize();
  Maitfor_055->setPropertyV(WSNuserValue,(long)3);
  Maitfor_055->setPropertyV(WSNtitleString,"Ranged");
  Maitfor_055->setPropertyV(WSNname,"Maitfor_055");
  Maitfor_055->setPropertyV(WSNx,(short)260);
  Maitfor_055->setPropertyV(WSNy,(short)60);
  Maitfor_055->setPropertyV(WSNwidth,(unsigned short)245);
  Maitfor_055->setPropertyV(WSNheight,(unsigned short)255);

  RangeddzEdit = new  WSCvifield(Maitfor_055,"RangeddzEdit");
      RangeddzEdit->initialize();
  RangeddzEdit->setPropertyV(WSNuserValue,(long)3);
  RangeddzEdit->setPropertyV(WSNname,"RangeddzEdit");
  RangeddzEdit->setPropertyV(WSNvis,(WSCbool)1);
  RangeddzEdit->setPropertyV(WSNx,(short)105);
  RangeddzEdit->setPropertyV(WSNy,(short)190);
  RangeddzEdit->setPropertyV(WSNwidth,(unsigned short)80);
  RangeddzEdit->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_062 = new  WSCvlabel(Maitfor_055,"Maivlab_062");
      Maivlab_062->initialize();
  Maivlab_062->setPropertyV(WSNuserValue,(long)3);
  Maivlab_062->setPropertyV(WSNlabelString,"Type");
  Maivlab_062->setPropertyV(WSNname,"Maivlab_062");
  Maivlab_062->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_062->setPropertyV(WSNx,(short)10);
  Maivlab_062->setPropertyV(WSNy,(short)15);
  Maivlab_062->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_062->setPropertyV(WSNheight,(unsigned short)25);

  BtnRangedType = new  WSCvbtn(Maitfor_055,"BtnRangedType");
      BtnRangedType->initialize();
  BtnRangedType->setPropertyV(WSNname,"BtnRangedType");
  BtnRangedType->setPropertyV(WSNvis,(WSCbool)1);
  BtnRangedType->setPropertyV(WSNx,(short)105);
  BtnRangedType->setPropertyV(WSNy,(short)15);
  BtnRangedType->setPropertyV(WSNwidth,(unsigned short)130);
  BtnRangedType->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_065 = new  WSCvlabel(Maitfor_055,"Maivlab_065");
      Maivlab_065->initialize();
  Maivlab_065->setPropertyV(WSNuserValue,(long)3);
  Maivlab_065->setPropertyV(WSNlabelString,"Repetitions");
  Maivlab_065->setPropertyV(WSNname,"Maivlab_065");
  Maivlab_065->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_065->setPropertyV(WSNx,(short)10);
  Maivlab_065->setPropertyV(WSNy,(short)40);
  Maivlab_065->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_065->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_066 = new  WSCvlabel(Maitfor_055,"Maivlab_066");
      Maivlab_066->initialize();
  Maivlab_066->setPropertyV(WSNuserValue,(long)3);
  Maivlab_066->setPropertyV(WSNlabelString,"Error");
  Maivlab_066->setPropertyV(WSNname,"Maivlab_066");
  Maivlab_066->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_066->setPropertyV(WSNx,(short)10);
  Maivlab_066->setPropertyV(WSNy,(short)65);
  Maivlab_066->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_066->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_067 = new  WSCvlabel(Maitfor_055,"Maivlab_067");
      Maivlab_067->initialize();
  Maivlab_067->setPropertyV(WSNuserValue,(long)3);
  Maivlab_067->setPropertyV(WSNlabelString,"Range");
  Maivlab_067->setPropertyV(WSNname,"Maivlab_067");
  Maivlab_067->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_067->setPropertyV(WSNx,(short)10);
  Maivlab_067->setPropertyV(WSNy,(short)90);
  Maivlab_067->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_067->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_068 = new  WSCvlabel(Maitfor_055,"Maivlab_068");
      Maivlab_068->initialize();
  Maivlab_068->setPropertyV(WSNuserValue,(long)3);
  Maivlab_068->setPropertyV(WSNlabelString,"Sequence");
  Maivlab_068->setPropertyV(WSNname,"Maivlab_068");
  Maivlab_068->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_068->setPropertyV(WSNx,(short)10);
  Maivlab_068->setPropertyV(WSNy,(short)115);
  Maivlab_068->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_068->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_069 = new  WSCvlabel(Maitfor_055,"Maivlab_069");
      Maivlab_069->initialize();
  Maivlab_069->setPropertyV(WSNuserValue,(long)3);
  Maivlab_069->setPropertyV(WSNlabelString,"dx");
  Maivlab_069->setPropertyV(WSNname,"Maivlab_069");
  Maivlab_069->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_069->setPropertyV(WSNx,(short)10);
  Maivlab_069->setPropertyV(WSNy,(short)140);
  Maivlab_069->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_069->setPropertyV(WSNheight,(unsigned short)25);

  RangedRepetitionsEdit = new  WSCvifield(Maitfor_055,"RangedRepetitionsEdit");
      RangedRepetitionsEdit->initialize();
  RangedRepetitionsEdit->setPropertyV(WSNuserValue,(long)3);
  RangedRepetitionsEdit->setPropertyV(WSNname,"RangedRepetitionsEdit");
  RangedRepetitionsEdit->setPropertyV(WSNvis,(WSCbool)1);
  RangedRepetitionsEdit->setPropertyV(WSNx,(short)105);
  RangedRepetitionsEdit->setPropertyV(WSNy,(short)40);
  RangedRepetitionsEdit->setPropertyV(WSNwidth,(unsigned short)80);
  RangedRepetitionsEdit->setPropertyV(WSNheight,(unsigned short)25);

  RangedErrorEdit = new  WSCvifield(Maitfor_055,"RangedErrorEdit");
      RangedErrorEdit->initialize();
  RangedErrorEdit->setPropertyV(WSNuserValue,(long)3);
  RangedErrorEdit->setPropertyV(WSNname,"RangedErrorEdit");
  RangedErrorEdit->setPropertyV(WSNvis,(WSCbool)1);
  RangedErrorEdit->setPropertyV(WSNx,(short)105);
  RangedErrorEdit->setPropertyV(WSNy,(short)65);
  RangedErrorEdit->setPropertyV(WSNwidth,(unsigned short)80);
  RangedErrorEdit->setPropertyV(WSNheight,(unsigned short)25);

  RangedRangeEdit = new  WSCvifield(Maitfor_055,"RangedRangeEdit");
      RangedRangeEdit->initialize();
  RangedRangeEdit->setPropertyV(WSNuserValue,(long)3);
  RangedRangeEdit->setPropertyV(WSNname,"RangedRangeEdit");
  RangedRangeEdit->setPropertyV(WSNvis,(WSCbool)1);
  RangedRangeEdit->setPropertyV(WSNx,(short)105);
  RangedRangeEdit->setPropertyV(WSNy,(short)90);
  RangedRangeEdit->setPropertyV(WSNwidth,(unsigned short)80);
  RangedRangeEdit->setPropertyV(WSNheight,(unsigned short)25);

  RangedSequenceEdit = new  WSCvifield(Maitfor_055,"RangedSequenceEdit");
      RangedSequenceEdit->initialize();
  RangedSequenceEdit->setPropertyV(WSNuserValue,(long)3);
  RangedSequenceEdit->setPropertyV(WSNname,"RangedSequenceEdit");
  RangedSequenceEdit->setPropertyV(WSNvis,(WSCbool)1);
  RangedSequenceEdit->setPropertyV(WSNx,(short)105);
  RangedSequenceEdit->setPropertyV(WSNy,(short)115);
  RangedSequenceEdit->setPropertyV(WSNwidth,(unsigned short)80);
  RangedSequenceEdit->setPropertyV(WSNheight,(unsigned short)25);

  RangeddxEdit = new  WSCvifield(Maitfor_055,"RangeddxEdit");
      RangeddxEdit->initialize();
  RangeddxEdit->setPropertyV(WSNuserValue,(long)3);
  RangeddxEdit->setPropertyV(WSNname,"RangeddxEdit");
  RangeddxEdit->setPropertyV(WSNvis,(WSCbool)1);
  RangeddxEdit->setPropertyV(WSNx,(short)105);
  RangeddxEdit->setPropertyV(WSNy,(short)140);
  RangeddxEdit->setPropertyV(WSNwidth,(unsigned short)80);
  RangeddxEdit->setPropertyV(WSNheight,(unsigned short)25);

  RangeddyEdit = new  WSCvifield(Maitfor_055,"RangeddyEdit");
      RangeddyEdit->initialize();
  RangeddyEdit->setPropertyV(WSNuserValue,(long)3);
  RangeddyEdit->setPropertyV(WSNname,"RangeddyEdit");
  RangeddyEdit->setPropertyV(WSNvis,(WSCbool)1);
  RangeddyEdit->setPropertyV(WSNx,(short)105);
  RangeddyEdit->setPropertyV(WSNy,(short)165);
  RangeddyEdit->setPropertyV(WSNwidth,(unsigned short)80);
  RangeddyEdit->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_082 = new  WSCvlabel(Maitfor_055,"Maivlab_082");
      Maivlab_082->initialize();
  Maivlab_082->setPropertyV(WSNuserValue,(long)3);
  Maivlab_082->setPropertyV(WSNlabelString,"dy");
  Maivlab_082->setPropertyV(WSNname,"Maivlab_082");
  Maivlab_082->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_082->setPropertyV(WSNx,(short)10);
  Maivlab_082->setPropertyV(WSNy,(short)165);
  Maivlab_082->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_082->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_083 = new  WSCvlabel(Maitfor_055,"Maivlab_083");
      Maivlab_083->initialize();
  Maivlab_083->setPropertyV(WSNuserValue,(long)3);
  Maivlab_083->setPropertyV(WSNlabelString,"dz");
  Maivlab_083->setPropertyV(WSNname,"Maivlab_083");
  Maivlab_083->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_083->setPropertyV(WSNx,(short)10);
  Maivlab_083->setPropertyV(WSNy,(short)190);
  Maivlab_083->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_083->setPropertyV(WSNheight,(unsigned short)25);

  BtnRangedPreset = new  WSCvbtn(Maitfor_055,"BtnRangedPreset");
      BtnRangedPreset->initialize();
  BtnRangedPreset->setPropertyV(WSNlabelString,"Preset From Other Monster");
  BtnRangedPreset->setPropertyV(WSNname,"BtnRangedPreset");
  BtnRangedPreset->setPropertyV(WSNvis,(WSCbool)1);
  BtnRangedPreset->setPropertyV(WSNx,(short)10);
  BtnRangedPreset->setPropertyV(WSNy,(short)220);
  BtnRangedPreset->setPropertyV(WSNwidth,(unsigned short)225);
    extern void BtnRangedPresetDownFunc(WSCbase*);
    BtnRangedPreset->addProcedureV("BtnRangedPresetDown","BtnRangedPresetDownFunc",BtnRangedPresetDownFunc,13);

  WndSelect = new  WSCdialog(MainWindow,"WndSelect");
      WndSelect->initialize();
  WndSelect->setPropertyV(WSNname,"WndSelect");
  WndSelect->setPropertyV(WSNtitleString,"SelectIt!");
  WndSelect->setPropertyV(WSNx,(short)47);
  WndSelect->setPropertyV(WSNy,(short)374);
  WndSelect->setPropertyV(WSNwidth,(unsigned short)290);
  WndSelect->setPropertyV(WSNheight,(unsigned short)425);
    extern void WndSelectActivateFunc(WSCbase*);
    WndSelect->addProcedureV("WndSelectActivate","WndSelectActivateFunc",WndSelectActivateFunc,2);

  ListSelect = new  WSClist(WndSelect,"ListSelect");
      ListSelect->initialize();
  ListSelect->setPropertyV(WSNtitleString,"title4");
  ListSelect->setPropertyV(WSNworkHeight,(unsigned short)10);
  ListSelect->setPropertyV(WSNhbarVisible,(WSCbool)1);
  ListSelect->setPropertyV(WSNname,"ListSelect");
  ListSelect->setPropertyV(WSNx,(short)0);
  ListSelect->setPropertyV(WSNy,(short)0);
  ListSelect->setPropertyV(WSNwidth,(unsigned short)285);
  ListSelect->setPropertyV(WSNheight,(unsigned short)465);
  ListSelect->setPropertyV(WSNvis,(WSCbool)1);
    extern void ListSelectSelectFunc(WSCbase*);
    ListSelect->addProcedureV("ListSelectSelect","ListSelectSelectFunc",ListSelectSelectFunc,35);

  FrmEffect = new  WSCform(MainWindow,"FrmEffect");
      FrmEffect->initialize();
  FrmEffect->setPropertyV(WSNname,"FrmEffect");
  FrmEffect->setPropertyV(WSNx,(short)95);
  FrmEffect->setPropertyV(WSNy,(short)25);
  FrmEffect->setPropertyV(WSNwidth,(unsigned short)690);
  FrmEffect->setPropertyV(WSNheight,(unsigned short)470);

  ListEffect = new  WSClist(FrmEffect,"ListEffect");
      ListEffect->initialize();
  ListEffect->setPropertyV(WSNitemHeight,(unsigned char)11);
  ListEffect->setPropertyV(WSNtitleString,"title3");
  ListEffect->setPropertyV(WSNdataSource,(unsigned char)2);
  ListEffect->setPropertyV(WSNdataSourceName,"data/Effects.txt");
  ListEffect->setPropertyV(WSNworkWidth,(unsigned short)200);
  ListEffect->setPropertyV(WSNworkHeight,(unsigned short)803);
  ListEffect->setPropertyV(WSNhbarVisible,(WSCbool)1);
  ListEffect->setPropertyV(WSNname,"ListEffect");
  ListEffect->setPropertyV(WSNx,(short)5);
  ListEffect->setPropertyV(WSNy,(short)5);
  ListEffect->setPropertyV(WSNwidth,(unsigned short)145);
  ListEffect->setPropertyV(WSNheight,(unsigned short)460);
  ListEffect->setPropertyV(WSNvis,(WSCbool)1);
    extern void ListEffectDownFunc(WSCbase*);
    ListEffect->addProcedureV("ListEffectDown","ListEffectDownFunc",ListEffectDownFunc,35);

  BtnEffectCollection = new  WSCvbtn(FrmEffect,"BtnEffectCollection");
      BtnEffectCollection->initialize();
  BtnEffectCollection->setPropertyV(WSNname,"BtnEffectCollection");
  BtnEffectCollection->setPropertyV(WSNvis,(WSCbool)1);
  BtnEffectCollection->setPropertyV(WSNx,(short)245);
  BtnEffectCollection->setPropertyV(WSNy,(short)10);
  BtnEffectCollection->setPropertyV(WSNwidth,(unsigned short)165);
  BtnEffectCollection->setPropertyV(WSNheight,(unsigned short)25);
    extern void BtnEffectCollectionDownFunc(WSCbase*);
    BtnEffectCollection->addProcedureV("BtnEffectCollectionDown","BtnEffectCollectionDownFunc",BtnEffectCollectionDownFunc,13);

  Maivlab_093 = new  WSCvlabel(FrmEffect,"Maivlab_093");
      Maivlab_093->initialize();
  Maivlab_093->setPropertyV(WSNlabelString,"Collection");
  Maivlab_093->setPropertyV(WSNname,"Maivlab_093");
  Maivlab_093->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_093->setPropertyV(WSNx,(short)150);
  Maivlab_093->setPropertyV(WSNy,(short)10);
  Maivlab_093->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_093->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_094 = new  WSCvlabel(FrmEffect,"Maivlab_094");
      Maivlab_094->initialize();
  Maivlab_094->setPropertyV(WSNlabelString,"Sequence");
  Maivlab_094->setPropertyV(WSNname,"Maivlab_094");
  Maivlab_094->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_094->setPropertyV(WSNx,(short)150);
  Maivlab_094->setPropertyV(WSNy,(short)35);
  Maivlab_094->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_094->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_095 = new  WSCvlabel(FrmEffect,"Maivlab_095");
      Maivlab_095->initialize();
  Maivlab_095->setPropertyV(WSNlabelString,"Sound Pitch");
  Maivlab_095->setPropertyV(WSNname,"Maivlab_095");
  Maivlab_095->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_095->setPropertyV(WSNx,(short)150);
  Maivlab_095->setPropertyV(WSNy,(short)60);
  Maivlab_095->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_095->setPropertyV(WSNheight,(unsigned short)25);

  EffectFlagsCheckGroup = new  WSCcheckGroup(FrmEffect,"EffectFlagsCheckGroup");
      EffectFlagsCheckGroup->initialize();
  EffectFlagsCheckGroup->setPropertyV(WSNmenuItems,"End When Animation Loops,End When Transfer Animation Loops,Sound Only, Make Twin Visible,Media Effect");
  EffectFlagsCheckGroup->setPropertyV(WSNtitleString,"Flags");
  EffectFlagsCheckGroup->setPropertyV(WSNname,"EffectFlagsCheckGroup");
  EffectFlagsCheckGroup->setPropertyV(WSNx,(short)150);
  EffectFlagsCheckGroup->setPropertyV(WSNy,(short)145);
  EffectFlagsCheckGroup->setPropertyV(WSNwidth,(unsigned short)235);
  EffectFlagsCheckGroup->setPropertyV(WSNheight,(unsigned short)165);
  EffectFlagsCheckGroup->setPropertyV(WSNvis,(WSCbool)1);

  Maivlab_097 = new  WSCvlabel(FrmEffect,"Maivlab_097");
      Maivlab_097->initialize();
  Maivlab_097->setPropertyV(WSNlabelString,"Delay");
  Maivlab_097->setPropertyV(WSNname,"Maivlab_097");
  Maivlab_097->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_097->setPropertyV(WSNx,(short)150);
  Maivlab_097->setPropertyV(WSNy,(short)85);
  Maivlab_097->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_097->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_099 = new  WSCvlabel(FrmEffect,"Maivlab_099");
      Maivlab_099->initialize();
  Maivlab_099->setPropertyV(WSNlabelString,"Delay Sound");
  Maivlab_099->setPropertyV(WSNname,"Maivlab_099");
  Maivlab_099->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_099->setPropertyV(WSNx,(short)150);
  Maivlab_099->setPropertyV(WSNy,(short)110);
  Maivlab_099->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_099->setPropertyV(WSNheight,(unsigned short)25);

  BtnEffectDelaySound = new  WSCvbtn(FrmEffect,"BtnEffectDelaySound");
      BtnEffectDelaySound->initialize();
  BtnEffectDelaySound->setPropertyV(WSNname,"BtnEffectDelaySound");
  BtnEffectDelaySound->setPropertyV(WSNvis,(WSCbool)1);
  BtnEffectDelaySound->setPropertyV(WSNx,(short)245);
  BtnEffectDelaySound->setPropertyV(WSNy,(short)110);
  BtnEffectDelaySound->setPropertyV(WSNwidth,(unsigned short)165);
  BtnEffectDelaySound->setPropertyV(WSNheight,(unsigned short)25);
    extern void BtnEffectDelaySoundDownFunc(WSCbase*);
    BtnEffectDelaySound->addProcedureV("BtnEffectDelaySoundDown","BtnEffectDelaySoundDownFunc",BtnEffectDelaySoundDownFunc,13);

  EffectSoundPitchEdit = new  WSCvifield(FrmEffect,"EffectSoundPitchEdit");
      EffectSoundPitchEdit->initialize();
  EffectSoundPitchEdit->setPropertyV(WSNname,"EffectSoundPitchEdit");
  EffectSoundPitchEdit->setPropertyV(WSNvis,(WSCbool)1);
  EffectSoundPitchEdit->setPropertyV(WSNx,(short)245);
  EffectSoundPitchEdit->setPropertyV(WSNy,(short)60);
  EffectSoundPitchEdit->setPropertyV(WSNwidth,(unsigned short)95);
  EffectSoundPitchEdit->setPropertyV(WSNheight,(unsigned short)25);

  EffectDelayEdit = new  WSCvifield(FrmEffect,"EffectDelayEdit");
      EffectDelayEdit->initialize();
  EffectDelayEdit->setPropertyV(WSNname,"EffectDelayEdit");
  EffectDelayEdit->setPropertyV(WSNvis,(WSCbool)1);
  EffectDelayEdit->setPropertyV(WSNx,(short)245);
  EffectDelayEdit->setPropertyV(WSNy,(short)85);
  EffectDelayEdit->setPropertyV(WSNwidth,(unsigned short)95);
  EffectDelayEdit->setPropertyV(WSNheight,(unsigned short)25);

  EffectSequenceEdit = new  WSCvifield(FrmEffect,"EffectSequenceEdit");
      EffectSequenceEdit->initialize();
  EffectSequenceEdit->setPropertyV(WSNname,"EffectSequenceEdit");
  EffectSequenceEdit->setPropertyV(WSNvis,(WSCbool)1);
  EffectSequenceEdit->setPropertyV(WSNx,(short)245);
  EffectSequenceEdit->setPropertyV(WSNy,(short)35);
  EffectSequenceEdit->setPropertyV(WSNwidth,(unsigned short)95);
  EffectSequenceEdit->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_104 = new  WSCvlabel(FrmEffect,"Maivlab_104");
      Maivlab_104->initialize();
  Maivlab_104->setPropertyV(WSNlabelString,"Pallet");
  Maivlab_104->setPropertyV(WSNname,"Maivlab_104");
  Maivlab_104->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_104->setPropertyV(WSNx,(short)420);
  Maivlab_104->setPropertyV(WSNy,(short)10);
  Maivlab_104->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_104->setPropertyV(WSNheight,(unsigned short)25);

  EffectPalletEdit = new  WSCvifield(FrmEffect,"EffectPalletEdit");
      EffectPalletEdit->initialize();
  EffectPalletEdit->setPropertyV(WSNname,"EffectPalletEdit");
  EffectPalletEdit->setPropertyV(WSNvis,(WSCbool)1);
  EffectPalletEdit->setPropertyV(WSNx,(short)515);
  EffectPalletEdit->setPropertyV(WSNy,(short)10);
  EffectPalletEdit->setPropertyV(WSNwidth,(unsigned short)95);
  EffectPalletEdit->setPropertyV(WSNheight,(unsigned short)25);

  FrmProjectile = new  WSCform(MainWindow,"FrmProjectile");
      FrmProjectile->initialize();
  FrmProjectile->setPropertyV(WSNname,"FrmProjectile");
  FrmProjectile->setPropertyV(WSNx,(short)95);
  FrmProjectile->setPropertyV(WSNy,(short)25);
  FrmProjectile->setPropertyV(WSNwidth,(unsigned short)690);
  FrmProjectile->setPropertyV(WSNheight,(unsigned short)470);

  ListProjectile = new  WSClist(FrmProjectile,"ListProjectile");
      ListProjectile->initialize();
  ListProjectile->setPropertyV(WSNitemHeight,(unsigned char)11);
  ListProjectile->setPropertyV(WSNtitleString,"title6");
  ListProjectile->setPropertyV(WSNdataSource,(unsigned char)2);
  ListProjectile->setPropertyV(WSNdataSourceName,"data/Projectiles.txt");
  ListProjectile->setPropertyV(WSNworkWidth,(unsigned short)200);
  ListProjectile->setPropertyV(WSNworkHeight,(unsigned short)456);
  ListProjectile->setPropertyV(WSNname,"ListProjectile");
  ListProjectile->setPropertyV(WSNx,(short)5);
  ListProjectile->setPropertyV(WSNy,(short)5);
  ListProjectile->setPropertyV(WSNwidth,(unsigned short)95);
  ListProjectile->setPropertyV(WSNheight,(unsigned short)460);
  ListProjectile->setPropertyV(WSNvis,(WSCbool)1);
    extern void ListProjectileDownFunc(WSCbase*);
    ListProjectile->addProcedureV("ListProjectileDown","ListProjectileDownFunc",ListProjectileDownFunc,35);

  Maivlab_109 = new  WSCvlabel(FrmProjectile,"Maivlab_109");
      Maivlab_109->initialize();
  Maivlab_109->setPropertyV(WSNlabelString,"Collection");
  Maivlab_109->setPropertyV(WSNname,"Maivlab_109");
  Maivlab_109->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_109->setPropertyV(WSNx,(short)105);
  Maivlab_109->setPropertyV(WSNy,(short)10);
  Maivlab_109->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_109->setPropertyV(WSNheight,(unsigned short)20);

  ProjPalletEdit = new  WSCvifield(FrmProjectile,"ProjPalletEdit");
      ProjPalletEdit->initialize();
  ProjPalletEdit->setPropertyV(WSNname,"ProjPalletEdit");
  ProjPalletEdit->setPropertyV(WSNvis,(WSCbool)1);
  ProjPalletEdit->setPropertyV(WSNx,(short)200);
  ProjPalletEdit->setPropertyV(WSNy,(short)30);
  ProjPalletEdit->setPropertyV(WSNwidth,(unsigned short)110);
  ProjPalletEdit->setPropertyV(WSNheight,(unsigned short)20);

  ProjCollectionBtn = new  WSCvbtn(FrmProjectile,"ProjCollectionBtn");
      ProjCollectionBtn->initialize();
  ProjCollectionBtn->setPropertyV(WSNname,"ProjCollectionBtn");
  ProjCollectionBtn->setPropertyV(WSNvis,(WSCbool)1);
  ProjCollectionBtn->setPropertyV(WSNx,(short)200);
  ProjCollectionBtn->setPropertyV(WSNy,(short)10);
  ProjCollectionBtn->setPropertyV(WSNwidth,(unsigned short)110);
  ProjCollectionBtn->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_112 = new  WSCvlabel(FrmProjectile,"Maivlab_112");
      Maivlab_112->initialize();
  Maivlab_112->setPropertyV(WSNlabelString,"Pallet");
  Maivlab_112->setPropertyV(WSNname,"Maivlab_112");
  Maivlab_112->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_112->setPropertyV(WSNx,(short)105);
  Maivlab_112->setPropertyV(WSNy,(short)30);
  Maivlab_112->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_112->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_113 = new  WSCvlabel(FrmProjectile,"Maivlab_113");
      Maivlab_113->initialize();
  Maivlab_113->setPropertyV(WSNlabelString,"ContrailEf");
  Maivlab_113->setPropertyV(WSNname,"Maivlab_113");
  Maivlab_113->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_113->setPropertyV(WSNx,(short)105);
  Maivlab_113->setPropertyV(WSNy,(short)110);
  Maivlab_113->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_113->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_114 = new  WSCvlabel(FrmProjectile,"Maivlab_114");
      Maivlab_114->initialize();
  Maivlab_114->setPropertyV(WSNlabelString,"DetonationEf");
  Maivlab_114->setPropertyV(WSNname,"Maivlab_114");
  Maivlab_114->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_114->setPropertyV(WSNx,(short)105);
  Maivlab_114->setPropertyV(WSNy,(short)70);
  Maivlab_114->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_114->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_115 = new  WSCvlabel(FrmProjectile,"Maivlab_115");
      Maivlab_115->initialize();
  Maivlab_115->setPropertyV(WSNlabelString,"Det(media)Ef");
  Maivlab_115->setPropertyV(WSNname,"Maivlab_115");
  Maivlab_115->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_115->setPropertyV(WSNx,(short)105);
  Maivlab_115->setPropertyV(WSNy,(short)90);
  Maivlab_115->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_115->setPropertyV(WSNheight,(unsigned short)20);

  ProjContrailEfBtn = new  WSCvbtn(FrmProjectile,"ProjContrailEfBtn");
      ProjContrailEfBtn->initialize();
  ProjContrailEfBtn->setPropertyV(WSNname,"ProjContrailEfBtn");
  ProjContrailEfBtn->setPropertyV(WSNvis,(WSCbool)1);
  ProjContrailEfBtn->setPropertyV(WSNx,(short)200);
  ProjContrailEfBtn->setPropertyV(WSNy,(short)110);
  ProjContrailEfBtn->setPropertyV(WSNwidth,(unsigned short)110);
  ProjContrailEfBtn->setPropertyV(WSNheight,(unsigned short)20);

  ProjDetonationEfBtn = new  WSCvbtn(FrmProjectile,"ProjDetonationEfBtn");
      ProjDetonationEfBtn->initialize();
  ProjDetonationEfBtn->setPropertyV(WSNname,"ProjDetonationEfBtn");
  ProjDetonationEfBtn->setPropertyV(WSNvis,(WSCbool)1);
  ProjDetonationEfBtn->setPropertyV(WSNx,(short)200);
  ProjDetonationEfBtn->setPropertyV(WSNy,(short)70);
  ProjDetonationEfBtn->setPropertyV(WSNwidth,(unsigned short)110);
  ProjDetonationEfBtn->setPropertyV(WSNheight,(unsigned short)20);

  ProjDetMediaEfBtn = new  WSCvbtn(FrmProjectile,"ProjDetMediaEfBtn");
      ProjDetMediaEfBtn->initialize();
  ProjDetMediaEfBtn->setPropertyV(WSNname,"ProjDetMediaEfBtn");
  ProjDetMediaEfBtn->setPropertyV(WSNvis,(WSCbool)1);
  ProjDetMediaEfBtn->setPropertyV(WSNx,(short)200);
  ProjDetMediaEfBtn->setPropertyV(WSNy,(short)90);
  ProjDetMediaEfBtn->setPropertyV(WSNwidth,(unsigned short)110);
  ProjDetMediaEfBtn->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_119 = new  WSCvlabel(FrmProjectile,"Maivlab_119");
      Maivlab_119->initialize();
  Maivlab_119->setPropertyV(WSNlabelString,"AreaOfEf");
  Maivlab_119->setPropertyV(WSNname,"Maivlab_119");
  Maivlab_119->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_119->setPropertyV(WSNx,(short)105);
  Maivlab_119->setPropertyV(WSNy,(short)210);
  Maivlab_119->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_119->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_120 = new  WSCvlabel(FrmProjectile,"Maivlab_120");
      Maivlab_120->initialize();
  Maivlab_120->setPropertyV(WSNlabelString,"TicksBetContrail");
  Maivlab_120->setPropertyV(WSNname,"Maivlab_120");
  Maivlab_120->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_120->setPropertyV(WSNx,(short)105);
  Maivlab_120->setPropertyV(WSNy,(short)130);
  Maivlab_120->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_120->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_121 = new  WSCvlabel(FrmProjectile,"Maivlab_121");
      Maivlab_121->initialize();
  Maivlab_121->setPropertyV(WSNlabelString,"MaxContrail");
  Maivlab_121->setPropertyV(WSNname,"Maivlab_121");
  Maivlab_121->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_121->setPropertyV(WSNx,(short)105);
  Maivlab_121->setPropertyV(WSNy,(short)150);
  Maivlab_121->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_121->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_122 = new  WSCvlabel(FrmProjectile,"Maivlab_122");
      Maivlab_122->initialize();
  Maivlab_122->setPropertyV(WSNlabelString,"MediaPromo");
  Maivlab_122->setPropertyV(WSNname,"Maivlab_122");
  Maivlab_122->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_122->setPropertyV(WSNx,(short)105);
  Maivlab_122->setPropertyV(WSNy,(short)170);
  Maivlab_122->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_122->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_123 = new  WSCvlabel(FrmProjectile,"Maivlab_123");
      Maivlab_123->initialize();
  Maivlab_123->setPropertyV(WSNlabelString,"Radius");
  Maivlab_123->setPropertyV(WSNname,"Maivlab_123");
  Maivlab_123->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_123->setPropertyV(WSNx,(short)105);
  Maivlab_123->setPropertyV(WSNy,(short)190);
  Maivlab_123->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_123->setPropertyV(WSNheight,(unsigned short)20);

  ProjAreaOfEfEdit = new  WSCvifield(FrmProjectile,"ProjAreaOfEfEdit");
      ProjAreaOfEfEdit->initialize();
  ProjAreaOfEfEdit->setPropertyV(WSNname,"ProjAreaOfEfEdit");
  ProjAreaOfEfEdit->setPropertyV(WSNvis,(WSCbool)1);
  ProjAreaOfEfEdit->setPropertyV(WSNx,(short)200);
  ProjAreaOfEfEdit->setPropertyV(WSNy,(short)210);
  ProjAreaOfEfEdit->setPropertyV(WSNwidth,(unsigned short)110);
  ProjAreaOfEfEdit->setPropertyV(WSNheight,(unsigned short)20);

  ProjTicksBetContrailEdit = new  WSCvifield(FrmProjectile,"ProjTicksBetContrailEdit");
      ProjTicksBetContrailEdit->initialize();
  ProjTicksBetContrailEdit->setPropertyV(WSNname,"ProjTicksBetContrailEdit");
  ProjTicksBetContrailEdit->setPropertyV(WSNvis,(WSCbool)1);
  ProjTicksBetContrailEdit->setPropertyV(WSNx,(short)200);
  ProjTicksBetContrailEdit->setPropertyV(WSNy,(short)130);
  ProjTicksBetContrailEdit->setPropertyV(WSNwidth,(unsigned short)110);
  ProjTicksBetContrailEdit->setPropertyV(WSNheight,(unsigned short)20);

  ProjMaxContrailEdit = new  WSCvifield(FrmProjectile,"ProjMaxContrailEdit");
      ProjMaxContrailEdit->initialize();
  ProjMaxContrailEdit->setPropertyV(WSNname,"ProjMaxContrailEdit");
  ProjMaxContrailEdit->setPropertyV(WSNvis,(WSCbool)1);
  ProjMaxContrailEdit->setPropertyV(WSNx,(short)200);
  ProjMaxContrailEdit->setPropertyV(WSNy,(short)150);
  ProjMaxContrailEdit->setPropertyV(WSNwidth,(unsigned short)110);
  ProjMaxContrailEdit->setPropertyV(WSNheight,(unsigned short)20);

  ProjMediaPromoEdit = new  WSCvifield(FrmProjectile,"ProjMediaPromoEdit");
      ProjMediaPromoEdit->initialize();
  ProjMediaPromoEdit->setPropertyV(WSNname,"ProjMediaPromoEdit");
  ProjMediaPromoEdit->setPropertyV(WSNvis,(WSCbool)1);
  ProjMediaPromoEdit->setPropertyV(WSNx,(short)200);
  ProjMediaPromoEdit->setPropertyV(WSNy,(short)170);
  ProjMediaPromoEdit->setPropertyV(WSNwidth,(unsigned short)110);
  ProjMediaPromoEdit->setPropertyV(WSNheight,(unsigned short)20);

  ProjRadiusEdit = new  WSCvifield(FrmProjectile,"ProjRadiusEdit");
      ProjRadiusEdit->initialize();
  ProjRadiusEdit->setPropertyV(WSNname,"ProjRadiusEdit");
  ProjRadiusEdit->setPropertyV(WSNvis,(WSCbool)1);
  ProjRadiusEdit->setPropertyV(WSNx,(short)200);
  ProjRadiusEdit->setPropertyV(WSNy,(short)190);
  ProjRadiusEdit->setPropertyV(WSNwidth,(unsigned short)110);
  ProjRadiusEdit->setPropertyV(WSNheight,(unsigned short)20);

  Maitfor_129 = new  WSCtform(FrmProjectile,"Maitfor_129");
      Maitfor_129->initialize();
  Maitfor_129->setPropertyV(WSNtitleString,"Damage");
  Maitfor_129->setPropertyV(WSNname,"Maitfor_129");
  Maitfor_129->setPropertyV(WSNx,(short)105);
  Maitfor_129->setPropertyV(WSNy,(short)235);
  Maitfor_129->setPropertyV(WSNwidth,(unsigned short)210);
  Maitfor_129->setPropertyV(WSNheight,(unsigned short)135);
  Maitfor_129->setPropertyV(WSNvis,(WSCbool)1);

  Maivlab_130 = new  WSCvlabel(Maitfor_129,"Maivlab_130");
      Maivlab_130->initialize();
  Maivlab_130->setPropertyV(WSNlabelString,"Type");
  Maivlab_130->setPropertyV(WSNname,"Maivlab_130");
  Maivlab_130->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_130->setPropertyV(WSNx,(short)15);
  Maivlab_130->setPropertyV(WSNy,(short)20);
  Maivlab_130->setPropertyV(WSNwidth,(unsigned short)80);
  Maivlab_130->setPropertyV(WSNheight,(unsigned short)20);

  ProjDamageTypeBtn = new  WSCvbtn(Maitfor_129,"ProjDamageTypeBtn");
      ProjDamageTypeBtn->initialize();
  ProjDamageTypeBtn->setPropertyV(WSNname,"ProjDamageTypeBtn");
  ProjDamageTypeBtn->setPropertyV(WSNvis,(WSCbool)1);
  ProjDamageTypeBtn->setPropertyV(WSNx,(short)95);
  ProjDamageTypeBtn->setPropertyV(WSNy,(short)20);
  ProjDamageTypeBtn->setPropertyV(WSNwidth,(unsigned short)110);
  ProjDamageTypeBtn->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_132 = new  WSCvlabel(Maitfor_129,"Maivlab_132");
      Maivlab_132->initialize();
  Maivlab_132->setPropertyV(WSNlabelString,"Base");
  Maivlab_132->setPropertyV(WSNname,"Maivlab_132");
  Maivlab_132->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_132->setPropertyV(WSNx,(short)15);
  Maivlab_132->setPropertyV(WSNy,(short)40);
  Maivlab_132->setPropertyV(WSNwidth,(unsigned short)80);
  Maivlab_132->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_133 = new  WSCvlabel(Maitfor_129,"Maivlab_133");
      Maivlab_133->initialize();
  Maivlab_133->setPropertyV(WSNlabelString,"Random");
  Maivlab_133->setPropertyV(WSNname,"Maivlab_133");
  Maivlab_133->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_133->setPropertyV(WSNx,(short)15);
  Maivlab_133->setPropertyV(WSNy,(short)60);
  Maivlab_133->setPropertyV(WSNwidth,(unsigned short)80);
  Maivlab_133->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_134 = new  WSCvlabel(Maitfor_129,"Maivlab_134");
      Maivlab_134->initialize();
  Maivlab_134->setPropertyV(WSNlabelString,"Scale");
  Maivlab_134->setPropertyV(WSNname,"Maivlab_134");
  Maivlab_134->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_134->setPropertyV(WSNx,(short)15);
  Maivlab_134->setPropertyV(WSNy,(short)80);
  Maivlab_134->setPropertyV(WSNwidth,(unsigned short)80);
  Maivlab_134->setPropertyV(WSNheight,(unsigned short)20);

  ProjDamageFlags = new  WSCvradio(Maitfor_129,"ProjDamageFlags");
      ProjDamageFlags->initialize();
  ProjDamageFlags->setPropertyV(WSNlabelString,"Alien");
  ProjDamageFlags->setPropertyV(WSNname,"ProjDamageFlags");
  ProjDamageFlags->setPropertyV(WSNvis,(WSCbool)1);
  ProjDamageFlags->setPropertyV(WSNx,(short)15);
  ProjDamageFlags->setPropertyV(WSNy,(short)105);
  ProjDamageFlags->setPropertyV(WSNwidth,(unsigned short)80);
  ProjDamageFlags->setPropertyV(WSNheight,(unsigned short)20);

  ProjDamageBaseEdit = new  WSCvifield(Maitfor_129,"ProjDamageBaseEdit");
      ProjDamageBaseEdit->initialize();
  ProjDamageBaseEdit->setPropertyV(WSNname,"ProjDamageBaseEdit");
  ProjDamageBaseEdit->setPropertyV(WSNvis,(WSCbool)1);
  ProjDamageBaseEdit->setPropertyV(WSNx,(short)95);
  ProjDamageBaseEdit->setPropertyV(WSNy,(short)40);
  ProjDamageBaseEdit->setPropertyV(WSNwidth,(unsigned short)110);
  ProjDamageBaseEdit->setPropertyV(WSNheight,(unsigned short)20);

  ProjDamageRandomEdit = new  WSCvifield(Maitfor_129,"ProjDamageRandomEdit");
      ProjDamageRandomEdit->initialize();
  ProjDamageRandomEdit->setPropertyV(WSNname,"ProjDamageRandomEdit");
  ProjDamageRandomEdit->setPropertyV(WSNvis,(WSCbool)1);
  ProjDamageRandomEdit->setPropertyV(WSNx,(short)95);
  ProjDamageRandomEdit->setPropertyV(WSNy,(short)60);
  ProjDamageRandomEdit->setPropertyV(WSNwidth,(unsigned short)110);
  ProjDamageRandomEdit->setPropertyV(WSNheight,(unsigned short)20);

  ProjDamageScaleEdit = new  WSCvifield(Maitfor_129,"ProjDamageScaleEdit");
      ProjDamageScaleEdit->initialize();
  ProjDamageScaleEdit->setPropertyV(WSNname,"ProjDamageScaleEdit");
  ProjDamageScaleEdit->setPropertyV(WSNvis,(WSCbool)1);
  ProjDamageScaleEdit->setPropertyV(WSNx,(short)95);
  ProjDamageScaleEdit->setPropertyV(WSNy,(short)80);
  ProjDamageScaleEdit->setPropertyV(WSNwidth,(unsigned short)110);
  ProjDamageScaleEdit->setPropertyV(WSNheight,(unsigned short)20);

  ListProjFlags = new  WSCcheckGroup(FrmProjectile,"ListProjFlags");
      ListProjFlags->initialize();
  ListProjFlags->setPropertyV(WSNtitleString,"Flags");
  ListProjFlags->setPropertyV(WSNmenuItemHeight,(unsigned short)11);
  ListProjFlags->setPropertyV(WSNindicatorSize,(unsigned char)11);
  ListProjFlags->setPropertyV(WSNname,"ListProjFlags");
  ListProjFlags->setPropertyV(WSNx,(short)315);
  ListProjFlags->setPropertyV(WSNy,(short)5);
  ListProjFlags->setPropertyV(WSNwidth,(unsigned short)140);
  ListProjFlags->setPropertyV(WSNheight,(unsigned short)460);
  ListProjFlags->setPropertyV(WSNvis,(WSCbool)1);

  Maivlab_137 = new  WSCvlabel(FrmProjectile,"Maivlab_137");
      Maivlab_137->initialize();
  Maivlab_137->setPropertyV(WSNlabelString,"Speed");
  Maivlab_137->setPropertyV(WSNname,"Maivlab_137");
  Maivlab_137->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_137->setPropertyV(WSNx,(short)475);
  Maivlab_137->setPropertyV(WSNy,(short)10);
  Maivlab_137->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_137->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_138 = new  WSCvlabel(FrmProjectile,"Maivlab_138");
      Maivlab_138->initialize();
  Maivlab_138->setPropertyV(WSNlabelString,"MaxRange");
  Maivlab_138->setPropertyV(WSNname,"Maivlab_138");
  Maivlab_138->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_138->setPropertyV(WSNx,(short)475);
  Maivlab_138->setPropertyV(WSNy,(short)30);
  Maivlab_138->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_138->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_139 = new  WSCvlabel(FrmProjectile,"Maivlab_139");
      Maivlab_139->initialize();
  Maivlab_139->setPropertyV(WSNlabelString,"SoundPitch");
  Maivlab_139->setPropertyV(WSNname,"Maivlab_139");
  Maivlab_139->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_139->setPropertyV(WSNx,(short)475);
  Maivlab_139->setPropertyV(WSNy,(short)50);
  Maivlab_139->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_139->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_140 = new  WSCvlabel(FrmProjectile,"Maivlab_140");
      Maivlab_140->initialize();
  Maivlab_140->setPropertyV(WSNlabelString,"FlyBySound");
  Maivlab_140->setPropertyV(WSNname,"Maivlab_140");
  Maivlab_140->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_140->setPropertyV(WSNx,(short)475);
  Maivlab_140->setPropertyV(WSNy,(short)70);
  Maivlab_140->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_140->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_141 = new  WSCvlabel(FrmProjectile,"Maivlab_141");
      Maivlab_141->initialize();
  Maivlab_141->setPropertyV(WSNlabelString,"ReboundSnd");
  Maivlab_141->setPropertyV(WSNname,"Maivlab_141");
  Maivlab_141->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_141->setPropertyV(WSNx,(short)475);
  Maivlab_141->setPropertyV(WSNy,(short)90);
  Maivlab_141->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_141->setPropertyV(WSNheight,(unsigned short)20);

  ProjFlyBySoundBtn = new  WSCvbtn(FrmProjectile,"ProjFlyBySoundBtn");
      ProjFlyBySoundBtn->initialize();
  ProjFlyBySoundBtn->setPropertyV(WSNname,"ProjFlyBySoundBtn");
  ProjFlyBySoundBtn->setPropertyV(WSNvis,(WSCbool)1);
  ProjFlyBySoundBtn->setPropertyV(WSNx,(short)570);
  ProjFlyBySoundBtn->setPropertyV(WSNy,(short)70);
  ProjFlyBySoundBtn->setPropertyV(WSNwidth,(unsigned short)110);
  ProjFlyBySoundBtn->setPropertyV(WSNheight,(unsigned short)20);

  ProjReboundSndBtn = new  WSCvbtn(FrmProjectile,"ProjReboundSndBtn");
      ProjReboundSndBtn->initialize();
  ProjReboundSndBtn->setPropertyV(WSNname,"ProjReboundSndBtn");
  ProjReboundSndBtn->setPropertyV(WSNvis,(WSCbool)1);
  ProjReboundSndBtn->setPropertyV(WSNx,(short)570);
  ProjReboundSndBtn->setPropertyV(WSNy,(short)90);
  ProjReboundSndBtn->setPropertyV(WSNwidth,(unsigned short)110);
  ProjReboundSndBtn->setPropertyV(WSNheight,(unsigned short)20);

  ProjSpeedEdit = new  WSCvifield(FrmProjectile,"ProjSpeedEdit");
      ProjSpeedEdit->initialize();
  ProjSpeedEdit->setPropertyV(WSNname,"ProjSpeedEdit");
  ProjSpeedEdit->setPropertyV(WSNvis,(WSCbool)1);
  ProjSpeedEdit->setPropertyV(WSNx,(short)570);
  ProjSpeedEdit->setPropertyV(WSNy,(short)10);
  ProjSpeedEdit->setPropertyV(WSNwidth,(unsigned short)110);
  ProjSpeedEdit->setPropertyV(WSNheight,(unsigned short)20);

  ProjMaxRangeEdit = new  WSCvifield(FrmProjectile,"ProjMaxRangeEdit");
      ProjMaxRangeEdit->initialize();
  ProjMaxRangeEdit->setPropertyV(WSNname,"ProjMaxRangeEdit");
  ProjMaxRangeEdit->setPropertyV(WSNvis,(WSCbool)1);
  ProjMaxRangeEdit->setPropertyV(WSNx,(short)570);
  ProjMaxRangeEdit->setPropertyV(WSNy,(short)30);
  ProjMaxRangeEdit->setPropertyV(WSNwidth,(unsigned short)110);
  ProjMaxRangeEdit->setPropertyV(WSNheight,(unsigned short)20);

  ProjSoundPitchEdit = new  WSCvifield(FrmProjectile,"ProjSoundPitchEdit");
      ProjSoundPitchEdit->initialize();
  ProjSoundPitchEdit->setPropertyV(WSNname,"ProjSoundPitchEdit");
  ProjSoundPitchEdit->setPropertyV(WSNvis,(WSCbool)1);
  ProjSoundPitchEdit->setPropertyV(WSNx,(short)570);
  ProjSoundPitchEdit->setPropertyV(WSNy,(short)50);
  ProjSoundPitchEdit->setPropertyV(WSNwidth,(unsigned short)110);
  ProjSoundPitchEdit->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_147 = new  WSCvlabel(FrmProjectile,"Maivlab_147");
      Maivlab_147->initialize();
  Maivlab_147->setPropertyV(WSNlabelString,"Sequence");
  Maivlab_147->setPropertyV(WSNname,"Maivlab_147");
  Maivlab_147->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_147->setPropertyV(WSNx,(short)105);
  Maivlab_147->setPropertyV(WSNy,(short)50);
  Maivlab_147->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_147->setPropertyV(WSNheight,(unsigned short)20);

  ProjSequenceEdit = new  WSCvifield(FrmProjectile,"ProjSequenceEdit");
      ProjSequenceEdit->initialize();
  ProjSequenceEdit->setPropertyV(WSNname,"ProjSequenceEdit");
  ProjSequenceEdit->setPropertyV(WSNvis,(WSCbool)1);
  ProjSequenceEdit->setPropertyV(WSNx,(short)200);
  ProjSequenceEdit->setPropertyV(WSNy,(short)50);
  ProjSequenceEdit->setPropertyV(WSNwidth,(unsigned short)110);
  ProjSequenceEdit->setPropertyV(WSNheight,(unsigned short)20);

  ProjPresetOtherProj = new  WSCvbtn(FrmProjectile,"ProjPresetOtherProj");
      ProjPresetOtherProj->initialize();
  ProjPresetOtherProj->setPropertyV(WSNlabelString,"Set As Preset Other Proj");
  ProjPresetOtherProj->setPropertyV(WSNname,"ProjPresetOtherProj");
  ProjPresetOtherProj->setPropertyV(WSNvis,(WSCbool)1);
  ProjPresetOtherProj->setPropertyV(WSNx,(short)465);
  ProjPresetOtherProj->setPropertyV(WSNy,(short)345);
  ProjPresetOtherProj->setPropertyV(WSNwidth,(unsigned short)180);
  ProjPresetOtherProj->setPropertyV(WSNheight,(unsigned short)20);

  Maivbtn_153 = new  WSCvbtn(FrmProjectile,"Maivbtn_153");
      Maivbtn_153->initialize();
  Maivbtn_153->setPropertyV(WSNlabelString,"Set As Hand Granade");
  Maivbtn_153->setPropertyV(WSNname,"Maivbtn_153");
  Maivbtn_153->setPropertyV(WSNvis,(WSCbool)1);
  Maivbtn_153->setPropertyV(WSNx,(short)465);
  Maivbtn_153->setPropertyV(WSNy,(short)365);
  Maivbtn_153->setPropertyV(WSNwidth,(unsigned short)180);
  Maivbtn_153->setPropertyV(WSNheight,(unsigned short)20);

  FrmPhysics = new  WSCform(MainWindow,"FrmPhysics");
      FrmPhysics->initialize();
  FrmPhysics->setPropertyV(WSNname,"FrmPhysics");
  FrmPhysics->setPropertyV(WSNx,(short)95);
  FrmPhysics->setPropertyV(WSNy,(short)25);
  FrmPhysics->setPropertyV(WSNwidth,(unsigned short)690);
  FrmPhysics->setPropertyV(WSNheight,(unsigned short)470);
  FrmPhysics->setPropertyV(WSNvis,(WSCbool)1);

  PhysicsTypeOpt = new  WSCoption(FrmPhysics,"PhysicsTypeOpt");
      PhysicsTypeOpt->initialize();
  PhysicsTypeOpt->setPropertyV(WSNmenuItems,"Walking:1:ep1_name,Running:2:ep2_name");
  PhysicsTypeOpt->setPropertyV(WSNvalue,(long)1);
  PhysicsTypeOpt->setPropertyV(WSNlabelString,"Walking");
  PhysicsTypeOpt->setPropertyV(WSNname,"PhysicsTypeOpt");
  PhysicsTypeOpt->setPropertyV(WSNvis,(WSCbool)1);
  PhysicsTypeOpt->setPropertyV(WSNx,(short)110);
  PhysicsTypeOpt->setPropertyV(WSNy,(short)10);
  PhysicsTypeOpt->setPropertyV(WSNwidth,(unsigned short)110);
  PhysicsTypeOpt->setPropertyV(WSNheight,(unsigned short)20);
    extern void PhysicsTypeOptChFunc(WSCbase*);
    PhysicsTypeOpt->addProcedureV("PhysicsTypeOptCh","PhysicsTypeOptChFunc",PhysicsTypeOptChFunc,3);

  Maivlab_158 = new  WSCvlabel(FrmPhysics,"Maivlab_158");
      Maivlab_158->initialize();
  Maivlab_158->setPropertyV(WSNlabelString,"Type");
  Maivlab_158->setPropertyV(WSNname,"Maivlab_158");
  Maivlab_158->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_158->setPropertyV(WSNx,(short)10);
  Maivlab_158->setPropertyV(WSNy,(short)10);
  Maivlab_158->setPropertyV(WSNheight,(unsigned short)20);

  PhyMaxForwardEdit = new  WSCvifield(FrmPhysics,"PhyMaxForwardEdit");
      PhyMaxForwardEdit->initialize();
  PhyMaxForwardEdit->setPropertyV(WSNname,"PhyMaxForwardEdit");
  PhyMaxForwardEdit->setPropertyV(WSNvis,(WSCbool)1);
  PhyMaxForwardEdit->setPropertyV(WSNx,(short)180);
  PhyMaxForwardEdit->setPropertyV(WSNy,(short)40);
  PhyMaxForwardEdit->setPropertyV(WSNwidth,(unsigned short)110);
  PhyMaxForwardEdit->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_160 = new  WSCvlabel(FrmPhysics,"Maivlab_160");
      Maivlab_160->initialize();
  Maivlab_160->setPropertyV(WSNlabelString,"Max Forward Velocity");
  Maivlab_160->setPropertyV(WSNname,"Maivlab_160");
  Maivlab_160->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_160->setPropertyV(WSNx,(short)10);
  Maivlab_160->setPropertyV(WSNy,(short)40);
  Maivlab_160->setPropertyV(WSNwidth,(unsigned short)170);
  Maivlab_160->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_161 = new  WSCvlabel(FrmPhysics,"Maivlab_161");
      Maivlab_161->initialize();
  Maivlab_161->setPropertyV(WSNlabelString,"Max Backward Velocity");
  Maivlab_161->setPropertyV(WSNname,"Maivlab_161");
  Maivlab_161->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_161->setPropertyV(WSNx,(short)10);
  Maivlab_161->setPropertyV(WSNy,(short)60);
  Maivlab_161->setPropertyV(WSNwidth,(unsigned short)170);
  Maivlab_161->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_162 = new  WSCvlabel(FrmPhysics,"Maivlab_162");
      Maivlab_162->initialize();
  Maivlab_162->setPropertyV(WSNlabelString,"Max Perpendicular Velocity");
  Maivlab_162->setPropertyV(WSNname,"Maivlab_162");
  Maivlab_162->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_162->setPropertyV(WSNx,(short)10);
  Maivlab_162->setPropertyV(WSNy,(short)80);
  Maivlab_162->setPropertyV(WSNwidth,(unsigned short)170);
  Maivlab_162->setPropertyV(WSNheight,(unsigned short)20);

  labne = new  WSCvlabel(FrmPhysics,"labne");
      labne->initialize();
  labne->setPropertyV(WSNlabelString,"Acceleration");
  labne->setPropertyV(WSNname,"labne");
  labne->setPropertyV(WSNvis,(WSCbool)1);
  labne->setPropertyV(WSNx,(short)10);
  labne->setPropertyV(WSNy,(short)100);
  labne->setPropertyV(WSNwidth,(unsigned short)170);
  labne->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_164 = new  WSCvlabel(FrmPhysics,"Maivlab_164");
      Maivlab_164->initialize();
  Maivlab_164->setPropertyV(WSNlabelString,"Deceleration");
  Maivlab_164->setPropertyV(WSNname,"Maivlab_164");
  Maivlab_164->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_164->setPropertyV(WSNx,(short)10);
  Maivlab_164->setPropertyV(WSNy,(short)120);
  Maivlab_164->setPropertyV(WSNwidth,(unsigned short)170);
  Maivlab_164->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_165 = new  WSCvlabel(FrmPhysics,"Maivlab_165");
      Maivlab_165->initialize();
  Maivlab_165->setPropertyV(WSNlabelString,"Airborne Deceleration");
  Maivlab_165->setPropertyV(WSNname,"Maivlab_165");
  Maivlab_165->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_165->setPropertyV(WSNx,(short)10);
  Maivlab_165->setPropertyV(WSNy,(short)140);
  Maivlab_165->setPropertyV(WSNwidth,(unsigned short)170);
  Maivlab_165->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_166 = new  WSCvlabel(FrmPhysics,"Maivlab_166");
      Maivlab_166->initialize();
  Maivlab_166->setPropertyV(WSNlabelString,"Gravity Accel");
  Maivlab_166->setPropertyV(WSNname,"Maivlab_166");
  Maivlab_166->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_166->setPropertyV(WSNx,(short)10);
  Maivlab_166->setPropertyV(WSNy,(short)160);
  Maivlab_166->setPropertyV(WSNwidth,(unsigned short)170);
  Maivlab_166->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_167 = new  WSCvlabel(FrmPhysics,"Maivlab_167");
      Maivlab_167->initialize();
  Maivlab_167->setPropertyV(WSNlabelString,"Climb Accel");
  Maivlab_167->setPropertyV(WSNname,"Maivlab_167");
  Maivlab_167->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_167->setPropertyV(WSNx,(short)10);
  Maivlab_167->setPropertyV(WSNy,(short)180);
  Maivlab_167->setPropertyV(WSNwidth,(unsigned short)170);
  Maivlab_167->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_168 = new  WSCvlabel(FrmPhysics,"Maivlab_168");
      Maivlab_168->initialize();
  Maivlab_168->setPropertyV(WSNlabelString,"Terminal Accel");
  Maivlab_168->setPropertyV(WSNname,"Maivlab_168");
  Maivlab_168->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_168->setPropertyV(WSNx,(short)10);
  Maivlab_168->setPropertyV(WSNy,(short)200);
  Maivlab_168->setPropertyV(WSNwidth,(unsigned short)170);
  Maivlab_168->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_169 = new  WSCvlabel(FrmPhysics,"Maivlab_169");
      Maivlab_169->initialize();
  Maivlab_169->setPropertyV(WSNlabelString,"External Deceleration");
  Maivlab_169->setPropertyV(WSNname,"Maivlab_169");
  Maivlab_169->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_169->setPropertyV(WSNx,(short)10);
  Maivlab_169->setPropertyV(WSNy,(short)220);
  Maivlab_169->setPropertyV(WSNwidth,(unsigned short)170);
  Maivlab_169->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_170 = new  WSCvlabel(FrmPhysics,"Maivlab_170");
      Maivlab_170->initialize();
  Maivlab_170->setPropertyV(WSNlabelString,"Angular Accel");
  Maivlab_170->setPropertyV(WSNname,"Maivlab_170");
  Maivlab_170->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_170->setPropertyV(WSNx,(short)10);
  Maivlab_170->setPropertyV(WSNy,(short)240);
  Maivlab_170->setPropertyV(WSNwidth,(unsigned short)170);
  Maivlab_170->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_171 = new  WSCvlabel(FrmPhysics,"Maivlab_171");
      Maivlab_171->initialize();
  Maivlab_171->setPropertyV(WSNlabelString,"Angular Deceleration");
  Maivlab_171->setPropertyV(WSNname,"Maivlab_171");
  Maivlab_171->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_171->setPropertyV(WSNx,(short)10);
  Maivlab_171->setPropertyV(WSNy,(short)260);
  Maivlab_171->setPropertyV(WSNwidth,(unsigned short)170);
  Maivlab_171->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_172 = new  WSCvlabel(FrmPhysics,"Maivlab_172");
      Maivlab_172->initialize();
  Maivlab_172->setPropertyV(WSNlabelString,"Max Angular Velocity");
  Maivlab_172->setPropertyV(WSNname,"Maivlab_172");
  Maivlab_172->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_172->setPropertyV(WSNx,(short)10);
  Maivlab_172->setPropertyV(WSNy,(short)280);
  Maivlab_172->setPropertyV(WSNwidth,(unsigned short)170);
  Maivlab_172->setPropertyV(WSNheight,(unsigned short)20);

  PhyMaxBackwardEdit = new  WSCvifield(FrmPhysics,"PhyMaxBackwardEdit");
      PhyMaxBackwardEdit->initialize();
  PhyMaxBackwardEdit->setPropertyV(WSNname,"PhyMaxBackwardEdit");
  PhyMaxBackwardEdit->setPropertyV(WSNvis,(WSCbool)1);
  PhyMaxBackwardEdit->setPropertyV(WSNx,(short)180);
  PhyMaxBackwardEdit->setPropertyV(WSNy,(short)60);
  PhyMaxBackwardEdit->setPropertyV(WSNwidth,(unsigned short)110);
  PhyMaxBackwardEdit->setPropertyV(WSNheight,(unsigned short)20);

  PhyMaxPerpendEdit = new  WSCvifield(FrmPhysics,"PhyMaxPerpendEdit");
      PhyMaxPerpendEdit->initialize();
  PhyMaxPerpendEdit->setPropertyV(WSNname,"PhyMaxPerpendEdit");
  PhyMaxPerpendEdit->setPropertyV(WSNvis,(WSCbool)1);
  PhyMaxPerpendEdit->setPropertyV(WSNx,(short)180);
  PhyMaxPerpendEdit->setPropertyV(WSNy,(short)80);
  PhyMaxPerpendEdit->setPropertyV(WSNwidth,(unsigned short)110);
  PhyMaxPerpendEdit->setPropertyV(WSNheight,(unsigned short)20);

  PhyAccelEdit = new  WSCvifield(FrmPhysics,"PhyAccelEdit");
      PhyAccelEdit->initialize();
  PhyAccelEdit->setPropertyV(WSNname,"PhyAccelEdit");
  PhyAccelEdit->setPropertyV(WSNvis,(WSCbool)1);
  PhyAccelEdit->setPropertyV(WSNx,(short)180);
  PhyAccelEdit->setPropertyV(WSNy,(short)100);
  PhyAccelEdit->setPropertyV(WSNwidth,(unsigned short)110);
  PhyAccelEdit->setPropertyV(WSNheight,(unsigned short)20);

  PhyDecelEdit = new  WSCvifield(FrmPhysics,"PhyDecelEdit");
      PhyDecelEdit->initialize();
  PhyDecelEdit->setPropertyV(WSNname,"PhyDecelEdit");
  PhyDecelEdit->setPropertyV(WSNvis,(WSCbool)1);
  PhyDecelEdit->setPropertyV(WSNx,(short)180);
  PhyDecelEdit->setPropertyV(WSNy,(short)120);
  PhyDecelEdit->setPropertyV(WSNwidth,(unsigned short)110);
  PhyDecelEdit->setPropertyV(WSNheight,(unsigned short)20);

  PhyAirDecelEdit = new  WSCvifield(FrmPhysics,"PhyAirDecelEdit");
      PhyAirDecelEdit->initialize();
  PhyAirDecelEdit->setPropertyV(WSNname,"PhyAirDecelEdit");
  PhyAirDecelEdit->setPropertyV(WSNvis,(WSCbool)1);
  PhyAirDecelEdit->setPropertyV(WSNx,(short)180);
  PhyAirDecelEdit->setPropertyV(WSNy,(short)140);
  PhyAirDecelEdit->setPropertyV(WSNwidth,(unsigned short)110);
  PhyAirDecelEdit->setPropertyV(WSNheight,(unsigned short)20);

  PhyGravityAccelEdit = new  WSCvifield(FrmPhysics,"PhyGravityAccelEdit");
      PhyGravityAccelEdit->initialize();
  PhyGravityAccelEdit->setPropertyV(WSNname,"PhyGravityAccelEdit");
  PhyGravityAccelEdit->setPropertyV(WSNvis,(WSCbool)1);
  PhyGravityAccelEdit->setPropertyV(WSNx,(short)180);
  PhyGravityAccelEdit->setPropertyV(WSNy,(short)160);
  PhyGravityAccelEdit->setPropertyV(WSNwidth,(unsigned short)110);
  PhyGravityAccelEdit->setPropertyV(WSNheight,(unsigned short)20);

  PhyClimbAccelEdit = new  WSCvifield(FrmPhysics,"PhyClimbAccelEdit");
      PhyClimbAccelEdit->initialize();
  PhyClimbAccelEdit->setPropertyV(WSNname,"PhyClimbAccelEdit");
  PhyClimbAccelEdit->setPropertyV(WSNvis,(WSCbool)1);
  PhyClimbAccelEdit->setPropertyV(WSNx,(short)180);
  PhyClimbAccelEdit->setPropertyV(WSNy,(short)180);
  PhyClimbAccelEdit->setPropertyV(WSNwidth,(unsigned short)110);
  PhyClimbAccelEdit->setPropertyV(WSNheight,(unsigned short)20);

  PhyTerminalAccelEdit = new  WSCvifield(FrmPhysics,"PhyTerminalAccelEdit");
      PhyTerminalAccelEdit->initialize();
  PhyTerminalAccelEdit->setPropertyV(WSNname,"PhyTerminalAccelEdit");
  PhyTerminalAccelEdit->setPropertyV(WSNvis,(WSCbool)1);
  PhyTerminalAccelEdit->setPropertyV(WSNx,(short)180);
  PhyTerminalAccelEdit->setPropertyV(WSNy,(short)200);
  PhyTerminalAccelEdit->setPropertyV(WSNwidth,(unsigned short)110);
  PhyTerminalAccelEdit->setPropertyV(WSNheight,(unsigned short)20);

  PhyExtDecEdit = new  WSCvifield(FrmPhysics,"PhyExtDecEdit");
      PhyExtDecEdit->initialize();
  PhyExtDecEdit->setPropertyV(WSNname,"PhyExtDecEdit");
  PhyExtDecEdit->setPropertyV(WSNvis,(WSCbool)1);
  PhyExtDecEdit->setPropertyV(WSNx,(short)180);
  PhyExtDecEdit->setPropertyV(WSNy,(short)220);
  PhyExtDecEdit->setPropertyV(WSNwidth,(unsigned short)110);
  PhyExtDecEdit->setPropertyV(WSNheight,(unsigned short)20);

  PhyAngularAccelEdit = new  WSCvifield(FrmPhysics,"PhyAngularAccelEdit");
      PhyAngularAccelEdit->initialize();
  PhyAngularAccelEdit->setPropertyV(WSNname,"PhyAngularAccelEdit");
  PhyAngularAccelEdit->setPropertyV(WSNvis,(WSCbool)1);
  PhyAngularAccelEdit->setPropertyV(WSNx,(short)180);
  PhyAngularAccelEdit->setPropertyV(WSNy,(short)240);
  PhyAngularAccelEdit->setPropertyV(WSNwidth,(unsigned short)110);
  PhyAngularAccelEdit->setPropertyV(WSNheight,(unsigned short)20);

  PhyAngularDecelEdit = new  WSCvifield(FrmPhysics,"PhyAngularDecelEdit");
      PhyAngularDecelEdit->initialize();
  PhyAngularDecelEdit->setPropertyV(WSNname,"PhyAngularDecelEdit");
  PhyAngularDecelEdit->setPropertyV(WSNvis,(WSCbool)1);
  PhyAngularDecelEdit->setPropertyV(WSNx,(short)180);
  PhyAngularDecelEdit->setPropertyV(WSNy,(short)260);
  PhyAngularDecelEdit->setPropertyV(WSNwidth,(unsigned short)110);
  PhyAngularDecelEdit->setPropertyV(WSNheight,(unsigned short)20);

  PhyMaxAngularVelEdit = new  WSCvifield(FrmPhysics,"PhyMaxAngularVelEdit");
      PhyMaxAngularVelEdit->initialize();
  PhyMaxAngularVelEdit->setPropertyV(WSNname,"PhyMaxAngularVelEdit");
  PhyMaxAngularVelEdit->setPropertyV(WSNvis,(WSCbool)1);
  PhyMaxAngularVelEdit->setPropertyV(WSNx,(short)180);
  PhyMaxAngularVelEdit->setPropertyV(WSNy,(short)280);
  PhyMaxAngularVelEdit->setPropertyV(WSNwidth,(unsigned short)110);
  PhyMaxAngularVelEdit->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_185 = new  WSCvlabel(FrmPhysics,"Maivlab_185");
      Maivlab_185->initialize();
  Maivlab_185->setPropertyV(WSNlabelString,"Angular Recentering Velocity");
  Maivlab_185->setPropertyV(WSNname,"Maivlab_185");
  Maivlab_185->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_185->setPropertyV(WSNx,(short)10);
  Maivlab_185->setPropertyV(WSNy,(short)300);
  Maivlab_185->setPropertyV(WSNwidth,(unsigned short)170);
  Maivlab_185->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_186 = new  WSCvlabel(FrmPhysics,"Maivlab_186");
      Maivlab_186->initialize();
  Maivlab_186->setPropertyV(WSNlabelString,"Fast Angular Velocity");
  Maivlab_186->setPropertyV(WSNname,"Maivlab_186");
  Maivlab_186->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_186->setPropertyV(WSNx,(short)10);
  Maivlab_186->setPropertyV(WSNy,(short)320);
  Maivlab_186->setPropertyV(WSNwidth,(unsigned short)170);
  Maivlab_186->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_187 = new  WSCvlabel(FrmPhysics,"Maivlab_187");
      Maivlab_187->initialize();
  Maivlab_187->setPropertyV(WSNlabelString,"Max Elevation");
  Maivlab_187->setPropertyV(WSNname,"Maivlab_187");
  Maivlab_187->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_187->setPropertyV(WSNx,(short)10);
  Maivlab_187->setPropertyV(WSNy,(short)340);
  Maivlab_187->setPropertyV(WSNwidth,(unsigned short)170);
  Maivlab_187->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_188 = new  WSCvlabel(FrmPhysics,"Maivlab_188");
      Maivlab_188->initialize();
  Maivlab_188->setPropertyV(WSNlabelString,"External Angular Decel");
  Maivlab_188->setPropertyV(WSNname,"Maivlab_188");
  Maivlab_188->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_188->setPropertyV(WSNx,(short)10);
  Maivlab_188->setPropertyV(WSNy,(short)360);
  Maivlab_188->setPropertyV(WSNwidth,(unsigned short)170);
  Maivlab_188->setPropertyV(WSNheight,(unsigned short)20);

  PhyAngularRecenterEdit = new  WSCvifield(FrmPhysics,"PhyAngularRecenterEdit");
      PhyAngularRecenterEdit->initialize();
  PhyAngularRecenterEdit->setPropertyV(WSNname,"PhyAngularRecenterEdit");
  PhyAngularRecenterEdit->setPropertyV(WSNvis,(WSCbool)1);
  PhyAngularRecenterEdit->setPropertyV(WSNx,(short)180);
  PhyAngularRecenterEdit->setPropertyV(WSNy,(short)300);
  PhyAngularRecenterEdit->setPropertyV(WSNwidth,(unsigned short)110);
  PhyAngularRecenterEdit->setPropertyV(WSNheight,(unsigned short)20);

  PhyFastAngularVelEdit = new  WSCvifield(FrmPhysics,"PhyFastAngularVelEdit");
      PhyFastAngularVelEdit->initialize();
  PhyFastAngularVelEdit->setPropertyV(WSNname,"PhyFastAngularVelEdit");
  PhyFastAngularVelEdit->setPropertyV(WSNvis,(WSCbool)1);
  PhyFastAngularVelEdit->setPropertyV(WSNx,(short)180);
  PhyFastAngularVelEdit->setPropertyV(WSNy,(short)320);
  PhyFastAngularVelEdit->setPropertyV(WSNwidth,(unsigned short)110);
  PhyFastAngularVelEdit->setPropertyV(WSNheight,(unsigned short)20);

  PhyMaxElevationEdit = new  WSCvifield(FrmPhysics,"PhyMaxElevationEdit");
      PhyMaxElevationEdit->initialize();
  PhyMaxElevationEdit->setPropertyV(WSNname,"PhyMaxElevationEdit");
  PhyMaxElevationEdit->setPropertyV(WSNvis,(WSCbool)1);
  PhyMaxElevationEdit->setPropertyV(WSNx,(short)180);
  PhyMaxElevationEdit->setPropertyV(WSNy,(short)340);
  PhyMaxElevationEdit->setPropertyV(WSNwidth,(unsigned short)110);
  PhyMaxElevationEdit->setPropertyV(WSNheight,(unsigned short)20);

  PhyExtAngularDecelEdit = new  WSCvifield(FrmPhysics,"PhyExtAngularDecelEdit");
      PhyExtAngularDecelEdit->initialize();
  PhyExtAngularDecelEdit->setPropertyV(WSNname,"PhyExtAngularDecelEdit");
  PhyExtAngularDecelEdit->setPropertyV(WSNvis,(WSCbool)1);
  PhyExtAngularDecelEdit->setPropertyV(WSNx,(short)180);
  PhyExtAngularDecelEdit->setPropertyV(WSNy,(short)360);
  PhyExtAngularDecelEdit->setPropertyV(WSNwidth,(unsigned short)110);
  PhyExtAngularDecelEdit->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_193 = new  WSCvlabel(FrmPhysics,"Maivlab_193");
      Maivlab_193->initialize();
  Maivlab_193->setPropertyV(WSNlabelString,"Step Delta");
  Maivlab_193->setPropertyV(WSNname,"Maivlab_193");
  Maivlab_193->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_193->setPropertyV(WSNx,(short)10);
  Maivlab_193->setPropertyV(WSNy,(short)380);
  Maivlab_193->setPropertyV(WSNwidth,(unsigned short)170);
  Maivlab_193->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_194 = new  WSCvlabel(FrmPhysics,"Maivlab_194");
      Maivlab_194->initialize();
  Maivlab_194->setPropertyV(WSNlabelString,"Step Amplitude");
  Maivlab_194->setPropertyV(WSNname,"Maivlab_194");
  Maivlab_194->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_194->setPropertyV(WSNx,(short)10);
  Maivlab_194->setPropertyV(WSNy,(short)400);
  Maivlab_194->setPropertyV(WSNwidth,(unsigned short)170);
  Maivlab_194->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_195 = new  WSCvlabel(FrmPhysics,"Maivlab_195");
      Maivlab_195->initialize();
  Maivlab_195->setPropertyV(WSNlabelString,"Radius");
  Maivlab_195->setPropertyV(WSNname,"Maivlab_195");
  Maivlab_195->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_195->setPropertyV(WSNx,(short)295);
  Maivlab_195->setPropertyV(WSNy,(short)40);
  Maivlab_195->setPropertyV(WSNwidth,(unsigned short)170);
  Maivlab_195->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_196 = new  WSCvlabel(FrmPhysics,"Maivlab_196");
      Maivlab_196->initialize();
  Maivlab_196->setPropertyV(WSNlabelString,"Height");
  Maivlab_196->setPropertyV(WSNname,"Maivlab_196");
  Maivlab_196->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_196->setPropertyV(WSNx,(short)295);
  Maivlab_196->setPropertyV(WSNy,(short)60);
  Maivlab_196->setPropertyV(WSNwidth,(unsigned short)170);
  Maivlab_196->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_197 = new  WSCvlabel(FrmPhysics,"Maivlab_197");
      Maivlab_197->initialize();
  Maivlab_197->setPropertyV(WSNlabelString,"Dead Height");
  Maivlab_197->setPropertyV(WSNname,"Maivlab_197");
  Maivlab_197->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_197->setPropertyV(WSNx,(short)295);
  Maivlab_197->setPropertyV(WSNy,(short)80);
  Maivlab_197->setPropertyV(WSNwidth,(unsigned short)170);
  Maivlab_197->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_198 = new  WSCvlabel(FrmPhysics,"Maivlab_198");
      Maivlab_198->initialize();
  Maivlab_198->setPropertyV(WSNlabelString,"Camera Height");
  Maivlab_198->setPropertyV(WSNname,"Maivlab_198");
  Maivlab_198->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_198->setPropertyV(WSNx,(short)295);
  Maivlab_198->setPropertyV(WSNy,(short)100);
  Maivlab_198->setPropertyV(WSNwidth,(unsigned short)170);
  Maivlab_198->setPropertyV(WSNheight,(unsigned short)20);

  Maivlab_199 = new  WSCvlabel(FrmPhysics,"Maivlab_199");
      Maivlab_199->initialize();
  Maivlab_199->setPropertyV(WSNlabelString,"Splash Height");
  Maivlab_199->setPropertyV(WSNname,"Maivlab_199");
  Maivlab_199->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_199->setPropertyV(WSNx,(short)295);
  Maivlab_199->setPropertyV(WSNy,(short)120);
  Maivlab_199->setPropertyV(WSNwidth,(unsigned short)170);
  Maivlab_199->setPropertyV(WSNheight,(unsigned short)20);

  PhyHalfCameraSepEdit = new  WSCvlabel(FrmPhysics,"PhyHalfCameraSepEdit");
      PhyHalfCameraSepEdit->initialize();
  PhyHalfCameraSepEdit->setPropertyV(WSNlabelString,"EHalf Camera Separation");
  PhyHalfCameraSepEdit->setPropertyV(WSNname,"PhyHalfCameraSepEdit");
  PhyHalfCameraSepEdit->setPropertyV(WSNvis,(WSCbool)1);
  PhyHalfCameraSepEdit->setPropertyV(WSNx,(short)295);
  PhyHalfCameraSepEdit->setPropertyV(WSNy,(short)140);
  PhyHalfCameraSepEdit->setPropertyV(WSNwidth,(unsigned short)170);
  PhyHalfCameraSepEdit->setPropertyV(WSNheight,(unsigned short)20);

  PhyStepDeltaEdit = new  WSCvifield(FrmPhysics,"PhyStepDeltaEdit");
      PhyStepDeltaEdit->initialize();
  PhyStepDeltaEdit->setPropertyV(WSNname,"PhyStepDeltaEdit");
  PhyStepDeltaEdit->setPropertyV(WSNvis,(WSCbool)1);
  PhyStepDeltaEdit->setPropertyV(WSNx,(short)180);
  PhyStepDeltaEdit->setPropertyV(WSNy,(short)380);
  PhyStepDeltaEdit->setPropertyV(WSNwidth,(unsigned short)110);
  PhyStepDeltaEdit->setPropertyV(WSNheight,(unsigned short)20);

  PhyStepAmpEdit = new  WSCvifield(FrmPhysics,"PhyStepAmpEdit");
      PhyStepAmpEdit->initialize();
  PhyStepAmpEdit->setPropertyV(WSNname,"PhyStepAmpEdit");
  PhyStepAmpEdit->setPropertyV(WSNvis,(WSCbool)1);
  PhyStepAmpEdit->setPropertyV(WSNx,(short)180);
  PhyStepAmpEdit->setPropertyV(WSNy,(short)400);
  PhyStepAmpEdit->setPropertyV(WSNwidth,(unsigned short)110);
  PhyStepAmpEdit->setPropertyV(WSNheight,(unsigned short)20);

  PhyRadiusEdit = new  WSCvifield(FrmPhysics,"PhyRadiusEdit");
      PhyRadiusEdit->initialize();
  PhyRadiusEdit->setPropertyV(WSNname,"PhyRadiusEdit");
  PhyRadiusEdit->setPropertyV(WSNvis,(WSCbool)1);
  PhyRadiusEdit->setPropertyV(WSNx,(short)465);
  PhyRadiusEdit->setPropertyV(WSNy,(short)40);
  PhyRadiusEdit->setPropertyV(WSNwidth,(unsigned short)110);
  PhyRadiusEdit->setPropertyV(WSNheight,(unsigned short)20);

  PhyHeightEdit = new  WSCvifield(FrmPhysics,"PhyHeightEdit");
      PhyHeightEdit->initialize();
  PhyHeightEdit->setPropertyV(WSNname,"PhyHeightEdit");
  PhyHeightEdit->setPropertyV(WSNvis,(WSCbool)1);
  PhyHeightEdit->setPropertyV(WSNx,(short)465);
  PhyHeightEdit->setPropertyV(WSNy,(short)60);
  PhyHeightEdit->setPropertyV(WSNwidth,(unsigned short)110);
  PhyHeightEdit->setPropertyV(WSNheight,(unsigned short)20);

  PhyDeadHeightEdit = new  WSCvifield(FrmPhysics,"PhyDeadHeightEdit");
      PhyDeadHeightEdit->initialize();
  PhyDeadHeightEdit->setPropertyV(WSNname,"PhyDeadHeightEdit");
  PhyDeadHeightEdit->setPropertyV(WSNvis,(WSCbool)1);
  PhyDeadHeightEdit->setPropertyV(WSNx,(short)465);
  PhyDeadHeightEdit->setPropertyV(WSNy,(short)80);
  PhyDeadHeightEdit->setPropertyV(WSNwidth,(unsigned short)110);
  PhyDeadHeightEdit->setPropertyV(WSNheight,(unsigned short)20);

  PhyCameraHeightEdit = new  WSCvifield(FrmPhysics,"PhyCameraHeightEdit");
      PhyCameraHeightEdit->initialize();
  PhyCameraHeightEdit->setPropertyV(WSNname,"PhyCameraHeightEdit");
  PhyCameraHeightEdit->setPropertyV(WSNvis,(WSCbool)1);
  PhyCameraHeightEdit->setPropertyV(WSNx,(short)465);
  PhyCameraHeightEdit->setPropertyV(WSNy,(short)100);
  PhyCameraHeightEdit->setPropertyV(WSNwidth,(unsigned short)110);
  PhyCameraHeightEdit->setPropertyV(WSNheight,(unsigned short)20);

  PhySplashHeightEdit = new  WSCvifield(FrmPhysics,"PhySplashHeightEdit");
      PhySplashHeightEdit->initialize();
  PhySplashHeightEdit->setPropertyV(WSNname,"PhySplashHeightEdit");
  PhySplashHeightEdit->setPropertyV(WSNvis,(WSCbool)1);
  PhySplashHeightEdit->setPropertyV(WSNx,(short)465);
  PhySplashHeightEdit->setPropertyV(WSNy,(short)120);
  PhySplashHeightEdit->setPropertyV(WSNwidth,(unsigned short)110);
  PhySplashHeightEdit->setPropertyV(WSNheight,(unsigned short)20);

  Maivifi_208 = new  WSCvifield(FrmPhysics,"Maivifi_208");
      Maivifi_208->initialize();
  Maivifi_208->setPropertyV(WSNname,"Maivifi_208");
  Maivifi_208->setPropertyV(WSNvis,(WSCbool)1);
  Maivifi_208->setPropertyV(WSNx,(short)465);
  Maivifi_208->setPropertyV(WSNy,(short)140);
  Maivifi_208->setPropertyV(WSNwidth,(unsigned short)110);
  Maivifi_208->setPropertyV(WSNheight,(unsigned short)20);

  FrmWeapon = new  WSCform(MainWindow,"FrmWeapon");
      FrmWeapon->initialize();
  FrmWeapon->setPropertyV(WSNname,"FrmWeapon");
  FrmWeapon->setPropertyV(WSNx,(short)95);
  FrmWeapon->setPropertyV(WSNy,(short)25);
  FrmWeapon->setPropertyV(WSNwidth,(unsigned short)690);
  FrmWeapon->setPropertyV(WSNheight,(unsigned short)470);

   MainWindow->setVisible(True);
   return MainWindow;
}

//--- end of src ---//
