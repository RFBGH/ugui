#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "GDI.h"
#include "Font.h"
#include "Brush.h"

#include "WinType.h"
#include "WinMsg.h"
#include "WinBase.h"
#include "WinErr.h"

#include "OnWinMsgProcList.h"


/*************************************************************************/
// FOR WINDOW TREE...
PWindow CreateWindow(UINT uFlag, INT iID);

PWindow CreateWindowE(UINT uFlag, PWindow pParent, INT iID);

INT InitWindowE(PWindow pWin, PWindow pParent, INT iID);

INT InitWindowTree(PWindow pWin, INT iID);

INT DeleteWindow(PWindow pWin);

PWindow FindWindowByID(INT iID);

INT AddSonWindow(PWindow pWinParent, PWindow pWinSon);

INT ReorderWindow(PWindow pWin);

typedef INT (*PFWindowFlow)(PWindow pWin);

INT FlowWindow0(PWindow pWin, PFWindowFlow pfWindowFlow);

INT FlowWindow1(PWindow pWin, PFWindowFlow pfWindowFlow);

INT FlowWindow2(PWindow pWin, PFWindowFlow pfWindowFlow);

INT FlowWindow11(PWindow pWin, PFWindowFlow pfWindowFlow);

VOID WinDispatchMsgDef(HANDLE hWin, INT iMsgType, UINT uMsg, PVOID pMsg);

/*#######################################################################*/


/*************************************************************************/
// FOR WINDOW TREE...
INT SetWinBKColor(PWindow pWin, RGBA rgba);

INT SetWinRect(PWindow pWin, PRect pRect);

PWindow LocatWinByXY(PPoint pPoint);

VOID PrintWindowDef(HANDLE hWin);

VOID* FindItemById(HANDLE hWin, INT iID);

VOID DragWinsToXY(PWindow pWindow, INT x, INT y);


/*#######################################################################*/


/*************************************************************************/

INT PostMessage(HANDLE hWin, INT iMsgID, UINT uMsg, PVOID pMsg);

INT SendMessage(HANDLE hWin, INT iMsgID, UINT uMsg, PVOID pMsg);

INT RegisterOnMessage(HANDLE hWin, INT iMsgType, INT iMsgID, PVOID pfOnMsgProc);

INT UnregisterOnMessage(HANDLE hWin, INT iMsgType, INT iMsgID);

PMsg GetFirstWinMsg(VOID);

INT InitWindow(HANDLE hWin, HANDLE hWinParent, INT iID, INT iWinType, UINT uWinFlag);

INT SelWinRect(HANDLE hWin, PRect pRectNew, PRect pRectOld);

INT SelWinFont(HANDLE hWin, PFont pFontNew, PFont pFontOld);

INT SelWinBrush(HANDLE hWin, PBrush pBrushNew, PBrush pBrushOld);

/*#######################################################################*/

VOID InitGUI(VOID);


extern PWindow pWinRoot;
extern PList pWinMsgList;

#endif

