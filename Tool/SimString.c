#include "SimString.h"
#include "Tool.h"


#define STRING_BLOCK_SIZE 1024


STATIC INT SetText(HANDLE handle, CHAR* pVal)
{
	INT iLen;
	PString pString = (PString)H2P(handle);

	if(pString == NULL)
	{
		return -1;
	}

	iLen = Strlen(pVal);
	if(iLen < pString->m_iSize)
	{//string value length less the size
		MemSet(pString->m_pcVal, 0, pString->m_iSize);
		MemCpy(pString->m_pcVal, pVal, iLen);

		pString->m_iValLen = iLen;
	}else
	{//string value length bigger the size
		INT iSize;

		iSize = (iLen/STRING_BLOCK_SIZE)+1;
		iSize *= STRING_BLOCK_SIZE;

		//free the origianl buffer
		Free(pString->m_pcVal);

		//malloc the new buffer.
		pString->m_pcVal = (CHAR*)Malloc(iSize);
		if(pString->m_pcVal == NULL)
		{
			return -1;
		}

		//reset the param value.
		pString->m_iSize = iSize;
		pString->m_iValLen = iLen;
		MemSet(pString->m_pcVal, 0, iSize);
		MemCpy(pString->m_pcVal, pVal, iLen);
	}

	return iLen;
}

STATIC INT Append(HANDLE handle, CHAR c)
{
	PString pString = (PString)H2P(handle);
	INT iLen;

	if(pString == NULL)
	{
		return -1;
	}

	iLen = pString->m_iValLen;
	if(pString->m_iValLen < pString->m_iSize-5)
	{//length after adding is less than the size
		pString->m_pcVal[iLen] = c;
		pString->m_iValLen = iLen+1;
	}else
	{
		CHAR* pBuffer = NULL;
		INT iSize;

		iSize = (iLen+6)/STRING_BLOCK_SIZE+1;
		iSize *= STRING_BLOCK_SIZE;

		//malloc the temp buffer.
		pBuffer = (CHAR*)Malloc(iSize);
		if(pBuffer == NULL)
		{
			return -1;
		}

		//copy the value to the temp buffer.
		MemSet(pBuffer, 0, iSize);
		MemCpy(pBuffer, pString->m_pcVal, iLen);
		pBuffer[iLen] = c;

		//free the original buffer.
		Free(pString->m_pcVal);

		//reset the param value.
		pString->m_iSize = iSize;
		pString->m_iValLen = iLen+1;
		pString->m_pcVal = pBuffer;

		return (iLen+1);
	}
}

STATIC INT GetChar(HANDLE handle, INT iIndex)
{
	PString pString = NULL;

	pString = (PString)H2P(handle);

	if(pString == NULL)
	{
		return 0;
	}
	
	if(iIndex < pString->m_iValLen && iIndex >= 0)
	{
		return pString->m_pcVal[iIndex];
	}

	return 0;
}

STATIC INT Insert(HANDLE handle, INT iIndex, CHAR c)
{
	INT iLen;
	INT i;
	PString pString = (PString)H2P(handle);

	if(pString == NULL)
	{
		return -1;
	}

	iLen = pString->m_iValLen;

	if(iIndex < 0 || iIndex >= iLen)
	{
		return -1;
	}
	
	if(pString->m_iValLen < pString->m_iSize-5)
	{//length after adding is less than the size
		iLen++;
		pString->m_iValLen = iLen;

		for(i = iLen; i > iIndex; i--)
		{
			pString->m_pcVal[i] = pString->m_pcVal[i-1];
		}
		pString->m_pcVal[i] = c;
		
	}else
	{
		CHAR* pBuffer = NULL;
		INT iSize;

		iSize = (iLen+6)/STRING_BLOCK_SIZE+1;
		iSize *= STRING_BLOCK_SIZE;

		//malloc the temp buffer.
		pBuffer = (CHAR*)Malloc(iSize);
		if(pBuffer == NULL)
		{
			return -1;
		}

		//copy the value to the temp buffer.
		MemSet(pBuffer, 0, iSize);
		MemCpy(pBuffer, pString->m_pcVal, iIndex);
		MemCpy(pBuffer+iIndex+1, pString->m_pcVal+iIndex, iLen-iIndex);
		pBuffer[iIndex] = c;
		iLen++;

		//free the original buffer.
		Free(pString->m_pcVal);
		
		//reset the param value.
		pString->m_iSize = iSize;
		pString->m_iValLen = iLen;
		pString->m_pcVal = pBuffer;

		return iLen;
	}
}

STATIC INT Remove(HANDLE handle, INT iIndex)
{
	PString pString = (PString)H2P(handle);
	INT i;

	if(pString == NULL)
	{
		return -1;
	}

	if(iIndex < 0 || iIndex >= pString->m_iValLen)
	{
		return -1;
	}

	for(i = iIndex; i < pString->m_iValLen; i++)
	{
		pString->m_pcVal[i] = pString->m_pcVal[i+1];
	}

	pString->m_pcVal[i] = 0;
	pString->m_iValLen--;
	
	return pString->m_iValLen;
}

