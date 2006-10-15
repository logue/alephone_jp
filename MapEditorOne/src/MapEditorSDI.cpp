// MapEditorSDI.cpp : �A�v���P�[�V�����̃N���X������`���܂��B
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "MainFrm.h"

#include "MapEditorSDIDoc.h"
#include "MapEditorSDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static char* POLYGON_COLOR_FILE_NAME = "data/PolygonColor.txt";
static char* LOG_FILE_NAME = "log.txt";

//logger
HPLLogger logger;

// CMapEditorSDIApp

BEGIN_MESSAGE_MAP(CMapEditorSDIApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CMapEditorSDIApp::OnAppAbout)
	// �W���̃t�@�C����{�h�L�������g �R�}���h
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// �W���̈���Z�b�g�A�b�v �R�}���h
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
    ON_COMMAND(ID_FILE_OPEN, &CMapEditorSDIApp::OnFileOpen)
END_MESSAGE_MAP()


// CMapEditorSDIApp �R���X�g���N�V����

void loadInformations(const char* filename, int max, 
                             Information *informations)
{
    const int LENGTH = 1024 * 10;
    char cstr[LENGTH];

    CFile f;
    if(!f.Open(CString(filename), CFile::modeRead)){
        CString errMsg = CString("Couldn't open:");
        errMsg += L"[" + CString(filename) + L"]";
        MessageBox(NULL, errMsg, L"Error", MB_OK);
        exit(-1);
    }
    f.Read(cstr, LENGTH);
    CString str = CString(cstr);
    CStringArray array;
    splitString(str, "\r\n", array);
    for(int i = 0; i < max; i ++){
        informations[i].jname = array.GetAt(i);
    }
    f.Close();
}

