/****************************************************************************
*
*this procedure is work for manager window system tree.
*
*############################################################################
*AUTHOR:RFB 	LOG: Creat this procedure	TIME:2014/02/26
*****************************************************************************/

#include "Window.h"
#include "Malloc.h"
#include "Mem.h"

#define MAX_WINDOW_SIZE 1024

STATIC INT windowIDCnt = 1;

/*
 * Create a window.
 *
 * @param uFlag: the value of flag of window
 *
 * @return the pointer of the window.
 *
 */
PWindow CreateWindow(UINT uFlag, INT iID)
{
    PWindow pWinRet = NULL;

    pWinRet = (PWindow)Malloc(sizeof(CWindow));

    if(pWinRet)
    {
        MemSet(pWinRet, 0, sizeof(CWindow));
    }

    pWinRet->m_iID = iID;//windowIDCnt;
    //windowIDCnt++;
    return pWinRet;
}

/*
 * init a window.
 *
 * @param pWin: the ponter of window
 *
 * @return success >=0, else fail.
 *
 * @note param cant use the pointer from CreateWindow
 */
INT InitWindowTree(PWindow pWin, INT iID)
{
    if(pWin == NULL)
    {
        return -1;
    }

    MemSet(pWin, 0, sizeof(CWindow));

    pWin->m_iID = iID;//windowIDCnt;
    //windowIDCnt++;

    return 0;
}

/*
 * add a son window to a parent.
 *
 * @param pWinParent: the window of parent
 * @param pWinSon: the window of son
 *
 * @return success >=0, else fail.
 *
 */
INT AddSonWindow(PWindow pWinParent, PWindow pWinSon)
{
    PWindow pWinCurr = NULL;
    if(pWinParent == NULL || pWinSon == NULL)
    {
        return -1;
    }

    if(pWinParent == pWinSon)
    {
        return -2;
    }

    if(pWinParent->m_pFirstSon == NULL)
    {
        pWinParent->m_pFirstSon = pWinSon;
        pWinParent->m_pLastSon = pWinSon;
        pWinSon->m_pParent = pWinParent;

        return 0;
    }

    pWinCurr  = pWinParent->m_pLastSon;

    pWinCurr->m_pNext = pWinSon;
    pWinSon->m_pLast = pWinCurr;
    pWinSon->m_pParent = pWinParent;
    pWinParent->m_pLastSon = pWinSon;

    return 1;
}

#if 0

method 1.
STATIC PWindow pWinFind = NULL;
STATIC INT iWinFindID = 0;
INT FindWindowFlow(PWindow pWin)
{
    if(pWin->m_ID == iWinFindID)
    {
        pWinFind = pWin;
    }
}

PWindow FindWindowByID(INT iID)
{
    if(iID > windowIDCnt)
    {
        return NULL;
    }
    pWinFind = NULL;
    iWinFindID = iID;

    FlowWindow0(pWinRoot, FindWindowFlow);

    return pWinFind;
}

method 2.
PWindow id2win[MAX_WINDOW_SIZE];
PWindow FindWindowByID(INT iID)
{
    return FindWindowByID[iID];
}

#endif

/*
 * find a window in window system by ID.
 *
 * @param iID: the ID of window wanted.
 *
 * @return the pointer of window wanted.
 *
 */
PWindow FindWindowByID(INT iID)
{
    INT iFront;
    INT iRear;
    PWindow pWinFind[MAX_WINDOW_SIZE];
    PWindow pWinCurr = NULL;
    PWindow pWinRet = NULL;
    
    if(iID > windowIDCnt)
    {
        return NULL;
    }

    if(pWinRoot->m_iID == iID)
    {
        return pWinRoot;
    }

    iFront = 0;
    iRear = 1;
    pWinFind[0] = pWinRoot;
    
    while(iFront < iRear)
    {
        pWinCurr = pWinFind[iFront]->m_pFirstSon;

        while(pWinCurr != NULL)
        {
            if(pWinCurr->m_iID == iID)
            {
                pWinRet = pWinCurr;
                break;
            }
            pWinFind[iRear++] = pWinCurr;
            pWinCurr = pWinCurr->m_pNext;
        }

        if(pWinRet)
        {
            break;
        }
        iFront++;
    }

    return pWinRet;
}

/*
 * move the win in front of screen.
 *
 * @param pWin: pointer of window wanted it in front of screen.
 *
 * @return success >=0, else fail.
 *
 */
