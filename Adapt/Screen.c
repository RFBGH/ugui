/****************************************************************************
*
*this procedure is work for the memory screen.
*
*############################################################################
*AUTHOR:RFB 	LOG: Creat this procedure	 TIME:2013/01/11
*****************************************************************************/

#include "stdio.h"

#include "Screen.h"

#include "Tool.h"

RGBA ScreenBuf[SCREEN_WIDTH*SCREEN_HEIGH+8];


/*
 * init screen buffer...
 *
 * @param null
 *
 * @return null
 *
 * @note: null
 */

VOID InitScreen(VOID)
{
    MemSet(ScreenBuf, 0xFF, sizeof(ScreenBuf));
}

/*
 * fill screen buffer with color...
 *
 * @param rgbaScreen: the color fill in screen
 *
 * @return null
 *
 * @note: null
 */

VOID CleanScreen(RGBA rgbaScreen)
{
    MemSet(ScreenBuf, rgbaScreen, sizeof(ScreenBuf));
}

/*
 * save screen buffer of rect...
 *
 * @param pScreenBuf: buffer to keep screen buffer.
 *        pRect: the rect of screen you want to keep.
 *
 * @return null
 *
 * @note: null
 */
VOID PushScreen(RGBA* pScreenBuf, PRect pRect)
{
    INT iW;
    INT iH;
    RGBA* pTmpBuf;
    
    if(pRect == NULL || pScreenBuf == NULL)
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

    pTmpBuf = pScreenBuf;
    for(iH = 0; iH < pRect->m_iHeigh; iH++)    
    {
        for(iW = 0; iW < pRect->m_iWidth; iW++)
        {
            *pTmpBuf++ = GetPixel(iW+pRect->m_iLeft, iH+pRect->m_iHeigh);
        }
    }
}

/*
 * restore screen buffer of rect by screen buffer...
 *
 * @param pScreenBuf: buffer to keep screen buffer.
 *        pRect: the rect of screen you want to restore.
 *
 * @return null
 *
 * @note: null
 */
VOID PopScreen(RGBA* pScreenBuf, PRect pRect)
{
    INT iW;
    INT iH;
    RGBA* pTmpBuf;
    
    if(pRect == NULL || pScreenBuf == NULL)
    {
        return;
    }

    if(pRect->m_iLeft < 0 || pRect->m_iLeft >= SCREEN_WIDTH
        || pRect->m_iTop < 0 || pRect->m_iTop >= SCREEN_HEIGH)
    {
        return;
    }

    if((pRect->m_iLeft+pRect->m_iWidth) >= SCREEN_WIDTH
        || (pRect->m_iTop+pRect->m_iHeigh) >= SCREEN_HEIGH)
    {
        return;
    }

    pTmpBuf = pScreenBuf;
    for(iH = 0; iH < pRect->m_iHeigh; iH++)    
    {
        for(iW = 0; iW < pRect->m_iWidth; iW++)
        {
            SetPixel(iW+pRect->m_iLeft, iH+pRect->m_iHeigh, *pTmpBuf++);
        }
    }
}


/*
 * set pixel in screen.
 *
 * @param x: x of pixel in screen.
 *        y: y of pixel in screen.
 *        rgba: the color want to fill
 *
 * @return null
 *
 * @note: null
 */
VOID SetPixel(INT x, INT y, RGBA rgba)
{
    INT offset;

    if(x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGH)
    {
        return;
    }

#ifdef CFG_SUPPORT_ALPHA
{
    RGBA rgbaBk = GetPixel(x, y);
    RGBA rgbaResult;
    UINT  Alpha;
    Alpha = GetA(rgba);

    rgbaResult = RGB(GetR(rgba)*Alpha/255+GetR(rgbaBk)-GetR(rgbaBk)*Alpha/255,
                     GetG(rgba)*Alpha/255+GetG(rgbaBk)-GetG(rgbaBk)*Alpha/255,
                     GetB(rgba)*Alpha/255+GetB(rgbaBk)-GetB(rgbaBk)*Alpha/255);
    rgba = rgbaResult;
}
#endif

    offset = y*SCREEN_WIDTH+x;
    ScreenBuf[offset] = rgba;
}

/*
 * get pixel rgba in screen.
 *
 * @param x: x of pixel in screen.
 *        y: y of pixel in screen.
 *
 * @return pixel rgba in screen
 *
 * @note: null
 */

RGBA GetPixel(INT x, INT y)
{
    INT offset;
    
    if(x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGH)
    {
        return 0;
    }

    offset = y*SCREEN_WIDTH+x;
    return ScreenBuf[offset];
}

//#ifdef DEBUG_IN_WINDOWS

VOID PrintScreen(VOID)
{
    FILE* pFile;
    INT iWidth;
    INT iHeigh;
    
    pFile = fopen("./screen.bin","wb+");

    if(pFile == NULL)
    {
        return;
    }

    iWidth = SCREEN_WIDTH;
    iHeigh = SCREEN_HEIGH;
    
    fwrite(&iWidth, sizeof(INT), 1, pFile);
    fwrite(&iHeigh, sizeof(INT), 1, pFile);
    fwrite(ScreenBuf, sizeof(ScreenBuf), 1, pFile);

    fclose(pFile);
}

//#endif


