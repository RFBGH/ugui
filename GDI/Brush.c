#include "Brush.h"

VOID CopyBrush(PBrush pBrushDst, PBrush pBrushSrc)
{
    pBrushDst->m_color = pBrushSrc->m_color;
}

//...
