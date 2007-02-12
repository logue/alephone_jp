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
#include <WSCwindow.h>
#include <WSCindexForm.h>
#include <WSCvlabel.h>
#include <WSCoption.h>
#include <WSCvifield.h>
#include <WSClist.h>

//--- OBJECT instance variable ---//
WSCmainWindow* MainWindow = NULL;
WSCmenuArea* Maimenu_000 = NULL;
WSCpulldownMenu* Maipull_001 = NULL;
WSCvbtn* BtnMonster = NULL;
WSCvbtn* BtnEffect = NULL;
WSCvbtn* BtnProjectile = NULL;
WSCvbtn* BtnPhysics = NULL;
WSCvbtn* BtnWeapon = NULL;
WSCwindow* WndMonster = NULL;
WSCindexForm* Maiinde_012 = NULL;
WSCvlabel* Maivlab_014 = NULL;
WSCoption* CollectionsCombo = NULL;
WSCvlabel* Maivlab_018 = NULL;
WSCoption* ClassCombo = NULL;
WSCvifield* PalletEdit = NULL;
WSCvlabel* Maivlab_021 = NULL;
WSCvlabel* Maivlab_023 = NULL;
WSCoption* CarryItemCombo = NULL;
WSCvifield* VitalityEdit = NULL;
WSCvlabel* Maivlab_026 = NULL;
WSCvlabel* Maivlab_027 = NULL;
WSCvifield* RadiusEdit = NULL;
WSCvifield* HeightEdit = NULL;
WSCvlabel* Maivlab_030 = NULL;
WSCvlabel* Maivlab_031 = NULL;
WSCvlabel* Maivlab_032 = NULL;
WSCvlabel* Maivlab_033 = NULL;
WSCvlabel* Maivlab_034 = NULL;
WSCvifield* HoverEdit = NULL;
WSCvifield* MinLedgeEdit = NULL;
WSCvifield* MaxLedgeEdit = NULL;
WSCvifield* ExtVelScaleEdit = NULL;
WSCvlabel* Maivlab_039 = NULL;
WSCvlabel* Maivlab_040 = NULL;
WSCvlabel* Maivlab_041 = NULL;
WSCvlabel* Maivlab_042 = NULL;
WSCvlabel* Maivlab_043 = NULL;
WSCvlabel* Maivlab_044 = NULL;
WSCvlabel* Maivlab_045 = NULL;
WSCvifield* Maivifi_000 = NULL;
WSCvlabel* Maivlab_001 = NULL;
WSCvlabel* Maivlab_002 = NULL;
WSCvifield* Maivifi_003 = NULL;
WSCvifield* Maivifi_004 = NULL;
WSCvifield* Maivifi_005 = NULL;
WSCvifield* Maivifi_006 = NULL;
WSCvifield* Maivifi_007 = NULL;
WSCvifield* Maivifi_008 = NULL;
WSCvifield* Maivifi_009 = NULL;
WSCvifield* Maivifi_010 = NULL;
WSCvlabel* Maivlab_005 = NULL;
WSCvlabel* Maivlab_006 = NULL;
WSCvlabel* Maivlab_007 = NULL;
WSCvlabel* Maivlab_008 = NULL;
WSCoption* Maiopti_009 = NULL;
WSCvlabel* Maivlab_010 = NULL;
WSCvlabel* Maivlab_011 = NULL;
WSCvlabel* Maivlab_012 = NULL;
WSCvlabel* Maivlab_013 = NULL;
WSCvlabel* Maivlab_015 = NULL;
WSCoption* Maiopti_017 = NULL;
WSCoption* Maiopti_018 = NULL;
WSCoption* Maiopti_020 = NULL;
WSCoption* Maiopti_021 = NULL;
WSCoption* Maiopti_022 = NULL;
WSCoption* Maiopti_023 = NULL;
WSCoption* Maiopti_025 = NULL;
WSCvifield* Maivifi_026 = NULL;
WSCvifield* Maivifi_027 = NULL;
WSCvlabel* Maivlab_028 = NULL;
WSCvlabel* Maivlab_029 = NULL;
WSCvlabel* Maivlab_035 = NULL;
WSCvlabel* Maivlab_036 = NULL;
WSCvlabel* HalfVisualArc = NULL;
WSCvlabel* VerticalVisualArc = NULL;
WSCvlabel* Intelligence = NULL;
WSCvlabel* Speed = NULL;
WSCvlabel* Gravity = NULL;
WSCvifield* HalfVisualArcEdit = NULL;
WSCvifield* VertVisualArc = NULL;
WSCvifield* SpeedEdit = NULL;
WSCvifield* GravityEdit = NULL;
WSCoption* SpeedCombo = NULL;
WSCoption* IntelligenceCombo = NULL;
WSClist* ListImmunities = NULL;
WSCvlabel* Maivlab_003 = NULL;
WSClist* Mailist_004 = NULL;
WSCvlabel* Maivlab_009 = NULL;
WSClist* Mailist_010 = NULL;
WSCvlabel* Maivlab_016 = NULL;
WSCvlabel* Maivlab_017 = NULL;
WSClist* Mailist_018 = NULL;
WSClist* Mailist_019 = NULL;
WSCvbtn* Maivbtn_020 = NULL;
WSClist* ListMonsterType = NULL;

//--- OBJECT src ---//

