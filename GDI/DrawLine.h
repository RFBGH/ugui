#ifndef __DRAW_LINE_H__
#define __DRAW_LINE_H__

#include "Screen.h"
#include "Common.h"

VOID DrawLine(PPoint pStart, PPoint pEnd, RGBA rgba);

VOID DrawLineRectBuffer(RGBA* pBuffer, PRect pBufRect, PPoint pStart, PPoint pEnd, RGBA rgba);

#endif

