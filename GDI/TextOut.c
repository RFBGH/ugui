/****************************************************************************
*
*this procedure is work for textout ascii info(8x16).
*
*############################################################################
*AUTHOR:RFB 	LOG: Creat this procedure	 TIME:2013/01/11
*****************************************************************************/
#include "Res.h"
#include "TextOut.h"

/*
 * text a ascii charactor.
 *
 * @param x: x coordinate of c in screen
 *        y: y coordinate of c in screen
 *        c: character printed in screen
 *        RGBA: color
 *       
 *
 * @return NULL
 */

VOID TextOutAsc8X16(INT x, INT y, CHAR c, RGBA rgba)
{
    INT i;
    INT iBit;
    INT iOffset;
    UCHAR uczAsc[32];

    iOffset = c - ' ';
    iOffset *= 16;
    
    MemCpy(uczAsc, guczAsc8x16Fonts + iOffset, 16);

    for(i = 0; i < ASC8x16_HEIGH; i++)
    {
        for(iBit = ASC8x16_WIDTH-1; iBit >= 0; iBit--)
        {
            if(uczAsc[i]&(1<<iBit))
            {
                SetPixel(x+(ASC8x16_WIDTH-1-iBit), y+i, rgba);
            }
        }
    }
}

/*
 * text a ascii charactor.
 *
 * @param x: x coordinate of c in screen
 *        y: y coordinate of c in screen
 *        c: character printed in screen
 *        RGBA: color
 *       
 *
 * @return NULL
 */
VOID TextOut8X16(INT x, INT y, CONST CHAR* pTip, RGBA rgba)
{
    CHAR c;
    INT iStrLen;
    INT i;
    INT sx, sy;

    sx = x;
    sy = y;
    iStrLen = Strlen(pTip);
    for(i = 0; i < iStrLen; i++)
    {
        c = pTip[i];

        if(c=='\n')
        {
            sx = x;
            sy += ASC8x16_HEIGH;
            continue;
        }

        
        if(c < ' ' || c > '~')
        {
            c = '?';
        }

        TextOutAsc8X16(sx, sy ,c, rgba);
        sx += ASC8x16_WIDTH;
        if(sx > SCREEN_WIDTH)
        {
            sx = x;
            sy += ASC8x16_HEIGH;
        }
    }
}


VOID TextOutAsc8X16E(INT x, INT y, CHAR c, RGBA rgba, PRect pRect, UINT uFlag)
{
    INT i;
    INT iBit;
    INT iOffset;
	CPoint point;
    UCHAR uczAsc[32];

    iOffset = c - ' ';
    iOffset *= 16;
    
    MemCpy(uczAsc, guczAsc8x16Fonts + iOffset, 16);

    for(i = 0; i < ASC8x16_HEIGH; i++)
    {
        for(iBit = ASC8x16_WIDTH-1; iBit >= 0; iBit--)
        {
            if(uczAsc[i]&(1<<iBit))
            {
				point.m_iX = x+(ASC8x16_WIDTH-1-iBit);
				point.m_iY = y+i;
				if(PointInRect(&point, pRect))
				{
					SetPixel(point.m_iX, point.m_iY, rgba);
				}
            }
        }
    }
}

/*
 * text a ascii charactor.
 *
 * @param x: x coordinate of c in screen
 *        y: y coordinate of c in screen
 *        c: character printed in screen
 *        RGBA: color
 *        pRect: text in rect
 *        uFlag: text flag
 *       
 *
 * @return NULL
 */
VOID TextOut8X16E(INT x, INT y, PRect pRect, CONST CHAR* pTip, RGBA rgba, UINT uFlag)
{
    CHAR c;
    INT iStrLen;
    INT i;
    INT sx, sy;

    sx = x;
    sy = y;

    iStrLen = Strlen(pTip);

    for(i = 0; i < iStrLen; i++)
    {
        c = pTip[i];

        if(c=='\n')
        {
            sx = x;
            sy += ASC8x16_HEIGH;
            continue;
        }

        
        if(c < ' ' || c > '~')
        {
            c = '?';
        }

        TextOutAsc8X16E(sx, sy ,c, rgba, pRect, uFlag);
        sx += ASC8x16_WIDTH;
        if(sx > SCREEN_WIDTH)
        {
            sx = x;
            sy += ASC8x16_HEIGH;
        }

		if(uFlag & TEXTOUT_FLAG_AUTO_NEW_LINE)
		{//support the auto new line.
			if(sx >= pRect->m_iLeft+pRect->m_iWidth)
			{
				sx = x;
				sy += ASC8x16_HEIGH;
			}
		}

		if(sy > pRect->m_iTop + pRect->m_iHeigh)
		{//out the print area.
			break;
		}
    }
}

//#ifdef DOUBLE_BUFFER_PRINT

VOID TextOutAsc8X16RectBuffer(RGBA* pBuffer, PRect pBufRect,INT x, INT y, CHAR c, RGBA rgba, UINT uFlag)
{
    INT i;
    INT iBit;
    INT iOffset;
    UCHAR uczAsc[32];

    iOffset = c - ' ';
    iOffset *= 16;
    
    MemCpy(uczAsc, guczAsc8x16Fonts + iOffset, 16);

    for(i = 0; i < ASC8x16_HEIGH; i++)
    {
        for(iBit = ASC8x16_WIDTH-1; iBit >= 0; iBit--)
        {
            if(uczAsc[i]&(1<<iBit))
            {
				CPoint point;
				point.m_iX = x+(ASC8x16_WIDTH-1-iBit);
				point.m_iY = y+i;
				if(PointInRect(&point, pBufRect))
				{
					pBuffer[point.m_iX+point.m_iY*pBufRect->m_iWidth] =  rgba;
				}           
            }
        }
    }
}

