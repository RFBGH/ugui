#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "window.h"

typedef VOID (*PFSetTitle)(HANDLE hWin, CHAR* pcTitle);


typedef struct _Button
{
	CWindow m_baseWin;

	CHAR    m_czBtnTitl[256];

	INT     m_iMsgID;

	//set window rect
	PFSetWinRect m_pfSelWinRect;

	//set window font
	PFSetWinFont m_pfSelWinFont;

	//set window brush
	PFSetWinBrush m_pfSelWinBrush;

	//print window
	PFPrintWindow m_pfPrintWindow;

	//set title
	PFSetTitle m_pfSetTitle;
	
}CButton, *PButton;

INT InitBUtton(PButton pBtn, PWindow pWinParent, INT iID, CHAR* pBtnTitl, UINT uFlag, INT iMsgID, PFWinOnUsrProc pfWinOnUsrProc);
PButton CreateButton(PWindow pWinParent, INT iID, CHAR* pBtnTitl, UINT uFlag, INT iMsgID, PFWinOnUsrProc pfWinOnUsrProc);

VOID DeleteButton(PButton pButton);

#endif

