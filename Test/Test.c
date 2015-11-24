#include "Test.h"


void Test1(void)
{
    UCHAR uczTestBuf[16];
    CHAR* pStr="hello world\n";
    INT i;

    MemSet(uczTestBuf, 0xFF, sizeof(uczTestBuf));
    Log("test buf:\n");
    for(i = 0; i < sizeof(uczTestBuf); i++)
    {
        Log("%02x ", uczTestBuf[i]);
    }
    Log("\n");

    MemCpy(uczTestBuf, pStr, 13);
    Log("test buf[%s]\n", uczTestBuf);

    if(MemCmp(uczTestBuf, pStr, 12))
    {
        Log("compare faild!\n");
    }else
    {
        Log("compare success\n");
    }
    
    printf("hello world\n");

    Log("hello world\n");
}

void Test2(void)
{
    InitHeapPool(INIT_HEAP_DEFAULT);

    UCHAR* pTest1;
    UCHAR* pTest2;
    UCHAR* pTest3;
    UCHAR* pTest4;
    int i;

    pTest1 = (UCHAR*)Malloc(128);
    pTest2 = (UCHAR*)Malloc(32);
    pTest3 = (UCHAR*)Malloc(64);
    pTest4 = (UCHAR*)Malloc(16);
    
    MemSet(pTest1, 0x11, 128);
    MemSet(pTest2, 0x22, 32);
    MemSet(pTest3, 0x33, 64);
    MemSet(pTest4, 0x44, 16);
    
    Log("test1: addr[0x%08x]\n", (UINT)pTest1);
    for(i = 0; i < 128; i++)
    {
        Log("%2x ", pTest1[i]);
    }
    Log("\n");

    Log("test2: addr[0x%08x]\n", (UINT)pTest2);
    for(i = 0; i < 32; i++)
    {
        Log("%2x ", pTest2[i]);
    }
    Log("\n");

    Log("test3: addr[0x%08x]\n", (UINT)pTest3);
    for(i = 0; i < 64; i++)
    {
        Log("%2x ", pTest3[i]);
    }
    Log("\n");

    Log("test4: addr[0x%08x]\n", (UINT)pTest4);
    for(i = 0; i < 16; i++)
    {
        Log("%2x ", pTest4[i]);
    }
    Log("\n");

    Log("################################################\n");
    Log("Free Test3\n");
    Free(pTest3);
    
    Log("test1: addr[0x%08x]\n", (UINT)pTest1);
    for(i = 0; i < 128; i++)
    {
        Log("%2x ", pTest1[i]);
    }
    Log("\n");

    Log("test2: addr[0x%08x]\n", (UINT)pTest2);
    for(i = 0; i < 32; i++)
    {
        Log("%2x ", pTest2[i]);
    }
    Log("\n");

    Log("test4: addr[0x%08x]\n", (UINT)pTest4);
    for(i = 0; i < 16; i++)
    {
        Log("%2x ", pTest4[i]);
    }
    Log("\n");

    Log("################################################\n");
    Log("Clean Heap\n");
    HeapCleanUp();
    
    Log("test1: addr[0x%08x]\n", (UINT)pTest1);
    for(i = 0; i < 128; i++)
    {
        Log("%2x ", pTest1[i]);
    }
    Log("\n");

    Log("test2: addr[0x%08x]\n", (UINT)pTest2);
    for(i = 0; i < 32; i++)
    {
        Log("%2x ", pTest2[i]);
    }
    Log("\n");

    Log("test4: addr[0x%08x]\n", (UINT)pTest4);
    for(i = 0; i < 16; i++)
    {
        Log("%2x ", pTest4[i]);
    }
    Log("\n");

    Free(pTest1);
    Free(pTest2);    
    Free(pTest4);
}

void Test3(void)
{
    UCHAR uczTestBuf[256];
    INT i;
    
    GenCharRnd(uczTestBuf, sizeof(uczTestBuf));
    Log("test buf:\n");
    for(i = 0; i < sizeof(uczTestBuf); i++)
    {
        Log("%02x ", uczTestBuf[i]);
    }
    Log("\r\n");
}

