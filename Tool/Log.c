#include <stdarg.h>
#include <stdio.h>
#include "Type.h"

#include <io.h>

VOID Log(CHAR* pFormat, ...)
{
	FILE* pFile = NULL;
	va_list vl;
	CHAR czTmpLog[512];

	INT iRet;

/*
	if(!access("./log", 0))
	{
		//����log�ļ���
	}else
	{
		//������log�ļ��У����´���
		iRet = CreateDirectory("./log", 0);
		if(iRet)
		{
			
		}else{
			printf("create directory faild...\n");
			return;
		}
	}
*/

	pFile = fopen("./gui.log", "at");
	if(pFile == NULL)
	{
		printf("can't open file\n");
		return ;
		//exit(1);
	}
	
	va_start(vl, pFormat);
	vsprintf(czTmpLog, pFormat, vl);
	fprintf(pFile, czTmpLog);
	va_end(vl);
	
	fclose(pFile);
}

