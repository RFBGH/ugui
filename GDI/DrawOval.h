#ifndef __DRAW_OVAL_H__
#define __DRAW_OVAL_H__

#include "Screen.h"
#include "Common.h"

VOID DrawOval(PRect rect, RGBA rgba);

VOID DrawOvalRectBuffer(RGBA* pBuffer, PRect pBufRect, PRect rect, RGBA rgba);

#endif