void Test4(void)
{
    int iW;
    int iH;
    CPoint start;
    CPoint end;
    CRect rect;
    
    InitScreen();

    for(iH = 0; iH < SCREEN_HEIGH; iH++)
    {
        for(iW = 0; iW < SCREEN_WIDTH; iW++)
        {
            //if(((iH%2) && !(iW%2))||(!(iH%2) && (iW%2)))
            {
                SetPixel(iW, iH, 0xFFFF0000);
            }
        }
    }

    for(iH = 0; iH < SCREEN_HEIGH/2; iH++)
    {
        for(iW = 0; iW < SCREEN_WIDTH; iW++)
        {
            //if(((iH%2) && !(iW%2))||(!(iH%2) && (iW%2)))
            {
                SetPixel(iW, iH, 0x1400FF00);
            }
        }
    }

    start.m_iX = 5;
    start.m_iY = 5;
    end.m_iX = 100;
    end.m_iY = 5;  
    DrawLine(&start, &end, 0xFF0000FF);

    start.m_iX = 5;
    start.m_iY = 5;
    end.m_iX = 5;
    end.m_iY = 100; 
    DrawLine(&start, &end, 0xFF0000FF);

    start.m_iX = 5;
    start.m_iY = 5;
    end.m_iX = 50;
    end.m_iY = 100; 
    DrawLine(&start, &end, 0xFF0000FF);

    start.m_iX = 5;
    start.m_iY = 5;
    end.m_iX = 30;
    end.m_iY = 100; 
    DrawLine(&start, &end, 0xFF0000FF);


    start.m_iX = 5;
    start.m_iY = 5;
    end.m_iX = 100;
    end.m_iY = 50;  
    DrawLine(&start, &end, 0xFF0000FF);

    start.m_iX = 100;
    start.m_iY = 5;
    end.m_iX = 100;
    end.m_iY = 100;  
    DrawLine(&start, &end, 0xFF0000FF);

    start.m_iX = 5;
    start.m_iY = 100;
    end.m_iX = 100;
    end.m_iY = 100; 
    DrawLine(&start, &end, 0xFF0000FF);

    TextOut(40, 30, "abcde12345#$%^!");

    rect.m_iTop = 35;
    rect.m_iLeft = 150;
    rect.m_iWidth = 50;
    rect.m_iHeigh = 30;
    FillRect(&rect, 0xFFFF00FF);
    DrawRect(&rect, 0xFFFFFFFF);


    rect.m_iTop = 5;
    rect.m_iLeft = 100;
    rect.m_iWidth = 50;
    rect.m_iHeigh = 30;
    DrawRect(&rect, 0xFFFFFFFF);



    rect.m_iTop = 80;
    rect.m_iLeft = 100;
    rect.m_iWidth = 50;
    rect.m_iHeigh = 30;
    DrawRoundRect(&rect, 0xFFFFFFFF);

    rect.m_iTop = 120;
    rect.m_iLeft = 100;
    rect.m_iWidth = 50;
    rect.m_iHeigh = 30;
    FillRoundRect(&rect, 0xFFFFFFFF);

    PrintScreen();
}

INT OnListFlow(PVOID pData)
{
    CHAR* pcData = (CHAR*)pData;
    Log("data[%s]\n", pcData);
}

