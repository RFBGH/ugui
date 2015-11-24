/****************************************************************************
*
*this procedure is work for offering same common operate.
*
*############################################################################
*AUTHOR:RFB 	LOG: Creat this procedure	TIME:2014/02/26
*****************************************************************************/
#include "Window.h"

/*
 * Create a window message.
 *
 * @param iMsgID: the ID of message.
 * @param uMsg  : the value of UINT Message.
 * @param pMsg  : the value of PVOID message.
 * @param hWin  : the handle of target window
 *
 * @return the POINT of the message.
 *
 */
PMsg CreateWinMsg(INT iMsgID, UINT uMsg, PVOID pMsg, HANDLE hWin)
{
    PMsg pMsgTmp = NULL;

    pMsgTmp = (PMsg)Malloc(sizeof(CMsg));
    if(!pMsgTmp)
    {
        return NULL;
    }

    pMsgTmp->m_iMsgID = iMsgID;
    pMsgTmp->m_uMsg = uMsg;
    pMsgTmp->m_pMsg = pMsg;
    pMsgTmp->m_pDstWin = H2P(hWin);

    return pMsgTmp;
}


/*
 * release a window message.
 *
 * @param pMsg: the point of window message.
 *
 * @return NULL.
 *
 */

VOID DestroyWinMsg(PMsg pMsg)
{
    Free(pMsg);
}

/*
 * push the message in the end of message list.
 *
 * @param pWin: the Pointer of the target window.
 * @param iMsgID: the ID of the message.
 * @param uMsg  : the value of UINT Message.
 * @param pMsg  : the value of PVOID message.
 *
 * @return NULL.
 *
 */

//Post the last message in list.
INT PostWinMsg(PWindow pWin, INT iMsgID, UINT uMsg, PVOID pMsg)
{
    if(pWin == NULL)
    {
        return -1;
    }

    PMsg pMsgTmp = NULL;

#if 0
    Log("PostWinMsg...\r\n");
#endif

    pMsgTmp = (PMsg)Malloc(sizeof(CMsg));
    if(!pMsgTmp)
    {
        return -2;
    }

    pMsgTmp->m_iMsgID = iMsgID;
    pMsgTmp->m_uMsg = uMsg;
    pMsgTmp->m_pMsg = pMsg;
    pMsgTmp->m_pDstWin = pWin;
    
    return PushList(pWinMsgList, pMsgTmp);
}

/*
 * insert the message in the head of message list.
 *
 * @param pWin: the Pointer of the target window.
 * @param iMsgID: the ID of the message.
 * @param uMsg  : the value of UINT Message.
 * @param pMsg  : the value of PVOID message.
 *
 * @return NULL.
 *
 */
//insert to the first message in list.
INT SendWinMsg(PWindow pWin, INT iMsgID, UINT uMsg, PVOID pMsg)
{
    if(pWin == NULL)
    {
        return -1;
    }

    PMsg pMsgTmp = NULL;

    pMsgTmp = (PMsg)Malloc(sizeof(CMsg));
    if(!pMsgTmp)
    {
        return -2;
    }

    pMsgTmp->m_iMsgID = iMsgID;
    pMsgTmp->m_uMsg = uMsg;
    pMsgTmp->m_pMsg = pMsg;
    pMsgTmp->m_pDstWin = pWin;
    
    return InsertList(pWinMsgList, 0, pMsgTmp);
}

/*
 * get the top message in the message list.
 *
 * @param NULL.
 *
 * @return the pointer of the message in the top of the list.
 *
 */
PMsg GetFirstWinMsg(VOID)
{
    PMsg pMsg = NULL;
    
    if(pWinMsgList->m_iListSize)
    {
        pMsg = (PMsg)GetListData(pWinMsgList, 0);
        RemoveListByData(pWinMsgList, pMsg);
    }
    return pMsg;
}

