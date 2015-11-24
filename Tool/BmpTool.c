#include "BmpTool.h"
#include "Color.h"

VOID SetBmpAlpha(PBitmap pBmp, INT iAlpha)
{
    INT i;
    if(pBmp == NULL)
    {
        return;
    }

    if(iAlpha > 255)
    {
        iAlpha = 255;
    }
    
    for(i = 0; i < pBmp->m_uBmpHeigh*pBmp->m_uBmpWidth; i++)
    {
        SetA(iAlpha, pBmp->m_pBmpBuf[i]);
    }
}


//...
