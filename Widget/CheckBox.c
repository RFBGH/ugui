#include "CheckBox.h"

#define CHECK_BOX_CHECK_FRAME_RECT_BAGAIN 5
#define CHECK_BOX_CHECK_FRAME_RECT_WIDTH 12
#define CHECK_BOX_CHECK_FRAME_RECT_HEIGH 12
#define CHECK_BOX_CHECK_RECT_WIDTH 6
#define CHECK_BOX_CHECK_RECT_HEIGH 6

#define CHECK_BOX_TEXT_BAGIN 27

STATIC VOID WinDispatchMsgCkBtn(HANDLE handle, INT iMsgID, UINT uMsg, PVOID pMsg)
{
	PCheckBox pBtn = (PCheckBox)H2P(handle);

	switch(iMsgID)
	{
		case WIN_MSG_ID_CLICK_SCREEN_DOWN:
		{
			PPoint pPoint = (PPoint)pMsg;
			PWindow pParent;
#if 0			
			CRect rect;

			rect.m_iHeigh = CHECK_BOX_CHECK_FRAME_RECT_HEIGH;
			rect.m_iWidth = CHECK_BOX_CHECK_FRAME_RECT_WIDTH;
			rect.m_iTop = ;
			rect.m_iLeft = ;
#endif

			if(PointInRect(pPoint, &pBtn->m_baseWin.m_rect))
			{
				if(pBtn->m_bCheck)
				{
					pBtn->m_bCheck = FALSE;
				}else
				{
					pBtn->m_bCheck = TRUE;
				}
				
				pParent = pBtn->m_baseWin.m_pParent;
				pParent->m_pfPostMessage(P2H(pParent), pBtn->m_iMsgID, pBtn->m_bCheck, NULL);
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


STATIC VOID PrintWindowCkBtn(HANDLE handle)
{
	PCheckBox pBtn = (PCheckBox)H2P(handle);

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

	x = pBtn->m_baseWin.m_rect.m_iLeft;
	y = pBtn->m_baseWin.m_rect.m_iTop;
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
		CBitmap bmp;
		CRect bufferRect;
		CRect rect;

		pLocalScreen = (RGBA*)Malloc(pWin->m_rect.m_iHeigh*pWin->m_rect.m_iWidth*sizeof(RGBA));
		if(pLocalScreen == NULL)
		{
			return;
		}

		bufferRect.m_iHeigh = pWin->m_rect.m_iHeigh;
		bufferRect.m_iWidth = pWin->m_rect.m_iWidth;
		bufferRect.m_iTop = 0;
		bufferRect.m_iLeft = 0;
		FillRectRectBuffer(pLocalScreen, &bufferRect, &bufferRect, pWin->m_brush.m_color);

		if(bufferRect.m_iHeigh+CHECK_BOX_CHECK_FRAME_RECT_BAGAIN > CHECK_BOX_CHECK_FRAME_RECT_HEIGH &&bufferRect.m_iWidth > CHECK_BOX_CHECK_FRAME_RECT_WIDTH)
		{//绘制checkBox选择框
			rect.m_iHeigh = CHECK_BOX_CHECK_FRAME_RECT_HEIGH-1;
			rect.m_iWidth = CHECK_BOX_CHECK_FRAME_RECT_WIDTH-1;
			rect.m_iLeft = CHECK_BOX_CHECK_FRAME_RECT_BAGAIN+1;
			rect.m_iTop = bufferRect.m_iHeigh/2-CHECK_BOX_CHECK_FRAME_RECT_HEIGH/2+1;

			FillRectRectBuffer(pLocalScreen, &bufferRect, &rect, 0xFFFFFFFF);
			DrawRectRectBuffer(pLocalScreen, &bufferRect, &rect, pWin->m_font.m_color);

			if(pBtn->m_bCheck)
			{//绘制checkBox选择
				rect.m_iHeigh = CHECK_BOX_CHECK_RECT_HEIGH;
				rect.m_iWidth = CHECK_BOX_CHECK_RECT_WIDTH;
				rect.m_iLeft += (CHECK_BOX_CHECK_FRAME_RECT_WIDTH-CHECK_BOX_CHECK_RECT_WIDTH)/2;
				rect.m_iTop += (CHECK_BOX_CHECK_FRAME_RECT_HEIGH-CHECK_BOX_CHECK_RECT_HEIGH)/2;	
				FillRectRectBuffer(pLocalScreen, &bufferRect, &rect, 0xFF000000);
			}

			if(bufferRect.m_iHeigh > ASC8x16_HEIGH && bufferRect.m_iWidth > CHECK_BOX_CHECK_FRAME_RECT_BAGAIN+CHECK_BOX_CHECK_FRAME_RECT_WIDTH + ASC8x16_WIDTH)
			{
				//绘制checkbox显示的字符内容
				TextOut8X16ERectBuffer(pLocalScreen, CHECK_BOX_TEXT_BAGIN, bufferRect.m_iHeigh/2-ASC8x16_HEIGH/2, &bufferRect, pBtn->m_czBtnTitl, pWin->m_font.m_color, 0);
			}
		
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
		}

		Free(pLocalScreen);
	}
}

STATIC VOID SetTitle(HANDLE handle, CHAR* pcTitle)
{
	PCheckBox pCkBox = NULL;
	INT iLen;
	
	pCkBox = (PCheckBox)H2P(handle);
	if(pCkBox == NULL)
	{
		return;
	}
	
	iLen = Strlen(pcTitle);
	if(iLen > sizeof(pCkBox->m_czBtnTitl))
	{
		iLen = sizeof(pCkBox->m_czBtnTitl)-4;
	}

	MemSet(pCkBox->m_czBtnTitl, 0, sizeof(pCkBox->m_czBtnTitl));
	MemCpy(pCkBox->m_czBtnTitl, pcTitle, iLen);
}

STATIC VOID SetCheck(HANDLE handle, BOOL bCheck)
{
	PCheckBox pCkBox = NULL;
	BOOL bOldCheck;
	
	pCkBox = (PCheckBox)H2P(handle);
	if(pCkBox == NULL)
	{
		return;
	}

	bOldCheck = pCkBox->m_bCheck;
	pCkBox->m_bCheck = bCheck;

	if(bOldCheck != bCheck)
	{
		//TODO...
		//reprint the checkbox view.
	}
}

STATIC BOOL IsCheck(HANDLE handle)
{
	PCheckBox pCkBox = NULL;
	
	pCkBox = (PCheckBox)H2P(handle);
	if(pCkBox == NULL)
	{
		return;
	}

	return pCkBox->m_bCheck;
}

PCheckBox CreateCheckBox(PWindow pParent, INT iID, CHAR* pBtnTitle, BOOL bCheck, UINT uFlag)
{
	PCheckBox pCkBox = NULL;
	INT iLen;

	pCkBox = (PCheckBox)Malloc(sizeof(CCheckBox));
	if(pCkBox == NULL)
	{
		return NULL;
	}

	InitCheckBox(pCkBox, pParent, iID, pBtnTitle, bCheck, uFlag);
	
	return pCkBox;
}	

VOID DeleteCheckBox(PCheckBox pCkBox)
{
	if(pCkBox)
	{
		Free(pCkBox);
	}
}

INT InitCheckBox(PCheckBox pCkBox, PWindow pParent, INT iID, CHAR* pBtnTitle, BOOL bCheck, UINT uFlag)
{
	INT iLen;

	if(FindWindowByID(iID))
	{
		return -1;
	}

	if(pCkBox == NULL)
	{
		return -1;
	}

	MemSet(pCkBox, 0, sizeof(CCheckBox));

	//init window
	InitWindowE(&pCkBox->m_baseWin, pParent, iID);

	//override
	pCkBox->m_baseWin.m_pfPrintWindow = PrintWindowCkBtn;
	pCkBox->m_baseWin.m_pfWinDispatchMsg = WinDispatchMsgCkBtn;
	pCkBox->m_baseWin.m_iWinType = WINDOW_TYPE_CHECKBOX;
	pCkBox->m_baseWin.m_iWinFlag = uFlag;

	//inherit.
	pCkBox->m_pfSelWinBrush = pCkBox->m_baseWin.m_pfSelWinBrush;
	pCkBox->m_pfSelWinFont = pCkBox->m_baseWin.m_pfSelWinFont;
	pCkBox->m_pfSelWinRect = pCkBox->m_baseWin.m_pfSelWinRect;

	//personal function.
	pCkBox->m_pfSetCheck = SetCheck;
	pCkBox->m_pfSetTitle = SetTitle;
	pCkBox->m_pfIsCheck = IsCheck;

	pCkBox->m_bCheck = bCheck;

	iLen = Strlen(pBtnTitle);
	if(iLen > sizeof(pCkBox->m_czBtnTitl))
	{
		iLen = sizeof(pCkBox->m_czBtnTitl)-4;
	}

	MemSet(pCkBox->m_czBtnTitl, 0, sizeof(pCkBox->m_czBtnTitl));
	MemCpy(pCkBox->m_czBtnTitl, pBtnTitle, iLen);
	
	return 0;
}

INT RegisterCheckBoxOnMsg(PCheckBox pCkBox, INT iMsgID, PFWinOnUsrProc pfWinOnUsrProc)
{
	PWindow pParent;

	if(pCkBox == NULL || pfWinOnUsrProc == NULL)
	{
		return -1;
	}

	pParent = pCkBox->m_baseWin.m_pParent;
	if(pParent == NULL)
	{
		return;
	}

	pCkBox->m_iMsgID = iMsgID;

	pParent->m_pfRegisterOnMsgProc(P2H(pParent), WIN_MSG_BUTTON, iMsgID, pfWinOnUsrProc);
}

INT UnregisterCheckBoxOnMsg(PCheckBox pCkBox, INT iMsgID)
{
	PWindow pParent;

	if(pCkBox == NULL)
	{
		return -1;
	}

	pParent = pCkBox->m_baseWin.m_pParent;
	if(pParent == NULL)
	{
		return;
	}

	pCkBox->m_iMsgID = 0;

	pParent->m_pfUnregisterOnMsgProc(P2H(pParent), WIN_MSG_BUTTON, iMsgID);
}



