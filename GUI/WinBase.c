/****************************************************************************
*
*this procedure is work for base set in window system.
*
*############################################################################
*AUTHOR:RFB 	LOG: Creat this procedure	TIME:2014/02/26
*****************************************************************************/

#include "Window.h"

/*
 * set a window backgroud color.
 *
 * @param pWin: the pointer of window wanted to set color.
 * @param rgba: the color value you wanted.
 *
 * @return success >=0, else fail.
 *
 */
INT SetWinBKColor(PWindow pWin, RGBA rgba)
{
    if(pWin == NULL)
    {
        return -1;
    }

    pWin->m_brush.m_color = rgba;
    return 0;
}

/*
 * set a window rect.
 *
 * @param pWin: the pointer of window wanted to set color.
 * @param pRect: the rect you wanted.
 *
 * @return success >=0, else fail.
 *
 */
INT SetWinRect(PWindow pWin, PRect pRect)
{
    if(pWin == NULL || pRect == NULL)
    {
        return -1;
    }

    pWin->m_rect.m_iLeft = pRect->m_iLeft;
    pWin->m_rect.m_iTop = pRect->m_iTop;
    pWin->m_rect.m_iWidth = pRect->m_iWidth;
    pWin->m_rect.m_iHeigh = pRect->m_iHeigh;
    //MemCpy(&pWin->m_rect, pRect, sizeof(CRect));
    return 0;
}

#if 0
STATIC PWindow pWinLocat = NULL;
STATIC PPoint  pPointLocat = NULL;
INT WindowLocatFlow(PWindow pWin)
{

    if(pWinLocat)
    {
        return 2;
    }
    
    if(PointInRect(pPointLocat, &pWin->m_rect))
    {
        pWinLocat = pWin;
        return 1;
    }
    return 0;
}
#endif

/*
 * local a window by the x and y coordinate.
 *
 * @param pPoint: the pointer of point wanted.
 *
 * @return the pointer of window wanted.
 *
 */

#if 0
PWindow LocatWinByXY(PPoint pPoint)
{
    PWindow pWinCurr = NULL;
    PWindow pWinParent = NULL;
    CList   list;
    int     iStackTop;

    InitList(&list);
    pWinCurr = pWinRoot;
    while(TRUE)
    {
        if(pWinCurr)
        {

            PushList(&list, pWinCurr);
            pWinCurr = pWinCurr->m_pLastSon;          
        }
        else{
            iStackTop = list.m_iListSize;
            if(iStackTop == -1)
            {
                break;
            }
            
            pWinCurr = GetListData(&list, iStackTop-1);
            RemoveListByData(&list, pWinCurr);

            if(PointInRect(pPoint, &pWinCurr->m_showRect))
            {
                break;
            }
            pWinCurr = pWinCurr->m_pLast;
        }
    }

    DeletList(&list);
    return pWinCurr;
}
#endif

#if 1
PWindow LocatWinByXY(PPoint pPoint)
{
    PWindow pWinCurr = NULL;
    PWindow pWinRet = NULL;

	pWinCurr = pWinRoot->m_pFirstSon;

	while(TRUE)
	{
		if(PointInRect(pPoint, &pWinCurr->m_showRect))
		{
			pWinRet = pWinCurr;
			pWinCurr = pWinCurr->m_pFirstSon;
		}else
		{
			pWinCurr = pWinCurr->m_pNext;
		}

		if(pWinCurr == NULL)
		{
			break;
		}
	}

	return pWinRet;
}

#endif


STATIC INT iDragWinCutX;
STATIC INT iDragWinCutY;

STATIC INT DragWinsToXYFlow(PWindow pWin)
{
	pWin->m_rect.m_iLeft += iDragWinCutX;
	pWin->m_rect.m_iTop += iDragWinCutY;
	return 0;
}

VOID DragWinsToXY(PWindow pWin, INT x, INT y)
{

	iDragWinCutX = x-pWin->m_rect.m_iLeft;
	iDragWinCutY = y-pWin->m_rect.m_iTop;
	FlowWindow0(pWin, DragWinsToXYFlow);
}

