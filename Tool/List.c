#include "List.h"
#include "Malloc.h"
#include "Mem.h"

INT InitList(PList pList)
{
    PListNode pListNodeTemp = NULL;

    
    if(pList == NULL)
    {
        return -1;
    }

    InitHeapPool(INIT_HEAP_DEFAULT);

    pListNodeTemp = (PListNode)Malloc(sizeof(CListNode));

    if(pListNodeTemp == NULL)
    {
        return -2;
    }
    
    MemSet(pListNodeTemp, 0, sizeof(CListNode));
    
    pList->m_iListSize = 0;
    pList->m_pListHead = pListNodeTemp;
    pList->m_pListEnd = pList->m_pListHead;
    return 0;
}

INT DeletList(PList pList)
{
    INT i;
    PListNode pListNodeCurr = NULL;
    PListNode pListNodeNext = NULL;
    
    if(pList == NULL)
    {   
        return -1;
    }

    if(pList->m_iListSize == 0)
    {
        return 0;
    }

    if(pList->m_pListHead == NULL)
    {
        return -2;
    }
    
    pListNodeCurr = pList->m_pListHead;
    pListNodeNext = pListNodeCurr->m_pNextNode;
    
    for(i = 0; i < pList->m_iListSize; i++)
    {
       Free(pListNodeCurr);

       if(pListNodeNext == NULL)
       {
            break;
       }
       pListNodeCurr = pListNodeNext;
       pListNodeNext = pListNodeCurr->m_pNextNode;
    }

    if(pList->m_iListSize-1 == i)
    {
        pList->m_iListSize = 0;
        return (i+1);
    }
    return -2;
}

INT FlowList(PList pList, PFunFlow pFunFlow)
{
    INT i;
    PListNode pListNodeCurr = NULL;
    
    if(pList == NULL)
    {   
        return -1;
    }

    if(pList->m_iListSize == 0)
    {
        return 0;
    }

    if(pList->m_pListHead == NULL)
    {
        return -2;
    }
    
    pListNodeCurr = pList->m_pListHead;
    
    for(i = 0; i < pList->m_iListSize; i++, pListNodeCurr = pListNodeCurr->m_pNextNode)
    {
        if(pFunFlow)
        {
            pFunFlow(pListNodeCurr->m_pData);
        }
    }

    return i;
}

INT PushList(PList pList, PVOID pData)
{
    PListNode pListNodeTemp = NULL;

    if(pList == NULL)
    {
        return -1;
    }

    if(pList->m_pListHead == NULL)
    {
        return -2;
    }

    if(pList->m_iListSize == 0)
    {
        pList->m_pListHead->m_pData = pData;
    }else
    {
        pListNodeTemp = (PListNode)Malloc(sizeof(CListNode));
        if(pListNodeTemp == NULL)
        {
            return -3;
        }
        MemSet(pListNodeTemp, 0, sizeof(CListNode));
        pListNodeTemp->m_pData = pData;
        pListNodeTemp->m_pLastNode = pList->m_pListEnd;
        pList->m_pListEnd->m_pNextNode = pListNodeTemp;
        pList->m_pListEnd = pListNodeTemp;
    }
    pList->m_iListSize++;

    return pList->m_iListSize;
}

INT InsertList(PList pList, INT iFind, PVOID pData)
{
    INT i;
    PListNode pListNodeCurr = NULL;
    
    if(pList == NULL)
    {   
        return -1;
    }

    if(pList->m_pListHead == NULL)
    {
        return -2;
    }

    if(iFind >= pList->m_iListSize)
    {   //ÁÐ±íÄ©Î²Ìî³ä
        return PushList(pList, pData);
    }

    if(pList->m_iListSize == 0)
    {
        pListNodeCurr->m_pData = pData;
    }else
    {
        PListNode pListNodeTemp = (PListNode)Malloc(sizeof(CListNode));
        if(pListNodeTemp == NULL)
        {
            return -3;
        }
        MemSet(pListNodeTemp, 0, sizeof(CListNode));
        
        pListNodeCurr = pList->m_pListHead;
        for(i = 0; i < iFind; i++,pListNodeCurr=pListNodeCurr->m_pNextNode)
        {
            ;
        }

        pListNodeTemp->m_pData = pData;
        pListNodeTemp->m_pNextNode = pListNodeCurr;
        if(pListNodeCurr->m_pLastNode)
        {
            ((PListNode)pListNodeCurr->m_pLastNode)->m_pNextNode = pListNodeTemp;
            pListNodeTemp->m_pLastNode = pListNodeCurr->m_pLastNode;
        }
        pListNodeCurr->m_pLastNode = pListNodeTemp;

        if(i == 0)
        {
            pList->m_pListHead = pListNodeTemp;
        }
    }

    pList->m_iListSize++;
    return pList->m_iListSize;
}

INT FindList(PList pList, PVOID pData)
{
    PListNode pListNodeCurr = NULL;
    INT i;

    if(pList == NULL)
    {
        return -1;
    }

    if(pList->m_pListHead == NULL)
    {
        return -2;
    }


    pListNodeCurr = pList->m_pListHead;

    for(i = 0; i < pList->m_iListSize; i++, pListNodeCurr = pListNodeCurr->m_pNextNode)
    {
        if(pListNodeCurr->m_pData == pData)
        {
            return i;
        }
    }
    return -4;
}

PVOID GetListData(PList pList, INT iFind)
{
    INT i;
    PListNode pListNodeCurr = NULL;
    
    if(pList == NULL)
    {   
        return NULL;
    }

    if(iFind >= pList->m_iListSize)
    {
        return NULL;
    }

    if(pList->m_pListHead == NULL)
    {
        return NULL;
    }

    pListNodeCurr = pList->m_pListHead;

    for(i = 0; i < iFind; i++,pListNodeCurr=pListNodeCurr->m_pNextNode)
    {
        ;
    }
    return pListNodeCurr->m_pData;
}

//INT RemoveListByI(PList pList, INT iFind)
//{
//    return 0;
//}

INT RemoveListByData(PList pList, PVOID pData)
{
    INT i;
    PListNode pListNodeCurr = NULL;
    
    if(pList == NULL)
    {   
        return -1;
    }

    if(pList->m_pListHead == NULL)
    {
        return -3;
    }

    pListNodeCurr = pList->m_pListHead;

    for(i = 0; i < pList->m_iListSize; i++,pListNodeCurr=pListNodeCurr->m_pNextNode)
    {

        if(pListNodeCurr->m_pData == pData)
        {
            break;
        }
    }    
    if(pListNodeCurr == NULL)
    {
        return -4;
    }

    if(pList->m_iListSize == 1)
    {
        pListNodeCurr->m_pData = NULL;
        pList->m_iListSize--;
        return 0;
    }
    
    if(pListNodeCurr->m_pNextNode)
    {
        ((PListNode)pListNodeCurr->m_pNextNode)->m_pLastNode = pListNodeCurr->m_pLastNode;
    }else{
    
        pList->m_pListEnd = pListNodeCurr->m_pLastNode;
    }   
    
    if(pListNodeCurr->m_pLastNode)
    {
        ((PListNode)pListNodeCurr->m_pLastNode)->m_pNextNode = pListNodeCurr->m_pNextNode;
    }else
    {
        pList->m_pListHead = pListNodeCurr->m_pNextNode;
    }
    
    pList->m_iListSize--;
    Free(pListNodeCurr);

    return pList->m_iListSize;
}

