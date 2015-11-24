#include "LoadWinRes.h"

#define WIN_RES_FLAG_WINDOW_START "WINSTART"
#define WIN_RES_FLAG_WINDOW_END   "WINEND"
#define WIN_RES_FLAG_ATTR_START   "ATTRSTART"
#define WIN_RES_FLAG_ATTR_END     "ATTREND"
#define WIN_RES_ID_FLAG           "ID:"
#define WIN_RES_PID_FLAG          "PID:"
#define WIN_RES_TYPE_FLAG         "TYPE"
#define WIN_RES_FLAG_FLAG         "FLAG"
#define WIN_RES_BKCLR_FLAG        "BKCLR"
#define WIN_RES_RECT_FLAG         "RECT:"
#define WIN_RES_FONT_FLAG         "FONT:"
#define WIN_RES_BRUSH_FLAG        "BRUSH:"
/*
对窗口资源树定义如下

WINSTART

	ATTRSTART
		ID:
		PID:
		TYPE:
		FLAG:
		RECT:
		FONT:
		BRUSH:
	ATTREND

	WINSTART
	WINEND

	WINSTART
		WINSTART
		WINEND
		
		...
	WINEND

	...
WINEND
*/

BOOL CharInStr(CHAR c, CHAR czStr[], INT iStrLen)
{
	INT i;
	for(i = 0; i < iStrLen; i++)
	{
		if(czStr[i] == c)
		{
			return TRUE;
		}
	}
	return FALSE;
}

CHAR GetNextAvaliChar(FILE* pFile, CHAR czUnavail[], INT iUnavailLen)
{
	CHAR c;
	
	while(TRUE)
	{	
		c = fgetc(pFile);

		if(c == EOF)
		{
			break;
		}
		
		if(!CharInStr(c, czUnavail, iUnavailLen))
		{
			break;
		}
	}
	return c;
}

INT GetStringUntil(FILE* pFile, CHAR czGet[], CHAR czUntil[], INT iUntilLen)
{
	INT i;
	CHAR c;

	i = 0;
	while(TRUE)
	{
		c = fgetc(pFile);

		if(c == EOF)
		{
			break;
		}

		if(CharInStr(c, czUntil, iUntilLen))
		{
			break;
		}
		
		czGet[i++] = c;
	}

	czGet[i] = 0;
	return i;
}

#define PARSE_STATE_START  0
#define PARSE_STATE_STRING 1
#define PARSE_STATE_LABEL  3
#define PARSE_STARE_END    2

#define PARSE_STATE_WINSTART 4
#define PARSE_STATE_WINEND   5
#define PARSE_STATE_ATTR_ID  6
#define PARSE_STATE_ATTR_PID 7
#define PARSE_STATE_ATTR_TYPE 8
#define PARSE_STATE_ATTR_FLAG 9
#define PARSE_STATE_ATTR_RECT 10
#define PARSE_STATE_ATTR_FONT 11
#define PARSE_STATE_ATTR_BRUSH 12

INT ParseResToWin(CHAR* pResFile)
{
	FILE* pFile;
	INT  iCurState;
	INT  iCurStrLen;
	CHAR czCurStr[256];

	CList list;
	PList pList;
	PWindow pWin;
	
	
	pFile = fopen(pResFile, "w+");
	if(pFile == NULL)
	{
		return -1;
	}

	iCurState = PARSE_STATE_START;
	iCurStrLen = 0;
	MemSet(czCurStr, 0, sizeof(czCurStr));

	InitList(&list);
	pList = &list;
	
	while(TRUE)
	{
		switch(iCurState)
		{
			case PARSE_STATE_START:
				czCurStr[iCurStrLen] = GetNextAvaliChar(pFile, "\n	 ", 3);
				iCurStrLen++;
				iCurStrLen += GetStringUntil(pFile, czCurStr+1, "\n	 ", 3);

				if(MemCmp(czCurStr, WIN_RES_FLAG_WINDOW_START, iCurStrLen) == 0)
				{
					iCurState = PARSE_STATE_WINSTART;
				}

				if(MemCmp(czCurStr, WIN_RES_FLAG_WINDOW_END, iCurStrLen) == 0)
				{
					iCurState = PARSE_STATE_WINEND;
				}

				iCurStrLen = 0;
			break;

			case PARSE_STATE_WINSTART:
				pWin = (PWindow)Malloc(sizeof(CWindow));
				PushList(pList, pWin);				
				iCurState = PARSE_STATE_START;
			break;

			case PARSE_STATE_WINEND:
				
				iCurState = PARSE_STATE_START;
			break;

			case 

			case PARSE_STATE_ATTR_ID:

			break;

			case PARSE_STATE_STRING:

			break;

			case PARSE_STATE_LABEL:

			break;

			case PARSE_STARE_END:

			break;

			default:

			break;
		}
	}

	fclose(pFile);
	return 0;
}

INT LoadWinSys(CHAR* pResFile)
{
	return 0;
}


