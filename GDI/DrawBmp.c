#include "DrawBmp.h"

STATIC VOID DrawBmp_SOLID_CP(PRect pDstRect, PRect pSrcRect, PBitmap pBmp)
{
    INT iWidthCnt;
    INT iHeighCnt;
    INT iOffset;
    UINT uColor;  

    for(iHeighCnt = 0; iHeighCnt < pSrcRect->m_iHeigh; iHeighCnt++)
    {
        if(iHeighCnt > pDstRect->m_iHeigh)
        {//heigh is out of the rect in screen.
            break;
        }
        
        iOffset = ((iHeighCnt+pSrcRect->m_iTop)*pBmp->m_uBmpWidth)+pSrcRect->m_iLeft;
        for(iWidthCnt = 0; iWidthCnt < pSrcRect->m_iWidth; iWidthCnt++)
        {
            if(iWidthCnt > pDstRect->m_iWidth)
            {//width is out of the rect in screen.
                break;
            }
            uColor = pBmp->m_pBmpBuf[iOffset+iWidthCnt];
            SetPixel(pDstRect->m_iLeft+iWidthCnt, pDstRect->m_iTop+iHeighCnt, (RGBA)uColor);
        }
    }
}

STATIC VOID DrawBmp_ADAPT_FILL(PRect pDstRect, PRect pSrcRect, PBitmap pBmp)
{
    INT iWidthCnt;
    INT iHeighCnt;
    UINT uColor;  
    INT iSameCnt;
    INT iOffset;
    INT iSetX;
    INT iSetY;
    INT i;

    UINT* pColorBuf;

    iSetX = 0;
    iSetY = 0;

    pColorBuf = (UINT*)Malloc(pDstRect->m_iWidth*pSrcRect->m_iHeigh*sizeof(UINT));

    if(!pColorBuf)
    {
        return;
    }

    //在位图中，按照宽度扩展的方式，将位图中的矩形，打印到屏幕上
    
    for(iHeighCnt = 0; iHeighCnt < pSrcRect->m_iHeigh; iHeighCnt++)
    {//遍历，在位图中矩形的高度

        //初始化，相同像素的计数
        iSameCnt = 1;
        //初始化当前行中，屏幕缓存的列索引
        iSetX = 0;
        //定位到，位图中，原矩形的开始像素位置
        iOffset = ((iHeighCnt+pSrcRect->m_iTop)*pBmp->m_uBmpWidth)+pSrcRect->m_iLeft;

        for(iWidthCnt = 0; iWidthCnt < pSrcRect->m_iWidth; iWidthCnt++)
        {//遍历位图中矩形宽度

            //得到相关像素
            uColor = pBmp->m_pBmpBuf[iOffset+iWidthCnt];
            //设置到屏幕矩形中，并增大索引
            pColorBuf[iSetX + iHeighCnt*pDstRect->m_iWidth] = uColor;
            iSetX++;

            if((iWidthCnt < pSrcRect->m_iWidth-1) 
                && (uColor == pBmp->m_pBmpBuf[iOffset+iWidthCnt+1]))
            {//如果当前像素和下一个像素相同，相同像素计数加一
                iSameCnt++;
            }else
            {//如果当前像素和下一个像素不相同
             //则需要EXPAND相同像素的索引

                //得到放大比例
                iSameCnt = iSameCnt*pDstRect->m_iWidth;
                if((iSameCnt % pSrcRect->m_iWidth) > (pSrcRect->m_iWidth>>1))
                {
                    iSameCnt += pSrcRect->m_iWidth;
                }
                iSameCnt = iSameCnt/pSrcRect->m_iWidth;

                //填充放大后的像素
                for(i = 0; i < iSameCnt; i++)
                {
                    pColorBuf[iSetX + iHeighCnt*pDstRect->m_iWidth] = uColor;
                    iSetX++;
                }
            }
        }
    }

    //将颜色缓存上，已经宽度扩展过的矩形，按高度重新扩展
    for(iWidthCnt = 0; iWidthCnt < pDstRect->m_iWidth; iWidthCnt++)
    {//遍历，在颜色缓存中矩形的宽度

        //初始化，相同像素的计数
        iSameCnt = 1;
        //初始化当前行中，屏幕缓存的列索引
        iSetY = 0;

        for(iHeighCnt = 0; iHeighCnt < pSrcRect->m_iHeigh; iHeighCnt++)
        {//按位图中的矩形高度，遍历位屏幕矩形高度

            //得到相关像素
            uColor = pColorBuf[iWidthCnt+(iHeighCnt*pDstRect->m_iWidth)];

            //设置到屏幕矩形中，并增大索引
            SetPixel(pDstRect->m_iLeft+iWidthCnt, pDstRect->m_iHeigh+iSetY, (RGBA)uColor);
            iSetY++;

            if((iHeighCnt < pSrcRect->m_iHeigh-1) 
                && (uColor == pBmp->m_pBmpBuf[iWidthCnt+((iHeighCnt+1)*pDstRect->m_iWidth)]))
            {//如果当前像素和下一个像素相同，相同像素计数加一
                iSameCnt++;
            }else
            {//如果当前像素和下一个像素不相同
             //则需要EXPAND相同像素的索引

                //得到放大比例
                iSameCnt = iSameCnt*pDstRect->m_iHeigh;
                if((iSameCnt % pSrcRect->m_iHeigh) > (pSrcRect->m_iHeigh>>1))
                {
                    iSameCnt += pSrcRect->m_iHeigh;
                }
                iSameCnt = iSameCnt/pSrcRect->m_iHeigh;

                //填充放大后的像素
                for(i = 0; i < iSameCnt; i++)
                {
                    SetPixel(pDstRect->m_iLeft+iWidthCnt, pDstRect->m_iHeigh+iSetY, (RGBA)uColor);
                    iSetY++;
                }
            }
        }
    }

    Free(pColorBuf);
}

