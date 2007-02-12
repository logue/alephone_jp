//----------------------------------------------------//
// MWT C++ Application Source File                    //
//      created by WideStudio Application Builder     //
//----------------------------------------------------//
#include <WScom.h>
#include <WSDappDev.h>

//--- OBJECT includes ---//
#include <WSCmainWindow.h>
#include <WSCvdrawingArea.h>
#include <WSCwindow.h>
#include <WSCmessageDialog.h>
#include <WSCmenuArea.h>
#include <WSCpulldownMenu.h>

//--- OBJECT instance variable ---//
WSCmainWindow* MainWindow = NULL;
WSCvdrawingArea* MainDrawArea = NULL;
WSCwindow* ToolPallet = NULL;
WSCmessageDialog* Messages = NULL;
WSCmenuArea* Maimenu_006 = NULL;
WSCpulldownMenu* FileMenu = NULL;

//--- OBJECT src ---//

WSCbase* _create_win_MainWindow(){


  MainWindow = new  WSCmainWindow(NULL,"MainWindow");
      MainWindow->initialize();
  MainWindow->setPropertyV(WSNname,"MainWindow");
  MainWindow->setPropertyV(WSNtitleString,"Main");
  MainWindow->setPropertyV(WSNx,(short)100);
  MainWindow->setPropertyV(WSNy,(short)100);
  MainWindow->setPropertyV(WSNwidth,(unsigned short)716);
  MainWindow->setPropertyV(WSNheight,(unsigned short)507);
  MainWindow->setPropertyV(WSNvis,(WSCbool)1);
    extern void MainInitFunc(WSCbase*);
    MainWindow->addProcedureV("MainInit","MainInitFunc",MainInitFunc,0);
    extern void MainResizeFunc(WSCbase*);
    MainWindow->addProcedureV("MainResize","MainResizeFunc",MainResizeFunc,10);

  MainDrawArea = new  WSCvdrawingArea(MainWindow,"MainDrawArea");
      MainDrawArea->initialize();
  MainDrawArea->setPropertyV(WSNname,"MainDrawArea");
  MainDrawArea->setPropertyV(WSNvis,(WSCbool)1);
  MainDrawArea->setPropertyV(WSNy,(short)36);
  MainDrawArea->setPropertyV(WSNwidth,(unsigned short)712);
  MainDrawArea->setPropertyV(WSNheight,(unsigned short)470);
    extern void MouseButtonDownFunc(WSCbase*);
    MainDrawArea->addProcedureV("MouseButtonDown","MouseButtonDownFunc",MouseButtonDownFunc,13);
    extern void OnExpose(WSCbase*);
    MainDrawArea->addProcedureV("MainDrawAreaExpose","OnExpose",OnExpose,9);
    extern void DrawAreaMouseMoveFunc(WSCbase*);
    MainDrawArea->addProcedureV("DrawAreaMouseMove","DrawAreaMouseMoveFunc",DrawAreaMouseMoveFunc,15);
    extern void DrawAreaMouseButtonReleaseFunc(WSCbase*);
    MainDrawArea->addProcedureV("DrawAreaMouseButtonRelease","DrawAreaMouseButtonReleaseFunc",DrawAreaMouseButtonReleaseFunc,14);

  ToolPallet = new  WSCwindow(MainWindow,"ToolPallet");
      ToolPallet->initialize();
  ToolPallet->setPropertyV(WSNname,"ToolPallet");
  ToolPallet->setPropertyV(WSNtitleString,"Tool");
  ToolPallet->setPropertyV(WSNx,(short)43);
  ToolPallet->setPropertyV(WSNy,(short)271);
  ToolPallet->setPropertyV(WSNwidth,(unsigned short)104);
  ToolPallet->setPropertyV(WSNheight,(unsigned short)65);
  ToolPallet->setPropertyV(WSNshadowThickness,(unsigned char)2);
  ToolPallet->setPropertyV(WSNvis,(WSCbool)1);
    extern void ToolPalletMouseButtonDownFunc(WSCbase*);
    ToolPallet->addProcedureV("ToolPalletMouseButtonDown","ToolPalletMouseButtonDownFunc",ToolPalletMouseButtonDownFunc,13);

  Messages = new  WSCmessageDialog(MainWindow,"Messages");
      Messages->initialize();
  Messages->setPropertyV(WSNlabelString,"HogeHoge");
  Messages->setPropertyV(WSNname,"Messages");
  Messages->setPropertyV(WSNtitleString,"Messages");
  Messages->setPropertyV(WSNx,(short)101);
  Messages->setPropertyV(WSNy,(short)247);
  Messages->setPropertyV(WSNwidth,(unsigned short)380);
  Messages->setPropertyV(WSNheight,(unsigned short)101);

  Maimenu_006 = new  WSCmenuArea(MainWindow,"Maimenu_006");
      Maimenu_006->initialize();
  Maimenu_006->setPropertyV(WSNname,"Maimenu_006");
  Maimenu_006->setPropertyV(WSNx,(short)0);
  Maimenu_006->setPropertyV(WSNy,(short)0);
  Maimenu_006->setPropertyV(WSNwidth,(unsigned short)716);
  Maimenu_006->setPropertyV(WSNvis,(WSCbool)1);
  Maimenu_006->setPropertyV(WSNanchorLeftFlag,(WSCbool)1);
  Maimenu_006->setPropertyV(WSNanchorRightFlag,(WSCbool)1);

  FileMenu = new  WSCpulldownMenu(Maimenu_006,"FileMenu");
      FileMenu->initialize();
  FileMenu->setPropertyV(WSNmenuItems,"New(N):FileNew:n:1,Open(O):FileOpen:o:2,SP,eXit(X):FileExit:x:3");
  FileMenu->setPropertyV(WSNlabelString,"File");
  FileMenu->setPropertyV(WSNname,"FileMenu");
  FileMenu->setPropertyV(WSNvis,(WSCbool)1);
  FileMenu->setPropertyV(WSNwidth,(unsigned short)104);
  FileMenu->setPropertyV(WSNheight,(unsigned short)28);
    extern void FileNewEp(WSCbase*);
    FileMenu->addProcedureV("FileNew","FileNewEp",FileNewEp,-1);
    extern void FileExitEp(WSCbase*);
    FileMenu->addProcedureV("FileExit","FileExitEp",FileExitEp,-1);
    extern void FileOpenFunc(WSCbase*);
    FileMenu->addProcedureV("FileOpen","FileOpenFunc",FileOpenFunc,-1);

   MainWindow->setVisible(True);
   return MainWindow;
}

//--- end of src ---//
