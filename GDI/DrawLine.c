/****************************************************************************
*
*this procedure is work for draw line.
*
*############################################################################
*AUTHOR:RFB 	LOG: Creat this procedure	 TIME:2013/01/11
*****************************************************************************/

#include "DrawLine.h"

#include "Tool.h"

/*
 * draw a line in screen.
 *
 * @param pStart: start point of line.
 *        pEnd:   end point of line.
 *       
 *
 * @return NULL
 */
VOID DrawLine(PPoint pStart, PPoint pEnd, RGBA rgba)
{
    INT sx, sy;
    INT ex, ey;
    INT d, dx, dy;
    INT t;
    PPoint pTmp;

    dx = pEnd->m_iX-pStart->m_iX;
    dy = pEnd->m_iY-pStart->m_iY;

    if(dx < 0)
    {
        dx = -dx;
    }

    if(dy < 0)
    {
        dy = -dy;
    }

    if(dy == 0)
    {
         if(pStart->m_iX < pEnd->m_iX)
        {
            sx = pStart->m_iX;
            sy = pStart->m_iY;
            ex = pEnd->m_iX;
            ey = pEnd->m_iY;
            
        }else
        {
            sx = pEnd->m_iX;
            sy = pEnd->m_iY;
            ex = pStart->m_iX;
            ey = pStart->m_iY;
        }

        while(sx <= ex)
        {
            SetPixel(sx, sy, rgba);
            sx++;
        }
        return;
    }

    if(dx == 0)
    {
        if(pStart->m_iY < pEnd->m_iY)
        {
            sx = pStart->m_iX;
            sy = pStart->m_iY;
            ex = pEnd->m_iX;
            ey = pEnd->m_iY;
            
        }else
        {
            sx = pEnd->m_iX;
            sy = pEnd->m_iY;
            ex = pStart->m_iX;
            ey = pStart->m_iY;
        }
        
        while(sy <= ey)
        {
            SetPixel(sx, sy, rgba);
            sy++;
        }
        return;
    }  

    if(dx > dy)
    {
        if(pStart->m_iX < pEnd->m_iX)
        {
            sx = pStart->m_iX;
            sy = pStart->m_iY;
            ex = pEnd->m_iX;
            ey = pEnd->m_iY;
            
        }else
        {
            sx = pEnd->m_iX;
            sy = pEnd->m_iY;
            ex = pStart->m_iX;
            ey = pStart->m_iY;
        }

        d = (ex-sx)/(ey-sy);
        t = d;
        while(sx <= ex)
        {
            SetPixel(sx, sy, rgba);
            sx++;
            if(t > 0)
            {
                t--;
            }else
            {
                t++;
            }

            if(t == 0)
            {
                t = d;
                if(d > 0)
                {
                    sy++;
                }else{
                    sy--;
                }
            }
        }
            
    }else
    {
        if(pStart->m_iY < pEnd->m_iY)
        {
            sx = pStart->m_iX;
            sy = pStart->m_iY;
            ex = pEnd->m_iX;
            ey = pEnd->m_iY;
            
        }else
        {
            sx = pEnd->m_iX;
            sy = pEnd->m_iY;
            ex = pStart->m_iX;
            ey = pStart->m_iY;
        }

        d = (ey-sy)/(ex-sx);
        t = d;

        
        while(sy <= ey)
        {
            
            SetPixel(sx, sy, rgba);
            sy++;
            if(t > 0)
            {
                t--;
            }else
            {
                t++;
            }

            if(t == 0)
            {
                t = d;
                if(d > 0)
                {
                    sx++;
                }else{
                    sx--;
                }
            }
        }
    }
}

VOID DrawLineRectBuffer(RGBA* pBuffer, PRect pBufRect, PPoint pStart, PPoint pEnd, RGBA rgba)
{
    INT sx, sy;
    INT ex, ey;
    INT d, dx, dy;
    INT t;
    PPoint pTmp;

    dx = pEnd->m_iX-pStart->m_iX;
    dy = pEnd->m_iY-pStart->m_iY;

    if(dx < 0)
    {
        dx = -dx;
    }

    if(dy < 0)
    {
        dy = -dy;
    }

    if(dy == 0)
    {
         if(pStart->m_iX < pEnd->m_iX)
        {
            sx = pStart->m_iX;
            sy = pStart->m_iY;
            ex = pEnd->m_iX;
            ey = pEnd->m_iY;
            
        }else
        {
            sx = pEnd->m_iX;
            sy = pEnd->m_iY;
            ex = pStart->m_iX;
            ey = pStart->m_iY;
        }

        while(sx <= ex)
        {
            //SetPixel(sx, sy, rgba);
            pBuffer[sx+sy*pBufRect->m_iWidth] = rgba;
            sx++;
        }
        return;
    }

    if(dx == 0)
    {
        if(pStart->m_iY < pEnd->m_iY)
        {
            sx = pStart->m_iX;
            sy = pStart->m_iY;
            ex = pEnd->m_iX;
            ey = pEnd->m_iY;
            
        }else
        {
            sx = pEnd->m_iX;
            sy = pEnd->m_iY;
            ex = pStart->m_iX;
            ey = pStart->m_iY;
        }
        
        while(sy <= ey)
        {
            //SetPixel(sx, sy, rgba);
            pBuffer[sx+sy*pBufRect->m_iWidth] = rgba;
            sy++;
        }
        return;
    }  

    if(dx > dy)
    {
        if(pStart->m_iX < pEnd->m_iX)
        {
            sx = pStart->m_iX;
            sy = pStart->m_iY;
            ex = pEnd->m_iX;
            ey = pEnd->m_iY;
            
        }else
        {
            sx = pEnd->m_iX;
            sy = pEnd->m_iY;
            ex = pStart->m_iX;
            ey = pStart->m_iY;
        }

        d = (ex-sx)/(ey-sy);
        t = d;
        while(sx <= ex)
        {
            //SetPixel(sx, sy, rgba);
            pBuffer[sx+sy*pBufRect->m_iWidth] = rgba;
            sx++;
            if(t > 0)
            {
                t--;
            }else
            {
                t++;
            }

            if(t == 0)
            {
                t = d;
                if(d > 0)
                {
                    sy++;
                }else{
                    sy--;
                }
            }
        }
            
    }else
    {
        if(pStart->m_iY < pEnd->m_iY)
        {
            sx = pStart->m_iX;
            sy = pStart->m_iY;
            ex = pEnd->m_iX;
            ey = pEnd->m_iY;
            
        }else
        {
            sx = pEnd->m_iX;
            sy = pEnd->m_iY;
            ex = pStart->m_iX;
            ey = pStart->m_iY;
        }

        d = (ey-sy)/(ex-sx);
        t = d;

        
        while(sy <= ey)
        {
            
            //SetPixel(sx, sy, rgba);
            pBuffer[sx+sy*pBufRect->m_iWidth] = rgba;
            sy++;
            if(t > 0)
            {
                t--;
            }else
            {
                t++;
            }

            if(t == 0)
            {
                t = d;
                if(d > 0)
                {
                    sx++;
                }else{
                    sx--;
                }
            }
        }
    }
}


