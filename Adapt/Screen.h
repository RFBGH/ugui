#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "guicfg.h"

#include "GdiCom.h"

VOID CleanScreen(RGBA rgbaScreen);
VOID InitScreen(VOID);

VOID SetPixel(INT x, INT y, RGBA rgba);
RGBA GetPixel(INT x, INT y);

VOID PushScreen(RGBA* pScreenBuf, PRect pRect);
VOID PopScreen(RGBA* pScreenBuf, PRect pRect);

//extern RGBA ScreenBuf[LCD_SCREEN_WIDTH*LCD_SCREEN_HEIGH+8];

#endif

