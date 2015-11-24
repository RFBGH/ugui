/****************************************************************************
*
*this procedure is work for basic operator for a window.
*
*############################################################################
*AUTHOR:RFB 	LOG: Creat this procedure	TIME:2014/02/26
*****************************************************************************/

#include "Window.h"

#define WINDOW_BRUSH_COLOR 0xFFF0F0F0
#define WINDOW_FONT_COLOR 0xFF000000

INT gWinErr = 0;

STATIC CWindow winRoot = {  NULL, //parent
                            NULL, //first son
                            NULL, //last son
                            NULL, //last
                            NULL, //next

                            0, //Window id.
                            
                            //window rect.
                            {
                                0, 0, SCREEN_WIDTH, SCREEN_HEIGH,
                            },

                            //window show rect.
                            {
                                0, 0, SCREEN_WIDTH, SCREEN_HEIGH,
                            },


                            //window font default color black
                            {
                                0xFF000000,
                            },

                            //window brush default color white
                            {
                                0xFFFFFFFF,  
                            },

                            //window type
                            0,

                            //window flag
                            0,
                            
                            {
                                NULL,
                                NULL, 
                                0,
                            },
                            //window message dispatch flow.
                            WinDispatchMsgDef,

                            //post window message
                            PostMessage,

                            //send window message                           
                            SendMessage,

                            //reigster on message process
                            RegisterOnMessage,

                            //unregister on message process
                            UnregisterOnMessage,

                            //init windows
                            InitWindow,

                            //Select window rect
                            SelWinRect,

                            //select window font
                            SelWinFont,

                            //select window brush
                            SelWinBrush,

							//print window
							PrintWindowDef,

							//find window item by ID
							FindItemById,
								
};      
PWindow pWinRoot = &winRoot;
CList   winMsgList = {
                        NULL,
                        NULL,
                        0,
                     };
PList pWinMsgList = &winMsgList;

PWindow CreateWindowE(UINT uFlag, PWindow pParent, INT iID)
{
	
	PWindow pWin = NULL;
	
	if(FindWindowByID(iID))
	{
		return NULL;
	}

	if(pParent == NULL)
	{
		pParent = pWinRoot;
	}

	pWin = (PWindow)Malloc(sizeof(CWindow));
	InitWindowE(pWin, pParent, iID);

#if 0
	pWin = CreateWindow(uFlag, iID);
	if(pWin)
	{
		//init on message procss list.
		InitList(&pWin->m_onMsgProcList);

		//add son to parent
		AddSonWindow(pParent, pWin);

		//init window init function
		pWin->m_pfInitWindow = InitWindow;

		//set window post message function
		pWin->m_pfPostMessage = PostMessage;

		//set window post message function
		pWin->m_pfSendMessage = SendMessage;

		//set window brush select function
		pWin->m_pfSelWinBrush = SelWinBrush;

		//set window font select function
		pWin->m_pfSelWinFont = SelWinFont;

		//Set window rect select function
		pWin->m_pfSelWinRect = SelWinRect;

		//Set window register on message function
		pWin->m_pfRegisterOnMsgProc = RegisterOnMessage;

		//Set window unregister on message function
		pWin->m_pfUnregisterOnMsgProc = UnregisterOnMessage;

		//set default window print function
		pWin->m_pfPrintWindow = PrintWindowDef;

		//Set default window message dispatch function
		pWin->m_pfWinDispatchMsg = WinDispatchMsgDef;
	
		//find son item by son ID.
		pWin->m_pfFindItemById = FindItemById;

		//default window bk color
		pWin->m_brush.m_color = WINDOW_BRUSH_COLOR;
		pWin->m_font.m_color = WINDOW_FONT_COLOR;
	}
#endif
	return pWin;
}

