//#include "Gdi.h"
#include "stdio.h"
#include "Tool.h"
#include "Screen.h"
#include "GDI.h"
#include "Window.h"
#include "Button.h"
#include "EditView.h"
#include "CheckBox.h"


VOID WinOnUsrProc(PWindow pWin, UINT uMsg, PVOID pMsg)
{
	CBrush brush;
	INT iRnd;
	static int i = 1;
	char czTitle[10] = "BTN0";

	iRnd = GenUIntRnd(0xFFFFFF);
	iRnd += 0xFF000000;

	brush.m_color = iRnd;

	pWin->m_pFirstSon->m_pfSelWinBrush(P2H(pWin->m_pFirstSon), &brush, NULL);

	czTitle[3] = '0'+i;
	i++;
	PButton pBtn = (PButton)pWin->m_pLastSon;
	pBtn->m_pfSetTitle(P2H(pBtn), czTitle);

	PEditView pEdit = (PEditView)pWin->m_pfFindItemById(P2H(pWin), 4);
	pEdit->m_string.m_pcVal[0] = i+'0';


	Log("button message %d\r\n", pWin->m_iID);

	if(i%2)
	{
		DragWinsToXY(pWin, 20, 20);
	}else
	{
		DragWinsToXY(pWin, 30, 30);
	}

}


INT WindowFlow(PWindow pWin)
{
	/*
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
*/
	pWin->m_pfPrintWindow(P2H(pWin));
	/*
    Log("left[%d] top[%d] width[%d] heigh[%d] id[%d]\n", \
        pWin->m_showRect.m_iLeft, pWin->m_showRect.m_iTop, pWin->m_showRect.m_iWidth,  pWin->m_showRect.m_iHeigh, pWin->m_iID);
	*/
    return 0;
}


void TestBtn(void)
{
	PWindow pWinSon0 = NULL;
	PButton pBtnSon0 = NULL;
	PEditView pEditSon0 = NULL;
	PCheckBox pBkBoxSon0 = NULL;
	PWindow pWinParent = NULL;
	int iRnd;
	int i;
	int iParent;
	CRect rect;
	CFont font;
	CBrush brush;
	INT iID;

	iID = 1;

	InitHeapPool(INIT_HEAP_DEFAULT);

	InitGUI();
	Log("start...\n");

	pWinParent = CreateWindowE(0, pWinRoot, iID++);

	rect.m_iLeft = 10;
	rect.m_iTop = 10;
	rect.m_iHeigh = 200;
	rect.m_iWidth = 300;

	pWinParent->m_pfSelWinRect(P2H(pWinParent), &rect, NULL);
	SetWinBKColor(pWinParent, 0xFF000000);

	pBtnSon0 = CreateButton(pWinParent, iID++, "btn1", 0, WIN_MSG_BUTTON, WinOnUsrProc);
	rect.m_iLeft = 80;
	rect.m_iTop = 10;
	rect.m_iHeigh = 50;
	rect.m_iWidth = 50;
	pBtnSon0->m_pfSelWinRect(P2H(pBtnSon0), &rect, NULL);
	SetWinBKColor(&pBtnSon0->m_baseWin, 0xFF00FF00);
	font.m_color = 0xFF000000;

	pBtnSon0->m_pfSelWinFont(P2H(pBtnSon0), &font, NULL);

	pWinSon0 = CreateWindowE(0, pWinParent, iID++);
	rect.m_iLeft = 50;
	rect.m_iTop = 10;
	rect.m_iHeigh = 50;
	rect.m_iWidth = 50;
	pWinSon0->m_pfSelWinRect(P2H(pWinSon0), &rect, NULL);
	SetWinBKColor(pWinSon0, 0xFFFF0000);

	pEditSon0 = CreateEditView(pWinParent, iID++, "you are pig stupid, fool is your nick name kill youyou are pig stupid, fool is your nick name kill you", 0/*EDIT_VIEW_MULTI_LINE*/);
	rect.m_iLeft = 30;
	rect.m_iTop = 90;
	rect.m_iHeigh = 50;
	rect.m_iWidth = 100;
	pEditSon0->m_pfSelWinRect(P2H(pEditSon0), &rect, NULL);
	pEditSon0->m_pfSelWinFont(P2H(pEditSon0), &font, NULL);
	brush.m_color = 0xFFFFFFFF;
	pEditSon0->m_pfSelWinBrush(P2H(pEditSon0), &brush, NULL);
	pEditSon0->m_iCurEdit =  10;

	pBkBoxSon0 = CreateCheckBox(pWinParent, iID++, "CheckMe", TRUE, 0);
	rect.m_iLeft = 146;
	rect.m_iTop = 80;
	rect.m_iHeigh = 24;
	rect.m_iWidth = 100;
	pBkBoxSon0->m_pfSelWinRect(P2H(pBkBoxSon0), &rect, NULL);
	pBkBoxSon0->m_pfSelWinFont(P2H(pBkBoxSon0), &font, NULL);
	brush.m_color = 0xFFFF00FF;
	pBkBoxSon0->m_pfSelWinBrush(P2H(pBkBoxSon0), &brush, NULL);

	Log("window flow...\n");
	FlowWindow0(pWinRoot, WindowFlow);

	//pWinTmp = FindWindowByID(25);
	//Log("find...");
	//WindowFlow(pWinTmp);

	PrintScreen();

#if 0
	pWinTmp = FindWindowByID(2);

	if(pWinTmp == NULL)
	{
		Log("NULL pointer\r\n");
	}

	Log("OK\r\n");

	ReorderWindow(pWinTmp);
	FlowWindow0(pWinRoot, WindowFlow);
#endif


	while(TRUE)
	{
		int x;
		int y;
		int iRet;
		PPoint pPoint;
		scanf("%d %d", &x, &y);
		pPoint = (PPoint)Malloc(sizeof(CPoint));
		pPoint->m_iX = x;
		pPoint->m_iY = y;

		iRet = pWinRoot->m_pfPostMessage(P2H(pWinRoot), WIN_MSG_ID_CLICK_SCREEN_DOWN, 0, pPoint);
		Log("iRet[%d]\r\n", iRet);
		WinFlowMain();

		FlowWindow0(pWinRoot, WindowFlow);
		PrintScreen();
	}

	DeleteEditView(pEditSon0);
	DeleteButton(pBtnSon0);
}

extern VOID AppCalcDlg(VOID);

void main(void)
{
	InitHeapPool(INIT_HEAP_DEFAULT);

	InitGUI();

	AppCalcDlg();
    //Test2();
    //Test3();
    //Test4();
    //Test5();
    //Test7();
	TestBtn();
	//TestString();
}

