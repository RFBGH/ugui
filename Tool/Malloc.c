/****************************************************************************
*
*this procedure is work for the Heap memory control.
*
*############################################################################
*AUTHOR:RFB 	LOG: Creat this procedure	 TIME:2013/01/11
*AUTHOR:RFB     LOG: Reset the initheap      TIME:2013/01/18
*AUTHOR:RFB     LOG: 添加内存整理功能        TIME:2013/03/26
                     修正空间浪费错误     
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "Type.h"
#include "Malloc.h"

#define MAX_HEAP_SIZE 1024*1024

static UCHAR bzHeapBuf[MAX_HEAP_SIZE];
static PMemBlk pMemBlk = NULL;

//#define RFB_DEBUG

#ifdef RFB_DEBUG

void PrintMemBlk(PMemBlk pMb)
{
	int i;
	unsigned char* pbTmp = (unsigned char*)pMb;
	pbTmp += sizeof(MemBlk);
	
	printf("Memory block address[0x%08x]\n", pMb);
	printf("Memory block all size[%d]\n", pMb->uAllSize);
	printf("Memory block use size[%d]\n", pMb->uUseSize);
	printf("Memory block address[0x%08x]\n", pMb->pMemBlkNext);
	printf("buff:\n");
	for(i = 0; i < pMb->uUseSize; i++)
	{
		printf("%d ", pbTmp[i]);	
	}
	printf("\n");
}

void PrintAllMemBlk()
{
	PMemBlk pMb;

	pMb = pMemBlk;
	printf("#####################################\n");
	printf("All Memory Block Info following:\r\n");
	//ergodic Memory block.
	while(pMb != NULL)
	{
		PrintMemBlk(pMb);
		pMb = pMb->pMemBlkNext;
	}
	printf("**************************************\n");
}

#endif

/*
 * Heap Init..
 *
 * @param iType: init type INIT_HEAP_FORCE INIT_HEAP_DEFAULT
 *
 * @return null
 *
 * @note: INIT_HEAP_FORCE it will force clean the heapmemory, resetall, use this must be careful.
 *        INIT_HEAP_DEFAULT if pMemBlk not NULL it will not clean the heapmemory.
 */
VOID InitHeapPool(INT iType)
{

	if((iType == INIT_HEAP_FORCE) || (pMemBlk == NULL))
	{
		MemSet(bzHeapBuf, 0, sizeof(bzHeapBuf));

		pMemBlk = (PMemBlk)bzHeapBuf;
		pMemBlk->uAllSize = MAX_HEAP_SIZE - sizeof(MemBlk);
		pMemBlk->uUseSize = 0;
		pMemBlk->pMemBlkNext = NULL;
	}
}

/*
PMemBlk GetMB(void* p)
{
	PMemBlk pMbCurr;

	pMbCurr = pMemBlk;

	while(pMbCurr != NULL)
	{
		if((p >= (pMbCurr+sizeof(MemBlk))) && (p < (pMbCurr + pMbCurr->uAllSize)))
		{
			break;
		}
		pMbCurr = pMbCurr->pMemBlkNext;
	}

	return pMbCurr;
}
*/

/*
 * clean the fragment in all memory.
 *
 * @param NULL
 *
 * @return NULL
 */
VOID HeapCleanUp(VOID)
{
/*    
	PMemBlk pMbCurr = NULL;
	PMemBlk pMbNext = NULL;	
	UCHAR* pbDst = NULL;
	UCHAR* pbSrc = NULL;
	
	INT iCnt = 0;
	
	if(pMemBlk->pMemBlkNext == NULL)
	{
		return;	
	}
	
	pMbCurr = pMemBlk;
	pMbNext = (PMemBlk)pMbCurr->pMemBlkNext;
	
	while(pMbNext != NULL)
	{
		if(pMbCurr->uAllSize > pMbCurr->uUseSize)
		{
			pbDst = (unsigned char*)pMbCurr;
			pbDst += sizeof(MemBlk); 
			pbDst += pMbCurr->uUseSize;
			
			pbSrc = (unsigned char*)pMbNext;
			iCnt = pMbNext->uUseSize+sizeof(MemBlk);
			
			pMbNext->uAllSize += pMbCurr->uAllSize - pMbCurr->uUseSize;
			
			pMbCurr->uAllSize = pMbCurr->uUseSize;
			pMbCurr->pMemBlkNext = pbDst;
			
			while(iCnt > 0)
			{
				*pbDst++ = *pbSrc++;
				iCnt--;	
			}
		}
		
		pMbCurr = (PMemBlk)pMbCurr->pMemBlkNext;
		pMbNext = (PMemBlk)pMbCurr->pMemBlkNext;	
	}
*/
}

