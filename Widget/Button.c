#include "Button.h"

#include "GDI.h"
#include "WinType.h"


STATIC VOID WinDispatchMsgButton(HANDLE handle, INT iMsgID, UINT uMsg, PVOID pMsg)
{
	PButton pBtn = (PButton)H2P(handle);

	switch(iMsgID)
	{
		case WIN_MSG_ID_CLICK_SCREEN_DOWN:
		{
			PPoint pPoint = (PPoint)pMsg;
			PWindow pParent;

			if(PointInRect(pPoint, &pBtn->m_baseWin.m_rect))
			{
				pParent = pBtn->m_baseWin.m_pParent;
				pParent->m_pfPostMessage(P2H(pParent), pBtn->m_iMsgID, pBtn->m_baseWin.m_iID, NULL);
			}

			//Free(pPoint);
		}
		break;

		case WIN_MSG_ID_REPAINT:
			pBtn->m_baseWin.m_pfPrintWindow(P2H(&pBtn->m_baseWin));
		break;

		default:
			//do nothing...
		break;
	}

	
	return;
}

#define BUTTON_VALUE_SHOW_LEFTST 1
#define BUTTON_VALUE_SHOW_TOPEST 2

STATIC VOID PrintWindowBtn(HANDLE handle)
{
	PButton pBtn = (PButton)H2P(handle);

	INT x;
	INT y;
	INT iFlag;

    PWindow pWinParent;
	PWindow pWin;

	pWin = &pBtn->m_baseWin;
    pWinParent = pWin->m_pParent;
	
    if(pWinParent == NULL)
    {
        CopyRect(&pWin->m_showRect, &pWin->m_rect);
    }
    else
    {
        RectInRect(&pWinParent->m_showRect, &pWin->m_rect, &pWin->m_showRect);
    }

	//x = pBtn->m_baseWin.m_rect.m_iLeft;
	//y = pBtn->m_baseWin.m_rect.m_iTop;
	x = 0;
	y = 0;
	iFlag = pBtn->m_baseWin.m_iWinFlag;

	if(!(iFlag&BUTTON_VALUE_SHOW_LEFTST))
	{
		INT iLen;
		iLen = Strlen(pBtn->m_czBtnTitl);
		iLen *= ASC8x16_WIDTH;
		x += pBtn->m_baseWin.m_rect.m_iWidth/2-iLen/2;
	}

	if(!(iFlag&BUTTON_VALUE_SHOW_TOPEST))
	{
		y += pBtn->m_baseWin.m_rect.m_iHeigh/2-ASC8x16_HEIGH/2;
	}

	if(pWin->m_showRect.m_iHeigh && pWin->m_showRect.m_iWidth)
	{
		RGBA* pLocalScreen = NULL;
		CRect bufferRect;
		CRect rect;
		CBitmap bmp;
		INT iStrOffset;
		UINT uCurEditXY;

		pLocalScreen = (RGBA*)Malloc(pWin->m_showRect.m_iHeigh*pWin->m_showRect.m_iWidth*sizeof(RGBA));
		if(pLocalScreen == NULL)
		{
			return ;
		}

		bufferRect.m_iHeigh = pWin->m_rect.m_iHeigh;
		bufferRect.m_iWidth = pWin->m_rect.m_iWidth;
		bufferRect.m_iTop = 0;
		bufferRect.m_iLeft = 0;
		FillRectRectBuffer(pLocalScreen, &bufferRect, &bufferRect, pWin->m_brush.m_color);

		TextOut8X16ERectBuffer(pLocalScreen, x, y, &bufferRect, pBtn->m_czBtnTitl, pWin->m_font.m_color, 0);

		DrawRectRectBuffer(pLocalScreen, &bufferRect, &bufferRect, 0xFF000000);


		//设置当前BMP图片中，需要打印到屏幕的矩形
		rect.m_iHeigh = pWin->m_showRect.m_iHeigh;
		rect.m_iWidth = pWin->m_showRect.m_iWidth;
		rect.m_iTop = pWin->m_showRect.m_iTop - pWin->m_rect.m_iTop;
		rect.m_iLeft = pWin->m_showRect.m_iLeft - pWin->m_rect.m_iLeft;

		bmp.m_uBmpWidth = pWin->m_rect.m_iWidth;
		bmp.m_uBmpHeigh = pWin->m_rect.m_iHeigh;
		bmp.m_uBmpType = 0;
		bmp.m_pBmpBuf = pLocalScreen;
		
		DrawBmp(&pWin->m_showRect, &rect, &bmp, DRAW_BMP_SOLID_CP);		
		Free(pLocalScreen);
	}


#if 0
	FillRect(&pWin->m_showRect, pBtn->m_baseWin.m_brush.m_color);
	TextOut8X16E(x, y, &pWinParent->m_showRect, pBtn->m_czBtnTitl, pBtn->m_baseWin.m_font.m_color, 0);
	DrawRect(&pWin->m_showRect, 0xFF000000);
#endif
}

STATIC VOID SetTitle(HANDLE handle, CHAR* pcTitle)
{
	PButton pBtn = (PButton)H2P(handle);
	INT iSize;

	iSize = sizeof(pBtn->m_czBtnTitl);
	if(iSize > Strlen(pcTitle))
	{
		iSize = Strlen(pcTitle);
	}

	MemSet(pBtn->m_czBtnTitl, 0, sizeof(pBtn->m_czBtnTitl));
	MemCpy(pBtn->m_czBtnTitl, pcTitle, iSize);
}


