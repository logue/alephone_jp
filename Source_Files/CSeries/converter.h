/*
 *  converter.h
 *  AlephOne-OSX10.4
 *
 *  Created by みちあき on 08/06/24.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 *  Modified by Logue on 11/06/10
 */
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif
char* sjis2utf8(const char* str, size_t len);
char* utf82sjis(const char* str, size_t len);

unsigned short* sjis2utf16(const char* str, size_t len);
unsigned short* utf82utf16(const char* str, size_t len);
char* utf162utf8(const unsigned short* str, size_t len);

typedef unsigned short uint16;
uint16 sjisChar(char* in, int* step);

static int isJChar(unsigned char text);
#ifdef __cplusplus
};
#endif
