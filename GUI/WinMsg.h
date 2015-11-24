#ifndef __WIN_MSG_H__
#define __WIN_MSG_H__

#include "Tool.h"
#include "WinType.h"
#include "Key.h"

typedef struct _Msg
{
    INT     m_iMsgID;
    UINT    m_uMsg;
    PVOID   m_pMsg;
    PWindow m_pDstWin;
}CMsg, *PMsg;

PMsg CreateWinMsg(INT iMsgID, UINT uMsg, PVOID pMsg, HANDLE hWin);
VOID DestroyWinMsg(PMsg pMsg);

//屏幕点击消息
#define WIN_MSG_ID_CLICK_SCREEN_DOWN (0x00000001) 
#define WIN_MSG_ID_CLICK_SCREEN_UP   (0x00000002) 
#define WIN_MSG_ID_DRAG_SCREEN       (0x00000003)

#define WIN_MSG_ID_REPAINT           (0x40000001)


//串口最小化按键消息
#define WIN_MSG_MAXMIZE_BUTTON  (0x20000001)
#define WIN_MSG_MINIZE_BUTTON   (0x20000002)        

#define WIN_MSG_BUTTON  (0x10000001)
#define WIN_MSG_KEY     (0x10000002)

#define WIN_MSG_ID_USR (0x80000000)

// FOR WINDOW Message...

INT PostWinMsg(PWindow pWin, INT iMsgID, UINT uMsg, PVOID pMsg);
INT SendWinMsg(PWindow pWin, INT iMsgID, UINT uMsg, PVOID pMsg);
PMsg GetFirstWinMsg(VOID);

#endif

