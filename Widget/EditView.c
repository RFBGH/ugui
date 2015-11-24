#include "EditView.h"

STATIC VOID WinDispatchMsgEV(HANDLE handle, INT iMsgID, UINT uMsg, PVOID pMsg)
{
	PEditView pEdit = NULL;

	pEdit = (PEditView)H2P(handle);
	if(pEdit == NULL)
	{
		return ;
	}	

	switch(iMsgID)
	{
		case WIN_MSG_KEY:
		{
			UINT uKey = uMsg;

			if(uKey >= MSG_KEY_VAL_CHAR_START && uKey < MSG_KEY_VAL_CHAR_END)
			{
				pEdit->m_string.m_pfAppend(P2H(&pEdit->m_string), uKey);
			}else
			{
				switch(uKey)
				{
					case MSG_KEY_VAL_BACKSPACE:
						pEdit->m_string.m_pfRemoveLast(P2H(&pEdit->m_string));
					break;

					case MSG_KEY_VAL_ENTER:
						pEdit->m_string.m_pfAppend(P2H(&pEdit->m_string), '\n'); 
					break;

					case MSG_KEY_VAL_CLAEN:
						pEdit->m_string.m_pfCleanString(P2H(&pEdit->m_string));
					break;

					case MSG_KEY_VAL_CANCEL:

					break;


					case MSG_KEY_VAL_LEFT:
						if(pEdit->m_iCurEdit > 0)
						{
							pEdit->m_iCurEdit--;
						}
					break;

					case MSG_KEY_VAL_RIGHT:
						if(pEdit->m_iCurEdit < pEdit->m_string.m_iValLen)
						{
							pEdit->m_iCurEdit++;
						}
					break;
					
					case MSG_KEY_VAL_UP:

					break;
					
					case MSG_KEY_VAL_DOWN:

					break;

					
					default:
						//do nothing...
					break;
				}
			}

		}
		break;

		case WIN_MSG_ID_REPAINT:
			pEdit->m_baseWin.m_pfPrintWindow(P2H(&pEdit->m_baseWin));
		break;

		default:
			//do nothing...
		break;
	}
}

