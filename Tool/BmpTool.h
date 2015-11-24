#ifndef __BMP_TOOL_H__
#define __BMP_TOOL_H__

#include "Type.h"

typedef struct _Bitmap
{
    UINT  m_uBmpType;
    UINT  m_uBmpWidth;
    UINT  m_uBmpHeigh;
    UINT* m_pBmpBuf;
}CBitmap, *PBitmap;

VOID SetBmpAlpha(PBitmap pBmp, INT iAlpha);

#endif

