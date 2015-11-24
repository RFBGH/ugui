/****************************************************************************
*
*this procedure is work for draw rect.
*
*############################################################################
*AUTHOR:RFB 	LOG: Creat this procedure	 TIME:2013/01/11
*****************************************************************************/

#include "DrawRect.h"
#include "Tool.h"

/*
 * fill a rect in screen.
 *
 * @param pRect: rect wanted fill.
 *        rgba:  color of fill.
 *       
 *
 * @return NULL
 */
VOID FillRect(PRect pRect, RGBA rgba)
{
    INT iW;
    INT iH;
    if(pRect == NULL)
    {
        return;
    }

    if(pRect->m_iLeft < 0 || pRect->m_iLeft >= SCREEN_WIDTH
        || pRect->m_iTop < 0 || pRect->m_iTop >= SCREEN_HEIGH)
    {
        return;
    }

    if((pRect->m_iLeft+pRect->m_iWidth) > SCREEN_WIDTH)
    {
        pRect->m_iWidth = SCREEN_WIDTH-pRect->m_iLeft;
    }

    if((pRect->m_iTop+pRect->m_iHeigh) > SCREEN_HEIGH)
    {
        pRect->m_iHeigh = SCREEN_HEIGH-pRect->m_iTop;
    }

    for(iH = 0; iH < pRect->m_iHeigh; iH++)    
    {
        for(iW = 0; iW < pRect->m_iWidth; iW++)
        {
            SetPixel(iW+pRect->m_iLeft, iH+pRect->m_iTop, rgba);
        }
    }
}

/*
 * draw a rect in screen.
 *
 * @param pRect: rect wanted draw.
 *        rgba:  color of fill.
 *       
 *
 * @return NULL
 */
VOID DrawRect(PRect pRect, RGBA rgba)
{
    CPoint start;
    CPoint end;
    
    if(pRect == NULL)
    {
        return;
    }

    if(pRect->m_iLeft < 0 || pRect->m_iLeft >= SCREEN_WIDTH
     || pRect->m_iTop < 0 || pRect->m_iTop >= SCREEN_HEIGH)
    {
        return;
    }

    if((pRect->m_iLeft+pRect->m_iWidth) > SCREEN_WIDTH)
    {
        pRect->m_iWidth = SCREEN_WIDTH-pRect->m_iLeft;
    }

    if((pRect->m_iTop+pRect->m_iHeigh) > SCREEN_HEIGH)
    {
        pRect->m_iHeigh = SCREEN_HEIGH-pRect->m_iTop;
    }

    start.m_iX = pRect->m_iLeft;
    start.m_iY = pRect->m_iTop;
    end.m_iX = pRect->m_iLeft+pRect->m_iWidth-1;
    end.m_iY = pRect->m_iTop;
    DrawLine(&start, &end, rgba);

    start.m_iX = pRect->m_iLeft+pRect->m_iWidth-1;
    start.m_iY = pRect->m_iTop;
    end.m_iX = pRect->m_iLeft+pRect->m_iWidth-1;
    end.m_iY = pRect->m_iTop+pRect->m_iHeigh-1;
    DrawLine(&start, &end, rgba);

    start.m_iX = pRect->m_iLeft;
    start.m_iY = pRect->m_iTop;
    end.m_iX = pRect->m_iLeft;
    end.m_iY = pRect->m_iTop+pRect->m_iHeigh-1;
    DrawLine(&start, &end, rgba);

    start.m_iX = pRect->m_iLeft;
    start.m_iY = pRect->m_iTop+pRect->m_iHeigh-1;
    end.m_iX = pRect->m_iLeft+pRect->m_iWidth-1;
    end.m_iY = pRect->m_iTop+pRect->m_iHeigh-1;
    DrawLine(&start, &end, rgba);    
}


VOID DrawRoundRect(PRect pRect, RGBA rgba)
{
    CPoint start;
    CPoint end;
    
    if(pRect == NULL)
    {
        return;
    }

    if(pRect->m_iLeft < 0 || pRect->m_iLeft >= SCREEN_WIDTH
     || pRect->m_iTop < 0 || pRect->m_iTop >= SCREEN_HEIGH)
    {
        return;
    }

    if((pRect->m_iLeft+pRect->m_iWidth) > SCREEN_WIDTH)
    {
        pRect->m_iWidth = SCREEN_WIDTH-pRect->m_iLeft;
    }

    if((pRect->m_iTop+pRect->m_iHeigh) > SCREEN_HEIGH)
    {
        pRect->m_iHeigh = SCREEN_HEIGH-pRect->m_iTop;
    }

    start.m_iX = pRect->m_iLeft+2;
    start.m_iY = pRect->m_iTop;
    end.m_iX = pRect->m_iLeft+pRect->m_iWidth-2;
    end.m_iY = pRect->m_iTop;
    DrawLine(&start, &end, rgba);
    SetPixel(pRect->m_iLeft+1, pRect->m_iTop+1, rgba);

    start.m_iX = pRect->m_iLeft+pRect->m_iWidth;
    start.m_iY = pRect->m_iTop+2;
    end.m_iX = pRect->m_iLeft+pRect->m_iWidth;
    end.m_iY = pRect->m_iTop+pRect->m_iHeigh-2;
    DrawLine(&start, &end, rgba);
    SetPixel(pRect->m_iLeft+pRect->m_iWidth-1, pRect->m_iTop+1, rgba);

    start.m_iX = pRect->m_iLeft;
    start.m_iY = pRect->m_iTop+2;
    end.m_iX = pRect->m_iLeft;
    end.m_iY = pRect->m_iTop+pRect->m_iHeigh-2;
    DrawLine(&start, &end, rgba);
    SetPixel(pRect->m_iLeft+1, pRect->m_iTop+pRect->m_iHeigh-1, rgba);

    start.m_iX = pRect->m_iLeft+2;
    start.m_iY = pRect->m_iTop+pRect->m_iHeigh;
    end.m_iX = pRect->m_iLeft+pRect->m_iWidth-2;
    end.m_iY = pRect->m_iTop+pRect->m_iHeigh;
    DrawLine(&start, &end, rgba); 
    SetPixel(pRect->m_iLeft+pRect->m_iWidth-1, pRect->m_iTop+pRect->m_iHeigh-1, rgba);

}