STATIC VOID PrintWindowEV(HANDLE handle)
{
	PEditView pEdit = NULL;

	PWindow pWinParent;
	PWindow pWin;
	
	pEdit = (PEditView)H2P(handle);
	if(pEdit == NULL)
	{
		return;
	}

	pWin = &pEdit->m_baseWin;
	pWinParent = pWin->m_pParent;

	if(pWinParent == NULL)
	{
		CopyRect(&pWin->m_showRect, &pWin->m_rect);
	}
	else
	{
		RectInRect(&pWinParent->m_showRect, &pWin->m_rect, &pWin->m_showRect);
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
		DrawRectRectBuffer(pLocalScreen, &bufferRect, &bufferRect, 0xFF000000);

#if 0
		if(pEdit->m_baseWin.m_iWinFlag & EDIT_VIEW_MULTI_LINE)
#endif
		{
			iStrOffset = MaxFullPrintAsc8x16(&bufferRect, pEdit->m_string.m_pcVal, pEdit->m_iCurEdit, &uCurEditXY);
			if(iStrOffset == 0)
			{//显示的内容小于当前编辑点，则，直接显示字符内容。
				TextOut8X16ERectBuffer(pLocalScreen, 0, 0, &bufferRect, pEdit->m_string.m_pcVal, pWin->m_font.m_color, pWin->m_iWinFlag);
			}else
			{//显示的内容大于当前编辑点，则，过滤之前的没有显示的行数。
				TextOut8X16ERectBuffer(pLocalScreen, 0, 0, &bufferRect, pEdit->m_string.m_pcVal+iStrOffset, pWin->m_font.m_color, pWin->m_iWinFlag);
			}
		}

#if 0
		else
		{
			INT iWidth;
			iWidth = rect.m_iWidth;
			rect.m_iHeigh = ASC8x16_HEIGH+2;
			rect.m_iWidth = bufferRect.m_iWidth;
			rect.m_iLeft = 0;
			rect.m_iTop = 0;
			uCurEditXY = ASC8x16_WIDTH*
			TextOut8X16ERectBuffer(pLocalScreen, 0, 0, &rect, pEdit->m_string.m_pcVal+iStrOffset, pWin->m_font.m_color, 0);
		}
#endif


		//if(iStrOffset)
		{
			CPoint start;
			CPoint end;
			start.m_iX = (uCurEditXY>>16)&0x0000FFFF;
			start.m_iY = (uCurEditXY)&0x0000FFFF;

			end.m_iX = start.m_iX;
			end.m_iY = start.m_iY+ASC8x16_HEIGH;
			DrawLineRectBuffer(pLocalScreen, &bufferRect, &start, &end, pWin->m_font.m_color);
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
		Free(pLocalScreen);
	}
}

STATIC INT SetEditText(HANDLE handle, CHAR* pcVal)
{
	PEditView pEdit = NULL;

	pEdit = (PEditView)H2P(handle);
	if(pEdit == NULL)
	{
		return -1;
	}

	return pEdit->m_string.m_pfSetText(P2H(&pEdit->m_string), pcVal);
}

STATIC INT SetCurEdit(HANDLE handle, INT iCurEdit)
{
	PEditView pEdit = NULL;

	pEdit = (PEditView)H2P(handle);
	if(pEdit == NULL)
	{
		return -1;
	}

	if(iCurEdit < 0 || iCurEdit > pEdit->m_string.m_iValLen)
	{
		iCurEdit = pEdit->m_string.m_iValLen;
	}

	pEdit->m_iCurEdit = iCurEdit;

	return iCurEdit;
}

STATIC INT SetCurSel(HANDLE handle, INT iSelStart, INT iSelLen)
{
	PEditView pEdit = NULL;

	pEdit = (PEditView)H2P(handle);
	if(pEdit == NULL)
	{
		return -1;
	}

	if(iSelStart < 0)
	{
		iSelStart = 0;
	}

	if(iSelStart+iSelLen > pEdit->m_string.m_iValLen)
	{
		iSelLen = pEdit->m_string.m_iValLen-iSelStart-1;
	}

	pEdit->m_iSelStart = iSelStart;
	pEdit->m_iSelLen = iSelLen;
	return iSelStart;
}


PEditView CreateEditView(PWindow pParent, INT iID, CHAR* pcVal, UINT uFlag)
{
	PEditView pEdit = NULL;
	
	if(FindWindowByID(iID))
	{
		return NULL;
	}


	pEdit = (PEditView)Malloc(sizeof(CEditView));
	if(pEdit)
	{
#if 0
		MemSet(pEdit, 0, sizeof(CEditView));
		InitWindowE(&pEdit->m_BaseWin, pParent, iID);

		//重载显示，消息处理，窗口类型
		pEdit->m_BaseWin.m_pfPrintWindow = PrintWindowEV;
		pEdit->m_BaseWin.m_pfWinDispatchMsg = WinDispatchMsgEV;
		pEdit->m_baseWin.m_iWinType = WINDOW_TYPE_EDITVIEW;

		//继承brush, font, rect选择接口
		pEdit->m_pfSelWinBrush = pEdit->m_baseWin.m_pfSelWinBrush;
		pEdit->m_pfSelWinFont = pEdit->m_baseWin.m_pfSelWinFont;
		pEdit->m_pfSelWinRect = pEdit->m_baseWin.m_pfSelWinRect;	

		//自身特有的处理函数。
		pEdit->m_pfSetText = SetText;

		//初始化String.
		InitStringE(pEdit->m_string, NULL, 1024);

#endif

		InitEditView(pEdit, pParent, iID, pcVal, uFlag);
	}
	
	return pEdit;
}

#define EDIT_VIEW_BRUSH_COLOR 0xFFFFFFFF
#define EDIT_VIEW_FONT_COLOR  0xFF000000

INT InitEditView(PEditView pEdit, PWindow pParent, INT iID, CHAR* pcVal, UINT uFlag)
{
	if(pEdit)
	{
		MemSet(pEdit, 0, sizeof(CEditView));
		InitWindowE(&pEdit->m_baseWin, pParent, iID);

		//重载显示，消息处理，窗口类型
		pEdit->m_baseWin.m_pfPrintWindow = PrintWindowEV;
		pEdit->m_baseWin.m_pfWinDispatchMsg = WinDispatchMsgEV;
		pEdit->m_baseWin.m_iWinType = WINDOW_TYPE_EDITVIEW;
		pEdit->m_baseWin.m_iWinFlag = uFlag;

		//继承brush, font, rect选择接口
		pEdit->m_pfSelWinBrush = pEdit->m_baseWin.m_pfSelWinBrush;
		pEdit->m_pfSelWinFont = pEdit->m_baseWin.m_pfSelWinFont;
		pEdit->m_pfSelWinRect = pEdit->m_baseWin.m_pfSelWinRect;	

		//自身特有的处理函数。
		pEdit->m_pfSetText = SetEditText;
		pEdit->m_pfSetCurEdit = SetCurEdit;
		pEdit->m_pfSetSel = SetCurSel;

		pEdit->m_baseWin.m_brush.m_color = EDIT_VIEW_BRUSH_COLOR;
		pEdit->m_baseWin.m_font.m_color = EDIT_VIEW_FONT_COLOR;

		//初始化String.
		InitStringE(&pEdit->m_string, pcVal, 1024);

		return 0;
	}
	
	return -1;
}


VOID DeleteEditView(PEditView pEdit)
{
	Free(pEdit->m_string.m_pcVal);
	Free(pEdit);
}



