#ifndef __MALLOC_H__
#define __MALLOC_H__

#include "Common.h"


typedef struct _MemoryBlock
{
	//uint32 uAddrStart;
	UINT uUseSize;
	UINT uAllSize;
	VOID* pMemBlkNext;
}MemBlk, *PMemBlk;

#define INIT_HEAP_FORCE 1
#define INIT_HEAP_DEFAULT 0

VOID InitHeapPool(INT iType);

VOID Free(VOID* p);

VOID* Malloc(UINT uSize);

//VOID HeapCleanUp(VOID);

//VOID test(VOID);

#endif