CMapEditorSDIApp::CMapEditorSDIApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B

    //try to load ini file
    setting.setIniFileName(INI_FILE_NAME);
    if(!setting.loadSetting()){
        AfxMessageBox(L"no setting file. I'll make default one");
        setting.setSettingToDefault();
    }

    //�t�@�C������R���{�p������ǂݍ���
    //���
    loadInformations("data/ObjectTypes.txt", NUMBER_OF_OBJECT_TYPES,
        objectTypeInformations);
    //�����X�^�[
    loadInformations("data/MonsterTypes.txt", NUMBER_OF_MONSTER_TYPES,
        monsterTypeInformations);
    //�I�u�W�F
    loadInformations("data/SceneryTypes.txt", NUMBER_OF_SCENERY_DEFINITIONS,
        sceneryTypeInformations);
    //�A�C�e��
    loadInformations("data/DefinedItems.txt", NUMBER_OF_DEFINED_ITEMS,
        itemTypeInformations);
    //��
    loadInformations("data/SoundSourceTypes.txt", NUMBER_OF_AMBIENT_SOUND_DEFINITIONS,
        soundSourceInformations);
    //�N��
    loadInformations("data/ActivateTypes.txt", NUMBER_OF_ACTIVATE_TYPES,
        activateTypeInformations);
    //�t���O
    objectFlagInformations[0].bind = _map_object_is_invisible;
    objectFlagInformations[1].bind = _map_object_hanging_from_ceiling;
    objectFlagInformations[2].bind = _map_object_is_blind;
    objectFlagInformations[3].bind = _map_object_is_deaf;
    objectFlagInformations[4].bind = _map_object_floats;
    objectFlagInformations[5].bind = _map_object_is_network_only;

    //termnal groups
    loadInformations("data/TerminalGroupTypes.txt", NUMBER_OF_GROUP_TYPES,
        terminalGroupTypeInformations);

    //polygon type
    loadInformations("data/PolygonType.txt", NUMBER_OF_POLYGON_TYPE,
        polygonTypeInformations);

    //environments
    loadInformations("data/Environments.txt", NUMBER_OF_ENVIRONMENTS,
        environmentInformations);
    //landscape
    loadInformations("data/Landscapes.txt", NUMBER_OF_LANDSPACES,
        landscapeInformations);
    //game type(bind)
    //(same order)
    //env type(bind)
    environmentTypeInformations[0].bind = _environment_normal;
    environmentTypeInformations[1].bind = _environment_vacuum;
    environmentTypeInformations[2].bind = _environment_magnetic;
    environmentTypeInformations[3].bind = _environment_rebellion;
    environmentTypeInformations[4].bind = _environment_low_gravity;
    environmentTypeInformations[5].bind = _environment_network;
    environmentTypeInformations[6].bind = _environment_single_player;
    //mission type(bind)
    missionTypeInformations[0].bind = _mission_none;
    missionTypeInformations[1].bind = _mission_extermination;
    missionTypeInformations[2].bind = _mission_exploration;
    missionTypeInformations[3].bind = _mission_retrieval;
    missionTypeInformations[4].bind = _mission_repair;
    missionTypeInformations[5].bind = _mission_rescue;

    //�F�ݒ�
    //�t�@�C������ǂݍ���
    const int LENGTH = 1024*10;
    char cstr[LENGTH];
    
    char *filename = POLYGON_COLOR_FILE_NAME;
    CFile f;
    if(!f.Open(CString(filename), CFile::modeRead)){
        CString errMsg = CString("Couldn't open:");
        errMsg += L"[" + CString(filename) + L"]";
        MessageBox(NULL, errMsg, L"Error", MB_OK);
        exit(-1);
    }
    f.Read(cstr, LENGTH);
    CString str = CString(cstr);
    CStringArray array;
    splitString(str, "\r\n", array);
    for(int i = 0; i < NUMBER_OF_POLYGON_TYPE; i ++){
        //�R���}�ŕ���
        CStringArray splits;
        splitString((CString&)array.GetAt(i), ",", splits);
        int col[3];
        for(int j = 0; j < 3; j ++){
            CString num = splits.GetAt(j);
            char dataCStr[256];
            strToChar(num.Trim(), dataCStr);
            col[j] = atoi(dataCStr);
        }
        this->polygonTypeColor[i] = RGB(col[0], col[1], col[2]);
    }
    f.Close();

    //Zoom
    zoomDivision = ZOOM_DIVISION_DEFAULT;

    isPressLButtonWithCtrl = false;

    offset.x = 0;
    offset.y = 0;

    objectPropertyDialog = NULL;

    //1WU 1/2WU 1/4WU 1/8 WU
    int intervals[]={
        WORLD_ONE * 2, WORLD_ONE, WORLD_ONE / 2, WORLD_ONE / 4, WORLD_ONE / 8
    };
    for(int i = 0; i < NUMBER_OF_GLID; i ++){
        gridIntervals[i] = intervals[i];
    }
    AfxInitRichEdit();

    selectGroupInformation.clear();
    isSelectingGroup = false;


    selectingToolType = TI_ARROW;
    viewHeightMin = - SHRT_MAX;
    viewHeightMax = -viewHeightMin;

    //no changes found(new)
    isChanged = false;

    logger = HPLLogger(LOG_FILE_NAME);
    if(!logger.open()){
        MessageBox(NULL, L"Cannot open log file for writing. Close it!", L"Error", 
            MB_OK | MB_ICONEXCLAMATION);
        exit(1);
    }


    //menu name to id
    menuIDMap[EM_DRAW] = ID_32795;
    menuIDMap[EM_VISUAL] = ID_32796;
    setEditMode(EM_DRAW);

}

CMapEditorSDIApp::~CMapEditorSDIApp()
{
    if(!setting.saveSetting()){
        AfxMessageBox(L"fail to save setting");
    }
    if(m_SDLToWindows)delete m_SDLToWindows;
    shutdown_shape_handler();
    exit_screen();
    mapIconImageList.DeleteImageList();
    for(int i = 0; i < (int)bitmapList.size(); i ++){
        bitmapList[i]->DeleteObject();
    }
    logger.close();
}

