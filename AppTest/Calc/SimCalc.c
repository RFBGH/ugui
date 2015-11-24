#include "Window.h"
#include "Widget.h"


typedef struct _CalcBtn
{
	CHAR  m_czCalcBtnVal[32];
	INT   m_iCalcBtnID;
	INT   m_iCalcBtnMsgID;
	CRect m_iCalcBtnRect;
	PVOID m_pfOnBtnMsg;
}CcalcBtn, *PCalcBtn;

typedef struct _CalcParam
{
	
}CCalcParam, *PCalcParam;

CString strCalc;

#define CALC_DLG_ID       0x1001
#define CALC_EV_PRINT_ID  0x1002
#define CALC_BTN_NUM0_ID  0x1003
#define CALC_BTN_NUM1_ID  0x1004
#define CALC_BTN_NUM2_ID  0x1005
#define CALC_BTN_NUM3_ID  0x1006
#define CALC_BTN_NUM4_ID  0x1007
#define CALC_BTN_NUM5_ID  0x1008
#define CALC_BTN_NUM6_ID  0x1009
#define CALC_BTN_NUM7_ID  0x100A
#define CALC_BTN_NUM8_ID  0x100B
#define CALC_BTN_NUM9_ID  0x100C
#define CALC_BTN_BK_ID    0x100D
#define CALC_BTN_CE_ID    0x100E
#define CALC_BTN_C_ID     0x100F
#define CALC_BTN_PN_ID    0x1010
#define CALC_BTN_ADD_ID   0x1011
#define CALC_BTN_SUB_ID   0x1012
#define CALC_BTN_MUL_ID   0x1013
#define CALC_BTN_DIV_ID   0x1014
#define CALC_BTN_EQL_ID   0x1015
#define CALC_BTN_BRA1_ID  0x1016
#define CALC_BTN_BRA2_ID  0x1017
#define CALC_BTN_PINT_ID  0x1018
#define CALC_BTN_MOD_ID  0x1019


#define CALC_BTN_MSG_ID 0x1000

VOID OnCalcBtn(PWindow pWin, UINT uMsg, PVOID pMsg)
{
	PEditView pEdit = (PEditView)pWin->m_pfFindItemById(P2H(pWin), CALC_EV_PRINT_ID);
	
	
	switch(uMsg)
	{
		case CALC_BTN_NUM0_ID:
		case CALC_BTN_NUM1_ID:
		case CALC_BTN_NUM2_ID:
		case CALC_BTN_NUM3_ID:
		case CALC_BTN_NUM4_ID:
		case CALC_BTN_NUM5_ID:
		case CALC_BTN_NUM6_ID:
		case CALC_BTN_NUM7_ID:
		case CALC_BTN_NUM8_ID:
		case CALC_BTN_NUM9_ID:
		{
			CHAR c = '0'+uMsg-CALC_BTN_NUM0_ID;
			pEdit->m_string.m_pfAppend(P2H(&pEdit->m_string), c);
		}
		break;

		case CALC_BTN_BRA1_ID:
		case CALC_BTN_BRA2_ID:
		{
			CHAR c = '('+uMsg-CALC_BTN_BRA1_ID;
			pEdit->m_string.m_pfAppend(P2H(&pEdit->m_string), c);			
		}
		break;

		case CALC_BTN_ADD_ID:
		{
			CHAR c = '+';
			pEdit->m_string.m_pfAppend(P2H(&pEdit->m_string), c);	
		}
		break;

		case CALC_BTN_SUB_ID:
		{
			CHAR c = '-';
			pEdit->m_string.m_pfAppend(P2H(&pEdit->m_string), c);	
		}
		break;

		case CALC_BTN_MUL_ID:
		{
			CHAR c = '*';
			pEdit->m_string.m_pfAppend(P2H(&pEdit->m_string), c);	
		}
		break;

		case CALC_BTN_DIV_ID:
		{
			CHAR c = '/';
			pEdit->m_string.m_pfAppend(P2H(&pEdit->m_string), c);	
		}
		break;

		case CALC_BTN_PINT_ID:
		{
			CHAR c = '.';
			pEdit->m_string.m_pfAppend(P2H(&pEdit->m_string), c);	
		}
		break;

		case CALC_BTN_MOD_ID:
		{
			CHAR c = '%';
			pEdit->m_string.m_pfAppend(P2H(&pEdit->m_string), c);	
		}
		break;

		case CALC_BTN_CE_ID:
		case CALC_BTN_C_ID:
			pEdit->m_string.m_pfSetText(P2H(&pEdit->m_string), "");
		break;

		case CALC_BTN_PN_ID:
		{
			CHAR c = '%';
			pEdit->m_string.m_pfAppend(P2H(&pEdit->m_string), c);	
		}			
		break;


		case CALC_BTN_EQL_ID:

		break;

		case CALC_BTN_BK_ID:
		{
			INT iLen = pEdit->m_string.m_iValLen;
			pEdit->m_string.m_pfRemove(P2H(&pEdit->m_string), iLen-1);
		}
		break;


		default:
		{
			
		}
		break;
	}

	pEdit->m_iCurEdit = pEdit->m_string.m_iValLen;
}

