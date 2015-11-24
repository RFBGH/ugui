#ifndef __CHECK_BOX_H__
#define __CHECK_BOX_H__

#include "Window.h"

typedef VOID (*PFSetTitle)(HANDLE handle, CHAR* pcTitle);
typedef VOID (*PFSetCheck)(HANDLE handle, BOOL bCheck);
typedef BOOL (*PFIsCheck)(HANDLE handle);


typedef struct _CheckBox
{
	CWindow m_baseWin;

	BOOL    m_bCheck;
	CHAR    m_czBtnTitl[256];

	INT     m_iMsgID;

		//set window rect
	PFSetWinRect m_pfSelWinRect;

	//set window font
	PFSetWinFont m_pfSelWinFont;

	//set window brush
	PFSetWinBrush m_pfSelWinBrush;

	//set titile
	PFSetTitle  m_pfSetTitle;

	//set check
	PFSetCheck m_pfSetCheck;

	//get check value
	PFIsCheck m_pfIsCheck;
	
}CCheckBox, *PCheckBox;

PCheckBox CreateCheckBox(PWindow pParent, INT iID, CHAR* pBtnTitle, BOOL bCheck, UINT uFlag);

VOID DeleteCheckBox(PCheckBox pCkBox);

INT InitCheckBox(PCheckBox pCkBox, PWindow pParent, INT iID, CHAR* pBtnTitle, BOOL bCheck, UINT uFlag);

INT RegisterCheckBoxOnMsg(PCheckBox pCkBox, INT iMsgID, PFWinOnUsrProc PFWinOnUsrProc);

INT UnregisterCheckBoxOnMsg(PCheckBox pCkBox, INT iMsgID);

#endif

