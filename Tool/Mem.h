#ifndef __MEM_H__
#define __MEM_H__

#include "Type.h"

VOID MemSet(PVOID pDst, INT iVal, INT iSize);

VOID MemCpy(PVOID pDst, PVOID pSrc, INT iSize);

INT MemCmp(PVOID pDst, PVOID pSrc, INT iSize);

INT Strlen(char* pc);

#endif

