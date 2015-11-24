#ifndef __GDI_COM_H__
#define __GDI_COM_H__

#include "Type.h"
#include "Color.h"

typedef struct _Point
{
    INT m_iX;
    INT m_iY;
}CPoint, *PPoint;

typedef struct _Rect
{
    INT m_iLeft;
    INT m_iTop;
    INT m_iWidth;
    INT m_iHeigh;
}CRect,*PRect;

BOOL PointInRect(PPoint pPoint, PRect pRect);

VOID RectInRect(PRect pRectParent, PRect pRectSon, PRect pRectDst);

VOID CopyRect(PRect pRectDst, PRect pRectSrc);

#endif

