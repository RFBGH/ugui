#include "Color.h"

//在两种颜色中，选择渐变值
RGBA FilterColor(RGBA start, RGBA end, INT iFilter)
{
    UINT uTmp;
    UINT uRet;
    INT i;
    if(iFilter > MAX_COLOR_FILTER)
    {
        iFilter = MAX_COLOR_FILTER;
    }

    if(iFilter < 0)
    {
        iFilter = 0;
    }

    uRet = 0;
    for(i = 0; i < 4; i++)
    {
        UINT uTmp1 = (start>>(i*8))&0xFF;
        UINT uTmp2 = (end>>(i*8))&0xFF;

        if(uTmp1 < uTmp2)
        {
            uTmp = uTmp2;
            uTmp2 = uTmp1;
            uTmp1 = uTmp;
        }
        uTmp1 = uTmp2+(uTmp1-uTmp2)*iFilter/MAX_COLOR_FILTER;
        uRet |= (uTmp1&0xFF)<<(i*8);
    }
    return uRet;
}

