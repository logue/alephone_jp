#ifndef _HPL_LIB_MFC_
#define _HPL_LIB_MFC_

#include "stdafx.h"
#include "HPLLibCommon.h"

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

#endif
