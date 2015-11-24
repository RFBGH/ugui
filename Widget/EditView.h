#ifndef __EDIT_VIEW_H__
#define __EDIT_VIEW_H__
#include "Window.h"

typedef INT (*PFSetText)(HANDLE hWin, CHAR* pcVal);

typedef INT (*PFSetCurEdit)(HANDLE hWin, INT iCurEdit);

typedef INT (*PFSetSel)(HANDLE hWin, INT iSelStart, INT iSelLen);



typedef struct _EditView
{
	//�̳д���
	CWindow m_baseWin;

	//�༭�ؼ���������б���
	CString m_string;

	//��ǰ�༭λ��
	INT     m_iCurEdit;

	//��ǰѡ����ʼ��ֹ
	INT     m_iSelStart;
	INT     m_iSelLen;

	//set window text.
	PFSetText m_pfSetText;

	//set window rect
	PFSetWinRect m_pfSelWinRect;

	//set window font
	PFSetWinFont m_pfSelWinFont;

	//set window brush
	PFSetWinBrush m_pfSelWinBrush;

	//print window
	PFPrintWindow m_pfPrintWindow;

	PFSetCurEdit m_pfSetCurEdit;

	PFSetSel     m_pfSetSel;

	
}CEditView, *PEditView;

INT InitEditView(PEditView pEdit, PWindow pParent, INT iID, CHAR* pcVal, UINT uFlag);
PEditView CreateEditView(PWindow pParent, INT iID, CHAR* pcVal, UINT uFlag);

VOID DeleteEditView(PEditView pEv);


#define EDIT_VIEW_MULTI_LINE  0x00100000
#define EDIT_VIEW_KEEPRIGHT   0x00200000
//#define EDIT_VIEW_KEEPLEFT    0x00200000
//#define EDIV_VIEW_SINGLE_LINE 0x00100000

#endif