INT ReorderWindow(PWindow pWin)
{
    PWindow pWinCurr = NULL;
    PWindow pWinParent = NULL;

    if(!pWin)
    {
        return -1;
    }

    pWinCurr = pWin;

    while(TRUE)//(pWinCurr != NULL)
    {
        
        pWinParent = pWinCurr->m_pParent;
        if(pWinParent == NULL)
        {
            break;
        }

        if(pWinParent->m_pLastSon == pWinCurr)
        {
            //... continue
        }else if(pWinParent->m_pFirstSon == pWinCurr)
        {
            pWinParent->m_pFirstSon = pWinCurr->m_pNext;
            pWinParent->m_pFirstSon->m_pLast = NULL;
            pWinCurr->m_pLast = pWinParent->m_pLastSon;
            pWinParent->m_pLastSon->m_pNext = pWinCurr;
            pWinParent->m_pLastSon = pWinCurr;

            pWinCurr->m_pNext = NULL;            
        }else
        {
            pWinCurr->m_pLast->m_pNext = pWinCurr->m_pNext;
            pWinCurr->m_pNext->m_pLast = pWinCurr->m_pLast;
            pWinCurr->m_pLast = pWinParent->m_pLastSon;
            pWinParent->m_pLastSon->m_pNext = pWinCurr;
            pWinParent->m_pLastSon = pWinCurr;                
            pWinCurr->m_pNext = NULL;
        }
        
        pWinCurr = pWinParent;
    }

    return 0;
}

/*
 * remove and release the windows relative the window.
 *
 * @param pWin: the pointer of window wanted to delete.
 *
 * @return success >=0, else fail.
 *
 */
INT DeleteWindow(PWindow pWin)
{
    PWindow pWinCurr = NULL;

    if(pWin == NULL)
    {
        return -1;
    }
    
    pWinCurr = pWin->m_pFirstSon;
    while(pWinCurr != NULL)
    {
        DeleteWindow(pWinCurr);
        pWinCurr = pWinCurr->m_pNext;
    }

    //free window buffer.
    Free(pWin);

    return 0;
}

/*
 * preorder flow the windows system.
 *
 * @param pWin: the root pointer of windows system.
 * @param pfWindowFlow: the deal function.
 *
 * @return success >=0, else fail.
 *
 */
typedef INT (*PFWindowFlow)(PWindow pWin);
int icnt = 0;
INT FlowWindow0(PWindow pWin, PFWindowFlow pfWindowFlow)
{
    PWindow pWinCurr = NULL;
    INT iRet = 0;

#if 0
    {
        int i;
        icnt++;
        for(i = 0; i < icnt; i++)
            Log(" ");
        Log("[0x%08x] firstson[0x%08x] lastson[0x%08x]",pWin, pWin->m_pFirstSon, pWin->m_pLastSon);
    }
#endif

    if(pfWindowFlow != NULL)
    {
        iRet = pfWindowFlow(pWin);
        if(iRet)
        {
            return iRet;
        }
    }

    pWinCurr = pWin->m_pFirstSon;
    while(pWinCurr != NULL)
    {
        iRet = FlowWindow0(pWinCurr, pfWindowFlow);
        if(iRet)
        {
            return iRet;
        }
        pWinCurr = pWinCurr->m_pNext;
    }

#if 1
    icnt--;
#endif

    return 0;
}


/*
 * infix flow the windows system.
 *
 * @param pWin: the root pointer of windows system.
 * @param pfWindowFlow: the deal function.
 *
 * @return success >=0, else fail.
 *
 */
INT FlowWindow1(PWindow pWin, PFWindowFlow pfWindowFlow)
{
    PWindow pWinCurr = NULL;
    INT iRet = 0;

    pWinCurr = pWin->m_pFirstSon;
    while(pWinCurr != NULL)
    {
        iRet = FlowWindow1(pWinCurr, pfWindowFlow);
        if(iRet)
        {
            return iRet;
        }
        pWinCurr = pWinCurr->m_pNext;
    }

    if(pfWindowFlow != NULL)
    {
        iRet = pfWindowFlow(pWin);
    }

    return iRet;
}

/*
 * infix flow the windows system, stop when pfWindowFlow return success.
 *
 * @param pWin: the root pointer of windows system.
 * @param pfWindowFlow: the deal function.
 *
 * @return success >=0, else fail.
 *
 */
INT FlowWindow11(PWindow pWin, PFWindowFlow pfWindowFlow)
{
    PWindow pWinCurr = NULL;
    INT iRet = 0;

    pWinCurr = pWin->m_pLastSon;
    while(pWinCurr != NULL)
    {
        iRet = FlowWindow11(pWinCurr, pfWindowFlow);
        if(iRet)
        {
            return iRet;
        }
        pWinCurr = pWinCurr->m_pLast;
    }

    if(pfWindowFlow != NULL)
    {
        iRet = pfWindowFlow(pWin);
    }

    return iRet;
}


/*
 * followup flow the windows system, stop when pfWindowFlow return success.
 *
 * @param pWin: the root pointer of windows system.
 * @param pfWindowFlow: the deal function.
 *
 * @return success >=0, else fail.
 *
 */
INT FlowWindow2(PWindow pWin, PFWindowFlow pfWindowFlow)
{
    PWindow pWinCurr = NULL;
    INT iRet = 0;

    pWinCurr = pWin->m_pFirstSon;
    while(pWinCurr != NULL)
    {
        if(pfWindowFlow != NULL)
        {
            iRet = pfWindowFlow(pWinCurr);
            if(iRet)
            {
                return iRet;
            }
        }
        
        iRet = FlowWindow2(pWinCurr, pfWindowFlow);
        if(iRet)
        {
            return iRet;
        }
        pWinCurr = pWinCurr->m_pNext;
    }

    return 0;
}