/*
 * free heap pointer
 *
 * @param p: the heap pointer.
 *
 * @return null
 */
VOID Free(VOID* p)
{
	PMemBlk pMbCurr = NULL;
	PMemBlk pMbTmp = NULL;

	if(p == NULL)
	{
		return;
	}

	pMbCurr = pMemBlk;
	//ergodic memroy block, local the p in which Memory block.
	while(pMbCurr != NULL)
	{
		if((p >= (VOID*)(((UCHAR*)pMbCurr)+sizeof(MemBlk))) && 
			(p < (VOID*)(((UCHAR*)pMbCurr)+sizeof(MemBlk) + pMbCurr->uAllSize)))
		{
			break;
		}
		
		pMbTmp = pMbCurr;
		pMbCurr = pMbCurr->pMemBlkNext;
	}

	//local p succeed.
	if(pMbCurr != NULL)
	{
		//fuse the current block with its parent.
		if(pMbTmp!= NULL)
		{

			pMbTmp->pMemBlkNext = pMbCurr->pMemBlkNext;
			pMbTmp->uAllSize += pMbCurr->uAllSize+sizeof(MemBlk);
			pMbCurr = pMbTmp;
		}else{
			pMbCurr->uUseSize = 0;	
		}
		
		//fuse the current block with its son.
		pMbTmp = pMbCurr->pMemBlkNext;
		if((pMbTmp != NULL) && (pMbTmp->uUseSize == 0))
		{
			pMbCurr->uAllSize += pMbTmp->uAllSize+sizeof(MemBlk);
			pMbCurr->pMemBlkNext = pMbTmp->pMemBlkNext;
		}
	}
}

/*
 * malloc heap pointer
 *
 * @param uSize: the size of memory malloc.
 *
 * @return success: malloc memory pointer, fail:null pointer.
 */
VOID* Malloc(UINT uSize)
{
	PMemBlk pMbNext = NULL;
	PMemBlk pMbCurr = NULL;
	PMemBlk pMbTmp = NULL;
	UCHAR* pbTmp = NULL;
	VOID* pResult = NULL;

	pResult = NULL;

	//size == 0.
	if(uSize == 0)
	{
		return NULL;
	}

	pMbCurr = pMemBlk;
	pMbNext = pMbCurr->pMemBlkNext;

	if((pMbCurr->uUseSize == 0) && 
		(pMbCurr->uAllSize >= (uSize + pMbCurr->uUseSize + sizeof(MemBlk))))
	{	//the first block not use and have the enough space.

		pMbCurr->uUseSize = uSize;
		pbTmp = (unsigned char*)pMbCurr;
		pResult = (void*)(pbTmp+sizeof(MemBlk));

	}else
	{
		//遍历全部内存管理块
		while(pMbCurr != NULL)
		{
			if(pMbCurr->uAllSize >= (uSize + pMbCurr->uUseSize + sizeof(MemBlk)))
			{
				pbTmp = (UCHAR*)pMbCurr;
				pbTmp += sizeof(MemBlk);
				pbTmp += pMbCurr->uUseSize;
				//找到满足空间大小的空闲块
				if(pMbCurr->uUseSize != 0)
				{
					//如果当前块的使用量不为0，则必须重新生成一个内存管理块
					pMbTmp = (PMemBlk)(pbTmp);
					pMbTmp->uUseSize = uSize;
					pMbTmp->uAllSize = pMbCurr->uAllSize - pMbCurr->uUseSize - sizeof(MemBlk);
					pMbTmp->pMemBlkNext = pMbCurr->pMemBlkNext;		
	
					pMbCurr->pMemBlkNext = pMbTmp;
					pMbCurr->uAllSize = pMbCurr->uUseSize; 
					pbTmp = (unsigned char*)pMbTmp;
					pbTmp += sizeof(MemBlk);
					pResult =  (VOID*)(pbTmp);					
				}else{
					//如果当前块的使用量为0，则不必重新生成一个内存管理块
					pMbCurr->uUseSize = uSize;
					pResult =  (VOID*)(pbTmp);
				}
				break;		
			}
			pMbCurr = pMbCurr->pMemBlkNext;
		}
	}

	return pResult;
}