// �B��� CMapEditorSDIApp �I�u�W�F�N�g�ł��B

CMapEditorSDIApp theApp;


// CMapEditorSDIApp ������

BOOL CMapEditorSDIApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	// �A�v���P�[�V���� �}�j�t�F�X�g�� visual �X�^�C����L���ɂ��邽�߂ɁA
	// ComCtl32.dll Version 6 �ȍ~�̎g�p���w�肷��ꍇ�́A
	// Windows XP �� InitCommonControlsEx() ���K�v�ł��B�����Ȃ���΁A�E�B���h�E�쐬�͂��ׂĎ��s���܂��B
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �A�v���P�[�V�����Ŏg�p���邷�ׂẴR���� �R���g���[�� �N���X���܂߂�ɂ́A
	// �����ݒ肵�܂��B
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// OLE ���C�u���������������܂��B
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// �W��������
	// �����̋@�\���g�킸�ɍŏI�I�Ȏ��s�\�t�@�C����
	// �T�C�Y���k���������ꍇ�́A�ȉ�����s�v�ȏ�����
	// ���[�`�����폜���Ă��������B
	// �ݒ肪�i�[����Ă��郌�W�X�g�� �L�[��ύX���܂��B
	// TODO: ��Ж��܂��͑g�D���Ȃǂ̓K�؂ȕ������
	// ���̕������ύX���Ă��������B
	SetRegistryKey(_T("MapEditorOne"));
	LoadStdProfileSettings(4);  // �W���� INI �t�@�C���̃I�v�V���������[�h���܂� (MRU ���܂�)
	// �A�v���P�[�V�����p�̃h�L�������g �e���v���[�g��o�^���܂��B�h�L�������g �e���v���[�g
	//  �̓h�L�������g�A�t���[�� �E�B���h�E�ƃr���[���������邽�߂ɋ@�\���܂��B
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMapEditorSDIDoc),
		RUNTIME_CLASS(CMainFrame),       // ���C�� SDI �t���[�� �E�B���h�E
		RUNTIME_CLASS(CMapEditorSDIView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// DDE Execute open ���g�p�\�ɂ��܂��B
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// DDE�Afile open �ȂǕW���̃V�F�� �R�}���h�̃R�}���h ���C������͂��܂��B
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// �R�}���h ���C���Ŏw�肳�ꂽ�f�B�X�p�b�` �R�}���h�ł��B�A�v���P�[�V������
	// /RegServer�A/Register�A/Unregserver �܂��� /Unregister �ŋN�����ꂽ�ꍇ�AFalse ��Ԃ��܂��B
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// ���C�� �E�B���h�E�����������ꂽ�̂ŁA�\���ƍX�V���s���܂��B
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// �ڔ��������݂���ꍇ�ɂ̂� DragAcceptFiles ���Ăяo���Ă��������B
	//  SDI �A�v���P�[�V�����ł́AProcessShellCommand �̒���ɂ��̌Ăяo�����������Ȃ���΂Ȃ�܂���B
	// �h���b�O/�h���b�v �I�[�v���������܂��B
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}



// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// �_�C�A���O�����s���邽�߂̃A�v���P�[�V���� �R�}���h
void CMapEditorSDIApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CMapEditorSDIApp ���b�Z�[�W �n���h��

static void loadMap(const char* filename)
{
}

void CMapEditorSDIApp::OnFileOpen()
{
    
    // TODO: �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
    //�J���_�C�A���O
}

void CMapEditorSDIApp::setEditMode(int mode)
{
    this->editMode = mode;
}
int CMapEditorSDIApp::getEditMode()
{
    return this->editMode;
}

void loadIcon(int id, CImageList* imageList){
    HICON icon;
    icon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(id));
    imageList->Add(icon);
}
void loadBitmap(int id, CImageList* imageList, COLORREF key)
{
    CBitmap image;
    image.LoadBitmap(id);
    imageList->Add(&image, key);
    image.DeleteObject();
}
//set object property to default
void setObjectPropertyToDefault()
{
    memset(&theApp.objectPropertyDialog->store, 0, sizeof(map_object));
    theApp.objectPropertyDialog->setupDialogByStore();
}

int searchSelectEndpoint(int viewPX, int viewPY)
{
    return -1;
}
int searchSelectObject(int viewPX, int viewPY)
{
    return -1;
}
int searchSelectLine(int viewPX, int viewPY)
{
    return -1;
}
int searchSelectPolygon(int viewPX, int viewPY)
{
    return -1;
}

//convert view <-> world point
world_point2d getWorldPoint2DFromViewPoint(int viewPX, int viewPY)
{
    world_point2d point;
    point.x = (world_distance)((viewPX - theApp.offset.x) * theApp.zoomDivision - OFFSET_X_WORLD);
    point.y = (world_distance)((viewPY + theApp.offset.y) * theApp.zoomDivision - OFFSET_Y_WORLD);
    return point;
}
void getViewPointFromWorldPoint2D(world_point2d& point, int *dest)
{
    dest[0] = (point.x + OFFSET_X_WORLD)/theApp.zoomDivision + theApp.offset.x;
    dest[1] = (point.y + OFFSET_Y_WORLD)/theApp.zoomDivision + theApp.offset.y;
}

//TODO
void setCursor()
{
    //
    LPWSTR cursors[] = {
        IDC_HAND,
        IDC_HAND,
        IDC_HAND,
        IDC_HAND,
        IDC_HAND,
        IDC_HAND,
        IDC_HAND
    };
    //�J�[�\���ω�
    HCURSOR cursor = LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_CURSOR_FILL));
        //cursors[theApp.selectingToolType]);
    //SetCursor(cursor);
    SetClassLong(AfxGetMainWnd()->m_hWnd, GCL_HCURSOR, NULL);
    //SetCursor(cursor);
    ShowCursor(TRUE);
}