void Test5(void)
{
    CList list;
    PList pList = NULL;
    CHAR* pc1 = "hello world1";
    CHAR* pc2 = "hello world2";
    CHAR* pc3 = "hello world3";
    CHAR* pc4 = "hello world4";
    CHAR* pc5 = "hello world5";
    
    

    pList = &list;
    InitList(pList);

    Log("start\n");
    PushList(pList, pc1);
    PushList(pList, pc2);
    PushList(pList, pc3);
    PushList(pList, pc4);
    PushList(pList, pc5);
    FlowList(pList, OnListFlow);

    Log("remove pc1\n");
    RemoveListByData(pList, pc1);
    FlowList(pList, OnListFlow);

    Log("remove pc3\n");
    RemoveListByData(pList, pc3);
    FlowList(pList, OnListFlow);

    Log("remove pc5\n");
    RemoveListByData(pList, pc5);
    FlowList(pList, OnListFlow);

    Log("remove pc2\n");
    RemoveListByData(pList, pc2);
    FlowList(pList, OnListFlow);

    Log("remove pc4\n");
    RemoveListByData(pList, pc4);
    FlowList(pList, OnListFlow);

    Log("insert pc1\n");
    InsertList(pList, 0, pc1);
    FlowList(pList, OnListFlow);

    Log("insert pc2\n");
    InsertList(pList, 0, pc2);
    FlowList(pList, OnListFlow);

    Log("insert pc3\n");
    InsertList(pList, 1, pc3);
    FlowList(pList, OnListFlow);

    Log("insert pc4\n");
    InsertList(pList, 2, pc4);
    FlowList(pList, OnListFlow);

    Log("insert pc5\n");
    InsertList(pList, 3, pc5);
    FlowList(pList, OnListFlow);
    
    DeletList(pList);
}

void Test6(void)
{
    char* pTest[20];
    CList list;
    PList pList = NULL;
    int i;
    int iRnd;

    pList = &list;
    for(i = 0; i < 40; i++)
    {
        
    }
}

INT WindowFlow(PWindow pWin)
{
	/*
 //   CRect rect;
    PWindow pWinParent;

    pWinParent = pWin->m_pParent;
    if(pWinParent == NULL)
    {
        CopyRect(&pWin->m_showRect, &pWin->m_rect);
    }
    else
    {
        RectInRect(&pWinParent->m_showRect, &pWin->m_rect, &pWin->m_showRect);
    }
    
    
    FillRect(&pWin->m_showRect, pWin->m_brush.m_color);
*/
	pWin->m_pfPrintWindow(P2H(pWin));
	/*
    Log("left[%d] top[%d] width[%d] heigh[%d] id[%d]\n", \
        pWin->m_showRect.m_iLeft, pWin->m_showRect.m_iTop, pWin->m_showRect.m_iWidth,  pWin->m_showRect.m_iHeigh, pWin->m_iID);
	*/
    return 0;
}
extern VOID WinFlowMain(VOID);

VOID WinOnUsrProc(PWindow pWin, UINT uMsg, PVOID pMsg)
{
	CBrush brush;
	INT iRnd;
	static int i = 1;
	char czTitle[10] = "BTN0";
	
	iRnd = GenUIntRnd(0xFFFFFF);
	iRnd += 0xFF000000;

	brush.m_color = iRnd;

	pWin->m_pFirstSon->m_pfSelWinBrush(P2H(pWin->m_pFirstSon), &brush, NULL);

	czTitle[3] = '0'+i;
	i++;
	PButton pBtn = (PButton)pWin->m_pLastSon;
	pBtn->m_pfSetTitle(P2H(pBtn), czTitle);
	
	
	Log("button message %d\r\n", pWin->m_iID);
}