INT InitWindowE(PWindow pWin, PWindow pParent, INT iID)
{	
	if(FindWindowByID(iID))
	{
		return -1;
	}

	if(pParent == NULL)
	{
		pParent = pWinRoot;
	}
	
	if(pWin)
	{
		InitWindowTree(pWin, iID);
		
		//init on message procss list.
		InitList(&pWin->m_onMsgProcList);

		//add son to parent
		AddSonWindow(pParent, pWin);

		//init window init function
		pWin->m_pfInitWindow = InitWindow;

		//set window post message function
		pWin->m_pfPostMessage = PostMessage;

		//set window post message function
		pWin->m_pfSendMessage = SendMessage;

		//set window brush select function
		pWin->m_pfSelWinBrush = SelWinBrush;

		//set window font select function
		pWin->m_pfSelWinFont = SelWinFont;

		//Set window rect select function
		pWin->m_pfSelWinRect = SelWinRect;

		//Set window register on message function
		pWin->m_pfRegisterOnMsgProc = RegisterOnMessage;

		//Set window unregister on message function
		pWin->m_pfUnregisterOnMsgProc = UnregisterOnMessage;

		//set default window print function
		pWin->m_pfPrintWindow = PrintWindowDef;

		//Set default window message dispatch function
		pWin->m_pfWinDispatchMsg = WinDispatchMsgDef;

		//find son item by son ID.
		pWin->m_pfFindItemById = FindItemById;

		//default window bk color
		pWin->m_brush.m_color = WINDOW_BRUSH_COLOR;
		pWin->m_font.m_color = WINDOW_FONT_COLOR;
	}

	return 0;
}


/*
 * basic windows message system flow.
 *
 * @param hWin: the handler of root window.
 * @param iMsgID: the ID of message.
 * @param uMsg  : the value of UINT Message.
 * @param pMsg  : the value of PVOID message.
 *
 * @return NULL.
 *
 */
VOID WinDispatchMsgDef(HANDLE hWin, INT iMsgID, UINT uMsg, PVOID pMsg)
{
    PWindow pWin = H2P(hWin);

    switch(iMsgID)
    {
        case WIN_MSG_ID_CLICK_SCREEN_DOWN:
        {//屏幕点击消息
            PPoint pPoint = (PPoint)pMsg;
        
            if(pPoint == NULL)
            {   //指针不能为零
                gWinErr = WIN_ERR_NULL_POINT;
                exit();
            }
        
            if(pWin->m_pLastSon!= NULL && PointInRect(pPoint, &pWin->m_pLastSon->m_showRect))
            {//如果当前点，在最右边子窗口上，将，屏幕点击消息，传递到子窗口上
                pWin->m_pLastSon->m_pfWinDispatchMsg(P2H(pWin->m_pLastSon), iMsgID, uMsg, pMsg);
            }else
            {//如果不是，获取屏幕点击到的窗口，重排窗口树
                PWindow pWinSel = LocatWinByXY(pPoint);
                ReorderWindow(pWinSel);

				if(pWinSel != pWin)
				{	//选择窗口非上次选择窗口。
					pWinSel->m_pfWinDispatchMsg(P2H(pWinSel), iMsgID, uMsg, pMsg);
				}
                //释放，点和消息内存
                //Free(pPoint);  
            }
            
        }
        break;

		case WIN_MSG_ID_DRAG_SCREEN:
		{
			PPoint pPoint = (PPoint)pMsg;
        
            if(pPoint == NULL)
            {   //指针不能为零
                gWinErr = WIN_ERR_NULL_POINT;
                exit();
            }
			
            if(PointInRect(pPoint, &pWin->m_rect))
            {//如果当前点，在最右边子窗口上，将，屏幕点击消息，传递到子窗口上
                pWin->m_pLastSon->m_pfWinDispatchMsg(P2H(pWin->m_pLastSon), iMsgID, uMsg, pMsg);
            }else
            {//移动窗口树位置
				DragWinsToXY(pWin, pPoint->m_iX, pPoint->m_iY);
				Free(pPoint);
			}

		}
		break;
 
        default:
        {
            int i;
            POnMsgProc pOnMsgProc;
            PListNode pListCurr = pWin->m_onMsgProcList.m_pListHead;
            for(i = 0; i < pWin->m_onMsgProcList.m_iListSize; i++)
            {
                pOnMsgProc = (POnMsgProc)pListCurr->m_pData;
				if(pOnMsgProc->m_iMsgID == iMsgID)
				{//有效按键ID。
				
					PFWinOnUsrProc pfWinOnUsrProc = (PFWinOnUsrProc)pOnMsgProc->m_pfOnMsgProc;
					pfWinOnUsrProc(pWin, uMsg, pMsg);
					break;
				}
                pListCurr = pListCurr->m_pNextNode;
            }

			if(i == pWin->m_onMsgProcList.m_iListSize)
			{

			}
        }
        break;
    }
}