CcalcBtn calcBtnCfg[30] = 
{
	{"<-", CALC_BTN_BK_ID, CALC_BTN_MSG_ID, {10,34,20,20}, OnCalcBtn},
	{"CE", CALC_BTN_CE_ID, CALC_BTN_MSG_ID, {32,34,20,20}, OnCalcBtn},
	{"C", CALC_BTN_C_ID, CALC_BTN_MSG_ID, {54,34,20,20}, OnCalcBtn},
	{"+-", CALC_BTN_PN_ID, CALC_BTN_MSG_ID, {76,34,20,20}, OnCalcBtn},
	{"1", CALC_BTN_NUM1_ID, CALC_BTN_MSG_ID, {10,56,20,20}, OnCalcBtn},
	{"2", CALC_BTN_NUM2_ID, CALC_BTN_MSG_ID, {32,56,20,20}, OnCalcBtn},
	{"3", CALC_BTN_NUM3_ID, CALC_BTN_MSG_ID, {54,56,20,20}, OnCalcBtn},
	{"+", CALC_BTN_ADD_ID, CALC_BTN_MSG_ID, {76,56,20,20}, OnCalcBtn},
	{"4", CALC_BTN_NUM4_ID, CALC_BTN_MSG_ID, {10,78,20,20}, OnCalcBtn},
	{"5", CALC_BTN_NUM5_ID, CALC_BTN_MSG_ID, {32,78,20,20}, OnCalcBtn},
	{"6", CALC_BTN_NUM6_ID, CALC_BTN_MSG_ID, {54,78,20,20}, OnCalcBtn},
	{"-", CALC_BTN_SUB_ID, CALC_BTN_MSG_ID, {76,78,20,20}, OnCalcBtn},
	{"7", CALC_BTN_NUM7_ID, CALC_BTN_MSG_ID, {10,100,20,20}, OnCalcBtn},
	{"8", CALC_BTN_NUM8_ID, CALC_BTN_MSG_ID, {32,100,20,20}, OnCalcBtn},
	{"9", CALC_BTN_NUM9_ID, CALC_BTN_MSG_ID, {54,100,20,20}, OnCalcBtn},
	{"*", CALC_BTN_MUL_ID, CALC_BTN_MSG_ID, {76,100,20,20}, OnCalcBtn},
	{"0", CALC_BTN_NUM0_ID, CALC_BTN_MSG_ID, {10,122,20,20}, OnCalcBtn},
	{"=", CALC_BTN_EQL_ID, CALC_BTN_MSG_ID, {32,122,42,20}, OnCalcBtn},
	{"/", CALC_BTN_DIV_ID, CALC_BTN_MSG_ID, {76,122,20,20}, OnCalcBtn},
	{".", CALC_BTN_PINT_ID, CALC_BTN_MSG_ID, {10,144,20,20}, OnCalcBtn},
	{"(", CALC_BTN_BRA1_ID, CALC_BTN_MSG_ID, {32,144,20,20}, OnCalcBtn},
	{")", CALC_BTN_BRA2_ID, CALC_BTN_MSG_ID, {54,144,20,20}, OnCalcBtn},
	{"%", CALC_BTN_MOD_ID, CALC_BTN_MSG_ID, {76,144,20,20}, OnCalcBtn},
};


STATIC INT WindowFlow(PWindow pWin)
{
	pWin->m_pfPrintWindow(P2H(pWin));
    return 0;
}

VOID AppCalcDlg(VOID)
{
	CWindow   calcDlg;
	CButton   calcbtn[25];
	CEditView calcPrint;
	CRect  rect;
	CBrush brush;
	CFont  font;
	INT i;

	InitStringE(&strCalc, "", 124);

	InitWindowE(&calcDlg, NULL, CALC_DLG_ID);
	
	rect.m_iLeft = 10;
	rect.m_iTop = 10;
	rect.m_iWidth = 88;
	rect.m_iHeigh = 156;
	calcDlg.m_pfSelWinRect(P2H(&calcDlg), &rect, NULL);

	font.m_color = 0xFF000000;
	//calcDlg.m_pfSelWinFont(P2H(&calcDlg), &font, NULL);

	brush.m_color = 0xFF00FF00;
	//calcDlg.m_pfSelWinBrush(P2H(&calcDlg), &brush, NULL);

	for(i = 0; i < 23; i++)
	{
		InitButton(&calcbtn[i], &calcDlg, calcBtnCfg[i].m_iCalcBtnID, calcBtnCfg[i].m_czCalcBtnVal, 0, calcBtnCfg[i].m_iCalcBtnMsgID, OnCalcBtn);
		calcbtn[i].m_pfSelWinRect(P2H(&calcbtn[i]), &calcBtnCfg[i].m_iCalcBtnRect, NULL);

		font.m_color = 0xFFFF00FF;
		//calcbtn[i].m_pfSelWinFont(P2H(&calcbtn[i]), &font, NULL);

		brush.m_color = 0xFF0000FF;
		//calcDlg.m_pfSelWinBrush(P2H(&calcbtn[i]), &brush, NULL);
	}

	InitEditView(&calcPrint, &calcDlg, CALC_EV_PRINT_ID, "", 0);

	rect.m_iLeft = 12;
	rect.m_iTop = 12;
	rect.m_iWidth = 84;
	rect.m_iHeigh = 20;
	calcPrint.m_pfSelWinRect(P2H(&calcPrint), &rect, NULL);

	font.m_color = 0xFF000000;
	//calcPrint.m_pfSelWinFont(P2H(&calcPrint), &font, NULL);

	brush.m_color = 0xFFFFFFFF;
	//calcPrint.m_pfSelWinBrush(P2H(&calcPrint), &brush, NULL);

	FlowWindow0(pWinRoot, WindowFlow);

	PrintScreen();


	while(TRUE)
	{
		int x;
		int y;
		int iRet;
		CPoint point;
		scanf("%d %d", &x, &y);
		//pPoint = (PPoint)Malloc(sizeof(CPoint));
		point.m_iX = x;
		point.m_iY = y;

		iRet = pWinRoot->m_pfPostMessage(P2H(pWinRoot), WIN_MSG_ID_CLICK_SCREEN_DOWN, 0, &point);
		WinFlowMain();

		FlowWindow0(pWinRoot, WindowFlow);
		PrintScreen();
	}
}

