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
#include <WSCdialog.h>

//--- OBJECT instance variable ---//
WSCmainWindow* MainWindow = NULL;
WSCmenuArea* Maimenu_000 = NULL;
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
WSCvifield* Maivifi_068 = NULL;
WSCvifield* Maivifi_069 = NULL;
WSCvifield* Maivifi_070 = NULL;
WSCvifield* Maivifi_071 = NULL;
WSCvifield* Maivifi_072 = NULL;
WSCvlabel* Maivlab_073 = NULL;
WSCvlabel* Maivlab_074 = NULL;
WSCvlabel* Maivlab_075 = NULL;
WSCvlabel* Maivlab_076 = NULL;
WSCvlabel* Maivlab_077 = NULL;
WSCvlabel* Maivlab_078 = NULL;
WSCvlabel* Maivlab_079 = NULL;
WSCvlabel* Maivlab_080 = NULL;
WSCvlabel* Maivlab_081 = NULL;
WSCvifield* Maivifi_082 = NULL;
WSCvifield* Maivifi_083 = NULL;
WSCvlabel* Maivlab_084 = NULL;
WSCvlabel* Maivlab_085 = NULL;
WSCvlabel* Maivlab_086 = NULL;
WSCvlabel* Maivlab_087 = NULL;
WSCvlabel* Maivlab_088 = NULL;
WSCvlabel* Maivlab_089 = NULL;
WSCvlabel* Maivlab_090 = NULL;
WSCvlabel* Maivlab_091 = NULL;
WSCvlabel* Maivlab_092 = NULL;
WSCvifield* Maivifi_093 = NULL;
WSCvifield* Maivifi_094 = NULL;
WSCvifield* Maivifi_095 = NULL;
WSCvifield* Maivifi_096 = NULL;
WSClist* Mailist_097 = NULL;
WSCvlabel* Maivlab_098 = NULL;
WSClist* Mailist_099 = NULL;
WSCvlabel* Maivlab_100 = NULL;
WSClist* Mailist_101 = NULL;
WSCvlabel* Maivlab_102 = NULL;
WSCvlabel* Maivlab_103 = NULL;
WSClist* Mailist_104 = NULL;
WSClist* Mailist_105 = NULL;
WSCvbtn* Maivbtn_106 = NULL;
WSCoption* Maiopti_107 = NULL;
WSCoption* Maiopti_108 = NULL;
WSCvbtn* Maivbtn_109 = NULL;
WSCvbtn* Maivbtn_110 = NULL;
WSCvbtn* Maivbtn_111 = NULL;
WSCvbtn* Maivbtn_112 = NULL;
WSCvbtn* Maivbtn_113 = NULL;
WSCvbtn* Maivbtn_114 = NULL;
WSCvbtn* Maivbtn_115 = NULL;
WSCvbtn* Maivbtn_116 = NULL;
WSCvbtn* Maivbtn_117 = NULL;
WSCvbtn* Maivbtn_118 = NULL;
WSCoption* Maiopti_119 = NULL;
WSCvbtn* Maivbtn_120 = NULL;
WSCvbtn* Maivbtn_121 = NULL;
WSCvbtn* Maivbtn_122 = NULL;
WSCdialog* WndSelect = NULL;
WSClist* ListSelect = NULL;

//--- OBJECT src ---//

