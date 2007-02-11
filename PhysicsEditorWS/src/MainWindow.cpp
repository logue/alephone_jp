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
WSCoption* Maiopti_016 = NULL;
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
  Maipull_001->setPropertyV(WSNmenuItems,"Open(O):open1:O,Close(C):close1:C,SP,Exit(X):exit1:X");
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

  BtnMonster = new  WSCvbtn(MainWindow,"BtnMonster");
      BtnMonster->initialize();
  BtnMonster->setPropertyV(WSNlabelString,"Monster");
  BtnMonster->setPropertyV(WSNname,"BtnMonster");
  BtnMonster->setPropertyV(WSNvis,(WSCbool)1);
  BtnMonster->setPropertyV(WSNx,(short)5);
  BtnMonster->setPropertyV(WSNy,(short)30);
  BtnMonster->setPropertyV(WSNwidth,(unsigned short)85);
  BtnMonster->setPropertyV(WSNheight,(unsigned short)65);

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
  WndMonster->setPropertyV(WSNwidth,(unsigned short)560);
  WndMonster->setPropertyV(WSNheight,(unsigned short)440);
  WndMonster->setPropertyV(WSNshadowThickness,(unsigned char)2);
  WndMonster->setPropertyV(WSNshadowType,(char)-1);

  Maiinde_012 = new  WSCindexForm(WndMonster,"Maiinde_012");
      Maiinde_012->initialize();
  Maiinde_012->setPropertyV(WSNname,"Maiinde_012");
  Maiinde_012->setPropertyV(WSNx,(short)110);
  Maiinde_012->setPropertyV(WSNy,(short)0);
  Maiinde_012->setPropertyV(WSNwidth,(unsigned short)445);
  Maiinde_012->setPropertyV(WSNheight,(unsigned short)435);
  Maiinde_012->setPropertyV(WSNvis,(WSCbool)1);

  Maivlab_014 = new  WSCvlabel(Maiinde_012,"Maivlab_014");
      Maivlab_014->initialize();
  Maivlab_014->setPropertyV(WSNuserValue,(long)1);
  Maivlab_014->setPropertyV(WSNname,"Maivlab_014");
  Maivlab_014->setPropertyV(WSNvis,(WSCbool)1);
  Maivlab_014->setPropertyV(WSNx,(short)5);
  Maivlab_014->setPropertyV(WSNy,(short)30);
  Maivlab_014->setPropertyV(WSNwidth,(unsigned short)90);
  Maivlab_014->setPropertyV(WSNheight,(unsigned short)25);

  Maiopti_016 = new  WSCoption(Maiinde_012,"Maiopti_016");
      Maiopti_016->initialize();
  Maiopti_016->setPropertyV(WSNuserValue,(long)1);
  Maiopti_016->setPropertyV(WSNvalue,(long)1);
  Maiopti_016->setPropertyV(WSNlabelString,"item1");
  Maiopti_016->setPropertyV(WSNname,"Maiopti_016");
  Maiopti_016->setPropertyV(WSNvis,(WSCbool)1);
  Maiopti_016->setPropertyV(WSNx,(short)95);
  Maiopti_016->setPropertyV(WSNy,(short)30);

  ListMonsterType = new  WSClist(WndMonster,"ListMonsterType");
      ListMonsterType->initialize();
  ListMonsterType->setPropertyV(WSNtitleString,"");
  ListMonsterType->setPropertyV(WSNworkHeight,(unsigned short)26);
  ListMonsterType->setPropertyV(WSNname,"ListMonsterType");
  ListMonsterType->setPropertyV(WSNx,(short)5);
  ListMonsterType->setPropertyV(WSNy,(short)5);
  ListMonsterType->setPropertyV(WSNwidth,(unsigned short)105);
  ListMonsterType->setPropertyV(WSNheight,(unsigned short)430);
  ListMonsterType->setPropertyV(WSNvis,(WSCbool)1);

   MainWindow->setVisible(True);
   return MainWindow;
}

//--- end of src ---//