STATIC INT InsertString(HANDLE handle, INT iIndex, CHAR* pc)
{
	PString pString = (PString)H2P(handle);
	INT i;
	INT iLen;

	if(pString == NULL)
	{
		return -1;
	}

	if(iIndex < 0 || iIndex >= pString->m_iValLen)
	{
		return -1;
	}

	iLen = Strlen(pc);
	
	if((iLen+pString->m_iValLen) < (pString->m_iSize-5))
	{
		for(i = pString->m_iValLen+iLen-1; i > iIndex; i--)
		{
			pString->m_pcVal[i] = pString->m_pcVal[i-iLen];
		}
		MemCpy(pString->m_pcVal+iIndex, pc, Strlen(pc));

		pString->m_iValLen += iLen;
	}else
	{
		INT iSize;
		CHAR* pBuffer = NULL;
		
		iSize = iLen + pString->m_iValLen;
		iSize = iSize/STRING_BLOCK_SIZE+1;
		iSize *= STRING_BLOCK_SIZE;

		pBuffer = (CHAR*)Malloc(iSize);
		if(pBuffer == NULL)
		{
			return -1;
		}

		MemSet(pBuffer, 0, sizeof(iSize));
		MemCpy(pBuffer, pString->m_pcVal, iIndex);
		MemCpy(pBuffer+iIndex, pc, iLen);
		MemCpy(pBuffer+iIndex+iLen, pString->m_pcVal+iIndex, pString->m_iValLen-iIndex);

		Free(pString->m_pcVal);
		
		pString->m_iSize = iSize;
		pString->m_iValLen = pString->m_iValLen+iLen;
		pString->m_pcVal = pBuffer;
	}

	return 0;
}

STATIC INT RemoveFromCnt(HANDLE handle, INT iIndex, INT iCnt)
{
	PString pString = (PString)H2P(handle);
	INT i;

	if(pString == NULL)
	{
		return -1;
	}

	if(iIndex < 0 || iIndex >= pString->m_iValLen)
	{
		return -1;
	}

	for(i = iIndex; i < pString->m_iValLen; i++)
	{
		if((i+iCnt) >= pString->m_iValLen)
		{
			break;
		}
		
		pString->m_pcVal[i] = pString->m_pcVal[i+iCnt];
	}

	MemSet(pString->m_pcVal+(pString->m_iValLen-iCnt), 0, iCnt);
	pString->m_iValLen -= iCnt;
	
	return pString->m_iValLen;
}

STATIC VOID CleanString(HANDLE handle)
{
	PString pString = (PString)H2P(handle);
	INT i;

	if(pString == NULL)
	{
		return ;
	}	

	MemSet(pString->m_pcVal, 0, pString->m_iSize);
	Free(pString->m_pcVal);
	pString->m_iSize = 0;
	pString->m_iValLen = 0;
}

INT RemoveLast(HANDLE handle)
{
	PString pString = (PString)H2P(handle);
	INT i;

	if(pString == NULL)
	{
		return ;
	}	

	if(pString->m_iValLen)
	{
		pString->m_pcVal[pString->m_iValLen-1] = 0;
		pString->m_iValLen--;
	}
	return pString->m_iValLen;
}


INT InitStringE(PString pString, CHAR* pVal, INT iSize)
{
	if(pString)
	{
		INT iLen;
		INT i;
		
		MemSet(pString, 0, sizeof(CString));
		
		iLen = Strlen(pVal);
		if(iSize < iLen)
		{
			iSize = iLen;
		}

		i = iSize / STRING_BLOCK_SIZE + 1;
		iSize = i*STRING_BLOCK_SIZE;

		pString->m_pcVal = (CHAR*)Malloc(iSize);
		if(pString->m_pcVal == NULL)
		{//string buffer malloc faild.
			Free(pString);
			return -1;
		}

		MemSet(pString->m_pcVal, 0, iSize);
		MemCpy(pString->m_pcVal, pVal, iLen);
		//set the string buffer param.
		pString->m_iSize = iSize;
		pString->m_iValLen = iLen;

		//操作函数初始化
		pString->m_pfAppend = Append;
		pString->m_pfGetChar = GetChar;
		pString->m_pfInsert = Insert;
		pString->m_pfSetText = SetText;
		pString->m_pfRemove = Remove;

		pString->m_pfRemoveFromCnt = RemoveFromCnt;
		pString->m_pfInsertString = InsertString;
		pString->m_pfCleanString = CleanString;
		pString->m_pfRemoveLast = RemoveLast;

		return pString->m_iSize;
	}else
	{
		return -1;
	}
	return 0;
}


PString CreateStringE(CHAR* pVal, INT iSize)
{
	PString pString = NULL;

	pString = (PString)Malloc(sizeof(CString));
	if(pString)
	{
#if 0
		INT iLen;
		INT i;
		
		MemSet(pString, 0, sizeof(CString));
		
		iLen = Strlen(pVal);
		if(iSize < iLen)
		{
			iSize = iLen;
		}

		i = iSize / STRING_BLOCK_SIZE + 1;
		iSize = i*STRING_BLOCK_SIZE;

		pString->m_pcVal = (CHAR*)Malloc(iSize);
		if(pString->m_pcVal == NULL)
		{//string buffer malloc faild.
			Free(pString);
			return NULL;
		}

		MemSet(pString->m_pcVal, 0, iSize);
		MemCpy(pString->m_pcVal, pVal, iLen);
		//set the string buffer param.
		pString->m_iSize = iSize;
		pString->m_iValLen = iLen;

		//操作函数初始化
		pString->m_pfAppend = Append;
		pString->m_pfGetChar = GetChar;
		pString->m_pfInsert = Insert;
		pString->m_pfSetText = SetText;
#endif
		InitStringE(pString, pVal, iSize);
	}
	return pString;
}


VOID DeleteString(PString pString)
{
	if(pString)
	{
		if(pString->m_pcVal)
		{//free string value buffer.
			Free(pString->m_pcVal);
		}

		//free string class buffer.
		Free(pString);
	}
}


