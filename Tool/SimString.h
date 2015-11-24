#ifndef __SIMPLE_STRING_H__
#define __SIMPLE_STRING_H__
#include "Type.h"

typedef INT (*PFSetText)(HANDLE handle, CHAR* pVal);
typedef INT (*PFAppend)(HANDLE handle, CHAR c);
typedef INT (*PFGetChar) (HANDLE handle, INT iIndex);
typedef INT (*PFInsert)(HANDLE handle, INT iIndex, CHAR c);
typedef INT (*PFRemove)(HANDLE handle, INT iIndex);
typedef INT (*PFRemoveLast)(HANDLE handle);

typedef INT (*PFInsertString)(HANDLE handle, INT iIndex, CHAR* pc);
typedef INT (*PFRemoveFromTo)(HANDLE handle, INT iIndex, INT iCnt);

typedef VOID (*PFCleanString)(HANDLE handle);


typedef struct _String
{
	CHAR* m_pcVal;
	INT   m_iValLen;
	INT   m_iSize;

	PFSetText m_pfSetText;
	PFAppend  m_pfAppend;
	PFGetChar m_pfGetChar;
	PFInsert  m_pfInsert;
	PFRemove  m_pfRemove;

	PFInsertString m_pfInsertString;
	PFRemoveFromTo m_pfRemoveFromCnt;
	PFCleanString  m_pfCleanString;
	PFRemoveLast   m_pfRemoveLast;
}CString, *PString;

INT InitStringE(PString pString, CHAR* pVal, INT iSize);
PString CreateStringE(CHAR* pVal, INT iSize);
VOID DeleteString(PString pString);

#endif

