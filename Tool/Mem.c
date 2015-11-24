#include "Mem.h"

VOID MemSet(PVOID pDst, INT iVal, INT iSize)
{
    INT i;
    PCHAR pcDst;

    if(pDst == NULL)
    {
        return;
    }

    pcDst = (PCHAR)pDst;
    for(i = 0; i < iSize; i++)
    {
        pcDst[i] = iVal;
    }
}

VOID MemCpy(PVOID pDst, PVOID pSrc, INT iSize)
{
    INT i;
    PCHAR pcDst;
    PCHAR pcSrc;

    if(pDst == NULL || pSrc == NULL)
    {
        return;
    }


    pcDst = (PCHAR)pDst;
    pcSrc = (PCHAR)pSrc;

    for(i = 0; i < iSize; i++)
    {
        pcDst[i] = pcSrc[i];
    }

}

INT MemCmp(PVOID pDst, PVOID pSrc, INT iSize)
{
    INT i;
    PCHAR pcDst;
    PCHAR pcSrc;
    INT iRet;

    if(pDst == NULL || pSrc == NULL)
    {
        return;
    }

    pcDst = (PCHAR)pDst;
    pcSrc = (PCHAR)pSrc;

    iRet = 0;
    for(i = 0; i < iSize; i++)
    {
        if(!iRet)
        {
            iRet = pcDst[i]-pcSrc[i];
        }
    }

    return iRet;
}

INT Strlen(char* pc)
{
    int i;
    for(i = 0; pc[i] != '\0'; i++)
    {

    }
    return i;
}


