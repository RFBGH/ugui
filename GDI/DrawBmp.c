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

    //��λͼ�У����տ����չ�ķ�ʽ����λͼ�еľ��Σ���ӡ����Ļ��
    
    for(iHeighCnt = 0; iHeighCnt < pSrcRect->m_iHeigh; iHeighCnt++)
    {//��������λͼ�о��εĸ߶�

        //��ʼ������ͬ���صļ���
        iSameCnt = 1;
        //��ʼ����ǰ���У���Ļ�����������
        iSetX = 0;
        //��λ����λͼ�У�ԭ���εĿ�ʼ����λ��
        iOffset = ((iHeighCnt+pSrcRect->m_iTop)*pBmp->m_uBmpWidth)+pSrcRect->m_iLeft;

        for(iWidthCnt = 0; iWidthCnt < pSrcRect->m_iWidth; iWidthCnt++)
        {//����λͼ�о��ο��

            //�õ��������
            uColor = pBmp->m_pBmpBuf[iOffset+iWidthCnt];
            //���õ���Ļ�����У�����������
            pColorBuf[iSetX + iHeighCnt*pDstRect->m_iWidth] = uColor;
            iSetX++;

            if((iWidthCnt < pSrcRect->m_iWidth-1) 
                && (uColor == pBmp->m_pBmpBuf[iOffset+iWidthCnt+1]))
            {//�����ǰ���غ���һ��������ͬ����ͬ���ؼ�����һ
                iSameCnt++;
            }else
            {//�����ǰ���غ���һ�����ز���ͬ
             //����ҪEXPAND��ͬ���ص�����

                //�õ��Ŵ����
                iSameCnt = iSameCnt*pDstRect->m_iWidth;
                if((iSameCnt % pSrcRect->m_iWidth) > (pSrcRect->m_iWidth>>1))
                {
                    iSameCnt += pSrcRect->m_iWidth;
                }
                iSameCnt = iSameCnt/pSrcRect->m_iWidth;

                //���Ŵ�������
                for(i = 0; i < iSameCnt; i++)
                {
                    pColorBuf[iSetX + iHeighCnt*pDstRect->m_iWidth] = uColor;
                    iSetX++;
                }
            }
        }
    }

    //����ɫ�����ϣ��Ѿ������չ���ľ��Σ����߶�������չ
    for(iWidthCnt = 0; iWidthCnt < pDstRect->m_iWidth; iWidthCnt++)
    {//����������ɫ�����о��εĿ��

        //��ʼ������ͬ���صļ���
        iSameCnt = 1;
        //��ʼ����ǰ���У���Ļ�����������
        iSetY = 0;

        for(iHeighCnt = 0; iHeighCnt < pSrcRect->m_iHeigh; iHeighCnt++)
        {//��λͼ�еľ��θ߶ȣ�����λ��Ļ���θ߶�

            //�õ��������
            uColor = pColorBuf[iWidthCnt+(iHeighCnt*pDstRect->m_iWidth)];

            //���õ���Ļ�����У�����������
            SetPixel(pDstRect->m_iLeft+iWidthCnt, pDstRect->m_iHeigh+iSetY, (RGBA)uColor);
            iSetY++;

            if((iHeighCnt < pSrcRect->m_iHeigh-1) 
                && (uColor == pBmp->m_pBmpBuf[iWidthCnt+((iHeighCnt+1)*pDstRect->m_iWidth)]))
            {//�����ǰ���غ���һ��������ͬ����ͬ���ؼ�����һ
                iSameCnt++;
            }else
            {//�����ǰ���غ���һ�����ز���ͬ
             //����ҪEXPAND��ͬ���ص�����

                //�õ��Ŵ����
                iSameCnt = iSameCnt*pDstRect->m_iHeigh;
                if((iSameCnt % pSrcRect->m_iHeigh) > (pSrcRect->m_iHeigh>>1))
                {
                    iSameCnt += pSrcRect->m_iHeigh;
                }
                iSameCnt = iSameCnt/pSrcRect->m_iHeigh;

                //���Ŵ�������
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
            //��λͼ�����Ƶ���Ļ��
            DrawBmp_SOLID_CP(pDstRect, pSrcRect, pBmp);
            break;

        case DRAW_BMP_ADAPT_FILL:
            //��λͼ����չ��䵽��Ļ��
            DrawBmp_ADAPT_FILL(pDstRect, pSrcRect, pBmp);
            break;

        case DRAW_BMP_REPEAT_CP:
            //��λͼ����Ҷ��ʽ�����
            DrawBmp_REPEAT_CP(pDstRect, pSrcRect, pBmp);
            break;

        default:

            break;
    }
}