#ifdef RFB_DEBUG
void test(void)
{
	void* p1;
	void* p2;
	void* p3;
	void* p4;
	//Test0(4, 4,3,2,1);
	printf("hello world\n");
	InitHeapPool(INIT_HEAP_DEFAULT); 
	PrintAllMemBlk();

/*
	p1 = Malloc(100);
	memset(p1, 1, 100);
	printf("after malloc p1 size = 100\n");
	PrintAllMemBlk();

	p2 = Malloc(200);
	memset(p2, 2, 200);
	printf("after malloc p2 size = 200\n");
	PrintAllMemBlk();

	p3 = Malloc(300);
	memset(p3, 3, 300);
	printf("after malloc p3 size = 300\n");
	PrintAllMemBlk();
	
	Free(p3);
	printf("after free p3\n");
	PrintAllMemBlk();

	p3 = Malloc(200);
	memset(p3, 4, 200);
	printf("after malloc p3 size = 200\n");
	PrintAllMemBlk();	
	
	Free(p2);
	printf(" free p2\n");
	PrintAllMemBlk();		

	Free(p1);
	printf(" free p1\n");
	PrintAllMemBlk();	
	
	Free(p3);
	printf(" free p3-\n");
	PrintAllMemBlk();	
	*/

	p1 = Malloc(100);
	memset(p1, 5, 100);
	printf("after malloc p1 size = 100\n");
	PrintAllMemBlk();	

	p2 = Malloc(50);
	memset(p2, 6, 50);
	printf("after malloc p2 size = 200\n");
	PrintAllMemBlk();
	
	p3 = Malloc(300);
	memset(p3, 7, 300);
	printf("after remalloc p3 size = 300\n");
	PrintAllMemBlk();

	p4 = Malloc(20);
	memset(p4, 8, 20);
	printf("after malloc p4 size = 20\n");
	PrintAllMemBlk();

	Free(p2);
	printf("after free p2\n");
	PrintAllMemBlk();
	
	p2 = Malloc(100);
	memset(p2, 9, 100);
	printf("after remalloc p2 size = 100\n");
	PrintAllMemBlk();

	Free(p4);
	printf("after free p4\n");
	PrintAllMemBlk();

	HeapCleanUp();
	printf("clean up\n");
	PrintAllMemBlk();
/*
	p1 = Malloc(50);
	memset(p1, 7, 50);
	printf("after remalloc p1 sizeof p1 = 50\n");
	PrintAllMemBlk();	

	Free(p2);
	printf("after free p2\n");
	PrintAllMemBlk();

	p2 = Malloc(100);
	memset(p2, 8, 100);
	printf("after remalloc p2 sizeof p1 = 100\n");
	PrintAllMemBlk();
		
	HeapCleanUp();
	printf("clean up\n");
	PrintAllMemBlk();

	p4 = Malloc(20);
	memset(p4, 0, 20);
	printf("after malloc p4 size = 20\n");
	PrintAllMemBlk();

	p4 = Malloc(200);
	memset(p4, 0, 200);
	printf("after reremalloc p4 size = 200\n");
	PrintAllMemBlk();
	
	HeapCleanUp();
	printf("clean up\n");
	PrintAllMemBlk();
*/
}
#endif