STATIC VOID DrawBmp_REPEAT_CP(PRect pDstRect, PRect pSrcRect, PBitmap pBmp)
{
    INT iWidthCnt;
    INT iHeighCnt;
    INT iOffset;
    UINT uColor;  

    for(iHeighCnt = 0; iHeighCnt < pDstRect->m_iHeigh; iHeighCnt++)
    {
        iOffset = ((iHeighCnt%pSrcRect->m_iHeigh)+pSrcRect->m_iTop)*pSrcRect->m_iWidth+pSrcRect->m_iLeft;
        for(iWidthCnt = 0; iWidthCnt < pDstRect->m_iWidth; iWidthCnt++)
        {
            uColor = pBmp->m_pBmpBuf[iOffset+(iWidthCnt%pSrcRect->m_iWidth)];
            SetPixel(pDstRect->m_iLeft+iWidthCnt, pDstRect->m_iTop+iHeighCnt, (RGBA)uColor);
        }
    }
}

VOID DrawBmp(PRect pDstRect, PRect pSrcRect, PBitmap pBmp, INT iType)
{

//format BMP in SCREEN
    if(pDstRect->m_iLeft < 0)
    {
        pDstRect->m_iLeft = 0;
    }

    if((pDstRect->m_iLeft+pDstRect->m_iWidth) > SCREEN_WIDTH)
    {
        pDstRect->m_iWidth = SCREEN_WIDTH-pDstRect->m_iLeft;
    }

    if(pDstRect->m_iTop < 0)
    {
        pDstRect->m_iTop = 0;
    }

    if((pDstRect->m_iTop+pDstRect->m_iHeigh) > SCREEN_HEIGH)
    {
        pDstRect->m_iHeigh = SCREEN_HEIGH - pDstRect->m_iTop;
    }

//format rect in BMP
    if(pSrcRect->m_iLeft < 0)
    {
        pSrcRect->m_iLeft = 0;
    }

    if((pSrcRect->m_iLeft+pSrcRect->m_iWidth) > pBmp->m_uBmpWidth)
    {
        pSrcRect->m_iWidth = pBmp->m_uBmpWidth-pSrcRect->m_iLeft;
    }

    if(pSrcRect->m_iTop < 0)
    {
        pSrcRect->m_iTop = 0;
    }

    if((pSrcRect->m_iTop+pSrcRect->m_iHeigh) > pBmp->m_uBmpHeigh)
    {
        pSrcRect->m_iHeigh =  pBmp->m_uBmpHeigh - pSrcRect->m_iTop;
    }   


    switch(iType)
    {
        case DRAW_BMP_SOLID_CP:
            //将位图，复制到屏幕上
            DrawBmp_SOLID_CP(pDstRect, pSrcRect, pBmp);
            break;

        case DRAW_BMP_ADAPT_FILL:
            //将位图，扩展填充到屏幕上
            DrawBmp_ADAPT_FILL(pDstRect, pSrcRect, pBmp);
            break;

        case DRAW_BMP_REPEAT_CP:
            //将位图，百叶窗式的填充
            DrawBmp_REPEAT_CP(pDstRect, pSrcRect, pBmp);
            break;

        default:

            break;
    }
}