/*
 * push a message to the end of a windows message list.
 *
 * @param hWin: the handler of window wanted.
 * @param iMsgID: the ID of message.
 * @param uMsg  : the value of UINT Message.
 * @param pMsg  : the value of PVOID message.
 *
 * @return success >=0, else fail..
 *
 */
INT PostMessage(HANDLE hWin, INT iMsgID, UINT uMsg, PVOID pMsg)
{
    PWindow pWin = H2P(hWin);
    return PostWinMsg(pWin, iMsgID, uMsg, pMsg);
}

/*
 * insert a message into the head of a windows message list.
 *
 * @param hWin: the handler of window wanted.
 * @param iMsgID: the ID of message.
 * @param uMsg  : the value of UINT Message.
 * @param pMsg  : the value of PVOID message.
 *
 * @return success >=0, else fail..
 *
 */
INT SendMessage(HANDLE hWin, INT iMsgID, UINT uMsg, PVOID pMsg)
{
    PWindow pWin = H2P(hWin);
    return PostWinMsg(pWin, iMsgID, uMsg, pMsg);
}

/*
 * register a on window message deal proc.
 *
 * @param hWin: the handler of window wanted.
 * @param iMsgType: the type of message.
 * @param iMsgID  : the ID of message.
 * @param pfOnMsgProc  : onmessagerpoc.
 *
 * @return success >=0, else fail..
 *
 */
INT RegisterOnMessage(HANDLE hWin, INT iMsgType, INT iMsgID, PVOID pfOnMsgProc)
{
    PWindow pWin = H2P(hWin);
    return RegisterOnMsgProc(pWin, iMsgType, iMsgID, pfOnMsgProc);
}

/*
 * unregister a on window message deal proc.
 *
 * @param hWin: the handler of window wanted.
 * @param iMsgType: the type of message.
 * @param iMsgID  : the ID of message.
 *
 * @return success >=0, else fail..
 *
 */
INT UnregisterOnMessage(HANDLE hWin, INT iMsgType, INT iMsgID)
{
    PWindow pWin = H2P(hWin);
    return UnregisterOnMsgProc(pWin, iMsgType, iMsgID);
}

/*
 * init window.
 *
 * @param hWin: the handler of window wanted.
 * @param hWinParent: the handler of parent window.
 * @param iWinType  : window type.
 * @param uWinFlag  : window flag.
 *
 * @return success >=0, else fail..
 *
 */
INT InitWindow(HANDLE hWin, HANDLE hWinParent, INT iID, INT iWinType, UINT uWinFlag)
{
    PWindow pWin = H2P(hWin);
    PWindow pWinParent = H2P(hWinParent);
    INT iRet;
	
	if(FindWindowByID(iID))
	{
		return -1;
	}
	
    iRet = AddSonWindow(pWinParent, pWin);
    if(iRet < 0)
    {
        return iRet;
    }
	
	InitList(&pWin->m_onMsgProcList);

    pWin->m_iWinFlag = uWinFlag;
    pWin->m_iWinType = iWinType;

    pWin->m_pfWinDispatchMsg = WinDispatchMsgDef;
    pWin->m_pfPostMessage = PostMessage;
    pWin->m_pfSendMessage = SendMessage;
    pWin->m_pfRegisterOnMsgProc = RegisterOnMessage;
    pWin->m_pfUnregisterOnMsgProc = UnregisterOnMessage;
    pWin->m_pfInitWindow = InitWindow;
    pWin->m_pfSelWinRect = SelWinRect;
    pWin->m_pfSelWinFont = SelWinFont;
    pWin->m_pfSelWinBrush = SelWinBrush;
	pWin->m_pfPrintWindow = PrintWindowDef;
    
    return 0;
}

