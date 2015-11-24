/****************************************************************************
*
*this procedure is work for on message process register/unregister.
*
*############################################################################
*AUTHOR:RFB 	LOG: Creat this procedure	TIME:2014/02/26
*****************************************************************************/

#include "OnWinMsgProcList.h"

/*
 * create a OnMessage procss.
 *
 * @param iOnMsgType: the type of message.
 * @param iMsgID: the ID of message.
 * @param pOnMsgProc: the on message process.
 *
 * @return on message.
 *
 */
POnMsgProc CreateOnMsgProc(INT iOnMsgType, INT iMsgID, PVOID pOnMsgProc)
{
    POnMsgProc pOnMsgProcTmp = NULL;

    pOnMsgProcTmp = (POnMsgProc)Malloc(sizeof(COnMsgProc));

    if(pOnMsgProcTmp)
    {
        pOnMsgProcTmp->m_iOnMsgType = iOnMsgType;
        pOnMsgProcTmp->m_pfOnMsgProc = pOnMsgProc;
        pOnMsgProcTmp->m_iMsgID = iMsgID;
    }

    return pOnMsgProcTmp;
}

VOID DeleteOnMsgProc(POnMsgProc pOnMsgProc)
{
    Free(pOnMsgProc);
}

INT RegisterOnMsgProc(PWindow pWin, INT iMsgType, INT iMsgID, PVOID pfOnMsgProc)
{
    PList pOnMsgProcList;
    PListNode pListCurr;
    POnMsgProc pOnMsgProc;
    INT i;

    if(pWin == NULL || pfOnMsgProc == NULL)
    {
        return -2;
    }
    
    pOnMsgProcList = &pWin->m_onMsgProcList;
    pListCurr = pOnMsgProcList->m_pListHead;
    for(i = 0; i < pOnMsgProcList->m_iListSize; i++)
    {
        pOnMsgProc = (POnMsgProc)(pListCurr->m_pData);
        if(/*pOnMsgProc->m_iOnMsgType == iMsgType && */pOnMsgProc->m_iMsgID == iMsgID)
        {
            return -1;
        }
        pListCurr = pListCurr->m_pNextNode;
    }
    
    pOnMsgProc = CreateOnMsgProc(iMsgType, iMsgID, pfOnMsgProc);
    PushList(pOnMsgProcList, pOnMsgProc);
    
    return 0;
}

INT UnregisterOnMsgProc(PWindow pWin, INT iMsgType, INT iMsgID)
{
    PList pOnMsgProcList;
    PListNode pListCurr;
    POnMsgProc pOnMsgProc; 
    INT i;
    
    if(pWin == NULL)
    {
        return -2;
    }

    pOnMsgProcList = &pWin->m_onMsgProcList;
    pListCurr = pOnMsgProcList->m_pListHead;
    for(i = 0; i < pOnMsgProcList->m_iListSize; i++)
    {
        pOnMsgProc = (POnMsgProc)(pListCurr->m_pData);
        if(pOnMsgProc->m_iOnMsgType == iMsgType && pOnMsgProc->m_iMsgID == iMsgID)
        {
            break;
        }
        pListCurr = pListCurr->m_pNextNode;
    }

    if(i == pOnMsgProcList->m_iListSize)
    {
        return -1;
    }

    RemoveListByData(pOnMsgProcList, pOnMsgProc);
}