//get placement from index(0 ~ DEFINED_ITEMS ~ DEFINED_ITEMS + MONSTERS)
object_frequency_definition *getIndexOfPlacement(int index)
{
    object_frequency_definition *place;
    if( index < NUMBER_OF_DEFINED_ITEMS){
        place = &item_placement_info[index];
    }else{
        int mons_index = index - NUMBER_OF_DEFINED_ITEMS;
        place = &monster_placement_info[mons_index];
    }
    return place;
}

void addInitialPlacement(int objectType, int index, int num)
{
    object_frequency_definition *place;
    if(objectType == _saved_item || objectType == _saved_monster){
        if(objectType == _saved_item){
            place = getIndexOfPlacement(index);
        }else if(objectType == _saved_monster){
            place = getIndexOfPlacement(index + NUMBER_OF_DEFINED_ITEMS);
        }
        //
        place->initial_count += num;
    }
}
void subInitialPlacement(int objectType, int index, int num)
{
    object_frequency_definition *place;
    if(objectType == _saved_item || objectType == _saved_monster){
        if(objectType == _saved_item){
            place = getIndexOfPlacement(index);
        }else if(objectType == _saved_monster){
            place = getIndexOfPlacement(index + NUMBER_OF_DEFINED_ITEMS);
        }
        //
        place->initial_count -= num;
    }
}