WSCbase* _create_win_MainWindow(){


  MainWindow = new  WSCmainWindow(NULL,"MainWindow");
      MainWindow->initialize();
  MainWindow->setPropertyV(WSNname,"MainWindow");
  MainWindow->setPropertyV(WSNtitleString,"PhysicsEditorWS");
  MainWindow->setPropertyV(WSNx,(short)100);
  MainWindow->setPropertyV(WSNy,(short)100);
  MainWindow->setPropertyV(WSNwidth,(unsigned short)786);
  MainWindow->setPropertyV(WSNheight,(unsigned short)497);
  MainWindow->setPropertyV(WSNvis,(WSCbool)1);
    extern void MainInitFunc(WSCbase*);
    MainWindow->addProcedureV("MainInit","MainInitFunc",MainInitFunc,0);
    extern void MainWindowExitFunc(WSCbase*);
    MainWindow->addProcedureV("MainWindowExit","MainWindowExitFunc",MainWindowExitFunc,32);
    extern void MainWindowCloseFunc(WSCbase*);
    MainWindow->addProcedureV("MainWindowClose","MainWindowCloseFunc",MainWindowCloseFunc,56);

  Maimenu_000 = new  WSCmenuArea(MainWindow,"Maimenu_000");
      Maimenu_000->initialize();
  Maimenu_000->setPropertyV(WSNname,"Maimenu_000");
  Maimenu_000->setPropertyV(WSNx,(short)0);
  Maimenu_000->setPropertyV(WSNy,(short)0);
  Maimenu_000->setPropertyV(WSNwidth,(unsigned short)786);
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

  FrmMonster = new  WSCform(MainWindow,"FrmMonster");
      FrmMonster->initialize();
  FrmMonster->setPropertyV(WSNname,"FrmMonster");
  FrmMonster->setPropertyV(WSNx,(short)95);
  FrmMonster->setPropertyV(WSNy,(short)25);
  FrmMonster->setPropertyV(WSNwidth,(unsigned short)690);
  FrmMonster->setPropertyV(WSNheight,(unsigned short)470);
  FrmMonster->setPropertyV(WSNvis,(WSCbool)1);

  ListMonsterTypes = new  WSClist(FrmMonster,"ListMonsterTypes");
      ListMonsterTypes->initialize();
  ListMonsterTypes->setPropertyV(WSNtitleString,"");
  ListMonsterTypes->setPropertyV(WSNdataSource,(unsigned char)2);
  ListMonsterTypes->setPropertyV(WSNdataSourceName,"data/MonsterTypes.txt");
  ListMonsterTypes->setPropertyV(WSNworkWidth,(unsigned short)300);
  ListMonsterTypes->setPropertyV(WSNworkHeight,(unsigned short)940);
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
  Maivlab_004->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_004->setPropertyV(WSNx,(short)5);
  Maivlab_004->setPropertyV(WSNy,(short)30);
  Maivlab_004->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_004->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_019 = new  WSCvlabel(Maiinde_012,"Maivlab_019");
      Maivlab_019->initialize();
  Maivlab_019->setPropertyV(WSNuserValue,(long)1);
  Maivlab_019->setPropertyV(WSNlabelString,"Pallet");
  Maivlab_019->setPropertyV(WSNname,"Maivlab_019");
  Maivlab_019->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_019->setPropertyV(WSNx,(short)5);
  Maivlab_019->setPropertyV(WSNy,(short)55);
  Maivlab_019->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_019->setPropertyV(WSNheight,(unsigned short)25);

  PalletEdit = new  WSCvifield(Maiinde_012,"PalletEdit");
      PalletEdit->initialize();
  PalletEdit->setPropertyV(WSNuserValue,(long)1);
  PalletEdit->setPropertyV(WSNname,"PalletEdit");
  PalletEdit->setPropertyV(WSNvis,(WSCbool)1);
  PalletEdit->setPropertyV(WSNx,(short)95);
  PalletEdit->setPropertyV(WSNy,(short)55);
  PalletEdit->setPropertyV(WSNwidth,(unsigned short)80);
  PalletEdit->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_022 = new  WSCvlabel(Maiinde_012,"Maivlab_022");
      Maivlab_022->initialize();
  Maivlab_022->setPropertyV(WSNuserValue,(long)1);
  Maivlab_022->setPropertyV(WSNlabelString,"Vitality");
  Maivlab_022->setPropertyV(WSNname,"Maivlab_022");
  Maivlab_022->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_022->setPropertyV(WSNx,(short)5);
  Maivlab_022->setPropertyV(WSNy,(short)80);
  Maivlab_022->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_022->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_024 = new  WSCvlabel(Maiinde_012,"Maivlab_024");
      Maivlab_024->initialize();
  Maivlab_024->setPropertyV(WSNuserValue,(long)1);
  Maivlab_024->setPropertyV(WSNlabelString,"Class");
  Maivlab_024->setPropertyV(WSNname,"Maivlab_024");
  Maivlab_024->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_024->setPropertyV(WSNx,(short)5);
  Maivlab_024->setPropertyV(WSNy,(short)105);
  Maivlab_024->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_024->setPropertyV(WSNheight,(unsigned short)25);

  VitalityEdit = new  WSCvifield(Maiinde_012,"VitalityEdit");
      VitalityEdit->initialize();
  VitalityEdit->setPropertyV(WSNuserValue,(long)1);
  VitalityEdit->setPropertyV(WSNname,"VitalityEdit");
  VitalityEdit->setPropertyV(WSNvis,(WSCbool)1);
  VitalityEdit->setPropertyV(WSNx,(short)95);
  VitalityEdit->setPropertyV(WSNy,(short)80);
  VitalityEdit->setPropertyV(WSNwidth,(unsigned short)80);
  VitalityEdit->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_037 = new  WSCvlabel(Maiinde_012,"Maivlab_037");
      Maivlab_037->initialize();
  Maivlab_037->setPropertyV(WSNuserValue,(long)1);
  Maivlab_037->setPropertyV(WSNlabelString,"Radius");
  Maivlab_037->setPropertyV(WSNname,"Maivlab_037");
  Maivlab_037->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_037->setPropertyV(WSNx,(short)5);
  Maivlab_037->setPropertyV(WSNy,(short)130);
  Maivlab_037->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_037->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_038 = new  WSCvlabel(Maiinde_012,"Maivlab_038");
      Maivlab_038->initialize();
  Maivlab_038->setPropertyV(WSNuserValue,(long)1);
  Maivlab_038->setPropertyV(WSNlabelString,"Height");
  Maivlab_038->setPropertyV(WSNname,"Maivlab_038");
  Maivlab_038->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_038->setPropertyV(WSNx,(short)5);
  Maivlab_038->setPropertyV(WSNy,(short)155);
  Maivlab_038->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_038->setPropertyV(WSNheight,(unsigned short)25);

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

  Maivlab_046 = new  WSCvlabel(Maiinde_012,"Maivlab_046");
      Maivlab_046->initialize();
  Maivlab_046->setPropertyV(WSNuserValue,(long)1);
  Maivlab_046->setPropertyV(WSNlabelString,"Hover");
  Maivlab_046->setPropertyV(WSNname,"Maivlab_046");
  Maivlab_046->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_046->setPropertyV(WSNx,(short)5);
  Maivlab_046->setPropertyV(WSNy,(short)180);
  Maivlab_046->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_046->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_047 = new  WSCvlabel(Maiinde_012,"Maivlab_047");
      Maivlab_047->initialize();
  Maivlab_047->setPropertyV(WSNuserValue,(long)1);
  Maivlab_047->setPropertyV(WSNlabelString,"Min Ledge");
  Maivlab_047->setPropertyV(WSNname,"Maivlab_047");
  Maivlab_047->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_047->setPropertyV(WSNx,(short)5);
  Maivlab_047->setPropertyV(WSNy,(short)205);
  Maivlab_047->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_047->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_048 = new  WSCvlabel(Maiinde_012,"Maivlab_048");
      Maivlab_048->initialize();
  Maivlab_048->setPropertyV(WSNuserValue,(long)1);
  Maivlab_048->setPropertyV(WSNlabelString,"Max Ledge");
  Maivlab_048->setPropertyV(WSNname,"Maivlab_048");
  Maivlab_048->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_048->setPropertyV(WSNx,(short)5);
  Maivlab_048->setPropertyV(WSNy,(short)230);
  Maivlab_048->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_048->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_049 = new  WSCvlabel(Maiinde_012,"Maivlab_049");
      Maivlab_049->initialize();
  Maivlab_049->setPropertyV(WSNuserValue,(long)1);
  Maivlab_049->setPropertyV(WSNlabelString,"ExtVelScale");
  Maivlab_049->setPropertyV(WSNname,"Maivlab_049");
  Maivlab_049->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_049->setPropertyV(WSNx,(short)5);
  Maivlab_049->setPropertyV(WSNy,(short)255);
  Maivlab_049->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_049->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_050 = new  WSCvlabel(Maiinde_012,"Maivlab_050");
      Maivlab_050->initialize();
  Maivlab_050->setPropertyV(WSNuserValue,(long)1);
  Maivlab_050->setPropertyV(WSNlabelString,"CarryItem");
  Maivlab_050->setPropertyV(WSNname,"Maivlab_050");
  Maivlab_050->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_050->setPropertyV(WSNx,(short)5);
  Maivlab_050->setPropertyV(WSNy,(short)280);
  Maivlab_050->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_050->setPropertyV(WSNheight,(unsigned short)25);

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

  Maivlab_055 = new  WSCvlabel(Maiinde_012,"Maivlab_055");
      Maivlab_055->initialize();
  Maivlab_055->setPropertyV(WSNuserValue,(long)1);
  Maivlab_055->setPropertyV(WSNlabelString,"Stationaly");
  Maivlab_055->setPropertyV(WSNname,"Maivlab_055");
  Maivlab_055->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_055->setPropertyV(WSNx,(short)205);
  Maivlab_055->setPropertyV(WSNy,(short)30);
  Maivlab_055->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_055->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_056 = new  WSCvlabel(Maiinde_012,"Maivlab_056");
      Maivlab_056->initialize();
  Maivlab_056->setPropertyV(WSNuserValue,(long)1);
  Maivlab_056->setPropertyV(WSNlabelString,"Moving");
  Maivlab_056->setPropertyV(WSNname,"Maivlab_056");
  Maivlab_056->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_056->setPropertyV(WSNx,(short)205);
  Maivlab_056->setPropertyV(WSNy,(short)55);
  Maivlab_056->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_056->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_057 = new  WSCvlabel(Maiinde_012,"Maivlab_057");
      Maivlab_057->initialize();
  Maivlab_057->setPropertyV(WSNuserValue,(long)1);
  Maivlab_057->setPropertyV(WSNlabelString,"Hitting");
  Maivlab_057->setPropertyV(WSNname,"Maivlab_057");
  Maivlab_057->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_057->setPropertyV(WSNx,(short)205);
  Maivlab_057->setPropertyV(WSNy,(short)80);
  Maivlab_057->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_057->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_058 = new  WSCvlabel(Maiinde_012,"Maivlab_058");
      Maivlab_058->initialize();
  Maivlab_058->setPropertyV(WSNuserValue,(long)1);
  Maivlab_058->setPropertyV(WSNlabelString,"Soft Dying");
  Maivlab_058->setPropertyV(WSNname,"Maivlab_058");
  Maivlab_058->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_058->setPropertyV(WSNx,(short)205);
  Maivlab_058->setPropertyV(WSNy,(short)105);
  Maivlab_058->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_058->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_059 = new  WSCvlabel(Maiinde_012,"Maivlab_059");
      Maivlab_059->initialize();
  Maivlab_059->setPropertyV(WSNuserValue,(long)1);
  Maivlab_059->setPropertyV(WSNlabelString,"Soft Dead");
  Maivlab_059->setPropertyV(WSNname,"Maivlab_059");
  Maivlab_059->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_059->setPropertyV(WSNx,(short)205);
  Maivlab_059->setPropertyV(WSNy,(short)130);
  Maivlab_059->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_059->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_060 = new  WSCvlabel(Maiinde_012,"Maivlab_060");
      Maivlab_060->initialize();
  Maivlab_060->setPropertyV(WSNuserValue,(long)1);
  Maivlab_060->setPropertyV(WSNlabelString,"Hard Dying");
  Maivlab_060->setPropertyV(WSNname,"Maivlab_060");
  Maivlab_060->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_060->setPropertyV(WSNx,(short)205);
  Maivlab_060->setPropertyV(WSNy,(short)155);
  Maivlab_060->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_060->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_061 = new  WSCvlabel(Maiinde_012,"Maivlab_061");
      Maivlab_061->initialize();
  Maivlab_061->setPropertyV(WSNuserValue,(long)1);
  Maivlab_061->setPropertyV(WSNlabelString,"Hard Dead");
  Maivlab_061->setPropertyV(WSNname,"Maivlab_061");
  Maivlab_061->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_061->setPropertyV(WSNx,(short)205);
  Maivlab_061->setPropertyV(WSNy,(short)180);
  Maivlab_061->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_061->setPropertyV(WSNheight,(unsigned short)25);

  SeqStationaly = new  WSCvifield(Maiinde_012,"SeqStationaly");
      SeqStationaly->initialize();
  SeqStationaly->setPropertyV(WSNuserValue,(long)1);
  SeqStationaly->setPropertyV(WSNname,"SeqStationaly");
  SeqStationaly->setPropertyV(WSNvis,(WSCbool)1);
  SeqStationaly->setPropertyV(WSNx,(short)295);
  SeqStationaly->setPropertyV(WSNy,(short)30);
  SeqStationaly->setPropertyV(WSNwidth,(unsigned short)55);
  SeqStationaly->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_063 = new  WSCvlabel(Maiinde_012,"Maivlab_063");
      Maivlab_063->initialize();
  Maivlab_063->setPropertyV(WSNuserValue,(long)1);
  Maivlab_063->setPropertyV(WSNlabelString,"Teleport In");
  Maivlab_063->setPropertyV(WSNname,"Maivlab_063");
  Maivlab_063->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_063->setPropertyV(WSNx,(short)205);
  Maivlab_063->setPropertyV(WSNy,(short)205);
  Maivlab_063->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_063->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_064 = new  WSCvlabel(Maiinde_012,"Maivlab_064");
      Maivlab_064->initialize();
  Maivlab_064->setPropertyV(WSNuserValue,(long)1);
  Maivlab_064->setPropertyV(WSNlabelString,"Teleport Out");
  Maivlab_064->setPropertyV(WSNname,"Maivlab_064");
  Maivlab_064->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_064->setPropertyV(WSNx,(short)205);
  Maivlab_064->setPropertyV(WSNy,(short)230);
  Maivlab_064->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_064->setPropertyV(WSNheight,(unsigned short)25);

  SeqMoving = new  WSCvifield(Maiinde_012,"SeqMoving");
      SeqMoving->initialize();
  SeqMoving->setPropertyV(WSNuserValue,(long)1);
  SeqMoving->setPropertyV(WSNname,"SeqMoving");
  SeqMoving->setPropertyV(WSNvis,(WSCbool)1);
  SeqMoving->setPropertyV(WSNx,(short)295);
  SeqMoving->setPropertyV(WSNy,(short)55);
  SeqMoving->setPropertyV(WSNwidth,(unsigned short)55);
  SeqMoving->setPropertyV(WSNheight,(unsigned short)25);

  SeqHitting = new  WSCvifield(Maiinde_012,"SeqHitting");
      SeqHitting->initialize();
  SeqHitting->setPropertyV(WSNuserValue,(long)1);
  SeqHitting->setPropertyV(WSNname,"SeqHitting");
  SeqHitting->setPropertyV(WSNvis,(WSCbool)1);
  SeqHitting->setPropertyV(WSNx,(short)295);
  SeqHitting->setPropertyV(WSNy,(short)80);
  SeqHitting->setPropertyV(WSNwidth,(unsigned short)55);
  SeqHitting->setPropertyV(WSNheight,(unsigned short)25);

  SeqSoftDying = new  WSCvifield(Maiinde_012,"SeqSoftDying");
      SeqSoftDying->initialize();
  SeqSoftDying->setPropertyV(WSNuserValue,(long)1);
  SeqSoftDying->setPropertyV(WSNname,"SeqSoftDying");
  SeqSoftDying->setPropertyV(WSNvis,(WSCbool)1);
  SeqSoftDying->setPropertyV(WSNx,(short)295);
  SeqSoftDying->setPropertyV(WSNy,(short)105);
  SeqSoftDying->setPropertyV(WSNwidth,(unsigned short)55);
  SeqSoftDying->setPropertyV(WSNheight,(unsigned short)25);

  Maivifi_068 = new  WSCvifield(Maiinde_012,"Maivifi_068");
      Maivifi_068->initialize();
  Maivifi_068->setPropertyV(WSNuserValue,(long)1);
  Maivifi_068->setPropertyV(WSNname,"Maivifi_068");
  Maivifi_068->setPropertyV(WSNvis,(WSCbool)1);
  Maivifi_068->setPropertyV(WSNx,(short)295);
  Maivifi_068->setPropertyV(WSNy,(short)130);
  Maivifi_068->setPropertyV(WSNwidth,(unsigned short)55);
  Maivifi_068->setPropertyV(WSNheight,(unsigned short)25);

  Maivifi_069 = new  WSCvifield(Maiinde_012,"Maivifi_069");
      Maivifi_069->initialize();
  Maivifi_069->setPropertyV(WSNuserValue,(long)1);
  Maivifi_069->setPropertyV(WSNname,"Maivifi_069");
  Maivifi_069->setPropertyV(WSNvis,(WSCbool)1);
  Maivifi_069->setPropertyV(WSNx,(short)295);
  Maivifi_069->setPropertyV(WSNy,(short)155);
  Maivifi_069->setPropertyV(WSNwidth,(unsigned short)55);
  Maivifi_069->setPropertyV(WSNheight,(unsigned short)25);

  Maivifi_070 = new  WSCvifield(Maiinde_012,"Maivifi_070");
      Maivifi_070->initialize();
  Maivifi_070->setPropertyV(WSNuserValue,(long)1);
  Maivifi_070->setPropertyV(WSNname,"Maivifi_070");
  Maivifi_070->setPropertyV(WSNvis,(WSCbool)1);
  Maivifi_070->setPropertyV(WSNx,(short)295);
  Maivifi_070->setPropertyV(WSNy,(short)180);
  Maivifi_070->setPropertyV(WSNwidth,(unsigned short)55);
  Maivifi_070->setPropertyV(WSNheight,(unsigned short)25);

  Maivifi_071 = new  WSCvifield(Maiinde_012,"Maivifi_071");
      Maivifi_071->initialize();
  Maivifi_071->setPropertyV(WSNuserValue,(long)1);
  Maivifi_071->setPropertyV(WSNname,"Maivifi_071");
  Maivifi_071->setPropertyV(WSNvis,(WSCbool)1);
  Maivifi_071->setPropertyV(WSNx,(short)295);
  Maivifi_071->setPropertyV(WSNy,(short)205);
  Maivifi_071->setPropertyV(WSNwidth,(unsigned short)55);
  Maivifi_071->setPropertyV(WSNheight,(unsigned short)25);

  Maivifi_072 = new  WSCvifield(Maiinde_012,"Maivifi_072");
      Maivifi_072->initialize();
  Maivifi_072->setPropertyV(WSNuserValue,(long)1);
  Maivifi_072->setPropertyV(WSNname,"Maivifi_072");
  Maivifi_072->setPropertyV(WSNvis,(WSCbool)1);
  Maivifi_072->setPropertyV(WSNx,(short)295);
  Maivifi_072->setPropertyV(WSNy,(short)230);
  Maivifi_072->setPropertyV(WSNwidth,(unsigned short)55);
  Maivifi_072->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_073 = new  WSCvlabel(Maiinde_012,"Maivlab_073");
      Maivlab_073->initialize();
  Maivlab_073->setPropertyV(WSNuserValue,(long)1);
  Maivlab_073->setPropertyV(WSNlabelString,"SoundPitch");
  Maivlab_073->setPropertyV(WSNname,"Maivlab_073");
  Maivlab_073->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_073->setPropertyV(WSNx,(short)350);
  Maivlab_073->setPropertyV(WSNy,(short)30);
  Maivlab_073->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_073->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_074 = new  WSCvlabel(Maiinde_012,"Maivlab_074");
      Maivlab_074->initialize();
  Maivlab_074->setPropertyV(WSNuserValue,(long)1);
  Maivlab_074->setPropertyV(WSNlabelString,"ActivationSnd");
  Maivlab_074->setPropertyV(WSNname,"Maivlab_074");
  Maivlab_074->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_074->setPropertyV(WSNx,(short)350);
  Maivlab_074->setPropertyV(WSNy,(short)55);
  Maivlab_074->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_075 = new  WSCvlabel(Maiinde_012,"Maivlab_075");
      Maivlab_075->initialize();
  Maivlab_075->setPropertyV(WSNuserValue,(long)1);
  Maivlab_075->setPropertyV(WSNlabelString,"FriendActSnd");
  Maivlab_075->setPropertyV(WSNname,"Maivlab_075");
  Maivlab_075->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_075->setPropertyV(WSNx,(short)350);
  Maivlab_075->setPropertyV(WSNy,(short)80);
  Maivlab_075->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_076 = new  WSCvlabel(Maiinde_012,"Maivlab_076");
      Maivlab_076->initialize();
  Maivlab_076->setPropertyV(WSNuserValue,(long)1);
  Maivlab_076->setPropertyV(WSNlabelString,"ClearSnd");
  Maivlab_076->setPropertyV(WSNname,"Maivlab_076");
  Maivlab_076->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_076->setPropertyV(WSNx,(short)350);
  Maivlab_076->setPropertyV(WSNy,(short)105);
  Maivlab_076->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_077 = new  WSCvlabel(Maiinde_012,"Maivlab_077");
      Maivlab_077->initialize();
  Maivlab_077->setPropertyV(WSNuserValue,(long)1);
  Maivlab_077->setPropertyV(WSNlabelString,"KillSnd");
  Maivlab_077->setPropertyV(WSNname,"Maivlab_077");
  Maivlab_077->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_077->setPropertyV(WSNx,(short)350);
  Maivlab_077->setPropertyV(WSNy,(short)130);
  Maivlab_077->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_078 = new  WSCvlabel(Maiinde_012,"Maivlab_078");
      Maivlab_078->initialize();
  Maivlab_078->setPropertyV(WSNuserValue,(long)1);
  Maivlab_078->setPropertyV(WSNlabelString,"ApologySnd");
  Maivlab_078->setPropertyV(WSNname,"Maivlab_078");
  Maivlab_078->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_078->setPropertyV(WSNx,(short)350);
  Maivlab_078->setPropertyV(WSNy,(short)155);
  Maivlab_078->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_079 = new  WSCvlabel(Maiinde_012,"Maivlab_079");
      Maivlab_079->initialize();
  Maivlab_079->setPropertyV(WSNuserValue,(long)1);
  Maivlab_079->setPropertyV(WSNlabelString,"FriendFireSnd");
  Maivlab_079->setPropertyV(WSNname,"Maivlab_079");
  Maivlab_079->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_079->setPropertyV(WSNx,(short)350);
  Maivlab_079->setPropertyV(WSNy,(short)180);
  Maivlab_079->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_080 = new  WSCvlabel(Maiinde_012,"Maivlab_080");
      Maivlab_080->initialize();
  Maivlab_080->setPropertyV(WSNuserValue,(long)1);
  Maivlab_080->setPropertyV(WSNlabelString,"FlamingSnd");
  Maivlab_080->setPropertyV(WSNname,"Maivlab_080");
  Maivlab_080->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_080->setPropertyV(WSNx,(short)350);
  Maivlab_080->setPropertyV(WSNy,(short)205);
  Maivlab_080->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_081 = new  WSCvlabel(Maiinde_012,"Maivlab_081");
      Maivlab_081->initialize();
  Maivlab_081->setPropertyV(WSNuserValue,(long)1);
  Maivlab_081->setPropertyV(WSNlabelString,"RandomSnd");
  Maivlab_081->setPropertyV(WSNname,"Maivlab_081");
  Maivlab_081->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_081->setPropertyV(WSNx,(short)350);
  Maivlab_081->setPropertyV(WSNy,(short)230);
  Maivlab_081->setPropertyV(WSNheight,(unsigned short)25);

  Maivifi_082 = new  WSCvifield(Maiinde_012,"Maivifi_082");
      Maivifi_082->initialize();
  Maivifi_082->setPropertyV(WSNuserValue,(long)1);
  Maivifi_082->setPropertyV(WSNname,"Maivifi_082");
  Maivifi_082->setPropertyV(WSNvis,(WSCbool)1);
  Maivifi_082->setPropertyV(WSNx,(short)440);
  Maivifi_082->setPropertyV(WSNy,(short)30);
  Maivifi_082->setPropertyV(WSNwidth,(unsigned short)80);
  Maivifi_082->setPropertyV(WSNheight,(unsigned short)25);

  Maivifi_083 = new  WSCvifield(Maiinde_012,"Maivifi_083");
      Maivifi_083->initialize();
  Maivifi_083->setPropertyV(WSNuserValue,(long)1);
  Maivifi_083->setPropertyV(WSNname,"Maivifi_083");
  Maivifi_083->setPropertyV(WSNvis,(WSCbool)1);
  Maivifi_083->setPropertyV(WSNx,(short)450);
  Maivifi_083->setPropertyV(WSNy,(short)255);
  Maivifi_083->setPropertyV(WSNwidth,(unsigned short)80);
  Maivifi_083->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_084 = new  WSCvlabel(Maiinde_012,"Maivlab_084");
      Maivlab_084->initialize();
  Maivlab_084->setPropertyV(WSNuserValue,(long)1);
  Maivlab_084->setPropertyV(WSNlabelString,"RandomSndMask");
  Maivlab_084->setPropertyV(WSNname,"Maivlab_084");
  Maivlab_084->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_084->setPropertyV(WSNx,(short)350);
  Maivlab_084->setPropertyV(WSNy,(short)255);
  Maivlab_084->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_085 = new  WSCvlabel(Maiinde_012,"Maivlab_085");
      Maivlab_085->initialize();
  Maivlab_085->setPropertyV(WSNuserValue,(long)1);
  Maivlab_085->setPropertyV(WSNlabelString,"ImpactEffect");
  Maivlab_085->setPropertyV(WSNname,"Maivlab_085");
  Maivlab_085->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_085->setPropertyV(WSNx,(short)350);
  Maivlab_085->setPropertyV(WSNy,(short)280);
  Maivlab_085->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_085->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_086 = new  WSCvlabel(Maiinde_012,"Maivlab_086");
      Maivlab_086->initialize();
  Maivlab_086->setPropertyV(WSNuserValue,(long)1);
  Maivlab_086->setPropertyV(WSNlabelString,"MeleeEffect");
  Maivlab_086->setPropertyV(WSNname,"Maivlab_086");
  Maivlab_086->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_086->setPropertyV(WSNx,(short)350);
  Maivlab_086->setPropertyV(WSNy,(short)305);
  Maivlab_086->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_086->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_087 = new  WSCvlabel(Maiinde_012,"Maivlab_087");
      Maivlab_087->initialize();
  Maivlab_087->setPropertyV(WSNuserValue,(long)1);
  Maivlab_087->setPropertyV(WSNlabelString,"ContrailEffect");
  Maivlab_087->setPropertyV(WSNname,"Maivlab_087");
  Maivlab_087->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_087->setPropertyV(WSNx,(short)350);
  Maivlab_087->setPropertyV(WSNy,(short)330);
  Maivlab_087->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_087->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_088 = new  WSCvlabel(Maiinde_012,"Maivlab_088");
      Maivlab_088->initialize();
  Maivlab_088->setPropertyV(WSNuserValue,(long)1);
  Maivlab_088->setPropertyV(WSNlabelString,"HalfVisualArc");
  Maivlab_088->setPropertyV(WSNname,"Maivlab_088");
  Maivlab_088->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_088->setPropertyV(WSNx,(short)5);
  Maivlab_088->setPropertyV(WSNy,(short)305);
  Maivlab_088->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_089 = new  WSCvlabel(Maiinde_012,"Maivlab_089");
      Maivlab_089->initialize();
  Maivlab_089->setPropertyV(WSNuserValue,(long)1);
  Maivlab_089->setPropertyV(WSNlabelString,"VertVisualArc");
  Maivlab_089->setPropertyV(WSNname,"Maivlab_089");
  Maivlab_089->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_089->setPropertyV(WSNx,(short)5);
  Maivlab_089->setPropertyV(WSNy,(short)330);
  Maivlab_089->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_090 = new  WSCvlabel(Maiinde_012,"Maivlab_090");
      Maivlab_090->initialize();
  Maivlab_090->setPropertyV(WSNuserValue,(long)1);
  Maivlab_090->setPropertyV(WSNlabelString,"Intelligence");
  Maivlab_090->setPropertyV(WSNname,"Maivlab_090");
  Maivlab_090->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_090->setPropertyV(WSNx,(short)5);
  Maivlab_090->setPropertyV(WSNy,(short)355);
  Maivlab_090->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_090->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_091 = new  WSCvlabel(Maiinde_012,"Maivlab_091");
      Maivlab_091->initialize();
  Maivlab_091->setPropertyV(WSNuserValue,(long)1);
  Maivlab_091->setPropertyV(WSNlabelString,"Speed");
  Maivlab_091->setPropertyV(WSNname,"Maivlab_091");
  Maivlab_091->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_091->setPropertyV(WSNx,(short)5);
  Maivlab_091->setPropertyV(WSNy,(short)380);
  Maivlab_091->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_091->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_092 = new  WSCvlabel(Maiinde_012,"Maivlab_092");
      Maivlab_092->initialize();
  Maivlab_092->setPropertyV(WSNuserValue,(long)1);
  Maivlab_092->setPropertyV(WSNlabelString,"Gravity");
  Maivlab_092->setPropertyV(WSNname,"Maivlab_092");
  Maivlab_092->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_092->setPropertyV(WSNx,(short)5);
  Maivlab_092->setPropertyV(WSNy,(short)405);
  Maivlab_092->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_092->setPropertyV(WSNheight,(unsigned short)25);

  Maivifi_093 = new  WSCvifield(Maiinde_012,"Maivifi_093");
      Maivifi_093->initialize();
  Maivifi_093->setPropertyV(WSNuserValue,(long)1);
  Maivifi_093->setPropertyV(WSNname,"Maivifi_093");
  Maivifi_093->setPropertyV(WSNvis,(WSCbool)1);
  Maivifi_093->setPropertyV(WSNx,(short)105);
  Maivifi_093->setPropertyV(WSNy,(short)305);
  Maivifi_093->setPropertyV(WSNwidth,(unsigned short)70);
  Maivifi_093->setPropertyV(WSNheight,(unsigned short)25);

  Maivifi_094 = new  WSCvifield(Maiinde_012,"Maivifi_094");
      Maivifi_094->initialize();
  Maivifi_094->setPropertyV(WSNuserValue,(long)1);
  Maivifi_094->setPropertyV(WSNname,"Maivifi_094");
  Maivifi_094->setPropertyV(WSNvis,(WSCbool)1);
  Maivifi_094->setPropertyV(WSNx,(short)105);
  Maivifi_094->setPropertyV(WSNy,(short)330);
  Maivifi_094->setPropertyV(WSNwidth,(unsigned short)70);
  Maivifi_094->setPropertyV(WSNheight,(unsigned short)25);

  Maivifi_095 = new  WSCvifield(Maiinde_012,"Maivifi_095");
      Maivifi_095->initialize();
  Maivifi_095->setPropertyV(WSNuserValue,(long)1);
  Maivifi_095->setPropertyV(WSNname,"Maivifi_095");
  Maivifi_095->setPropertyV(WSNvis,(WSCbool)1);
  Maivifi_095->setPropertyV(WSNx,(short)95);
  Maivifi_095->setPropertyV(WSNy,(short)380);
  Maivifi_095->setPropertyV(WSNwidth,(unsigned short)80);
  Maivifi_095->setPropertyV(WSNheight,(unsigned short)25);

  Maivifi_096 = new  WSCvifield(Maiinde_012,"Maivifi_096");
      Maivifi_096->initialize();
  Maivifi_096->setPropertyV(WSNuserValue,(long)1);
  Maivifi_096->setPropertyV(WSNname,"Maivifi_096");
  Maivifi_096->setPropertyV(WSNvis,(WSCbool)1);
  Maivifi_096->setPropertyV(WSNx,(short)95);
  Maivifi_096->setPropertyV(WSNy,(short)405);
  Maivifi_096->setPropertyV(WSNwidth,(unsigned short)80);
  Maivifi_096->setPropertyV(WSNheight,(unsigned short)25);

  Mailist_097 = new  WSClist(Maiinde_012,"Mailist_097");
      Mailist_097->initialize();
  Mailist_097->setPropertyV(WSNuserValue,(long)2);
  Mailist_097->setPropertyV(WSNmultiSelect,(WSCbool)1);
  Mailist_097->setPropertyV(WSNtitleString,"Immunities");
  Mailist_097->setPropertyV(WSNdataSource,(unsigned char)2);
  Mailist_097->setPropertyV(WSNdataSourceName,"data/WSImmunitiesWeaknesses.txt");
  Mailist_097->setPropertyV(WSNworkWidth,(unsigned short)200);
  Mailist_097->setPropertyV(WSNworkHeight,(unsigned short)385);
  Mailist_097->setPropertyV(WSNhbarVisible,(WSCbool)1);
  Mailist_097->setPropertyV(WSNname,"Mailist_097");
  Mailist_097->setPropertyV(WSNx,(short)0);
  Mailist_097->setPropertyV(WSNy,(short)50);
  Mailist_097->setPropertyV(WSNwidth,(unsigned short)115);
  Mailist_097->setPropertyV(WSNheight,(unsigned short)405);

  Maivlab_098 = new  WSCvlabel(Maiinde_012,"Maivlab_098");
      Maivlab_098->initialize();
  Maivlab_098->setPropertyV(WSNuserValue,(long)2);
  Maivlab_098->setPropertyV(WSNlabelString,"Immunities");
  Maivlab_098->setPropertyV(WSNname,"Maivlab_098");
  Maivlab_098->setPropertyV(WSNy,(short)25);
  Maivlab_098->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_098->setPropertyV(WSNheight,(unsigned short)25);

  Mailist_099 = new  WSClist(Maiinde_012,"Mailist_099");
      Mailist_099->initialize();
  Mailist_099->setPropertyV(WSNuserValue,(long)2);
  Mailist_099->setPropertyV(WSNmultiSelect,(WSCbool)1);
  Mailist_099->setPropertyV(WSNtitleString,"Immunities");
  Mailist_099->setPropertyV(WSNdataSource,(unsigned char)2);
  Mailist_099->setPropertyV(WSNdataSourceName,"data/WSImmunitiesWeaknesses.txt");
  Mailist_099->setPropertyV(WSNworkWidth,(unsigned short)200);
  Mailist_099->setPropertyV(WSNworkHeight,(unsigned short)385);
  Mailist_099->setPropertyV(WSNhbarVisible,(WSCbool)1);
  Mailist_099->setPropertyV(WSNname,"Mailist_099");
  Mailist_099->setPropertyV(WSNx,(short)115);
  Mailist_099->setPropertyV(WSNy,(short)50);
  Mailist_099->setPropertyV(WSNwidth,(unsigned short)110);
  Mailist_099->setPropertyV(WSNheight,(unsigned short)405);

  Maivlab_100 = new  WSCvlabel(Maiinde_012,"Maivlab_100");
      Maivlab_100->initialize();
  Maivlab_100->setPropertyV(WSNuserValue,(long)2);
  Maivlab_100->setPropertyV(WSNlabelString,"Weaknesses");
  Maivlab_100->setPropertyV(WSNname,"Maivlab_100");
  Maivlab_100->setPropertyV(WSNx,(short)115);
  Maivlab_100->setPropertyV(WSNy,(short)25);
  Maivlab_100->setPropertyV(WSNwidth,(unsigned short)95);
  Maivlab_100->setPropertyV(WSNheight,(unsigned short)25);

  Mailist_101 = new  WSClist(Maiinde_012,"Mailist_101");
      Mailist_101->initialize();
  Mailist_101->setPropertyV(WSNuserValue,(long)2);
  Mailist_101->setPropertyV(WSNmultiSelect,(WSCbool)1);
  Mailist_101->setPropertyV(WSNtitleString,"Immunities");
  Mailist_101->setPropertyV(WSNdataSource,(unsigned char)2);
  Mailist_101->setPropertyV(WSNdataSourceName,"data/WSEnemiesFriends.txt");
  Mailist_101->setPropertyV(WSNworkWidth,(unsigned short)200);
  Mailist_101->setPropertyV(WSNworkHeight,(unsigned short)385);
  Mailist_101->setPropertyV(WSNhbarVisible,(WSCbool)1);
  Mailist_101->setPropertyV(WSNname,"Mailist_101");
  Mailist_101->setPropertyV(WSNx,(short)235);
  Mailist_101->setPropertyV(WSNy,(short)50);
  Mailist_101->setPropertyV(WSNwidth,(unsigned short)80);
  Mailist_101->setPropertyV(WSNheight,(unsigned short)405);

  Maivlab_102 = new  WSCvlabel(Maiinde_012,"Maivlab_102");
      Maivlab_102->initialize();
  Maivlab_102->setPropertyV(WSNuserValue,(long)2);
  Maivlab_102->setPropertyV(WSNlabelString,"Enemies");
  Maivlab_102->setPropertyV(WSNname,"Maivlab_102");
  Maivlab_102->setPropertyV(WSNx,(short)235);
  Maivlab_102->setPropertyV(WSNy,(short)25);
  Maivlab_102->setPropertyV(WSNwidth,(unsigned short)80);
  Maivlab_102->setPropertyV(WSNheight,(unsigned short)25);

  Maivlab_103 = new  WSCvlabel(Maiinde_012,"Maivlab_103");
      Maivlab_103->initialize();
  Maivlab_103->setPropertyV(WSNuserValue,(long)2);
  Maivlab_103->setPropertyV(WSNlabelString,"Friends");
  Maivlab_103->setPropertyV(WSNname,"Maivlab_103");
  Maivlab_103->setPropertyV(WSNx,(short)315);
  Maivlab_103->setPropertyV(WSNy,(short)25);
  Maivlab_103->setPropertyV(WSNwidth,(unsigned short)80);
  Maivlab_103->setPropertyV(WSNheight,(unsigned short)25);

  Mailist_104 = new  WSClist(Maiinde_012,"Mailist_104");
      Mailist_104->initialize();
  Mailist_104->setPropertyV(WSNuserValue,(long)2);
  Mailist_104->setPropertyV(WSNmultiSelect,(WSCbool)1);
  Mailist_104->setPropertyV(WSNtitleString,"Immunities");
  Mailist_104->setPropertyV(WSNdataSource,(unsigned char)2);
  Mailist_104->setPropertyV(WSNdataSourceName,"data/WSEnemiesFriends.txt");
  Mailist_104->setPropertyV(WSNworkWidth,(unsigned short)200);
  Mailist_104->setPropertyV(WSNworkHeight,(unsigned short)385);
  Mailist_104->setPropertyV(WSNhbarVisible,(WSCbool)1);
  Mailist_104->setPropertyV(WSNname,"Mailist_104");
  Mailist_104->setPropertyV(WSNx,(short)315);
  Mailist_104->setPropertyV(WSNy,(short)50);
  Mailist_104->setPropertyV(WSNwidth,(unsigned short)80);
  Mailist_104->setPropertyV(WSNheight,(unsigned short)405);

  Mailist_105 = new  WSClist(Maiinde_012,"Mailist_105");
      Mailist_105->initialize();
  Mailist_105->setPropertyV(WSNuserValue,(long)2);
  Mailist_105->setPropertyV(WSNmultiSelect,(WSCbool)1);
  Mailist_105->setPropertyV(WSNtitleString,"Immunities");
  Mailist_105->setPropertyV(WSNdataSource,(unsigned char)2);
  Mailist_105->setPropertyV(WSNdataSourceName,"data/WSFlags.txt");
  Mailist_105->setPropertyV(WSNworkWidth,(unsigned short)200);
  Mailist_105->setPropertyV(WSNworkHeight,(unsigned short)345);
  Mailist_105->setPropertyV(WSNhbarVisible,(WSCbool)1);
  Mailist_105->setPropertyV(WSNname,"Mailist_105");
  Mailist_105->setPropertyV(WSNx,(short)400);
  Mailist_105->setPropertyV(WSNy,(short)50);
  Mailist_105->setPropertyV(WSNwidth,(unsigned short)155);
  Mailist_105->setPropertyV(WSNheight,(unsigned short)365);

  Maivbtn_106 = new  WSCvbtn(Maiinde_012,"Maivbtn_106");
      Maivbtn_106->initialize();
  Maivbtn_106->setPropertyV(WSNuserValue,(long)2);
  Maivbtn_106->setPropertyV(WSNlabelString,"Set as Default");
  Maivbtn_106->setPropertyV(WSNname,"Maivbtn_106");
  Maivbtn_106->setPropertyV(WSNx,(short)430);
  Maivbtn_106->setPropertyV(WSNy,(short)425);
  Maivbtn_106->setPropertyV(WSNwidth,(unsigned short)115);

  Maiopti_107 = new  WSCoption(Maiinde_012,"Maiopti_107");
      Maiopti_107->initialize();
  Maiopti_107->setPropertyV(WSNuserValue,(long)1);
  Maiopti_107->setPropertyV(WSNvalue,(long)1);
  Maiopti_107->setPropertyV(WSNlabelString,"item1");
  Maiopti_107->setPropertyV(WSNname,"Maiopti_107");
  Maiopti_107->setPropertyV(WSNvis,(WSCbool)1);
  Maiopti_107->setPropertyV(WSNx,(short)175);
  Maiopti_107->setPropertyV(WSNy,(short)380);
  Maiopti_107->setPropertyV(WSNheight,(unsigned short)25);

  Maiopti_108 = new  WSCoption(Maiinde_012,"Maiopti_108");
      Maiopti_108->initialize();
  Maiopti_108->setPropertyV(WSNuserValue,(long)1);
  Maiopti_108->setPropertyV(WSNmenuItems,"Low:1:ep1_name,Average:2:ep2_name,High:3:ep3_name");
  Maiopti_108->setPropertyV(WSNvalue,(long)1);
  Maiopti_108->setPropertyV(WSNlabelString,"Low");
  Maiopti_108->setPropertyV(WSNname,"Maiopti_108");
  Maiopti_108->setPropertyV(WSNvis,(WSCbool)1);
  Maiopti_108->setPropertyV(WSNx,(short)95);
  Maiopti_108->setPropertyV(WSNy,(short)355);
  Maiopti_108->setPropertyV(WSNwidth,(unsigned short)80);
  Maiopti_108->setPropertyV(WSNheight,(unsigned short)25);
    extern void IntelligenceValueChFunc(WSCbase*);
    Maiopti_108->addProcedureV("IntelligenceValueCh","IntelligenceValueChFunc",IntelligenceValueChFunc,3);

  Maivbtn_109 = new  WSCvbtn(Maiinde_012,"Maivbtn_109");
      Maivbtn_109->initialize();
  Maivbtn_109->setPropertyV(WSNuserValue,(long)1);
  Maivbtn_109->setPropertyV(WSNname,"Maivbtn_109");
  Maivbtn_109->setPropertyV(WSNvis,(WSCbool)1);
  Maivbtn_109->setPropertyV(WSNx,(short)95);
  Maivbtn_109->setPropertyV(WSNy,(short)30);
  Maivbtn_109->setPropertyV(WSNwidth,(unsigned short)80);
  Maivbtn_109->setPropertyV(WSNheight,(unsigned short)25);
    extern void CollectionBtnFunc(WSCbase*);
    Maivbtn_109->addProcedureV("CollectionBtn","CollectionBtnFunc",CollectionBtnFunc,13);

  Maivbtn_110 = new  WSCvbtn(Maiinde_012,"Maivbtn_110");
      Maivbtn_110->initialize();
  Maivbtn_110->setPropertyV(WSNuserValue,(long)1);
  Maivbtn_110->setPropertyV(WSNname,"Maivbtn_110");
  Maivbtn_110->setPropertyV(WSNvis,(WSCbool)1);
  Maivbtn_110->setPropertyV(WSNx,(short)95);
  Maivbtn_110->setPropertyV(WSNy,(short)280);
  Maivbtn_110->setPropertyV(WSNwidth,(unsigned short)110);
  Maivbtn_110->setPropertyV(WSNheight,(unsigned short)25);

  Maivbtn_111 = new  WSCvbtn(Maiinde_012,"Maivbtn_111");
      Maivbtn_111->initialize();
  Maivbtn_111->setPropertyV(WSNuserValue,(long)1);
  Maivbtn_111->setPropertyV(WSNname,"Maivbtn_111");
  Maivbtn_111->setPropertyV(WSNvis,(WSCbool)1);
  Maivbtn_111->setPropertyV(WSNx,(short)450);
  Maivbtn_111->setPropertyV(WSNy,(short)55);
  Maivbtn_111->setPropertyV(WSNwidth,(unsigned short)95);
  Maivbtn_111->setPropertyV(WSNheight,(unsigned short)25);

  Maivbtn_112 = new  WSCvbtn(Maiinde_012,"Maivbtn_112");
      Maivbtn_112->initialize();
  Maivbtn_112->setPropertyV(WSNuserValue,(long)1);
  Maivbtn_112->setPropertyV(WSNname,"Maivbtn_112");
  Maivbtn_112->setPropertyV(WSNvis,(WSCbool)1);
  Maivbtn_112->setPropertyV(WSNx,(short)450);
  Maivbtn_112->setPropertyV(WSNy,(short)80);
  Maivbtn_112->setPropertyV(WSNwidth,(unsigned short)95);
  Maivbtn_112->setPropertyV(WSNheight,(unsigned short)25);

  Maivbtn_113 = new  WSCvbtn(Maiinde_012,"Maivbtn_113");
      Maivbtn_113->initialize();
  Maivbtn_113->setPropertyV(WSNuserValue,(long)1);
  Maivbtn_113->setPropertyV(WSNname,"Maivbtn_113");
  Maivbtn_113->setPropertyV(WSNvis,(WSCbool)1);
  Maivbtn_113->setPropertyV(WSNx,(short)450);
  Maivbtn_113->setPropertyV(WSNy,(short)105);
  Maivbtn_113->setPropertyV(WSNwidth,(unsigned short)95);
  Maivbtn_113->setPropertyV(WSNheight,(unsigned short)25);

  Maivbtn_114 = new  WSCvbtn(Maiinde_012,"Maivbtn_114");
      Maivbtn_114->initialize();
  Maivbtn_114->setPropertyV(WSNuserValue,(long)1);
  Maivbtn_114->setPropertyV(WSNname,"Maivbtn_114");
  Maivbtn_114->setPropertyV(WSNvis,(WSCbool)1);
  Maivbtn_114->setPropertyV(WSNx,(short)450);
  Maivbtn_114->setPropertyV(WSNy,(short)130);
  Maivbtn_114->setPropertyV(WSNwidth,(unsigned short)95);
  Maivbtn_114->setPropertyV(WSNheight,(unsigned short)25);

  Maivbtn_115 = new  WSCvbtn(Maiinde_012,"Maivbtn_115");
      Maivbtn_115->initialize();
  Maivbtn_115->setPropertyV(WSNuserValue,(long)1);
  Maivbtn_115->setPropertyV(WSNname,"Maivbtn_115");
  Maivbtn_115->setPropertyV(WSNvis,(WSCbool)1);
  Maivbtn_115->setPropertyV(WSNx,(short)450);
  Maivbtn_115->setPropertyV(WSNy,(short)155);
  Maivbtn_115->setPropertyV(WSNwidth,(unsigned short)95);
  Maivbtn_115->setPropertyV(WSNheight,(unsigned short)25);

  Maivbtn_116 = new  WSCvbtn(Maiinde_012,"Maivbtn_116");
      Maivbtn_116->initialize();
  Maivbtn_116->setPropertyV(WSNuserValue,(long)1);
  Maivbtn_116->setPropertyV(WSNname,"Maivbtn_116");
  Maivbtn_116->setPropertyV(WSNvis,(WSCbool)1);
  Maivbtn_116->setPropertyV(WSNx,(short)450);
  Maivbtn_116->setPropertyV(WSNy,(short)180);
  Maivbtn_116->setPropertyV(WSNwidth,(unsigned short)95);
  Maivbtn_116->setPropertyV(WSNheight,(unsigned short)25);

  Maivbtn_117 = new  WSCvbtn(Maiinde_012,"Maivbtn_117");
      Maivbtn_117->initialize();
  Maivbtn_117->setPropertyV(WSNuserValue,(long)1);
  Maivbtn_117->setPropertyV(WSNname,"Maivbtn_117");
  Maivbtn_117->setPropertyV(WSNvis,(WSCbool)1);
  Maivbtn_117->setPropertyV(WSNx,(short)450);
  Maivbtn_117->setPropertyV(WSNy,(short)205);
  Maivbtn_117->setPropertyV(WSNwidth,(unsigned short)95);
  Maivbtn_117->setPropertyV(WSNheight,(unsigned short)25);

  Maivbtn_118 = new  WSCvbtn(Maiinde_012,"Maivbtn_118");
      Maivbtn_118->initialize();
  Maivbtn_118->setPropertyV(WSNuserValue,(long)1);
  Maivbtn_118->setPropertyV(WSNname,"Maivbtn_118");
  Maivbtn_118->setPropertyV(WSNvis,(WSCbool)1);
  Maivbtn_118->setPropertyV(WSNx,(short)450);
  Maivbtn_118->setPropertyV(WSNy,(short)230);
  Maivbtn_118->setPropertyV(WSNwidth,(unsigned short)95);
  Maivbtn_118->setPropertyV(WSNheight,(unsigned short)25);

  Maiopti_119 = new  WSCoption(Maiinde_012,"Maiopti_119");
      Maiopti_119->initialize();
  Maiopti_119->setPropertyV(WSNuserValue,(long)1);
  Maiopti_119->setPropertyV(WSNvalue,(long)1);
  Maiopti_119->setPropertyV(WSNlabelString,"item1");
  Maiopti_119->setPropertyV(WSNname,"Maiopti_119");
  Maiopti_119->setPropertyV(WSNvis,(WSCbool)1);
  Maiopti_119->setPropertyV(WSNx,(short)95);
  Maiopti_119->setPropertyV(WSNy,(short)105);
  Maiopti_119->setPropertyV(WSNwidth,(unsigned short)110);
  Maiopti_119->setPropertyV(WSNheight,(unsigned short)25);

  Maivbtn_120 = new  WSCvbtn(Maiinde_012,"Maivbtn_120");
      Maivbtn_120->initialize();
  Maivbtn_120->setPropertyV(WSNuserValue,(long)1);
  Maivbtn_120->setPropertyV(WSNname,"Maivbtn_120");
  Maivbtn_120->setPropertyV(WSNvis,(WSCbool)1);
  Maivbtn_120->setPropertyV(WSNx,(short)440);
  Maivbtn_120->setPropertyV(WSNy,(short)280);
  Maivbtn_120->setPropertyV(WSNwidth,(unsigned short)90);
  Maivbtn_120->setPropertyV(WSNheight,(unsigned short)25);

  Maivbtn_121 = new  WSCvbtn(Maiinde_012,"Maivbtn_121");
      Maivbtn_121->initialize();
  Maivbtn_121->setPropertyV(WSNuserValue,(long)1);
  Maivbtn_121->setPropertyV(WSNname,"Maivbtn_121");
  Maivbtn_121->setPropertyV(WSNvis,(WSCbool)1);
  Maivbtn_121->setPropertyV(WSNx,(short)440);
  Maivbtn_121->setPropertyV(WSNy,(short)305);
  Maivbtn_121->setPropertyV(WSNwidth,(unsigned short)90);
  Maivbtn_121->setPropertyV(WSNheight,(unsigned short)25);

  Maivbtn_122 = new  WSCvbtn(Maiinde_012,"Maivbtn_122");
      Maivbtn_122->initialize();
  Maivbtn_122->setPropertyV(WSNuserValue,(long)1);
  Maivbtn_122->setPropertyV(WSNname,"Maivbtn_122");
  Maivbtn_122->setPropertyV(WSNvis,(WSCbool)1);
  Maivbtn_122->setPropertyV(WSNx,(short)440);
  Maivbtn_122->setPropertyV(WSNy,(short)330);
  Maivbtn_122->setPropertyV(WSNwidth,(unsigned short)90);
  Maivbtn_122->setPropertyV(WSNheight,(unsigned short)25);

  WndSelect = new  WSCdialog(MainWindow,"WndSelect");
      WndSelect->initialize();
  WndSelect->setPropertyV(WSNname,"WndSelect");
  WndSelect->setPropertyV(WSNtitleString,"SelectIt!");
  WndSelect->setPropertyV(WSNx,(short)47);
  WndSelect->setPropertyV(WSNy,(short)374);
  WndSelect->setPropertyV(WSNwidth,(unsigned short)290);
  WndSelect->setPropertyV(WSNheight,(unsigned short)496);

  ListSelect = new  WSClist(WndSelect,"ListSelect");
      ListSelect->initialize();
  ListSelect->setPropertyV(WSNtitleString,"title4");
  ListSelect->setPropertyV(WSNworkHeight,(unsigned short)26);
  ListSelect->setPropertyV(WSNhbarVisible,(WSCbool)1);
  ListSelect->setPropertyV(WSNname,"ListSelect");
  ListSelect->setPropertyV(WSNx,(short)0);
  ListSelect->setPropertyV(WSNy,(short)0);
  ListSelect->setPropertyV(WSNwidth,(unsigned short)285);
  ListSelect->setPropertyV(WSNheight,(unsigned short)465);
  ListSelect->setPropertyV(WSNvis,(WSCbool)1);

   MainWindow->setVisible(True);
   return MainWindow;
}

//--- end of src ---//