WSCbase* _create_win_MainWindow(){


  MainWindow = new  WSCmainWindow(NULL,"MainWindow");
      MainWindow->initialize();
  MainWindow->setPropertyV(WSNname,"MainWindow");
  MainWindow->setPropertyV(WSNtitleString,"PhysicsEditorWS");
  MainWindow->setPropertyV(WSNx,(short)100);
  MainWindow->setPropertyV(WSNy,(short)100);
  MainWindow->setPropertyV(WSNwidth,(unsigned short)109);
  MainWindow->setPropertyV(WSNheight,(unsigned short)365);
  MainWindow->setPropertyV(WSNvis,(WSCbool)1);
    extern void MainInitFunc(WSCbase*);
    MainWindow->addProcedureV("MainInit","MainInitFunc",MainInitFunc,0);

  Maimenu_000 = new  WSCmenuArea(MainWindow,"Maimenu_000");
      Maimenu_000->initialize();
  Maimenu_000->setPropertyV(WSNname,"Maimenu_000");
  Maimenu_000->setPropertyV(WSNx,(short)0);
  Maimenu_000->setPropertyV(WSNy,(short)0);
  Maimenu_000->setPropertyV(WSNwidth,(unsigned short)109);
  Maimenu_000->setPropertyV(WSNheight,(unsigned short)23);
  Maimenu_000->setPropertyV(WSNvis,(WSCbool)1);
  Maimenu_000->setPropertyV(WSNanchorLeftFlag,(WSCbool)1);
  Maimenu_000->setPropertyV(WSNanchorRightFlag,(WSCbool)1);

  Maipull_001 = new  WSCpulldownMenu(Maimenu_000,"Maipull_001");
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

  BtnProjectile = new  WSCvbtn(MainWindow,"BtnProjectile");
      BtnProjectile->initialize();
  BtnProjectile->setPropertyV(WSNlabelString,"Projectile");
  BtnProjectile->setPropertyV(WSNname,"BtnProjectile");
  BtnProjectile->setPropertyV(WSNvis,(WSCbool)1);
  BtnProjectile->setPropertyV(WSNx,(short)5);
  BtnProjectile->setPropertyV(WSNy,(short)160);
  BtnProjectile->setPropertyV(WSNwidth,(unsigned short)85);
  BtnProjectile->setPropertyV(WSNheight,(unsigned short)65);

  BtnPhysics = new  WSCvbtn(MainWindow,"BtnPhysics");
      BtnPhysics->initialize();
  BtnPhysics->setPropertyV(WSNlabelString,"Physics");
  BtnPhysics->setPropertyV(WSNname,"BtnPhysics");
  BtnPhysics->setPropertyV(WSNvis,(WSCbool)1);
  BtnPhysics->setPropertyV(WSNx,(short)5);
  BtnPhysics->setPropertyV(WSNy,(short)225);
  BtnPhysics->setPropertyV(WSNwidth,(unsigned short)85);
  BtnPhysics->setPropertyV(WSNheight,(unsigned short)65);

  BtnWeapon = new  WSCvbtn(MainWindow,"BtnWeapon");
      BtnWeapon->initialize();
  BtnWeapon->setPropertyV(WSNlabelString,"Weapon");
  BtnWeapon->setPropertyV(WSNname,"BtnWeapon");
  BtnWeapon->setPropertyV(WSNvis,(WSCbool)1);
  BtnWeapon->setPropertyV(WSNx,(short)5);
  BtnWeapon->setPropertyV(WSNy,(short)290);
  BtnWeapon->setPropertyV(WSNwidth,(unsigned short)85);
  BtnWeapon->setPropertyV(WSNheight,(unsigned short)65);

  WndMonster = new  WSCwindow(MainWindow,"WndMonster");
      WndMonster->initialize();
  WndMonster->setPropertyV(WSNname,"WndMonster");
  WndMonster->setPropertyV(WSNtitleString,"Monster");
  WndMonster->setPropertyV(WSNx,(short)272);
  WndMonster->setPropertyV(WSNy,(short)159);
  WndMonster->setPropertyV(WSNwidth,(unsigned short)678);
  WndMonster->setPropertyV(WSNheight,(unsigned short)463);
  WndMonster->setPropertyV(WSNshadowThickness,(unsigned char)2);
  WndMonster->setPropertyV(WSNtitleBar,(char)2);
  WndMonster->setPropertyV(WSNshadowType,(char)-1);
    extern void WndMonsterClosedFunc(WSCbase*);
    WndMonster->addProcedureV("WndMonsterClosed","WndMonsterClosedFunc",WndMonsterClosedFunc,56);

  Maiinde_012 = new  WSCindexForm(WndMonster,"Maiinde_012");
      Maiinde_012->initialize();
  Maiinde_012->setPropertyV(WSNmenuItems,"Appearance,Flags1,Attack");
  Maiinde_012->setPropertyV(WSNname,"Maiinde_012");
  Maiinde_012->setPropertyV(WSNx,(short)110);
  Maiinde_012->setPropertyV(WSNy,(short)0);
  Maiinde_012->setPropertyV(WSNwidth,(unsigned short)565);
  Maiinde_012->setPropertyV(WSNheight,(unsigned short)460);
  Maiinde_012->setPropertyV(WSNvis,(WSCbool)1);
    extern void MonsterTabsInitFunc(WSCbase*);
    Maiinde_012->addProcedureV("MonsterTabsInit","MonsterTabsInitFunc",MonsterTabsInitFunc,0);

  Maivlab_014 = new  WSCvlabel(Maiinde_012,"Maivlab_014");
      Maivlab_014->initialize();
  Maivlab_014->setPropertyV(WSNuserValue,(long)1);
  Maivlab_014->setPropertyV(WSNlabelString,"Collection");
  Maivlab_014->setPropertyV(WSNname,"Maivlab_014");
  Maivlab_014->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_014->setPropertyV(WSNx,(short)5);
  Maivlab_014->setPropertyV(WSNy,(short)30);
  Maivlab_014->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_014->setPropertyV(WSNheight,(unsigned short)25);

  CollectionsCombo = new  WSCoption(Maiinde_012,"CollectionsCombo");
      CollectionsCombo->initialize();
  CollectionsCombo->setPropertyV(WSNuserValue,(long)1);
  CollectionsCombo->setPropertyV(WSNvalue,(long)1);
  CollectionsCombo->setPropertyV(WSNlabelString,"item1");
  CollectionsCombo->setPropertyV(WSNname,"CollectionsCombo");
  CollectionsCombo->setPropertyV(WSNvis,(WSCbool)1);
  CollectionsCombo->setPropertyV(WSNx,(short)95);
  CollectionsCombo->setPropertyV(WSNy,(short)30);
  CollectionsCombo->setPropertyV(WSNwidth,(unsigned short)80);
  CollectionsCombo->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_018 = new  WSCvlabel(Maiinde_012,"Maivlab_018");
      Maivlab_018->initialize();
  Maivlab_018->setPropertyV(WSNuserValue,(long)1);
  Maivlab_018->setPropertyV(WSNlabelString,"Pallet");
  Maivlab_018->setPropertyV(WSNname,"Maivlab_018");
  Maivlab_018->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_018->setPropertyV(WSNx,(short)5);
  Maivlab_018->setPropertyV(WSNy,(short)55);
  Maivlab_018->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_018->setPropertyV(WSNheight,(unsigned short)25);

  ClassCombo = new  WSCoption(Maiinde_012,"ClassCombo");
      ClassCombo->initialize();
  ClassCombo->setPropertyV(WSNuserValue,(long)1);
  ClassCombo->setPropertyV(WSNvalue,(long)3);
  ClassCombo->setPropertyV(WSNlabelString,"item3");
  ClassCombo->setPropertyV(WSNname,"ClassCombo");
  ClassCombo->setPropertyV(WSNvis,(WSCbool)1);
  ClassCombo->setPropertyV(WSNx,(short)95);
  ClassCombo->setPropertyV(WSNy,(short)105);
  ClassCombo->setPropertyV(WSNwidth,(unsigned short)80);
  ClassCombo->setPropertyV(WSNheight,(unsigned short)25);

  PalletEdit = new  WSCvifield(Maiinde_012,"PalletEdit");
      PalletEdit->initialize();
  PalletEdit->setPropertyV(WSNuserValue,(long)1);
  PalletEdit->setPropertyV(WSNname,"PalletEdit");
  PalletEdit->setPropertyV(WSNvis,(WSCbool)1);
  PalletEdit->setPropertyV(WSNx,(short)95);
  PalletEdit->setPropertyV(WSNy,(short)55);
  PalletEdit->setPropertyV(WSNwidth,(unsigned short)80);
  PalletEdit->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_021 = new  WSCvlabel(Maiinde_012,"Maivlab_021");
      Maivlab_021->initialize();
  Maivlab_021->setPropertyV(WSNuserValue,(long)1);
  Maivlab_021->setPropertyV(WSNlabelString,"Vitality");
  Maivlab_021->setPropertyV(WSNname,"Maivlab_021");
  Maivlab_021->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_021->setPropertyV(WSNx,(short)5);
  Maivlab_021->setPropertyV(WSNy,(short)80);
  Maivlab_021->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_021->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_023 = new  WSCvlabel(Maiinde_012,"Maivlab_023");
      Maivlab_023->initialize();
  Maivlab_023->setPropertyV(WSNuserValue,(long)1);
  Maivlab_023->setPropertyV(WSNlabelString,"Class");
  Maivlab_023->setPropertyV(WSNname,"Maivlab_023");
  Maivlab_023->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_023->setPropertyV(WSNx,(short)5);
  Maivlab_023->setPropertyV(WSNy,(short)105);
  Maivlab_023->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_023->setPropertyV(WSNheight,(unsigned short)25);

  CarryItemCombo = new  WSCoption(Maiinde_012,"CarryItemCombo");
      CarryItemCombo->initialize();
  CarryItemCombo->setPropertyV(WSNuserValue,(long)1);
  CarryItemCombo->setPropertyV(WSNvalue,(long)1);
  CarryItemCombo->setPropertyV(WSNlabelString,"item1");
  CarryItemCombo->setPropertyV(WSNname,"CarryItemCombo");
  CarryItemCombo->setPropertyV(WSNvis,(WSCbool)1);
  CarryItemCombo->setPropertyV(WSNx,(short)95);
  CarryItemCombo->setPropertyV(WSNy,(short)280);
  CarryItemCombo->setPropertyV(WSNwidth,(unsigned short)80);
  CarryItemCombo->setPropertyV(WSNheight,(unsigned short)25);

  VitalityEdit = new  WSCvifield(Maiinde_012,"VitalityEdit");
      VitalityEdit->initialize();
  VitalityEdit->setPropertyV(WSNuserValue,(long)1);
  VitalityEdit->setPropertyV(WSNname,"VitalityEdit");
  VitalityEdit->setPropertyV(WSNvis,(WSCbool)1);
  VitalityEdit->setPropertyV(WSNx,(short)95);
  VitalityEdit->setPropertyV(WSNy,(short)80);
  VitalityEdit->setPropertyV(WSNwidth,(unsigned short)80);
  VitalityEdit->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_026 = new  WSCvlabel(Maiinde_012,"Maivlab_026");
      Maivlab_026->initialize();
  Maivlab_026->setPropertyV(WSNuserValue,(long)1);
  Maivlab_026->setPropertyV(WSNlabelString,"Radius");
  Maivlab_026->setPropertyV(WSNname,"Maivlab_026");
  Maivlab_026->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_026->setPropertyV(WSNx,(short)5);
  Maivlab_026->setPropertyV(WSNy,(short)130);
  Maivlab_026->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_026->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_027 = new  WSCvlabel(Maiinde_012,"Maivlab_027");
      Maivlab_027->initialize();
  Maivlab_027->setPropertyV(WSNuserValue,(long)1);
  Maivlab_027->setPropertyV(WSNlabelString,"Height");
  Maivlab_027->setPropertyV(WSNname,"Maivlab_027");
  Maivlab_027->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_027->setPropertyV(WSNx,(short)5);
  Maivlab_027->setPropertyV(WSNy,(short)155);
  Maivlab_027->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_027->setPropertyV(WSNheight,(unsigned short)25);

  RadiusEdit = new  WSCvifield(Maiinde_012,"RadiusEdit");
      RadiusEdit->initialize();
  RadiusEdit->setPropertyV(WSNuserValue,(long)1);
  RadiusEdit->setPropertyV(WSNname,"RadiusEdit");
  RadiusEdit->setPropertyV(WSNvis,(WSCbool)1);
  RadiusEdit->setPropertyV(WSNx,(short)95);
  RadiusEdit->setPropertyV(WSNy,(short)130);
  RadiusEdit->setPropertyV(WSNwidth,(unsigned short)80);
  RadiusEdit->setPropertyV(WSNheight,(unsigned short)25);

  HeightEdit = new  WSCvifield(Maiinde_012,"HeightEdit");
      HeightEdit->initialize();
  HeightEdit->setPropertyV(WSNuserValue,(long)1);
  HeightEdit->setPropertyV(WSNname,"HeightEdit");
  HeightEdit->setPropertyV(WSNvis,(WSCbool)1);
  HeightEdit->setPropertyV(WSNx,(short)95);
  HeightEdit->setPropertyV(WSNy,(short)155);
  HeightEdit->setPropertyV(WSNwidth,(unsigned short)80);
  HeightEdit->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_030 = new  WSCvlabel(Maiinde_012,"Maivlab_030");
      Maivlab_030->initialize();
  Maivlab_030->setPropertyV(WSNuserValue,(long)1);
  Maivlab_030->setPropertyV(WSNlabelString,"Hover");
  Maivlab_030->setPropertyV(WSNname,"Maivlab_030");
  Maivlab_030->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_030->setPropertyV(WSNx,(short)5);
  Maivlab_030->setPropertyV(WSNy,(short)180);
  Maivlab_030->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_030->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_031 = new  WSCvlabel(Maiinde_012,"Maivlab_031");
      Maivlab_031->initialize();
  Maivlab_031->setPropertyV(WSNuserValue,(long)1);
  Maivlab_031->setPropertyV(WSNlabelString,"Min Ledge");
  Maivlab_031->setPropertyV(WSNname,"Maivlab_031");
  Maivlab_031->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_031->setPropertyV(WSNx,(short)5);
  Maivlab_031->setPropertyV(WSNy,(short)205);
  Maivlab_031->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_031->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_032 = new  WSCvlabel(Maiinde_012,"Maivlab_032");
      Maivlab_032->initialize();
  Maivlab_032->setPropertyV(WSNuserValue,(long)1);
  Maivlab_032->setPropertyV(WSNlabelString,"Max Ledge");
  Maivlab_032->setPropertyV(WSNname,"Maivlab_032");
  Maivlab_032->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_032->setPropertyV(WSNx,(short)5);
  Maivlab_032->setPropertyV(WSNy,(short)230);
  Maivlab_032->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_032->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_033 = new  WSCvlabel(Maiinde_012,"Maivlab_033");
      Maivlab_033->initialize();
  Maivlab_033->setPropertyV(WSNuserValue,(long)1);
  Maivlab_033->setPropertyV(WSNlabelString,"ExtVelScale");
  Maivlab_033->setPropertyV(WSNname,"Maivlab_033");
  Maivlab_033->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_033->setPropertyV(WSNx,(short)5);
  Maivlab_033->setPropertyV(WSNy,(short)255);
  Maivlab_033->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_033->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_034 = new  WSCvlabel(Maiinde_012,"Maivlab_034");
      Maivlab_034->initialize();
  Maivlab_034->setPropertyV(WSNuserValue,(long)1);
  Maivlab_034->setPropertyV(WSNlabelString,"CarryItem");
  Maivlab_034->setPropertyV(WSNname,"Maivlab_034");
  Maivlab_034->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_034->setPropertyV(WSNx,(short)5);
  Maivlab_034->setPropertyV(WSNy,(short)280);
  Maivlab_034->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_034->setPropertyV(WSNheight,(unsigned short)25);

  HoverEdit = new  WSCvifield(Maiinde_012,"HoverEdit");
      HoverEdit->initialize();
  HoverEdit->setPropertyV(WSNuserValue,(long)1);
  HoverEdit->setPropertyV(WSNname,"HoverEdit");
  HoverEdit->setPropertyV(WSNvis,(WSCbool)1);
  HoverEdit->setPropertyV(WSNx,(short)95);
  HoverEdit->setPropertyV(WSNy,(short)180);
  HoverEdit->setPropertyV(WSNwidth,(unsigned short)80);
  HoverEdit->setPropertyV(WSNheight,(unsigned short)25);

  MinLedgeEdit = new  WSCvifield(Maiinde_012,"MinLedgeEdit");
      MinLedgeEdit->initialize();
  MinLedgeEdit->setPropertyV(WSNuserValue,(long)1);
  MinLedgeEdit->setPropertyV(WSNname,"MinLedgeEdit");
  MinLedgeEdit->setPropertyV(WSNvis,(WSCbool)1);
  MinLedgeEdit->setPropertyV(WSNx,(short)95);
  MinLedgeEdit->setPropertyV(WSNy,(short)205);
  MinLedgeEdit->setPropertyV(WSNwidth,(unsigned short)80);
  MinLedgeEdit->setPropertyV(WSNheight,(unsigned short)25);

  MaxLedgeEdit = new  WSCvifield(Maiinde_012,"MaxLedgeEdit");
      MaxLedgeEdit->initialize();
  MaxLedgeEdit->setPropertyV(WSNuserValue,(long)1);
  MaxLedgeEdit->setPropertyV(WSNname,"MaxLedgeEdit");
  MaxLedgeEdit->setPropertyV(WSNvis,(WSCbool)1);
  MaxLedgeEdit->setPropertyV(WSNx,(short)95);
  MaxLedgeEdit->setPropertyV(WSNy,(short)230);
  MaxLedgeEdit->setPropertyV(WSNwidth,(unsigned short)80);
  MaxLedgeEdit->setPropertyV(WSNheight,(unsigned short)25);

  ExtVelScaleEdit = new  WSCvifield(Maiinde_012,"ExtVelScaleEdit");
      ExtVelScaleEdit->initialize();
  ExtVelScaleEdit->setPropertyV(WSNuserValue,(long)1);
  ExtVelScaleEdit->setPropertyV(WSNname,"ExtVelScaleEdit");
  ExtVelScaleEdit->setPropertyV(WSNvis,(WSCbool)1);
  ExtVelScaleEdit->setPropertyV(WSNx,(short)95);
  ExtVelScaleEdit->setPropertyV(WSNy,(short)255);
  ExtVelScaleEdit->setPropertyV(WSNwidth,(unsigned short)80);
  ExtVelScaleEdit->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_039 = new  WSCvlabel(Maiinde_012,"Maivlab_039");
      Maivlab_039->initialize();
  Maivlab_039->setPropertyV(WSNuserValue,(long)1);
  Maivlab_039->setPropertyV(WSNlabelString,"Stationaly");
  Maivlab_039->setPropertyV(WSNname,"Maivlab_039");
  Maivlab_039->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_039->setPropertyV(WSNx,(short)180);
  Maivlab_039->setPropertyV(WSNy,(short)30);
  Maivlab_039->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_039->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_040 = new  WSCvlabel(Maiinde_012,"Maivlab_040");
      Maivlab_040->initialize();
  Maivlab_040->setPropertyV(WSNuserValue,(long)1);
  Maivlab_040->setPropertyV(WSNlabelString,"Moving");
  Maivlab_040->setPropertyV(WSNname,"Maivlab_040");
  Maivlab_040->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_040->setPropertyV(WSNx,(short)180);
  Maivlab_040->setPropertyV(WSNy,(short)55);
  Maivlab_040->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_040->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_041 = new  WSCvlabel(Maiinde_012,"Maivlab_041");
      Maivlab_041->initialize();
  Maivlab_041->setPropertyV(WSNuserValue,(long)1);
  Maivlab_041->setPropertyV(WSNlabelString,"Hitting");
  Maivlab_041->setPropertyV(WSNname,"Maivlab_041");
  Maivlab_041->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_041->setPropertyV(WSNx,(short)180);
  Maivlab_041->setPropertyV(WSNy,(short)80);
  Maivlab_041->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_041->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_042 = new  WSCvlabel(Maiinde_012,"Maivlab_042");
      Maivlab_042->initialize();
  Maivlab_042->setPropertyV(WSNuserValue,(long)1);
  Maivlab_042->setPropertyV(WSNlabelString,"Soft Dying");
  Maivlab_042->setPropertyV(WSNname,"Maivlab_042");
  Maivlab_042->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_042->setPropertyV(WSNx,(short)180);
  Maivlab_042->setPropertyV(WSNy,(short)105);
  Maivlab_042->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_042->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_043 = new  WSCvlabel(Maiinde_012,"Maivlab_043");
      Maivlab_043->initialize();
  Maivlab_043->setPropertyV(WSNuserValue,(long)1);
  Maivlab_043->setPropertyV(WSNlabelString,"Soft Dead");
  Maivlab_043->setPropertyV(WSNname,"Maivlab_043");
  Maivlab_043->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_043->setPropertyV(WSNx,(short)180);
  Maivlab_043->setPropertyV(WSNy,(short)130);
  Maivlab_043->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_043->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_044 = new  WSCvlabel(Maiinde_012,"Maivlab_044");
      Maivlab_044->initialize();
  Maivlab_044->setPropertyV(WSNuserValue,(long)1);
  Maivlab_044->setPropertyV(WSNlabelString,"Hard Dying");
  Maivlab_044->setPropertyV(WSNname,"Maivlab_044");
  Maivlab_044->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_044->setPropertyV(WSNx,(short)180);
  Maivlab_044->setPropertyV(WSNy,(short)155);
  Maivlab_044->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_044->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_045 = new  WSCvlabel(Maiinde_012,"Maivlab_045");
      Maivlab_045->initialize();
  Maivlab_045->setPropertyV(WSNuserValue,(long)1);
  Maivlab_045->setPropertyV(WSNlabelString,"Hard Dead");
  Maivlab_045->setPropertyV(WSNname,"Maivlab_045");
  Maivlab_045->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_045->setPropertyV(WSNx,(short)180);
  Maivlab_045->setPropertyV(WSNy,(short)180);
  Maivlab_045->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_045->setPropertyV(WSNheight,(unsigned short)25);

  Maivifi_000 = new  WSCvifield(Maiinde_012,"Maivifi_000");
      Maivifi_000->initialize();
  Maivifi_000->setPropertyV(WSNuserValue,(long)1);
  Maivifi_000->setPropertyV(WSNname,"Maivifi_000");
  Maivifi_000->setPropertyV(WSNvis,(WSCbool)1);
  Maivifi_000->setPropertyV(WSNx,(short)270);
  Maivifi_000->setPropertyV(WSNy,(short)30);
  Maivifi_000->setPropertyV(WSNwidth,(unsigned short)80);
  Maivifi_000->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_001 = new  WSCvlabel(Maiinde_012,"Maivlab_001");
      Maivlab_001->initialize();
  Maivlab_001->setPropertyV(WSNuserValue,(long)1);
  Maivlab_001->setPropertyV(WSNlabelString,"Teleport In");
  Maivlab_001->setPropertyV(WSNname,"Maivlab_001");
  Maivlab_001->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_001->setPropertyV(WSNx,(short)180);
  Maivlab_001->setPropertyV(WSNy,(short)205);
  Maivlab_001->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_001->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_002 = new  WSCvlabel(Maiinde_012,"Maivlab_002");
      Maivlab_002->initialize();
  Maivlab_002->setPropertyV(WSNuserValue,(long)1);
  Maivlab_002->setPropertyV(WSNlabelString,"Teleport Out");
  Maivlab_002->setPropertyV(WSNname,"Maivlab_002");
  Maivlab_002->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_002->setPropertyV(WSNx,(short)180);
  Maivlab_002->setPropertyV(WSNy,(short)230);
  Maivlab_002->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_002->setPropertyV(WSNheight,(unsigned short)25);

  Maivifi_003 = new  WSCvifield(Maiinde_012,"Maivifi_003");
      Maivifi_003->initialize();
  Maivifi_003->setPropertyV(WSNuserValue,(long)1);
  Maivifi_003->setPropertyV(WSNname,"Maivifi_003");
  Maivifi_003->setPropertyV(WSNvis,(WSCbool)1);
  Maivifi_003->setPropertyV(WSNx,(short)270);
  Maivifi_003->setPropertyV(WSNy,(short)55);
  Maivifi_003->setPropertyV(WSNwidth,(unsigned short)80);
  Maivifi_003->setPropertyV(WSNheight,(unsigned short)25);

  Maivifi_004 = new  WSCvifield(Maiinde_012,"Maivifi_004");
      Maivifi_004->initialize();
  Maivifi_004->setPropertyV(WSNuserValue,(long)1);
  Maivifi_004->setPropertyV(WSNname,"Maivifi_004");
  Maivifi_004->setPropertyV(WSNvis,(WSCbool)1);
  Maivifi_004->setPropertyV(WSNx,(short)270);
  Maivifi_004->setPropertyV(WSNy,(short)80);
  Maivifi_004->setPropertyV(WSNwidth,(unsigned short)80);
  Maivifi_004->setPropertyV(WSNheight,(unsigned short)25);

  Maivifi_005 = new  WSCvifield(Maiinde_012,"Maivifi_005");
      Maivifi_005->initialize();
  Maivifi_005->setPropertyV(WSNuserValue,(long)1);
  Maivifi_005->setPropertyV(WSNname,"Maivifi_005");
  Maivifi_005->setPropertyV(WSNvis,(WSCbool)1);
  Maivifi_005->setPropertyV(WSNx,(short)270);
  Maivifi_005->setPropertyV(WSNy,(short)105);
  Maivifi_005->setPropertyV(WSNwidth,(unsigned short)80);
  Maivifi_005->setPropertyV(WSNheight,(unsigned short)25);

  Maivifi_006 = new  WSCvifield(Maiinde_012,"Maivifi_006");
      Maivifi_006->initialize();
  Maivifi_006->setPropertyV(WSNuserValue,(long)1);
  Maivifi_006->setPropertyV(WSNname,"Maivifi_006");
  Maivifi_006->setPropertyV(WSNvis,(WSCbool)1);
  Maivifi_006->setPropertyV(WSNx,(short)270);
  Maivifi_006->setPropertyV(WSNy,(short)130);
  Maivifi_006->setPropertyV(WSNwidth,(unsigned short)80);
  Maivifi_006->setPropertyV(WSNheight,(unsigned short)25);

  Maivifi_007 = new  WSCvifield(Maiinde_012,"Maivifi_007");
      Maivifi_007->initialize();
  Maivifi_007->setPropertyV(WSNuserValue,(long)1);
  Maivifi_007->setPropertyV(WSNname,"Maivifi_007");
  Maivifi_007->setPropertyV(WSNvis,(WSCbool)1);
  Maivifi_007->setPropertyV(WSNx,(short)270);
  Maivifi_007->setPropertyV(WSNy,(short)155);
  Maivifi_007->setPropertyV(WSNwidth,(unsigned short)80);
  Maivifi_007->setPropertyV(WSNheight,(unsigned short)25);

  Maivifi_008 = new  WSCvifield(Maiinde_012,"Maivifi_008");
      Maivifi_008->initialize();
  Maivifi_008->setPropertyV(WSNuserValue,(long)1);
  Maivifi_008->setPropertyV(WSNname,"Maivifi_008");
  Maivifi_008->setPropertyV(WSNvis,(WSCbool)1);
  Maivifi_008->setPropertyV(WSNx,(short)270);
  Maivifi_008->setPropertyV(WSNy,(short)180);
  Maivifi_008->setPropertyV(WSNwidth,(unsigned short)80);
  Maivifi_008->setPropertyV(WSNheight,(unsigned short)25);

  Maivifi_009 = new  WSCvifield(Maiinde_012,"Maivifi_009");
      Maivifi_009->initialize();
  Maivifi_009->setPropertyV(WSNuserValue,(long)1);
  Maivifi_009->setPropertyV(WSNname,"Maivifi_009");
  Maivifi_009->setPropertyV(WSNvis,(WSCbool)1);
  Maivifi_009->setPropertyV(WSNx,(short)270);
  Maivifi_009->setPropertyV(WSNy,(short)205);
  Maivifi_009->setPropertyV(WSNwidth,(unsigned short)80);
  Maivifi_009->setPropertyV(WSNheight,(unsigned short)25);

  Maivifi_010 = new  WSCvifield(Maiinde_012,"Maivifi_010");
      Maivifi_010->initialize();
  Maivifi_010->setPropertyV(WSNuserValue,(long)1);
  Maivifi_010->setPropertyV(WSNname,"Maivifi_010");
  Maivifi_010->setPropertyV(WSNvis,(WSCbool)1);
  Maivifi_010->setPropertyV(WSNx,(short)270);
  Maivifi_010->setPropertyV(WSNy,(short)230);
  Maivifi_010->setPropertyV(WSNwidth,(unsigned short)80);
  Maivifi_010->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_005 = new  WSCvlabel(Maiinde_012,"Maivlab_005");
      Maivlab_005->initialize();
  Maivlab_005->setPropertyV(WSNuserValue,(long)1);
  Maivlab_005->setPropertyV(WSNlabelString,"SoundPitch");
  Maivlab_005->setPropertyV(WSNname,"Maivlab_005");
  Maivlab_005->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_005->setPropertyV(WSNx,(short)350);
  Maivlab_005->setPropertyV(WSNy,(short)30);
  Maivlab_005->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_005->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_006 = new  WSCvlabel(Maiinde_012,"Maivlab_006");
      Maivlab_006->initialize();
  Maivlab_006->setPropertyV(WSNuserValue,(long)1);
  Maivlab_006->setPropertyV(WSNlabelString,"ActivationSnd");
  Maivlab_006->setPropertyV(WSNname,"Maivlab_006");
  Maivlab_006->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_006->setPropertyV(WSNx,(short)350);
  Maivlab_006->setPropertyV(WSNy,(short)55);
  Maivlab_006->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_007 = new  WSCvlabel(Maiinde_012,"Maivlab_007");
      Maivlab_007->initialize();
  Maivlab_007->setPropertyV(WSNuserValue,(long)1);
  Maivlab_007->setPropertyV(WSNlabelString,"FriendActSnd");
  Maivlab_007->setPropertyV(WSNname,"Maivlab_007");
  Maivlab_007->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_007->setPropertyV(WSNx,(short)350);
  Maivlab_007->setPropertyV(WSNy,(short)80);
  Maivlab_007->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_008 = new  WSCvlabel(Maiinde_012,"Maivlab_008");
      Maivlab_008->initialize();
  Maivlab_008->setPropertyV(WSNuserValue,(long)1);
  Maivlab_008->setPropertyV(WSNlabelString,"ClearSnd");
  Maivlab_008->setPropertyV(WSNname,"Maivlab_008");
  Maivlab_008->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_008->setPropertyV(WSNx,(short)350);
  Maivlab_008->setPropertyV(WSNy,(short)105);
  Maivlab_008->setPropertyV(WSNheight,(unsigned short)25);

  Maiopti_009 = new  WSCoption(Maiinde_012,"Maiopti_009");
      Maiopti_009->initialize();
  Maiopti_009->setPropertyV(WSNuserValue,(long)1);
  Maiopti_009->setPropertyV(WSNvalue,(long)1);
  Maiopti_009->setPropertyV(WSNlabelString,"item1");
  Maiopti_009->setPropertyV(WSNname,"Maiopti_009");
  Maiopti_009->setPropertyV(WSNvis,(WSCbool)1);
  Maiopti_009->setPropertyV(WSNx,(short)450);
  Maiopti_009->setPropertyV(WSNy,(short)55);
  Maiopti_009->setPropertyV(WSNwidth,(unsigned short)80);
  Maiopti_009->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_010 = new  WSCvlabel(Maiinde_012,"Maivlab_010");
      Maivlab_010->initialize();
  Maivlab_010->setPropertyV(WSNuserValue,(long)1);
  Maivlab_010->setPropertyV(WSNlabelString,"KillSnd");
  Maivlab_010->setPropertyV(WSNname,"Maivlab_010");
  Maivlab_010->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_010->setPropertyV(WSNx,(short)350);
  Maivlab_010->setPropertyV(WSNy,(short)130);
  Maivlab_010->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_011 = new  WSCvlabel(Maiinde_012,"Maivlab_011");
      Maivlab_011->initialize();
  Maivlab_011->setPropertyV(WSNuserValue,(long)1);
  Maivlab_011->setPropertyV(WSNlabelString,"ApologySnd");
  Maivlab_011->setPropertyV(WSNname,"Maivlab_011");
  Maivlab_011->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_011->setPropertyV(WSNx,(short)350);
  Maivlab_011->setPropertyV(WSNy,(short)155);
  Maivlab_011->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_012 = new  WSCvlabel(Maiinde_012,"Maivlab_012");
      Maivlab_012->initialize();
  Maivlab_012->setPropertyV(WSNuserValue,(long)1);
  Maivlab_012->setPropertyV(WSNlabelString,"FriendFireSnd");
  Maivlab_012->setPropertyV(WSNname,"Maivlab_012");
  Maivlab_012->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_012->setPropertyV(WSNx,(short)350);
  Maivlab_012->setPropertyV(WSNy,(short)180);
  Maivlab_012->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_013 = new  WSCvlabel(Maiinde_012,"Maivlab_013");
      Maivlab_013->initialize();
  Maivlab_013->setPropertyV(WSNuserValue,(long)1);
  Maivlab_013->setPropertyV(WSNlabelString,"FlamingSnd");
  Maivlab_013->setPropertyV(WSNname,"Maivlab_013");
  Maivlab_013->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_013->setPropertyV(WSNx,(short)350);
  Maivlab_013->setPropertyV(WSNy,(short)205);
  Maivlab_013->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_015 = new  WSCvlabel(Maiinde_012,"Maivlab_015");
      Maivlab_015->initialize();
  Maivlab_015->setPropertyV(WSNuserValue,(long)1);
  Maivlab_015->setPropertyV(WSNlabelString,"RandomSnd");
  Maivlab_015->setPropertyV(WSNname,"Maivlab_015");
  Maivlab_015->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_015->setPropertyV(WSNx,(short)350);
  Maivlab_015->setPropertyV(WSNy,(short)230);
  Maivlab_015->setPropertyV(WSNheight,(unsigned short)25);

  Maiopti_017 = new  WSCoption(Maiinde_012,"Maiopti_017");
      Maiopti_017->initialize();
  Maiopti_017->setPropertyV(WSNuserValue,(long)1);
  Maiopti_017->setPropertyV(WSNvalue,(long)1);
  Maiopti_017->setPropertyV(WSNlabelString,"item1");
  Maiopti_017->setPropertyV(WSNname,"Maiopti_017");
  Maiopti_017->setPropertyV(WSNvis,(WSCbool)1);
  Maiopti_017->setPropertyV(WSNx,(short)450);
  Maiopti_017->setPropertyV(WSNy,(short)80);
  Maiopti_017->setPropertyV(WSNwidth,(unsigned short)80);
  Maiopti_017->setPropertyV(WSNheight,(unsigned short)25);

  Maiopti_018 = new  WSCoption(Maiinde_012,"Maiopti_018");
      Maiopti_018->initialize();
  Maiopti_018->setPropertyV(WSNuserValue,(long)1);
  Maiopti_018->setPropertyV(WSNvalue,(long)1);
  Maiopti_018->setPropertyV(WSNlabelString,"item1");
  Maiopti_018->setPropertyV(WSNname,"Maiopti_018");
  Maiopti_018->setPropertyV(WSNvis,(WSCbool)1);
  Maiopti_018->setPropertyV(WSNx,(short)450);
  Maiopti_018->setPropertyV(WSNy,(short)105);
  Maiopti_018->setPropertyV(WSNwidth,(unsigned short)80);
  Maiopti_018->setPropertyV(WSNheight,(unsigned short)25);

  Maiopti_020 = new  WSCoption(Maiinde_012,"Maiopti_020");
      Maiopti_020->initialize();
  Maiopti_020->setPropertyV(WSNuserValue,(long)1);
  Maiopti_020->setPropertyV(WSNvalue,(long)1);
  Maiopti_020->setPropertyV(WSNlabelString,"item1");
  Maiopti_020->setPropertyV(WSNname,"Maiopti_020");
  Maiopti_020->setPropertyV(WSNvis,(WSCbool)1);
  Maiopti_020->setPropertyV(WSNx,(short)450);
  Maiopti_020->setPropertyV(WSNy,(short)130);
  Maiopti_020->setPropertyV(WSNwidth,(unsigned short)80);
  Maiopti_020->setPropertyV(WSNheight,(unsigned short)25);

  Maiopti_021 = new  WSCoption(Maiinde_012,"Maiopti_021");
      Maiopti_021->initialize();
  Maiopti_021->setPropertyV(WSNuserValue,(long)1);
  Maiopti_021->setPropertyV(WSNvalue,(long)1);
  Maiopti_021->setPropertyV(WSNlabelString,"item1");
  Maiopti_021->setPropertyV(WSNname,"Maiopti_021");
  Maiopti_021->setPropertyV(WSNvis,(WSCbool)1);
  Maiopti_021->setPropertyV(WSNx,(short)450);
  Maiopti_021->setPropertyV(WSNy,(short)155);
  Maiopti_021->setPropertyV(WSNwidth,(unsigned short)80);
  Maiopti_021->setPropertyV(WSNheight,(unsigned short)25);

  Maiopti_022 = new  WSCoption(Maiinde_012,"Maiopti_022");
      Maiopti_022->initialize();
  Maiopti_022->setPropertyV(WSNuserValue,(long)1);
  Maiopti_022->setPropertyV(WSNvalue,(long)1);
  Maiopti_022->setPropertyV(WSNlabelString,"item1");
  Maiopti_022->setPropertyV(WSNname,"Maiopti_022");
  Maiopti_022->setPropertyV(WSNvis,(WSCbool)1);
  Maiopti_022->setPropertyV(WSNx,(short)450);
  Maiopti_022->setPropertyV(WSNy,(short)180);
  Maiopti_022->setPropertyV(WSNwidth,(unsigned short)80);
  Maiopti_022->setPropertyV(WSNheight,(unsigned short)25);

  Maiopti_023 = new  WSCoption(Maiinde_012,"Maiopti_023");
      Maiopti_023->initialize();
  Maiopti_023->setPropertyV(WSNuserValue,(long)1);
  Maiopti_023->setPropertyV(WSNvalue,(long)1);
  Maiopti_023->setPropertyV(WSNlabelString,"item1");
  Maiopti_023->setPropertyV(WSNname,"Maiopti_023");
  Maiopti_023->setPropertyV(WSNvis,(WSCbool)1);
  Maiopti_023->setPropertyV(WSNx,(short)450);
  Maiopti_023->setPropertyV(WSNy,(short)205);
  Maiopti_023->setPropertyV(WSNwidth,(unsigned short)80);
  Maiopti_023->setPropertyV(WSNheight,(unsigned short)25);

  Maiopti_025 = new  WSCoption(Maiinde_012,"Maiopti_025");
      Maiopti_025->initialize();
  Maiopti_025->setPropertyV(WSNuserValue,(long)1);
  Maiopti_025->setPropertyV(WSNvalue,(long)1);
  Maiopti_025->setPropertyV(WSNlabelString,"item1");
  Maiopti_025->setPropertyV(WSNname,"Maiopti_025");
  Maiopti_025->setPropertyV(WSNvis,(WSCbool)1);
  Maiopti_025->setPropertyV(WSNx,(short)450);
  Maiopti_025->setPropertyV(WSNy,(short)230);
  Maiopti_025->setPropertyV(WSNwidth,(unsigned short)80);
  Maiopti_025->setPropertyV(WSNheight,(unsigned short)25);

  Maivifi_026 = new  WSCvifield(Maiinde_012,"Maivifi_026");
      Maivifi_026->initialize();
  Maivifi_026->setPropertyV(WSNuserValue,(long)1);
  Maivifi_026->setPropertyV(WSNname,"Maivifi_026");
  Maivifi_026->setPropertyV(WSNvis,(WSCbool)1);
  Maivifi_026->setPropertyV(WSNx,(short)440);
  Maivifi_026->setPropertyV(WSNy,(short)30);
  Maivifi_026->setPropertyV(WSNwidth,(unsigned short)80);
  Maivifi_026->setPropertyV(WSNheight,(unsigned short)25);

  Maivifi_027 = new  WSCvifield(Maiinde_012,"Maivifi_027");
      Maivifi_027->initialize();
  Maivifi_027->setPropertyV(WSNuserValue,(long)1);
  Maivifi_027->setPropertyV(WSNname,"Maivifi_027");
  Maivifi_027->setPropertyV(WSNvis,(WSCbool)1);
  Maivifi_027->setPropertyV(WSNx,(short)450);
  Maivifi_027->setPropertyV(WSNy,(short)255);
  Maivifi_027->setPropertyV(WSNwidth,(unsigned short)80);
  Maivifi_027->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_028 = new  WSCvlabel(Maiinde_012,"Maivlab_028");
      Maivlab_028->initialize();
  Maivlab_028->setPropertyV(WSNuserValue,(long)1);
  Maivlab_028->setPropertyV(WSNlabelString,"RandomSndMask");
  Maivlab_028->setPropertyV(WSNname,"Maivlab_028");
  Maivlab_028->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_028->setPropertyV(WSNx,(short)350);
  Maivlab_028->setPropertyV(WSNy,(short)255);
  Maivlab_028->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_029 = new  WSCvlabel(Maiinde_012,"Maivlab_029");
      Maivlab_029->initialize();
  Maivlab_029->setPropertyV(WSNuserValue,(long)1);
  Maivlab_029->setPropertyV(WSNlabelString,"Teleport Out");
  Maivlab_029->setPropertyV(WSNname,"Maivlab_029");
  Maivlab_029->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_029->setPropertyV(WSNx,(short)180);
  Maivlab_029->setPropertyV(WSNy,(short)255);
  Maivlab_029->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_029->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_035 = new  WSCvlabel(Maiinde_012,"Maivlab_035");
      Maivlab_035->initialize();
  Maivlab_035->setPropertyV(WSNuserValue,(long)1);
  Maivlab_035->setPropertyV(WSNlabelString,"Teleport Out");
  Maivlab_035->setPropertyV(WSNname,"Maivlab_035");
  Maivlab_035->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_035->setPropertyV(WSNx,(short)180);
  Maivlab_035->setPropertyV(WSNy,(short)280);
  Maivlab_035->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_035->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_036 = new  WSCvlabel(Maiinde_012,"Maivlab_036");
      Maivlab_036->initialize();
  Maivlab_036->setPropertyV(WSNuserValue,(long)1);
  Maivlab_036->setPropertyV(WSNlabelString,"Teleport Out");
  Maivlab_036->setPropertyV(WSNname,"Maivlab_036");
  Maivlab_036->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_036->setPropertyV(WSNx,(short)180);
  Maivlab_036->setPropertyV(WSNy,(short)305);
  Maivlab_036->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_036->setPropertyV(WSNheight,(unsigned short)25);

  HalfVisualArc = new  WSCvlabel(Maiinde_012,"HalfVisualArc");
      HalfVisualArc->initialize();
  HalfVisualArc->setPropertyV(WSNuserValue,(long)1);
  HalfVisualArc->setPropertyV(WSNlabelString,"HalfVisualArc");
  HalfVisualArc->setPropertyV(WSNname,"HalfVisualArc");
  HalfVisualArc->setPropertyV(WSNvis,(WSCbool)1);
  HalfVisualArc->setPropertyV(WSNx,(short)5);
  HalfVisualArc->setPropertyV(WSNy,(short)305);
  HalfVisualArc->setPropertyV(WSNheight,(unsigned short)25);

  VerticalVisualArc = new  WSCvlabel(Maiinde_012,"VerticalVisualArc");
      VerticalVisualArc->initialize();
  VerticalVisualArc->setPropertyV(WSNuserValue,(long)1);
  VerticalVisualArc->setPropertyV(WSNlabelString,"VertVisualArc");
  VerticalVisualArc->setPropertyV(WSNname,"VerticalVisualArc");
  VerticalVisualArc->setPropertyV(WSNvis,(WSCbool)1);
  VerticalVisualArc->setPropertyV(WSNx,(short)5);
  VerticalVisualArc->setPropertyV(WSNy,(short)330);
  VerticalVisualArc->setPropertyV(WSNheight,(unsigned short)25);

  Intelligence = new  WSCvlabel(Maiinde_012,"Intelligence");
      Intelligence->initialize();
  Intelligence->setPropertyV(WSNuserValue,(long)1);
  Intelligence->setPropertyV(WSNlabelString,"Intelligence");
  Intelligence->setPropertyV(WSNname,"Intelligence");
  Intelligence->setPropertyV(WSNvis,(WSCbool)1);
  Intelligence->setPropertyV(WSNx,(short)5);
  Intelligence->setPropertyV(WSNy,(short)355);
  Intelligence->setPropertyV(WSNwidth,(unsigned short)90);
  Intelligence->setPropertyV(WSNheight,(unsigned short)25);

  Speed = new  WSCvlabel(Maiinde_012,"Speed");
      Speed->initialize();
  Speed->setPropertyV(WSNuserValue,(long)1);
  Speed->setPropertyV(WSNlabelString,"Speed");
  Speed->setPropertyV(WSNname,"Speed");
  Speed->setPropertyV(WSNvis,(WSCbool)1);
  Speed->setPropertyV(WSNx,(short)5);
  Speed->setPropertyV(WSNy,(short)380);
  Speed->setPropertyV(WSNwidth,(unsigned short)90);
  Speed->setPropertyV(WSNheight,(unsigned short)25);

  Gravity = new  WSCvlabel(Maiinde_012,"Gravity");
      Gravity->initialize();
  Gravity->setPropertyV(WSNuserValue,(long)1);
  Gravity->setPropertyV(WSNlabelString,"Gravity");
  Gravity->setPropertyV(WSNname,"Gravity");
  Gravity->setPropertyV(WSNvis,(WSCbool)1);
  Gravity->setPropertyV(WSNx,(short)5);
  Gravity->setPropertyV(WSNy,(short)405);
  Gravity->setPropertyV(WSNwidth,(unsigned short)90);
  Gravity->setPropertyV(WSNheight,(unsigned short)25);

  HalfVisualArcEdit = new  WSCvifield(Maiinde_012,"HalfVisualArcEdit");
      HalfVisualArcEdit->initialize();
  HalfVisualArcEdit->setPropertyV(WSNuserValue,(long)1);
  HalfVisualArcEdit->setPropertyV(WSNname,"HalfVisualArcEdit");
  HalfVisualArcEdit->setPropertyV(WSNvis,(WSCbool)1);
  HalfVisualArcEdit->setPropertyV(WSNx,(short)105);
  HalfVisualArcEdit->setPropertyV(WSNy,(short)305);
  HalfVisualArcEdit->setPropertyV(WSNwidth,(unsigned short)70);
  HalfVisualArcEdit->setPropertyV(WSNheight,(unsigned short)25);

  VertVisualArc = new  WSCvifield(Maiinde_012,"VertVisualArc");
      VertVisualArc->initialize();
  VertVisualArc->setPropertyV(WSNuserValue,(long)1);
  VertVisualArc->setPropertyV(WSNname,"VertVisualArc");
  VertVisualArc->setPropertyV(WSNvis,(WSCbool)1);
  VertVisualArc->setPropertyV(WSNx,(short)105);
  VertVisualArc->setPropertyV(WSNy,(short)330);
  VertVisualArc->setPropertyV(WSNwidth,(unsigned short)70);
  VertVisualArc->setPropertyV(WSNheight,(unsigned short)25);

  SpeedEdit = new  WSCvifield(Maiinde_012,"SpeedEdit");
      SpeedEdit->initialize();
  SpeedEdit->setPropertyV(WSNuserValue,(long)1);
  SpeedEdit->setPropertyV(WSNname,"SpeedEdit");
  SpeedEdit->setPropertyV(WSNvis,(WSCbool)1);
  SpeedEdit->setPropertyV(WSNx,(short)95);
  SpeedEdit->setPropertyV(WSNy,(short)380);
  SpeedEdit->setPropertyV(WSNwidth,(unsigned short)80);
  SpeedEdit->setPropertyV(WSNheight,(unsigned short)25);

  GravityEdit = new  WSCvifield(Maiinde_012,"GravityEdit");
      GravityEdit->initialize();
  GravityEdit->setPropertyV(WSNuserValue,(long)1);
  GravityEdit->setPropertyV(WSNname,"GravityEdit");
  GravityEdit->setPropertyV(WSNvis,(WSCbool)1);
  GravityEdit->setPropertyV(WSNx,(short)95);
  GravityEdit->setPropertyV(WSNy,(short)405);
  GravityEdit->setPropertyV(WSNwidth,(unsigned short)80);
  GravityEdit->setPropertyV(WSNheight,(unsigned short)25);

  SpeedCombo = new  WSCoption(Maiinde_012,"SpeedCombo");
      SpeedCombo->initialize();
  SpeedCombo->setPropertyV(WSNuserValue,(long)1);
  SpeedCombo->setPropertyV(WSNvalue,(long)1);
  SpeedCombo->setPropertyV(WSNlabelString,"item1");
  SpeedCombo->setPropertyV(WSNname,"SpeedCombo");
  SpeedCombo->setPropertyV(WSNvis,(WSCbool)1);
  SpeedCombo->setPropertyV(WSNx,(short)175);
  SpeedCombo->setPropertyV(WSNy,(short)380);
  SpeedCombo->setPropertyV(WSNwidth,(unsigned short)80);
  SpeedCombo->setPropertyV(WSNheight,(unsigned short)25);

  IntelligenceCombo = new  WSCoption(Maiinde_012,"IntelligenceCombo");
      IntelligenceCombo->initialize();
  IntelligenceCombo->setPropertyV(WSNuserValue,(long)1);
  IntelligenceCombo->setPropertyV(WSNmenuItems,"Low:1:IntelligenceLow,Average:2:IntelligenceAverage,High:3:IntelligenceHigh");
  IntelligenceCombo->setPropertyV(WSNvalue,(long)1);
  IntelligenceCombo->setPropertyV(WSNlabelString,"Low");
  IntelligenceCombo->setPropertyV(WSNname,"IntelligenceCombo");
  IntelligenceCombo->setPropertyV(WSNvis,(WSCbool)1);
  IntelligenceCombo->setPropertyV(WSNx,(short)95);
  IntelligenceCombo->setPropertyV(WSNy,(short)355);
  IntelligenceCombo->setPropertyV(WSNwidth,(unsigned short)80);
  IntelligenceCombo->setPropertyV(WSNheight,(unsigned short)25);

  ListImmunities = new  WSClist(Maiinde_012,"ListImmunities");
      ListImmunities->initialize();
  ListImmunities->setPropertyV(WSNuserValue,(long)2);
  ListImmunities->setPropertyV(WSNmultiSelect,(WSCbool)1);
  ListImmunities->setPropertyV(WSNtitleString,"Immunities");
  ListImmunities->setPropertyV(WSNdataSource,(unsigned char)2);
  ListImmunities->setPropertyV(WSNdataSourceName,"data/WSImmunitiesWeaknesses.txt");
  ListImmunities->setPropertyV(WSNworkWidth,(unsigned short)200);
  ListImmunities->setPropertyV(WSNworkHeight,(unsigned short)480);
  ListImmunities->setPropertyV(WSNhbarVisible,(WSCbool)1);
  ListImmunities->setPropertyV(WSNname,"ListImmunities");
  ListImmunities->setPropertyV(WSNx,(short)0);
  ListImmunities->setPropertyV(WSNy,(short)50);
  ListImmunities->setPropertyV(WSNwidth,(unsigned short)115);
  ListImmunities->setPropertyV(WSNheight,(unsigned short)405);

  Maivlab_003 = new  WSCvlabel(Maiinde_012,"Maivlab_003");
      Maivlab_003->initialize();
  Maivlab_003->setPropertyV(WSNuserValue,(long)2);
  Maivlab_003->setPropertyV(WSNlabelString,"Immunities");
  Maivlab_003->setPropertyV(WSNname,"Maivlab_003");
  Maivlab_003->setPropertyV(WSNy,(short)25);
  Maivlab_003->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_003->setPropertyV(WSNheight,(unsigned short)25);

  Mailist_004 = new  WSClist(Maiinde_012,"Mailist_004");
      Mailist_004->initialize();
  Mailist_004->setPropertyV(WSNuserValue,(long)2);
  Mailist_004->setPropertyV(WSNmultiSelect,(WSCbool)1);
  Mailist_004->setPropertyV(WSNtitleString,"Immunities");
  Mailist_004->setPropertyV(WSNdataSource,(unsigned char)2);
  Mailist_004->setPropertyV(WSNdataSourceName,"data/WSImmunitiesWeaknesses.txt");
  Mailist_004->setPropertyV(WSNworkWidth,(unsigned short)200);
  Mailist_004->setPropertyV(WSNworkHeight,(unsigned short)480);
  Mailist_004->setPropertyV(WSNhbarVisible,(WSCbool)1);
  Mailist_004->setPropertyV(WSNname,"Mailist_004");
  Mailist_004->setPropertyV(WSNx,(short)115);
  Mailist_004->setPropertyV(WSNy,(short)50);
  Mailist_004->setPropertyV(WSNwidth,(unsigned short)110);
  Mailist_004->setPropertyV(WSNheight,(unsigned short)405);

  Maivlab_009 = new  WSCvlabel(Maiinde_012,"Maivlab_009");
      Maivlab_009->initialize();
  Maivlab_009->setPropertyV(WSNuserValue,(long)2);
  Maivlab_009->setPropertyV(WSNlabelString,"Weaknesses");
  Maivlab_009->setPropertyV(WSNname,"Maivlab_009");
  Maivlab_009->setPropertyV(WSNx,(short)115);
  Maivlab_009->setPropertyV(WSNy,(short)25);
  Maivlab_009->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_009->setPropertyV(WSNheight,(unsigned short)25);

  Mailist_010 = new  WSClist(Maiinde_012,"Mailist_010");
      Mailist_010->initialize();
  Mailist_010->setPropertyV(WSNuserValue,(long)2);
  Mailist_010->setPropertyV(WSNmultiSelect,(WSCbool)1);
  Mailist_010->setPropertyV(WSNtitleString,"Immunities");
  Mailist_010->setPropertyV(WSNdataSource,(unsigned char)2);
  Mailist_010->setPropertyV(WSNdataSourceName,"data/WSEnemiesFriends.txt");
  Mailist_010->setPropertyV(WSNworkWidth,(unsigned short)200);
  Mailist_010->setPropertyV(WSNworkHeight,(unsigned short)385);
  Mailist_010->setPropertyV(WSNhbarVisible,(WSCbool)1);
  Mailist_010->setPropertyV(WSNname,"Mailist_010");
  Mailist_010->setPropertyV(WSNx,(short)235);
  Mailist_010->setPropertyV(WSNy,(short)50);
  Mailist_010->setPropertyV(WSNwidth,(unsigned short)80);
  Mailist_010->setPropertyV(WSNheight,(unsigned short)405);

  Maivlab_016 = new  WSCvlabel(Maiinde_012,"Maivlab_016");
      Maivlab_016->initialize();
  Maivlab_016->setPropertyV(WSNuserValue,(long)2);
  Maivlab_016->setPropertyV(WSNlabelString,"Enemies");
  Maivlab_016->setPropertyV(WSNname,"Maivlab_016");
  Maivlab_016->setPropertyV(WSNx,(short)235);
  Maivlab_016->setPropertyV(WSNy,(short)25);
  Maivlab_016->setPropertyV(WSNwidth,(unsigned short)80);
  Maivlab_016->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_017 = new  WSCvlabel(Maiinde_012,"Maivlab_017");
      Maivlab_017->initialize();
  Maivlab_017->setPropertyV(WSNuserValue,(long)2);
  Maivlab_017->setPropertyV(WSNlabelString,"Friends");
  Maivlab_017->setPropertyV(WSNname,"Maivlab_017");
  Maivlab_017->setPropertyV(WSNx,(short)315);
  Maivlab_017->setPropertyV(WSNy,(short)25);
  Maivlab_017->setPropertyV(WSNwidth,(unsigned short)80);
  Maivlab_017->setPropertyV(WSNheight,(unsigned short)25);

  Mailist_018 = new  WSClist(Maiinde_012,"Mailist_018");
      Mailist_018->initialize();
  Mailist_018->setPropertyV(WSNuserValue,(long)2);
  Mailist_018->setPropertyV(WSNmultiSelect,(WSCbool)1);
  Mailist_018->setPropertyV(WSNtitleString,"Immunities");
  Mailist_018->setPropertyV(WSNdataSource,(unsigned char)2);
  Mailist_018->setPropertyV(WSNdataSourceName,"data/WSEnemiesFriends.txt");
  Mailist_018->setPropertyV(WSNworkWidth,(unsigned short)200);
  Mailist_018->setPropertyV(WSNworkHeight,(unsigned short)385);
  Mailist_018->setPropertyV(WSNhbarVisible,(WSCbool)1);
  Mailist_018->setPropertyV(WSNname,"Mailist_018");
  Mailist_018->setPropertyV(WSNx,(short)315);
  Mailist_018->setPropertyV(WSNy,(short)50);
  Mailist_018->setPropertyV(WSNwidth,(unsigned short)80);
  Mailist_018->setPropertyV(WSNheight,(unsigned short)405);

  Mailist_019 = new  WSClist(Maiinde_012,"Mailist_019");
      Mailist_019->initialize();
  Mailist_019->setPropertyV(WSNuserValue,(long)2);
  Mailist_019->setPropertyV(WSNmultiSelect,(WSCbool)1);
  Mailist_019->setPropertyV(WSNtitleString,"Immunities");
  Mailist_019->setPropertyV(WSNdataSource,(unsigned char)2);
  Mailist_019->setPropertyV(WSNdataSourceName,"data/WSFlags.txt");
  Mailist_019->setPropertyV(WSNworkWidth,(unsigned short)200);
  Mailist_019->setPropertyV(WSNworkHeight,(unsigned short)560);
  Mailist_019->setPropertyV(WSNhbarVisible,(WSCbool)1);
  Mailist_019->setPropertyV(WSNname,"Mailist_019");
  Mailist_019->setPropertyV(WSNx,(short)400);
  Mailist_019->setPropertyV(WSNy,(short)50);
  Mailist_019->setPropertyV(WSNwidth,(unsigned short)155);
  Mailist_019->setPropertyV(WSNheight,(unsigned short)365);

  Maivbtn_020 = new  WSCvbtn(Maiinde_012,"Maivbtn_020");
      Maivbtn_020->initialize();
  Maivbtn_020->setPropertyV(WSNuserValue,(long)2);
  Maivbtn_020->setPropertyV(WSNlabelString,"Set as Default");
  Maivbtn_020->setPropertyV(WSNname,"Maivbtn_020");
  Maivbtn_020->setPropertyV(WSNx,(short)430);
  Maivbtn_020->setPropertyV(WSNy,(short)425);
  Maivbtn_020->setPropertyV(WSNwidth,(unsigned short)115);

  ListMonsterType = new  WSClist(WndMonster,"ListMonsterType");
      ListMonsterType->initialize();
  ListMonsterType->setPropertyV(WSNtitleString,"");
  ListMonsterType->setPropertyV(WSNdataSource,(unsigned char)2);
  ListMonsterType->setPropertyV(WSNdataSourceName,"data/MonsterTypes.txt");
  ListMonsterType->setPropertyV(WSNworkWidth,(unsigned short)300);
  ListMonsterType->setPropertyV(WSNworkHeight,(unsigned short)940);
  ListMonsterType->setPropertyV(WSNhbarVisible,(WSCbool)1);
  ListMonsterType->setPropertyV(WSNname,"ListMonsterType");
  ListMonsterType->setPropertyV(WSNx,(short)5);
  ListMonsterType->setPropertyV(WSNy,(short)5);
  ListMonsterType->setPropertyV(WSNwidth,(unsigned short)105);
  ListMonsterType->setPropertyV(WSNheight,(unsigned short)450);
  ListMonsterType->setPropertyV(WSNvis,(WSCbool)1);

   MainWindow->setVisible(True);
   return MainWindow;
}

//--- end of src ---//
