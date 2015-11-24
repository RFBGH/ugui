#ifndef __DRAW_RECT_H__
#define __DRAW_RECT_H__

#include "Screen.h"

VOID DrawRect(PRect pRect, RGBA rgba);

VOID FillRect(PRect pRect, RGBA rgba);

VOID DrawRoundRect(PRect pRect, RGBA rgba);

VOID FillRoundRect(PRect pRect, RGBA rgba);

VOID FillRectRectBuffer(RGBA* pBuffer, PRect pBufRect, PRect pRect, RGBA rgba);

VOID DrawRectRectBuffer(RGBA* pBuffer, PRect pBufRect, PRect pRect, RGBA rgba);


#endif

