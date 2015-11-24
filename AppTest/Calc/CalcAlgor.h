#ifndef __CALC_ALGORITHM_H__
#define __CALC_ALGORITHM_H__

#include "Type.h"


/*
enum CALC_PARAM
{
	CALC_PARAM_OP_ADD = 1,
	CALC_PARAM_OP_SUB,
	CALC_PARAM_OP_MUL,
	CALC_PARAM_OP_DIV,
	CALC_PARAM_OP_MOD,
	CALC_PARAM_OP_BRA1,
	CALC_PARAM_OP_BRA2,
};
*/

#define CALC_PARAM_OP_ADD 1
#define CALC_PARAM_OP_SUB 2
#define CALC_PARAM_OP_MUL 3
#define CALC_PARAM_OP_DIV 4
#define CALC_PARAM_OP_MOD 5
#define CALC_PARAM_OP_BRA1 6
#define CALC_PARAM_OP_BRA2 7

#define CALC_ANALSE_CNT 1024

typedef struct _CalcParam
{
	INT op[CALC_ANALSE_CNT];
	INT data[CALC_ANALSE_CNT];
	INT iOpCnt;
	INT iDataCnt;
	INT iErr;
}CCalcParam, *PCalcParam;

VOID InitCalcParam(PCalcParam pCalcParam);

INT PushData(PCalcParam pCalcParam, INT iData);
INT PushOp(PCalcParam pCalcParam, INT iOp);
INT GetResult(PCalcParam pCalcParam);

#endif

