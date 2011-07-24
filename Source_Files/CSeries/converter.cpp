/*
 *  converter.cpp
 *  AlephOne-OSX10.4
 *
 *  Created by みちあき on 08/06/24.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 *  Modified by Logue
 */

#include "converter.h"
typedef unsigned short uint16;
#include <string.h>
#include <iconv.h>

// Convert from Shift_JIS to UTF8
char* sjis2utf8(const char* str, size_t len) {
	static char text[1024];
	memset(text,0,1024);
	const char* strp = str;
	char* retp = text;
	size_t sz = 1024;
	iconv_t i = iconv_open("UTF-8", "SHIFT-JIS");
	iconv_t j = iconv_open("UTF-8", "MACROMAN");
	if( iconv(i,  &strp, &len, &retp, &sz) == -1 ) {
		strp = str;
		retp = text;
		sz = 1024;
		iconv(j,  &strp, &len, &retp, &sz);
	}
	if( text[strlen(text)-1] == 13) { text[strlen(text)-1] = 0; }
	iconv_close(i);
	iconv_close(j);
	return text;
}
// Convert from UTF8 to Shift_JIS
char* utf82sjis(const char* str, size_t len) {
	static char text[1024];
	memset(text,0,1024);
	const char* strp = str;
	char* retp = text;
	size_t sz = 1024;
	iconv_t i = iconv_open("SHIFT-JIS", "UTF-8");
	if( iconv(i,  &strp, &len, &retp, &sz) == -1 ) {
		// SHIFT-JISにできないときはそのままコピー
		strncpy(text, str, len);
	}
	if( text[strlen(text)-1] == 13) { text[strlen(text)-1] = 0; }
	iconv_close(i);
	return text;
}

// Convert from Shift_JIS to Unidode
// AlephOneJP overrides to process_macroman().
uint16* sjis2utf16(const char* str, size_t len) {
	static uint16 text[1024];
	memset(text,0,2048);
	const char* strp = str;
	char* retp = (char*)text;
	size_t sz = 1024;
	iconv_t i = iconv_open("UCS-2-INTERNAL", "SHIFT-JIS");
	iconv_t j = iconv_open("UCS-2-INTERNAL", "MACROMAN");
	if( iconv(i,  &strp, &len, &retp, &sz) == -1 ) {
		strp = str;
		retp = (char*)text;
		sz = 1024;
		iconv(j,  &strp, &len, &retp, &sz);
	}
	iconv_close(i);
	iconv_close(j);
	return text;
}

// Convert from UTF8 to Unidode
uint16* utf82utf16(const char* str, size_t len) {
	static uint16 text[1024];
	memset(text,0,2048);
	const char* strp = str;
	char* retp = (char*)text;
	size_t sz = 1024;
	iconv_t i = iconv_open("UCS-2-INTERNAL", "UTF-8");
	if( iconv(i,  &strp, &len, &retp, &sz) == -1 ) {
	}
	iconv_close(i);
	return text;
}

// Convert from Unicode to UTF8
char* utf162utf8(const uint16* str, size_t len) {
	static char text[1024];
	memset(text,0,1024);
	len *= 2;
	const char* strp = (const char*)str;
	char* retp = text;
	size_t sz = 1024;
	iconv_t i = iconv_open("UTF-8", "UCS-2-INTERNAL");
	if( iconv(i,  &strp, &len, &retp, &sz) == -1 ) {
	}
	iconv_close(i);
	return text;
}

uint16 sjisChar(char* in, int* step) {
	size_t len;
	if( *in == 13 ) { if( step ) *step += 1; return 13; }
	if( step ) {
		if ( isJChar((unsigned char)*in) ) {
			*step += 2;
			len = 2;
		} else {
			*step += 1;
			len = 1;
		}
	}
	uint16 text[2];
	memset(text,0,4);
	const char* strp = in;
	char* retp = (char*)text;
	size_t sz = 4;
	iconv_t i = iconv_open("UCS-2-INTERNAL", "SHIFT-JIS");
	iconv_t j = iconv_open("UCS-2-INTERNAL", "MACROMAN");
	if( iconv(i,  &strp, &len, &retp, &sz) == -1 ) {
		strp = in;
		retp = (char*)text;
		sz = 4;
		iconv(j,  &strp, &len, &retp, &sz);
	}
	iconv_close(i);
	iconv_close(j);
	return text[0];
}

int unicodeChar( const char* input, uint16* ret) {
	uint16 text[3];
	memset(text,0,4);
	const char* strp = input;
	char* retp = (char*)text;
	size_t len = strlen(input), sz = 6;

	iconv_t i = iconv_open("UCS-2-INTERNAL", "SHIFT-JIS");
	iconv_t j = iconv_open("UCS-2-INTERNAL", "MACROMAN");

	if( iconv(i,  &strp, &len, &retp, &sz) == -1 ) {
		strp = input;
		retp = (char*)text;
		sz = 4;
		iconv(j,  &strp, &len, &retp, &sz);
	}
	iconv_close(i);
	iconv_close(j);
	*ret = text[0];
	
	unsigned char first = *input;
	if( first < 0x80 || ( first > 0xa0 && first < 0xe0 ) ) {
		return 1;
	} else if( first < 0xeb ) {
		return 2;
	} else {
		return 1;
	}
}

// Detect 2-byte char. (for Shift_JIS)
bool isJChar(unsigned char text) {
	return (((text >= 0x81) && (text <= 0x9f)) || ((text >= 0xe0) && (text <= 0xfc))) ? true : false;
}
// Detect 2nd charactor of 2-byte char. (for Shift_JIS)
bool is2ndJChar(unsigned char text) {
	return (((0x7F != text) && (0x40 <= text)) || ((text >= 0xe0) && (text <= 0xfc))) ? true : false;
}
