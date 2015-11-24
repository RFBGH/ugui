#ifndef __TEXT_OUT_H__
#define __TEXT_OUT_H__

#include "Screen.h"
#include "Common.h"
#include "Color.h"

#define ASC8x16_WIDTH 8
#define ASC8x16_HEIGH 16

VOID TextOut8X16(INT x, INT y, CONST CHAR* pTip, RGBA rgba);

#define TEXTOUT_FLAG_AUTO_NEW_LINE 0x00000002
#define TEXTOUT_FLAG_NEW_LINE      0x00000001
#define TEXTOUT_FLAG_H_SCROLL      0x00010000
#define TEXTOUT_FLAG_V_SCROLL      0x00020000

VOID TextOut8X16E(INT x, INT y, PRect pRect, CONST CHAR* pTip, RGBA rgba, UINT uFlag);

VOID TextOut8X16ERectBuffer(RGBA* pBuffer, INT x, INT y, PRect pBufRect, CONST CHAR* pTip, RGBA rgba, UINT uFlag);

INT MaxFullPrintAsc8x16(PRect pRect, CHAR* pcStr, INT iCurEdit, UINT* r_uXY);

#define TextOut(x, y, pTip) TextOut8X16(x, y, pTip, RGBA_BLACK)

#define TEXT_OUT_IN_RECT_MULTI_LINE 0x00100000
#define TEXT_OUT_IN_RECT_KEEP_RIGHT 0x00200000
//#define TEXT_OUT_IN_RECT_SINGLE_LINE 0x0010000

#endif
