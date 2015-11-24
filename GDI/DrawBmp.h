#ifndef __DRAW_BMP_H__
#define __DRAW_BMP_H__

#include "GdiCom.h"
#include "Screen.h"
#include "BmpTool.h"

#define DRAW_BMP_SOLID_CP   1
#define DRAW_BMP_ADAPT_FILL 2
#define DRAW_BMP_REPEAT_CP  3

VOID DrawBmp(PRect pDstRect, PRect pSrcRect, PBitmap pBmp, INT iFlag);


#endif

