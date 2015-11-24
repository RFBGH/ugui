#ifndef __ON_WIN_MSG_PROC_LIST_H__
#define __ON_WIN_MSG_PROC_LIST_H__

#include "Window.h"

#define WIN_MSG_TYPE_BUTTON       0x00000001
#define WIN_MSG_TYPE_EDIT         0x00000002
#define WIN_MSG_TYPE_RADIO_BUTTON 0x00000003

#define WIN_MSG_TYPE_USER         0x80000000

typedef VOID (*PFWinOnUsrProc)(PWindow pWin, UINT uMsg, PVOID pMsg);
typedef VOID (*PFOnButton)(VOID);

typedef struct _OnMsgProc
{
    INT    m_iOnMsgType;
    INT    m_iMsgID;
    PVOID  m_pfOnMsgProc;
}COnMsgProc, *POnMsgProc;

//主要用于用户级别的消息处理函数注册

POnMsgProc CreateOnMsgProc(INT iOnMsgType, INT iMsgID, PVOID pOnMsgProc);
VOID DeleteOnMsgProc(POnMsgProc pOnMsgProc);

INT RegisterOnMsgProc(PWindow pWin, INT iMsgType, INT iMsgID, PVOID pfOnMsgProc);
INT UnregisterOnMsgProc(PWindow pWin, INT iMsgType, INT iMsgID);

#endif

