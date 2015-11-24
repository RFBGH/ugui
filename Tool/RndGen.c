#include "RndGen.h"

STATIC INT iRndRoot = 0;
STATIC INT iA = 3;
STATIC INT iB = 17;
STATIC INT iC = 13;
STATIC INT iM = 100000000;
//STATIC INT iD = 19;

UINT GenUIntRnd(INT iMax)
{
    INT i;
    INT iRet;

    if(iMax == 0)
    {
        return 0;
    }

    iRet = iRndRoot;
    for(i = 0; i < 100; i++)
    {
        iRet = iA*(iRet*iRet)-iB*iRet+iC;
        //iRet = iC*(iRet*iRet*iRet)-iB*(iRet*iRet)+iA*iRet-iD;
    }
    
    if(iRet < 0)
    {
        iRet = -iRet;
    }
    iRndRoot = iRet;

    iRndRoot %= iM;
    
    return (iRet%iMax);
}

VOID GenCharRnd(UCHAR* pRndBuf, INT iLen)
{
    INT i;

    for(i = 0; i < iLen; i++)
    {
        pRndBuf[i] = GenUIntRnd(255);
    }
}

INT GenIntRnd(INT iMin, INT iMax)
{
    if(iMax < iMin)
    {
        int iTmp = iMin;
        iMin = iMax;
        iMax = iTmp;
    }
    UINT u = GenUIntRnd(iMax-iMin);

    return (iMin+u);
}


