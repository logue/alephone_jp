#ifndef _HPL_LIB_MFC_
#define _HPL_LIB_MFC_

#include "stdafx.h"
#include "HPLLibCommon.h"
#include <fstream>
using namespace std;

////////////////////
//structures
//����
typedef struct Information_tag{
    CString jname;
}Information;
//�l������
typedef struct InformationBinded_tag{
    CString jname;
    int bind;
}InformationBinded;

//////////////////
//CString->char
void strToChar(CString& src, char* dest);

//WCHAR->char
void wcharToChar(WCHAR* src, char* dest);

//char->WCHAR
void charToWChar(char* src, WCHAR* dest);

//split
void splitString(CString& src, const char* sep, CStringArray &array);



void setIntegerNum(int num, CEdit* edit);
int getIntegerNum(CEdit* edit);
void setComboAndIntegerNum(int num, int max,
                           CEdit* edit, CComboBox* cmb);

/**disable*/
void worldToWindow(int worldX, int worldY, POINT* point);

void setStatusBar(int index, CString str);

//load information
void loadInformations(const char* filename, int max, 
                             Information *informations);
#endif
