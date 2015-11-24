#ifndef __BRUSH_H__
#define __BRUSH_H__

#include "Color.h"

typedef struct _Brush
{
    RGBA m_color;
}CBrush, *PBrush;

VOID CopyBrush(PBrush pBrushDst, PBrush pBrushSrc);

#endif

