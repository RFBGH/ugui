#ifndef __LIST_H__
#define __LIST_H__

#include "Type.h"

typedef struct _ListNode
{
    PVOID m_pData;
    PVOID m_pNextNode;
    PVOID m_pLastNode;
}CListNode, *PListNode;

typedef struct _List
{
    PListNode m_pListHead;
    PListNode m_pListEnd;
    INT       m_iListSize;
}CList, *PList;

typedef INT (*PFunFlow)(PVOID pData);

INT FlowList(PList pList, PFunFlow pFunFlow);

INT InitList(PList pList);

INT DeletList(PList pList);

INT PushList(PList pList, PVOID pData);

INT InsertList(PList pList, INT iFind, PVOID pData);

INT FindList(PList pList, PVOID pData);

PVOID GetListData(PList pList, INT iFind);

//INT RemoveListByI(PList pList, INT iFind);

INT RemoveListByData(PList pList, PVOID pData);

#endif