/*
void Test7(void)
{   //window test...
    PWindow pWinTmp = NULL;
    PWindow pWinParent = NULL;
    int iRnd;
    int i;
	int iParent;
    CRect rect;

    InitHeapPool(INIT_HEAP_DEFAULT);

    InitGUI();
    Log("start...\n");
    pWinParent = pWinRoot;
    for(i = 0; i < 18; i++)
    {
        pWinTmp = CreateWindow(0);

        if(pWinTmp == NULL)
        {
            break;
        }

        iRnd = GenUIntRnd(0xFFFFFF);
        iRnd += 0xFF000000;
        SetWinBKColor(pWinTmp, iRnd);

        rect.m_iTop = GenIntRnd(1, pWinParent->m_rect.m_iHeigh-1);        
        rect.m_iLeft = GenIntRnd(1, pWinParent->m_rect.m_iWidth-1);        
        rect.m_iHeigh = GenIntRnd(1, pWinParent->m_rect.m_iHeigh-rect.m_iTop);
        rect.m_iWidth = GenIntRnd(1, pWinParent->m_rect.m_iWidth-rect.m_iLeft);

        rect.m_iTop += pWinParent->m_rect.m_iTop;
        rect.m_iLeft += pWinParent->m_rect.m_iLeft;

        SetWinRect(pWinTmp, &rect);
        Log("left[%d] top[%d] width[%d] heigh[%d] id[%d]\n", \
             pWinTmp->m_rect.m_iLeft, pWinTmp->m_rect.m_iTop, pWinTmp->m_rect.m_iWidth,  pWinTmp->m_rect.m_iHeigh, pWinTmp->m_iID);
        

        iRnd = GenUIntRnd(pWinTmp->m_iID);
        //pWinParent = FindWindowByID(iRnd);
        
        InitWindow(P2H(pWinTmp), P2H(pWinParent), 0, 0);
        //AddSonWindow(pWinParent, pWinTmp);
        /*
        iRnd = GenUIntRnd(5);
        
        switch(iRnd)
        {
            case 1:
                
                pWinParent = pWinTmp;
                break;
                
            default:
                break;
        }
        //
        
    }

    for(i = 0; i < 32; i++)
    {
        pWinTmp = CreateWindow(0);

        if(pWinTmp == NULL)
        {
            break;
        }

        iRnd = GenUIntRnd(0xFFFFFF);
        iRnd += 0xFF000000;
        SetWinBKColor(pWinTmp, iRnd);

        rect.m_iTop = GenIntRnd(1, pWinParent->m_rect.m_iHeigh-1);        
        rect.m_iLeft = GenIntRnd(1, pWinParent->m_rect.m_iWidth-1);        
        rect.m_iHeigh = GenIntRnd(1, pWinParent->m_rect.m_iHeigh-rect.m_iTop);
        rect.m_iWidth = GenIntRnd(1, pWinParent->m_rect.m_iWidth-rect.m_iLeft);

        rect.m_iTop += pWinParent->m_rect.m_iTop;
        rect.m_iLeft += pWinParent->m_rect.m_iLeft;

        SetWinRect(pWinTmp, &rect);
        Log("left[%d] top[%d] width[%d] heigh[%d] id[%d]\n", \
             pWinTmp->m_rect.m_iLeft, pWinTmp->m_rect.m_iTop, pWinTmp->m_rect.m_iWidth,  pWinTmp->m_rect.m_iHeigh, pWinTmp->m_iID);
        

        iRnd = GenUIntRnd(pWinTmp->m_iID);
        pWinParent = FindWindowByID(/*iRnd//18);
        
        InitWindow(P2H(pWinTmp), P2H(pWinParent), 0, 0);
        //AddSonWindow(pWinParent, pWinTmp);
        /*
        iRnd = GenUIntRnd(5);
        
        switch(iRnd)
        {
            case 1:
                
                pWinParent = pWinTmp;
                break;
                
            default:
                break;
        }
        //
        
    }
	
    Log("window flow...\n");
    FlowWindow0(pWinRoot, WindowFlow);

    //pWinTmp = FindWindowByID(25);
    //Log("find...");
    //WindowFlow(pWinTmp);

    PrintScreen();

#if 0
    pWinTmp = FindWindowByID(2);

    if(pWinTmp == NULL)
    {
        Log("NULL pointer\r\n");
    }

    Log("OK\r\n");
    
    ReorderWindow(pWinTmp);
    FlowWindow0(pWinRoot, WindowFlow);
#endif


    while(TRUE)
    {
        int x;
        int y;
        int iRet;
        PPoint pPoint;
        scanf("%d %d", &x, &y);
        pPoint = (PPoint)Malloc(sizeof(CPoint));
        pPoint->m_iX = x;
        pPoint->m_iY = y;

        iRet = pWinRoot->m_pfPostMessage(P2H(pWinRoot), WIN_MSG_ID_CLICK_SCREEN_DOWN, 0, pPoint);
        Log("iRet[%d]\r\n", iRet);
        WinFlowMain();

        FlowWindow0(pWinRoot, WindowFlow);
        PrintScreen();
    }
}
*/
void TestBtn(void)
{
	PWindow pWinSon0 = NULL;
	PButton pBtnSon0 = NULL;
	PWindow pWinParent = NULL;
	int iRnd;
	int i;
	int iParent;
	CRect rect;
	CFont font;
	INT iID;

	iID = 1;
	
	InitHeapPool(INIT_HEAP_DEFAULT);

	InitGUI();
	Log("start...\n");

	pWinParent = CreateWindowE(0, pWinRoot, iID++);

	rect.m_iLeft = 10;
	rect.m_iTop = 10;
	rect.m_iHeigh = 100;
	rect.m_iWidth = 200;
	
	pWinParent->m_pfSelWinRect(P2H(pWinParent), &rect, NULL);
	SetWinBKColor(pWinParent, 0xFF000000);

	pBtnSon0 = CreateButton(pWinParent, iID++, "btn1", WIN_MSG_BUTTON, WinOnUsrProc);
	rect.m_iLeft = 80;
	rect.m_iTop = 10;
	rect.m_iHeigh = 50;
	rect.m_iWidth = 50;
	pBtnSon0->m_pfSelWinRect(P2H(pBtnSon0), &rect, NULL);
	SetWinBKColor(&pBtnSon0->m_baseWin, 0xFF00FF00);
	font.m_color = 0xFF000000;

	pBtnSon0->m_pfSelWinFont(P2H(pBtnSon0), &font, NULL);

	pWinSon0 = CreateWindowE(0, pWinParent, iID++);
	rect.m_iLeft = 50;
	rect.m_iTop = 10;
	rect.m_iHeigh = 50;
	rect.m_iWidth = 50;
	pWinSon0->m_pfSelWinRect(P2H(pWinSon0), &rect, NULL);
	SetWinBKColor(pWinSon0, 0xFFFF0000);



	Log("window flow...\n");
	FlowWindow0(pWinRoot, WindowFlow);

	//pWinTmp = FindWindowByID(25);
	//Log("find...");
	//WindowFlow(pWinTmp);

	PrintScreen();

#if 0
	pWinTmp = FindWindowByID(2);

	if(pWinTmp == NULL)
	{
		Log("NULL pointer\r\n");
	}

	Log("OK\r\n");
	
	ReorderWindow(pWinTmp);
	FlowWindow0(pWinRoot, WindowFlow);
#endif


	while(TRUE)
	{
		int x;
		int y;
		int iRet;
		PPoint pPoint;
		scanf("%d %d", &x, &y);
		pPoint = (PPoint)Malloc(sizeof(CPoint));
		pPoint->m_iX = x;
		pPoint->m_iY = y;

		iRet = pWinRoot->m_pfPostMessage(P2H(pWinRoot), WIN_MSG_ID_CLICK_SCREEN_DOWN, 0, pPoint);
		Log("iRet[%d]\r\n", iRet);
		WinFlowMain();

		FlowWindow0(pWinRoot, WindowFlow);
		PrintScreen();
	}

}

