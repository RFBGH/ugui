#ifndef __FONT_H__
#define __FONT_H__

#include "GDI.h"

typedef struct _Font
{
    RGBA m_color;
}CFont, *PFont;

VOID CopyFont(PFont pFontDst, PFont pFontSrc);

#endif