VOID FillRoundRect(PRect pRect, RGBA rgba)
{
    INT iW;
    INT iH;
    if(pRect == NULL)
    {
        return;
    }

    if(pRect->m_iLeft < 0 || pRect->m_iLeft >= SCREEN_WIDTH
        || pRect->m_iTop < 0 || pRect->m_iTop >= SCREEN_HEIGH)
    {
        return;
    }

    if((pRect->m_iLeft+pRect->m_iWidth) > SCREEN_WIDTH)
    {
        pRect->m_iWidth = SCREEN_WIDTH-pRect->m_iLeft;
    }

    if((pRect->m_iTop+pRect->m_iHeigh) > SCREEN_HEIGH)
    {
        pRect->m_iHeigh = SCREEN_HEIGH-pRect->m_iTop;
    }

    for(iH = 0; iH < pRect->m_iHeigh; iH++)    
    {
        for(iW = 0; iW < pRect->m_iWidth; iW++)
        {
            if((iH == 0 || iH == pRect->m_iHeigh-1) && (iW > 1 && iW < pRect->m_iWidth-2))
            {
                 SetPixel(iW+pRect->m_iLeft, iH+pRect->m_iTop, rgba);
            }else if((iH == 1 || iH == pRect->m_iHeigh-2) && (iW > 0 && iW < pRect->m_iWidth-1))
            {
                 SetPixel(iW+pRect->m_iLeft, iH+pRect->m_iTop, rgba);
            }
            else if(iH > 1 && iH < pRect->m_iHeigh-2)
            {
                SetPixel(iW+pRect->m_iLeft, iH+pRect->m_iTop, rgba);
            }
        }
    }
}

//#ifdef DOUBLE_BUFFER_PRINT

VOID FillRectRectBuffer(RGBA* pBuffer, PRect pBufRect, PRect pRect, RGBA rgba)
{
	INT iX, iY;
	for(iY = 0; iY < pRect->m_iHeigh; iY++)
	{
		for(iX = 0; iX < pRect->m_iWidth; iX++)
		{
			CPoint point;
			point.m_iX = iX+pRect->m_iLeft;
			point.m_iY = iY+pRect->m_iTop;
			if(PointInRect(&point, pBufRect))
			{
				pBuffer[point.m_iX+point.m_iY*pBufRect->m_iWidth] = rgba;
			}
		}
	}
}

VOID DrawRectRectBuffer(RGBA* pBuffer, PRect pBufRect, PRect pRect, RGBA rgba)
{
	INT iX, iY;
	for(iY = 0; iY < pRect->m_iHeigh; iY++)
	{
		CPoint point;
		point.m_iX = pRect->m_iLeft;
		point.m_iY = iY+pRect->m_iTop;
		if(PointInRect(&point, pBufRect))
		{
			pBuffer[point.m_iX+point.m_iY*pBufRect->m_iWidth] = rgba;
		}
	}

	for(iY = 0; iY < pRect->m_iHeigh; iY++)
	{
		CPoint point;
		point.m_iX = pRect->m_iLeft+pRect->m_iWidth-1;
		point.m_iY = iY+pRect->m_iTop;
		if(PointInRect(&point, pBufRect))
		{
			pBuffer[point.m_iX+point.m_iY*pBufRect->m_iWidth] = rgba;
		}
	}

	for(iX = 0; iX < pRect->m_iWidth; iX++)
	{
		CPoint point;
		point.m_iX = pRect->m_iLeft+iX;
		point.m_iY = pRect->m_iTop;
		if(PointInRect(&point, pBufRect))
		{
			pBuffer[point.m_iX+point.m_iY*pBufRect->m_iWidth] = rgba;
		}
	}

	for(iX = 0; iX < pRect->m_iWidth; iX++)
	{
		CPoint point;
		point.m_iX = pRect->m_iLeft+iX;
		point.m_iY = pRect->m_iTop+pRect->m_iHeigh-1;
		if(PointInRect(&point, pBufRect))
		{
			pBuffer[point.m_iX+point.m_iY*pBufRect->m_iWidth] = rgba;
		}
	}
}

//#endif