/*
 * select a new rect for window.
 *
 * @param hWin: the handler of window wanted.
 * @param pRectNew: new rect for windo.
 * @param pRectOld  : keep the old window rect.
 *
 * @return success >=0, else fail..
 *
 */
INT SelWinRect(HANDLE hWin, PRect pRectNew, PRect pRectOld)
{
    PWindow pWin = H2P(hWin);
    INT iRet;
    
    if(pWin == NULL)
    {
        return -1;
    }

    iRet = 0;
    if(pRectOld)
    {
        pRectOld->m_iLeft = pWin->m_rect.m_iLeft;
        pRectOld->m_iTop = pWin->m_rect.m_iTop;
        pRectOld->m_iWidth = pWin->m_rect.m_iWidth;
        pRectOld->m_iHeigh = pWin->m_rect.m_iHeigh;
        //MemCpy(pRectOld, &pWin->m_rect, sizeof(CRect));
        iRet = 1;
    }

    if(pRectNew)
    {
        pWin->m_rect.m_iLeft = pRectNew->m_iLeft;
        pWin->m_rect.m_iTop = pRectNew->m_iTop;
        pWin->m_rect.m_iWidth = pRectNew->m_iWidth;
        pWin->m_rect.m_iHeigh = pRectNew->m_iHeigh;        
        //MemCpy(&pWin->m_rect, pRectNew, sizeof(CRect));
        iRet |= 2;
    }
    
    return iRet;
}


/*
 * select a new font for window.
 *
 * @param hWin: the handler of window wanted.
 * @param pFontNew: new font for windo.
 * @param pFontOld  : keep the old window font.
 *
 * @return success >=0, else fail..
 *
 */
INT SelWinFont(HANDLE hWin, PFont pFontNew, PFont pFontOld)
{
    PWindow pWin = H2P(hWin);
    INT iRet;
    
    if(pWin == NULL)
    {
        return -1;
    }

    iRet = 0;
    if(pFontOld)
    {
        CopyFont(pFontOld, &pWin->m_font);
        iRet = 1;
    }

    if(pFontNew)
    {
        CopyFont(&pWin->m_font, pFontNew);
        iRet |= 2;
    }
    
    return iRet;

}

/*
 * select a new brush for window.
 *
 * @param hWin: the handler of window wanted.
 * @param pBrushNew: new brush for window.
 * @param pBrushOld  : keep the old window brush.
 *
 * @return success >=0, else fail..
 *
 */
INT SelWinBrush(HANDLE hWin, PBrush pBrushNew, PBrush pBrushOld)
{
    PWindow pWin = H2P(hWin);
    INT iRet;
    
    if(pWin == NULL)
    {
        return -1;
    }

    iRet = 0;
    if(pBrushOld)
    {
        CopyBrush(pBrushOld, &pWin->m_brush);
        iRet = 1;
    }

    if(pBrushNew)
    {
        CopyBrush(&pWin->m_brush, pBrushNew);
        iRet |= 2;
    }
    
    return iRet;

}

VOID* FindItemById(HANDLE hWin, INT iID)
{
	PWindow pWin = NULL;
	PWindow pSon = NULL;
	
	pWin = H2P(hWin);

	if(pWin == NULL)
	{
		//return NULL;
		pWin = pWinRoot;
	}

	pSon = pWin->m_pFirstSon;
	while(pSon != NULL)
	{
		if(pSon->m_iID == iID)
		{
			break;
		}
		pSon = pSon->m_pNext;
	}

	return pSon;
}


VOID PrintWindowDef(HANDLE hWin)
{
	PrintWindowFlow(H2P(hWin));
}

