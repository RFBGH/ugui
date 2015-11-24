#ifndef __RND_GEN_H__
#define __RND_GEN_H__

#include "Type.h"

VOID GenCharRnd(UCHAR* pRndBuf, INT iLen);

UINT GenUIntRnd(INT iMax);

INT GenIntRnd(INT iMin, INT iMax);

#endif
