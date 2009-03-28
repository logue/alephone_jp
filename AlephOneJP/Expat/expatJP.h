/*
 * $Id: expatJP.h,v 1.2 2009-03-28 07:16:32 ookawa_mi Exp $
 * expatをShift_JISおよびEUC-JPに対応させる
 * ISO-2022JPにも対応させたいところだがexpatの実装上難しい
 */

#ifndef _YEBISUYA_EXPATJP_H_
#define _YEBISUYA_EXPATJP_H_
#include "expat.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * UTF8の文字列をEUC-JPに変換する。
 * @param utf8     UTF8の文字列
 * @param utf8len  文字列の長さ。-1を指定すると終端文字までを変換する。
 * @param eucjp    EUC-JPに変換した文字列を格納するバッファ。
 * @param eucjplen バッファの長さ。0を指定すると実際には変換を行わず、変換後の文字列長を取得する。
 * @return 変換後の文字列長。
 */
int UTF8toEUCJP(const char* utf8, int utf8len, char* eucjp, int eucjplen);

/**
 * UTF8の文字列をSHIFT_JISに変換する。
 * @param utf8	UTF8の文字列
 * @param utf8len	文字列の長さ。-1を指定すると終端文字までを変換する。
 * @param sjis	SHIFT_JISに変換した文字列を格納するバッファ。
 * @param sjislen	バッファの長さ。0を指定すると実際には変換を行わず、変換後の文字列長を取得する。
 * @return 変換後の文字列長。
 */
int UTF8toSJIS(const char* utf8, int utf8len, char* sjis, int sjislen);

/**
 * 日本語文字コード(EUC-JPとSHIFT_JISのみ)を処理するためのハンドラ
 * @param encodingHandlerData このハンドラのためのユーザ定義データ(未使用)
 * @param name 文字コード名(このハンドラではSHIFT_JISとEUC-JPのみ対応)
 * @param info 文字コード変換のための情報
 * @return このハンドラで処理を行うのであれば非0。
 */

int XML_JapaneseEncodingHandler(void *encodingHandlerData, const XML_Char *name, XML_Encoding *info);

#ifdef __cplusplus
}
#endif


#if 0 //sample

void printUTF8(FILE* fp, const XML_Char* string) {
	int sjislen = UTF8toSJIS(string, -1, NULL, 0);
	char* sjis = (char*) alloca(sjislen);
	UTF8toSJIS(string, -1, sjis, sjislen);
	fputs(sjis, fp);
}

void startElementHandler(void* userData, const XML_Char* name, const XML_Char** atts) {
	fputs(stdout, "start element(tag name: ");
	printUTF8(stdout, name);
	fputs(stdout, ")\n");
	if (atts != NULL) {
		while (*atts != NULL) {
			fputs(stdout, "  attribute(name: ");
			printUTF8(stdout, *atts++);
			fputs(stdout, ", value: \n");
			printUTF8(stdout, *atts++);
			fputs(stdout, ")\n");
		}
	}
}

void endElementHandler(void* userData, const XML_Char* name) {
	int sjislen = UTF8toSJIS(name, -1, NULL, 0);
	char* sjis = (char*) alloca(sjislen);
	UTF8toSJIS(name, -1, sjis, sjislen);
	printf("end element(tag name: %s)\n", sjis)
}

void parseString(const char* string) {
	XML_Parser parser = XML_ParserCreate(NULL);
	XML_SetUnknownEncodingHandler(parser, XML_JapaneseEncodingHandler, NULL);
	XML_SetElementHandler(parser, startElementHandler, endElementHandler);
	XML_Parse(string, strlen(string), true);
}

#endif

#endif//_YEBISUYA_EXPATJP_H_

/*
 * Changes:
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2007/01/21 05:01:18  ookawa_mi
 * *** empty log message ***
 *
 * Revision 1.2  2003/11/27 05:54:45  sugoroku
 * CVSキーワードをコメントに挿入
 *
 */