/**
    add objet on polygon
*/
int addObject(struct world_point2d &world_point, int polygonIndex)
{
    //�I�u�W�F�N�g���
    map_object obj;
    memcpy(&obj, &theApp.objectPropertyDialog->store, sizeof(map_object));
    obj.polygon_index = polygonIndex;
    obj.location.x = world_point.x;
    obj.location.y = world_point.y;
    //calc height(delta)
    /*if(obj.flags & _map_object_hanging_from_ceiling){
        obj.location.z = polygon->ceiling_height;
    }else{
        obj.location.z = polygon->floor_height;
    }*/
    //�ǉ�
    SavedObjectList.push_back(obj);
    int objectIndex = (int)SavedObjectList.size() - 1;
    //add
    addInitialPlacement(obj.type, obj.index, 1);
    theApp.objectPropertyDialog->setupDialog(objectIndex);

    //check polygon's first object
    int firstObjectIndex = PolygonList[polygonIndex].first_object;
    if(firstObjectIndex == NONE){
        //set
        PolygonList[polygonIndex].first_object = objectIndex;
    }
    //���E���ݒ�
    dynamic_world->initial_objects_count = (int)SavedObjectList.size();
    return objectIndex;
}
/**
    get platform_data by using polygon index
    only platform has polygon index. not polygon have
*/
platform_data *searchPlatformByPolygonIndex(int index)
{
    for(int i = 0; i < (int)PlatformList.size(); i ++){
        if(PlatformList[i].polygon_index == index){
            return &PlatformList[i];
        }
    }
    return NULL;
}

