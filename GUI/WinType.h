#ifndef __WIN_TYPE_H__
#define __WIN_TYPE_H__

#include "Tool.h"

#define WINDOW_TYPE_WINDOW 0x00000000
#define WINDOW_TYPE_BUTTON 0x00000001
#define WINDOW_TYPE_EDITVIEW 0x00000002
#define WINDOW_TYPE_CHECKBOX 0x00000003

typedef VOID (*PFWinDispatchMsg)(HANDLE hWin, INT iMsgID, UINT uMsg, PVOID pMsg);
typedef INT  (*PFPostMessage)(HANDLE hWin, INT iMsgID, UINT uMsg, PVOID pMSg);
typedef INT  (*PFSendMessage)(HANDLE hWin, INT iMsgID, UINT uMsg, PVOID pMsg);
typedef INT  (*PFRegisterOnMsgProc)(HANDLE hWin, INT iMsgType, INT iMsgID, PVOID pfOnMsgProc);
typedef int  (*PFUnregisterOnMsgProc)(HANDLE hWin, INT iMsgType, INT iMsgID);

typedef INT  (*PFInitWindow)(HANDLE hWin, HANDLE hWinParent, INT iID, INT iWinType, UINT uWinFlag);
typedef INT  (*PFSetWinRect)(HANDLE hWin, PRect pRectNew, PRect pRectOld);
typedef INT  (*PFSetWinFont)(HANDLE hWin, PFont pFontNew, PFont pFontOld);
typedef INT  (*PFSetWinBrush)(HANDLE hWin, PBrush pBrushNew, PBrush pBrushOld);

typedef VOID* (*PFFindItemById)(HANDLE hWin, INT iID);

typedef VOID (*PFPrintWindow)(HANDLE hWin);


typedef struct _Window
{
    //manager the windows
    struct _Window* m_pParent;
    struct _Window* m_pFirstSon;
    struct _Window* m_pLastSon;
    struct _Window* m_pLast;
    struct _Window* m_pNext;

    //window id
    INT m_iID;

    //window rect
    CRect m_rect;

    //window show rect
    CRect m_showRect;

    //window font for textout
    CFont   m_font;

    //window brush for brush bk
    CBrush  m_brush;

    //window type for divid button,edit
    INT m_iWinType;

	//reserve for extend option for window
    UINT m_iWinFlag;

	//window register onmessage process list.
    CList m_onMsgProcList;
    
    //window dispatch message.
    PFWinDispatchMsg m_pfWinDispatchMsg;

    //post message
    PFPostMessage m_pfPostMessage;

    //send message
    PFSendMessage m_pfSendMessage;

    //register message process
    PFRegisterOnMsgProc m_pfRegisterOnMsgProc;

    //unregister message process
    PFUnregisterOnMsgProc m_pfUnregisterOnMsgProc;

    //init windows
    PFInitWindow m_pfInitWindow;

    //set window rect
    PFSetWinRect m_pfSelWinRect;

    //set window font
    PFSetWinFont m_pfSelWinFont;

    //set window brush
    PFSetWinBrush m_pfSelWinBrush;

	//print window
	PFPrintWindow m_pfPrintWindow;

	//Get window item by ID
	PFFindItemById m_pfFindItemById;
}CWindow, *PWindow;

#endif