void TestString(void)
{
	PString pString;
	int i;
	char czTest[1024+5];

	MemSet(czTest, 0, sizeof(czTest));
	MemSet(czTest, '1', 1023);

	InitHeapPool(INIT_HEAP_DEFAULT);

	pString = CreateStringE("hello world", 512);
	
	Log("value [%s] len[%d] size[%d]\r\n", pString->m_pcVal, pString->m_iValLen, pString->m_iSize);

	pString->m_pfInsert(P2H(pString), 0, 'a');
	Log("insert 'a' to 0\r\n");
	Log("value [%s] len[%d] size[%d]\r\n", pString->m_pcVal, pString->m_iValLen, pString->m_iSize);

	pString->m_pfInsert(P2H(pString), 1, 'b');
	Log("insert 'b' to 1\r\n");
	Log("value [%s] len[%d] size[%d]\r\n", pString->m_pcVal, pString->m_iValLen, pString->m_iSize);

	pString->m_pfInsert(P2H(pString), 0, 'c');
	Log("insert 'c' to 0\r\n");
	Log("value [%s] len[%d] size[%d]\r\n", pString->m_pcVal, pString->m_iValLen, pString->m_iSize);

	pString->m_pfAppend(P2H(pString), 'a');
	Log("append 'a'\r\n");
	Log("value [%s] len[%d] size[%d]\r\n", pString->m_pcVal, pString->m_iValLen, pString->m_iSize);

	pString->m_pfAppend(P2H(pString), 'b');
	Log("append 'b'\r\n");
	Log("value [%s] len[%d] size[%d]\r\n", pString->m_pcVal, pString->m_iValLen, pString->m_iSize);
	
	pString->m_pfSetText(P2H(pString), "you are big pig");
	Log("reset text\r\n");
	Log("value [%s] len[%d] size[%d]\r\n", pString->m_pcVal, pString->m_iValLen, pString->m_iSize);
		

	pString->m_pfAppend(P2H(pString), 'b');
	Log("append 'b'\r\n");
	Log("value [%s] len[%d] size[%d]\r\n", pString->m_pcVal, pString->m_iValLen, pString->m_iSize);

	pString->m_pfRemove(P2H(pString), 4);
	Log("remove 4\r\n");
	Log("value [%s] len[%d] size[%d]\r\n", pString->m_pcVal, pString->m_iValLen, pString->m_iSize);

	pString->m_pfRemove(P2H(pString), pString->m_iValLen-1);
	Log("remove iValLen\r\n");
	Log("value [%s] len[%d] size[%d]\r\n", pString->m_pcVal, pString->m_iValLen, pString->m_iSize);

	pString->m_pfRemoveFromCnt(P2H(pString), 0, pString->m_iValLen);
	Log("remove 5\r\n");
	Log("value [%s] len[%d] size[%d]\r\n", pString->m_pcVal, pString->m_iValLen, pString->m_iSize);

	pString->m_pfInsertString(P2H(pString), 5, "hello world");
	Log("insert string 5\r\n");
	Log("value [%s] len[%d] size[%d]\r\n", pString->m_pcVal, pString->m_iValLen, pString->m_iSize);

/*
	for(i = 0; i < 1024; i++)
	{
		pString->m_pfAppend(P2H(pString), 'b');
	}
*/


	pString->m_pfInsertString(P2H(pString), 5, czTest);

	printf("value [%s] len[%d] size[%d]\r\n", pString->m_pcVal, pString->m_iValLen, pString->m_iSize);



/*
	Log("**********************\r\n");


	pString->m_pfSetText(P2H(pString), czTest);
	Log("reset text\r\n");
	Log("value [%s] len[%d] size[%d]\r\n", pString->m_pcVal, pString->m_iValLen, pString->m_iSize);

	pString->m_pfInsert(P2H(pString), 0, 'a');
	Log("insert 'a' to 0\r\n");
	Log("value [%s] len[%d] size[%d]\r\n", pString->m_pcVal, pString->m_iValLen, pString->m_iSize);

	pString->m_pfInsert(P2H(pString), 1, 'b');
	Log("insert 'b' to 1\r\n");
	Log("value [%s] len[%d] size[%d]\r\n", pString->m_pcVal, pString->m_iValLen, pString->m_iSize);

	pString->m_pfInsert(P2H(pString), 0, 'c');
	Log("insert 'c' to 0\r\n");
	Log("value [%s] len[%d] size[%d]\r\n", pString->m_pcVal, pString->m_iValLen, pString->m_iSize);

	pString->m_pfAppend(P2H(pString), 'a');
	Log("append 'a'\r\n");
	Log("value [%s] len[%d] size[%d]\r\n", pString->m_pcVal, pString->m_iValLen, pString->m_iSize);

	pString->m_pfAppend(P2H(pString), 'b');
	Log("append 'b'\r\n");
	Log("value [%s] len[%d] size[%d]\r\n", pString->m_pcVal, pString->m_iValLen, pString->m_iSize);
	
	pString->m_pfSetText(P2H(pString), "you are big pig");
	Log("reset text\r\n");
	Log("value [%s] len[%d] size[%d]\r\n", pString->m_pcVal, pString->m_iValLen, pString->m_iSize);
		

	pString->m_pfAppend(P2H(pString), 'b');
	Log("append 'b'\r\n");
	Log("value [%s] len[%d] size[%d]\r\n", pString->m_pcVal, pString->m_iValLen, pString->m_iSize);
*/
		
	DeleteString(pString);
}

