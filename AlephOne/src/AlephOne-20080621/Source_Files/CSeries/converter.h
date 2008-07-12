/*
 *  converter.h
 *  AlephOne-OSX10.4
 *
 *  Created by みちあき on 08/06/24.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif
char* sjis2utf8(const char* str, size_t len);
unsigned short* sjis2utf16(const char* str, size_t len);
unsigned short* utf82utf16(const char* str, size_t len);
char* utf162utf8(const unsigned short* str, size_t len);

#ifdef __cplusplus
};
#endif