VOID TextOut8X16ERectBuffer(RGBA* pBuffer, INT x, INT y, PRect pBufRect, CONST CHAR* pTip, RGBA rgba, UINT uFlag)
{
    CHAR c;
    INT iStrLen;
    INT i;
    INT sx, sy;

    sx = x;
    sy = y;

    iStrLen = Strlen(pTip);

	if(x+ASC8x16_WIDTH > pBufRect->m_iLeft+pBufRect->m_iWidth)
	{
		return;
	}
	
	if(uFlag & TEXT_OUT_IN_RECT_MULTI_LINE)
	{
		for(i = 0; i < iStrLen; i++)
		{
			c = pTip[i];
		
			if(c=='\n')
			{
				sx = x;
				sy += ASC8x16_HEIGH;
				continue;
			}
		
			
			if(c < ' ' || c > '~')
			{
				c = '?';
			}
		
			if((sx+ASC8x16_WIDTH) >= pBufRect->m_iLeft+pBufRect->m_iWidth)
			{
				sx = x;
				sy += ASC8x16_HEIGH;
			}
		
			TextOutAsc8X16RectBuffer(pBuffer, pBufRect, sx, sy ,c, rgba, uFlag);
			sx += ASC8x16_WIDTH;
			/*
			sx += ASC8x16_WIDTH;
			if(sx >= )
			{
				sx = x;
				sy += ASC8x16_HEIGH;
			}
			*/
			if(sy+ASC8x16_WIDTH > pBufRect->m_iTop + pBufRect->m_iHeigh)
			{//out the print area.
				break;
			}
		}
	}
	else
	{
		if(uFlag & TEXT_OUT_IN_RECT_KEEP_RIGHT)
		{
			
		}else
		{
			for(i = 0; i < iStrLen; i++)
			{
				c = pTip[i];
				if(c == '\n')
				{
					continue;
				}
				
				if(c < ' ' || c > '~')
				{
					c = '?';
				}

				if((sx+ASC8x16_WIDTH) >= pBufRect->m_iLeft+pBufRect->m_iWidth)
				{
					sx = x;
					break;
				}

				TextOutAsc8X16RectBuffer(pBuffer, pBufRect, sx, sy ,c, rgba, uFlag);
				sx += ASC8x16_WIDTH;
			}
		}
	}
}

#if 0
INT MaxFullPrintAsc8x16(PRect pRect, CHAR* pcStr, INT iLen)
{
	INT ret;
	INT i;
	INT iX, iY;
	
	if(pRect == NULL || pcStr == NULL || iLen == 0)
	{
		return 0;
	}

	iX = 0;
	iY = 0;
	
	for(i = 0; i < iLen; i++)
	{
		if(pcStr[i] == '\n')
		{
			iX = 0;
			iY += ASC8x16_HEIGH;
		}

		if((iX+ASC8x16_WIDTH) >= pRect->m_iWidth)
		{
			iX = 0;
			iY += ASC8x16_HEIGH;			
		}

		if((iX+ASC8x16_WIDTH) < pRect->m_iWidth)
		{
			iX += ASC8x16_WIDTH;
		}

		if((iY+ASC8x16_HEIGH) > pRect->m_iHeigh)
		{
			break;
		}
	}

	return i;
}
#endif

/*
找到能在PRECT矩形中显示的str字符的开始索引
*/
INT MaxFullPrintAsc8x16(PRect pRect, CHAR* pcStr, INT iCurEdit, UINT* r_uXY)
{
	INT ret;
	INT i;
	INT iX, iY;
	INT iOffset;
	
	if(pRect == NULL || pcStr == NULL || iCurEdit == 0)
	{
		*r_uXY = 0;
		return 0;
	}

	iX = 0;
	iY = 0;

	iOffset = 0;

	for(i = 0; i < iCurEdit; i++)
	{
		if(pcStr[i] == '\n')
		{
			iX = 0;
			iY += ASC8x16_HEIGH;
		}
	
		if((iX+ASC8x16_WIDTH) >= pRect->m_iWidth)
		{
			iX = 0;
			iY += ASC8x16_HEIGH;			
		}
	
		if((iY+ASC8x16_HEIGH) > pRect->m_iHeigh)
		{
			iX = 0;
			iY = 0;
			iOffset = i;
		}

		iX += ASC8x16_WIDTH;
	}

	*r_uXY = ((iX<<16)|iY);
	return (iOffset);
}


#if 0
INT CurrEditTextOut(PRect pRect, CHAR* pcStr, INT iLen)
{
	INT ret;
	INT i;
	INT iX, iY;
	
	if(pRect == NULL || pcStr == NULL || iLen == 0)
	{
		return 0;
	}

	iX = 0;
	iY = 0;
	
	for(i = 0; i < iLen; i++)
	{
		if(pcStr[i] == '\n')
		{
			iX = 0;
			iY += ASC8x16_HEIGH;
		}

		if((iX+ASC8x16_WIDTH) >= pRect->m_iWidth)
		{
			iX = 0;
			iY += ASC8x16_HEIGH;			
		}

		if((iX+ASC8x16_WIDTH) < pRect->m_iWidth)
		{
			iX += ASC8x16_WIDTH;
		}

		if((iY+ASC8x16_HEIGH) > pRect->m_iHeigh)
		{
			break;
		}
	}

}
#endif