VOID WinFlowMain(VOID)
{
#if 0    
    Log("WinFlowMain...\r\n");
#endif

    PMsg pMsg = NULL;
    while(TRUE)
    {
        pMsg = GetFirstWinMsg();

		if(pMsg == NULL)
		{
			break;
		}
		
        if(pMsg != NULL)
        {//得到头消息
        
            if(pMsg->m_pDstWin)
            {//消息中，存在目标窗口
                pMsg->m_pDstWin->m_pfWinDispatchMsg(P2H(pMsg->m_pDstWin), pMsg->m_iMsgID, pMsg->m_uMsg, pMsg->m_pMsg);
            }else
            {//如果没存在目标窗口，发送ROOT窗口
                pWinRoot->m_pfWinDispatchMsg(P2H(pWinRoot), pMsg->m_iMsgID, pMsg->m_uMsg, pMsg->m_pMsg);
            }

            //释放消息内存
            DestroyWinMsg(pMsg);
        }
    }
#if 0    
    Log("WinFlowMain END...\r\n");
#endif 

}

/*
 * init GUI system.
 *
 * @param NULL.
 *
 * @return NULL.
 *
 */
VOID InitGUI(VOID)
{
    InitList(pWinMsgList);
}


INT PrintWindowFlow(PWindow pWin)
{
    PWindow pWinParent;

    pWinParent = pWin->m_pParent;
    if(pWinParent == NULL)
    {
        CopyRect(&pWin->m_showRect, &pWin->m_rect);
    }
    else
    {
        RectInRect(&pWinParent->m_showRect, &pWin->m_rect, &pWin->m_showRect);
    }

#if 0
    FillRect(&pWin->m_showRect, pWin->m_brush.m_color);
#endif

#if 1
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

#endif

}

/*
 * update screen.
 *
 * @param NULL.
 *
 * @return NULL.
 *
 */
VOID UpdateScreen(VOID)
{
	FlowWindow0(pWinRoot, PrintWindowFlow);
}

#if 0
VOID WinMsgFlow(PWindow pWin)
{
    PMsg pMsg;

    if(pWin == NULL)
    {
        return;
    }

    while(TRUE)
    {
        pMsg = GetWinFirstMsg(PWindow pWin);

        if(pMsg)
        {
            break;
        }
        
        switch(pMsg->m_iMsgType)
        {
            case WIN_MSG_CLICK_SCREEN_DOWN:
            {//屏幕点击消息
                PPoint pPoint = (PPoint)pMsg->m_pMsg;
        
                if(pPoint == NULL)
                {   //指针不能为零
                    gWinErr = WIN_ERR_NULL_POINT;
                    exit();
                }

                if(PointInRect(pPoint, pWin->m_pLastSon))
                {//如果当前点，在最右边子窗口上，将，屏幕点击消息，传递到子窗口上
                    SendWinMsg(pWin->m_pLastSon, WIN_MSG_CLICK_SCREEN, pMsg->m_uMsg, pMsg->m_pMsg);
                    pWin->m_pLastSon->m_pfWinMsgFlow(pWin->m_pLastSon);
                }else
                {//如果不是，获取屏幕点击到的窗口，重排窗口树
                    PWindow pWinSel = LocatWinByXY(pPoint);
                    ReorderWindow(pWinSel);
                }

                //释放，点和消息内存
                Free(pPoint);
                Free(pMsg);
            }
                break;

            case WIN_MSG_MAXMIZE_BUTTON:
            {//按钮消息
                
            }
                break;

            case WIN_MSG_MINIZE_BUTTON:
            {//按钮消息
                
            }
                break;
        
            default:
                break;
        }

    }

}

INT WindowFlow(PWindow pWin)
{
 //   CRect rect;
    PWindow pWinParent;

    pWinParent = pWin->m_pParent;
    if(pWinParent == NULL)
    {
        CopyRect(&pWin->m_showRect, &pWin->m_rect);
    }
    else
    {
        RectInRect(&pWinParent->m_showRect, &pWin->m_rect, &pWin->m_showRect);
    }
    
    
    FillRect(&pWin->m_showRect, pWin->m_brush.m_color);

    Log("left[%d] top[%d] width[%d] heigh[%d] id[%d]\n", \
        pWin->m_showRect.m_iLeft, pWin->m_showRect.m_iTop, pWin->m_showRect.m_iWidth,  pWin->m_showRect.m_iHeigh, pWin->m_iID);
    return 0;
}

#endif



