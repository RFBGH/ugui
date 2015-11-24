#include "GdiCom.h"

BOOL PointInRect(PPoint pPoint, PRect pRect)
{
	if(pRect == NULL || pPoint == NULL)
	{
		return FALSE;
	}
	
    if((pPoint->m_iX >= pRect->m_iLeft && pPoint->m_iX < (pRect->m_iLeft+pRect->m_iWidth))
        &&(pPoint->m_iY >= pRect->m_iTop && pPoint->m_iY < (pRect->m_iTop+pRect->m_iHeigh)))  
    {
        return TRUE;
    }
    return FALSE;
}

VOID RectInRect(PRect pRectParent, PRect pRectSon, PRect pRectDst)
{
    pRectDst->m_iLeft = MAX(pRectParent->m_iLeft, pRectSon->m_iLeft);

    pRectDst->m_iTop = MAX(pRectParent->m_iTop, pRectSon->m_iTop);

    pRectDst->m_iWidth = MIN(pRectParent->m_iLeft+pRectParent->m_iWidth, pRectSon->m_iLeft+pRectSon->m_iWidth)-pRectDst->m_iLeft;
    if(pRectDst->m_iWidth < 0)
    {
        pRectDst->m_iWidth = 0;
    }

    pRectDst->m_iHeigh = MIN(pRectParent->m_iTop+pRectParent->m_iHeigh, pRectSon->m_iTop+pRectSon->m_iHeigh)-pRectDst->m_iTop;
    if(pRectDst->m_iHeigh < 0)
    {
        pRectDst->m_iHeigh = 0;
    }
}

VOID CopyRect(PRect pRectDst, PRect pRectSrc)
{
    pRectDst->m_iLeft = pRectSrc->m_iLeft;
    pRectDst->m_iTop = pRectSrc->m_iTop;
    pRectDst->m_iWidth = pRectSrc->m_iWidth;
    pRectDst->m_iHeigh = pRectSrc->m_iHeigh;
}