//load bitmap from file
CBitmap* loadBitmapFromFile(const char *pathName)
{
    CBitmap *bitmap = new CBitmap;
    HBITMAP handleBitmap = (HBITMAP)LoadImage(
        AfxGetInstanceHandle(), CString(pathName),
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if(handleBitmap == NULL){
        AfxMessageBox(CString("Couldn't load [") + CString(pathName) + CString("]"));
        exit(1);
    }
    memcpy(bitmap, CBitmap::FromHandle(handleBitmap), sizeof(CBitmap));
    return bitmap;
}

/**
    add point on polygon
    if it is on line, add point to the line and polygon
    @return added or already existed point's index
        NONE : fail to add
*/
int addPoint(struct world_point2d &world_point)
{
    endpoint_data newPoint;
    newPoint.vertex.x = world_point.x;
    newPoint.vertex.y = world_point.y;
    newPoint.flags = POINT_FLAG_SOLID;

    bool isFound = false;

    //�_�𓥂�łȂ����m�F
    int endpointIndex = NONE;
    for(int i = 0; i < (int)EndpointList.size(); i ++){
        endpoint_data *point = &EndpointList[i];
        //check height
        if( point->highest_adjacent_floor_height > theApp.viewHeightMax ||
            point->lowest_adjacent_ceiling_height < theApp.viewHeightMin)
        {
            continue;
        }
        if(isSelectPoint(world_point, point->vertex, POINT_DISTANCE_EPSILON * theApp.zoomDivision))
        {
            //�ǉ����Ȃ�
            isFound = true;
            endpointIndex = i;
            break;
        }
    }
    
    if(isFound){
        return endpointIndex;
    }

    //���𓥂�łȂ����m�F
    int lineIndex = NONE;
    for(int i = 0; i < (int)LineList.size(); i ++){
        line_data *line = &LineList[i];
        //check height
        if(line->highest_adjacent_floor > theApp.viewHeightMax ||
            line->lowest_adjacent_ceiling < theApp.viewHeightMin)
        {
            //not add on the outter height line
            continue;
        }
        endpoint_data *begin = &EndpointList[line->endpoint_indexes[0]];
        endpoint_data *end = &EndpointList[line->endpoint_indexes[1]];
        if(isSelectLine(world_point, begin->vertex, end->vertex,
            LINE_DISTANCE_EPSILON * theApp.zoomDivision))
        {
            isFound = true;
            lineIndex = i;
            break;
        }
    }

    if(isFound){
        int polygonIndex = getPolygonIndexFromLineIndex(lineIndex);
        if(polygonIndex != NONE){
            // there is already a polygon! delete it before add point!
            MessageBeep(MB_OK);
            AfxMessageBox(L"Couldn't add point because there is already a polygon. Delete it before add point");
            return NONE;
        }else{
            //add point on the line (if it is included)

            //old line
            line_data* oldLine = &LineList[lineIndex];

            //add point
            newPoint.highest_adjacent_floor_height = oldLine->highest_adjacent_floor;
            newPoint.lowest_adjacent_ceiling_height = oldLine->lowest_adjacent_ceiling;
            newPoint.supporting_polygon_index = NONE;
            //TODO newPoint.transformed = ;??
            EndpointList.push_back(newPoint);
            int newPointIndex = (int)EndpointList.size() - 1;

            //set oldLine's end to newPoint
            int oldLineEndPointIndex = oldLine->endpoint_indexes[1];
            oldLine->endpoint_indexes[1] = newPointIndex;
            double dx = EndpointList[oldLine->endpoint_indexes[0]].vertex.x - EndpointList[oldLine->endpoint_indexes[1]].vertex.x;
            double dy = EndpointList[oldLine->endpoint_indexes[0]].vertex.y - EndpointList[oldLine->endpoint_indexes[1]].vertex.y;
            oldLine->length = (world_distance)sqrt(dx * dx + dy * dy);

            //add new line
            int newLineIndex = addLine(newPointIndex, oldLineEndPointIndex);

            return newPointIndex;
        }
        
    }

    //add point in space
    {
        newPoint.highest_adjacent_floor_height = theApp.viewHeightMin;
        newPoint.lowest_adjacent_ceiling_height = theApp.viewHeightMax;
        newPoint.supporting_polygon_index = NONE;
        EndpointList.push_back(newPoint);
        int newPointIndex = (int)EndpointList.size() - 1;
        return newPointIndex;
    }
}

int addLine(int beginPointIndex, int endPointIndex)
{
    line_data newLine;
    memset(&newLine, 0, sizeof(line_data));
    newLine.endpoint_indexes[0] = beginPointIndex;
    newLine.endpoint_indexes[1] = endPointIndex;
    newLine.clockwise_polygon_owner = NONE;
    newLine.clockwise_polygon_side_index = NONE;
    newLine.counterclockwise_polygon_owner = NONE;
    newLine.counterclockwise_polygon_side_index = NONE;
    newLine.flags = SOLID_LINE_BIT;
    newLine.highest_adjacent_floor = max(EndpointList[beginPointIndex].highest_adjacent_floor_height,
        EndpointList[endPointIndex].highest_adjacent_floor_height);
    newLine.lowest_adjacent_ceiling = min(EndpointList[beginPointIndex].lowest_adjacent_ceiling_height,
        EndpointList[endPointIndex].lowest_adjacent_ceiling_height);
    double dx = EndpointList[newLine.endpoint_indexes[0]].vertex.x - EndpointList[newLine.endpoint_indexes[1]].vertex.x;
    double dy = EndpointList[newLine.endpoint_indexes[0]].vertex.y - EndpointList[newLine.endpoint_indexes[1]].vertex.y;
    newLine.length = (world_distance)sqrt(dx * dx + dy * dy);
    LineList.push_back(newLine);
    int newLineIndex = (int)LineList.size() - 1;
    return newLineIndex;
}

/**
    get line index from point of edge.
    @return index of point
        NONE : not found
*/
int getLineIndexFromPointIndex(int pointIndex)
{
    AfxMessageBox(L"not yet");
    exit(1);
}
int getPolygonIndexFromLineIndex(int lineIndex)
{
    for(int i = 0; i < (int)PolygonList.size(); i ++){
        polygon_data *polygon = &PolygonList[i];

        int vertexCount = polygon->vertex_count;
        for(int j = 0; j < vertexCount - 1; j ++){
            if(polygon->line_indexes[j] == lineIndex){
                return i;
            }
        }
    }
    return NONE;
}
int getPolygonIndexFromPointIndex(int pointIndex)
{
    AfxMessageBox(L"not yet");
    exit(1);
}