#if 0
INT SetWinRectBtn(HANDLE handle, PRect pRectNew, PRect pRectOld)
{
	PButton pBtn = (PButton)H2P(handle);
	return pBtn->m_buttonWin.m_pfSelWinRect(P2H(&pBtn->m_buttonWin), pRectNew, pRectOld);
}

INT SetWinFontBtn(HANDLE handle, PFont pFontNew, PFont pFontOld)
{
	PButton pBtn = (PButton)H2P(handle);
	return pBtn->m_buttonWin.m_pfSelWinFont(P2H(&pBtn->m_buttonWin), pFontNew, pFontOld);
}

INT SetWinBrushBtn(HANDLE handle, PBrush pBrushNew, PBrush pBrushOld)
{
	PButton pBtn = (PButton)H2P(handle);
	return pBtn->m_buttonWin.m_pfSelWinBrush(P2H(&pBtn->m_buttonWin), pBrushNew, pBrushOld);
}
#endif

PButton CreateButton(PWindow pWinParent, INT iID, CHAR* pBtnTitl, UINT uFlag, INT iMsgID, PFWinOnUsrProc pfWinOnUsrProc)
{
	PButton pBtn;
	
	if(FindWindowByID(iID))
	{
		return NULL;
	}

	pBtn = (PButton)Malloc(sizeof(CButton));
	if(pBtn == NULL)
	{
		return NULL;
	}

#if 0
	MemSet(pBtn, 0, sizeof(CButton));

	//初始化BUTTON按钮
	InitWindowE(&pBtn->m_baseWin, pWinParent, iID);
	pBtn->m_baseWin.m_pfPrintWindow = PrintWindowBtn;
	pBtn->m_baseWin.m_pfWinDispatchMsg = WinDispatchMsgButton;
	pBtn->m_baseWin.m_iWinType = WINDOW_TYPE_BUTTON;
	pBtn->m_baseWin.m_iWinFlag = uFlag;

#if 0
	pBtn->m_pfSelWinBrush = SetWinBrushBtn;
	pBtn->m_pfSelWinFont = SetWinFontBtn;
	pBtn->m_pfSelWinRect = SetWinRectBtn;
#endif
	pBtn->m_pfSelWinBrush = pBtn->m_baseWin.m_pfSelWinBrush;
	pBtn->m_pfSelWinFont = pBtn->m_baseWin.m_pfSelWinFont;
	pBtn->m_pfSelWinRect = pBtn->m_baseWin.m_pfSelWinRect;
	pBtn->m_pfSetTitle = SetTitle;

	pBtn->m_pfPrintWindow = PrintWindowBtn;
	pBtn->m_iMsgID = iMsgID;

	MemCpy(pBtn->m_czBtnTitl, pBtnTitl, Strlen(pBtnTitl));

	//在父亲窗口注册消息处理函数
	if(pfWinOnUsrProc)
	{
		pWinParent->m_pfRegisterOnMsgProc(P2H(pWinParent), WIN_MSG_BUTTON, iMsgID, pfWinOnUsrProc);
	}
#endif
	InitButton(pBtn, pWinParent, iID, pBtnTitl,uFlag, iMsgID, pfWinOnUsrProc);
	return pBtn;
}

VOID DeleteButton(PButton pButton)
{
	if(pButton)
	{
		Free(pButton);
		pButton = NULL;
	}
	return;
}

#define BUTTON_BRUSH_COLOR 0xFFF0F0F0
#define BUTTON_FONT_COLOR 0xFF000000

INT InitButton(PButton pBtn, PWindow pWinParent, INT iID, CHAR* pBtnTitl,UINT uFlag, INT iMsgID, PFWinOnUsrProc pfWinOnUsrProc)
{
	if(FindWindowByID(iID))
	{
		return -1;
	}

	if(pBtn == NULL)
	{
		return -1;
	}

	MemSet(pBtn, 0, sizeof(CButton));

	//初始化BUTTON按钮
	InitWindowE(&pBtn->m_baseWin, pWinParent, iID);
	pBtn->m_baseWin.m_pfPrintWindow = PrintWindowBtn;
	pBtn->m_baseWin.m_pfWinDispatchMsg = WinDispatchMsgButton;
	pBtn->m_baseWin.m_iWinType = WINDOW_TYPE_BUTTON;
	pBtn->m_baseWin.m_iWinFlag = uFlag;

#if 0
	pBtn->m_pfSelWinBrush = SetWinBrushBtn;
	pBtn->m_pfSelWinFont = SetWinFontBtn;
	pBtn->m_pfSelWinRect = SetWinRectBtn;
#endif
	pBtn->m_pfSelWinBrush = pBtn->m_baseWin.m_pfSelWinBrush;
	pBtn->m_pfSelWinFont = pBtn->m_baseWin.m_pfSelWinFont;
	pBtn->m_pfSelWinRect = pBtn->m_baseWin.m_pfSelWinRect;
	pBtn->m_pfSetTitle = SetTitle;

	pBtn->m_baseWin.m_brush.m_color = BUTTON_BRUSH_COLOR;
	pBtn->m_baseWin.m_font.m_color = BUTTON_FONT_COLOR;

	pBtn->m_pfPrintWindow = PrintWindowBtn;
	pBtn->m_iMsgID = iMsgID;

	MemCpy(pBtn->m_czBtnTitl, pBtnTitl, Strlen(pBtnTitl));

	//在父亲窗口注册消息处理函数
	pWinParent->m_pfRegisterOnMsgProc(P2H(pWinParent), WIN_MSG_BUTTON, iMsgID, pfWinOnUsrProc);
	return 0;
}



