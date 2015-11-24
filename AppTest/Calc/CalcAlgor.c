#include "CalcAlgor.h"
#include "Tool.h"


VOID InitCalcParam(PCalcParam pCalcParam)
{
	if(pCalcParam == NULL)
	{
		return;
	}

	MemSet(pCalcParam, 0, sizeof(pCalcParam));
}

INT PushData(PCalcParam pCalcParam, INT iData)
{
	if(pCalcParam == NULL)
	{
		return -1;
	}

	if(pCalcParam->iOpCnt)
	{
		if(pCalcParam->iDataCnt)
		{
			pCalcParam->iErr = 5;
			return -1;
		}else
		{
			switch(pCalcParam->op[pCalcParam->iOpCnt])
			{
				case CALC_PARAM_OP_MUL:
					pCalcParam->data[pCalcParam->iDataCnt-1] = pCalcParam->data[pCalcParam->iDataCnt-1]*iData;
					pCalcParam->iOpCnt--;
					break;
					
				case CALC_PARAM_OP_DIV:
					pCalcParam->data[pCalcParam->iDataCnt-1] = pCalcParam->data[pCalcParam->iDataCnt-1]/iData;
					pCalcParam->iOpCnt--;
					break;
			
				case CALC_PARAM_OP_MOD:
					pCalcParam->data[pCalcParam->iDataCnt-1] = pCalcParam->data[pCalcParam->iDataCnt-1]%iData;
					pCalcParam->iOpCnt--;			
					break;
					
				case CALC_PARAM_OP_ADD:
				case CALC_PARAM_OP_SUB:

					if(pCalcParam->iDataCnt > CALC_ANALSE_CNT)
					{
						pCalcParam->iErr = 6;
						return -1;
					}else
					{
						pCalcParam->data[pCalcParam->iDataCnt++] = iData;
					}
					
					//donothing...
					break;
			
				case CALC_PARAM_OP_BRA1:
				case CALC_PARAM_OP_BRA2:
					pCalcParam->iErr = 3;
					return -1;
					break;
			
				default:
					pCalcParam->iErr = 4;
					return -1;
					break;
			}
		}

	}else
	{
		if(pCalcParam->iDataCnt > CALC_ANALSE_CNT)
		{
			pCalcParam->iErr = 2;
			return -1;
		}else
		{
			if(pCalcParam->iDataCnt)
			{
				pCalcParam->iErr = 1;
				return -1;
			}else
			{
				pCalcParam->data[pCalcParam->iDataCnt++] = iData;
			}
		}
	}

	return 0;
}

INT PushOp(PCalcParam pCalcParam, INT iOp)
{
	if(pCalcParam == NULL)
	{
		return -1;
	}

	if(pCalcParam->iDataCnt == 0)
	{
		if(iOp != CALC_PARAM_OP_BRA1)
		{
			pCalcParam->iErr = 0x1001;
			return -1;
		}else
		{
			if(pCalcParam->iOpCnt > CALC_ANALSE_CNT)
			{
				pCalcParam->iErr = 0x1002;
				return -1;
			}else
			{
				pCalcParam->op[pCalcParam->iOpCnt++] = iOp;
			}
		}
		return 0;
	}

	switch(iOp)
	{
		case CALC_PARAM_OP_MUL:
		case CALC_PARAM_OP_DIV:
		case CALC_PARAM_OP_MOD:
		case CALC_PARAM_OP_BRA1:
			if(pCalcParam->iOpCnt > CALC_ANALSE_CNT)
			{
				pCalcParam->iErr = 0x1003;
			}else
			{
				pCalcParam->op[pCalcParam->iOpCnt++] = iOp;
			}
			break;


		case CALC_PARAM_OP_ADD:
		case CALC_PARAM_OP_SUB:

			if(pCalcParam->iOpCnt)
			{
				switch(pCalcParam->op[pCalcParam->iOpCnt-1])
				{
					case CALC_PARAM_OP_ADD:
						pCalcParam->data[pCalcParam->iDataCnt-2] += pCalcParam->data[pCalcParam->iDataCnt-1];
						pCalcParam->op[pCalcParam->iOpCnt-1] = iOp;
					break;
				
					case CALC_PARAM_OP_SUB:
						pCalcParam->data[pCalcParam->iDataCnt-2] -= pCalcParam->data[pCalcParam->iDataCnt-1];
						pCalcParam->op[pCalcParam->iOpCnt-1] = iOp;
					break;
				
					case CALC_PARAM_OP_MUL:
						pCalcParam->data[pCalcParam->iDataCnt-2] *= pCalcParam->data[pCalcParam->iDataCnt-1];
						pCalcParam->op[pCalcParam->iOpCnt-1] = iOp;
					break;
				
					case CALC_PARAM_OP_DIV:
						pCalcParam->data[pCalcParam->iDataCnt-2] /= pCalcParam->data[pCalcParam->iDataCnt-1];
						pCalcParam->op[pCalcParam->iOpCnt-1] = iOp;
					break;
					
					case CALC_PARAM_OP_MOD:
						pCalcParam->data[pCalcParam->iDataCnt-2] %= pCalcParam->data[pCalcParam->iDataCnt-1];
						pCalcParam->op[pCalcParam->iOpCnt-1] = iOp;
					break;
				
					default:
				
					break;
				}
			}else
			{
				if(pCalcParam->iOpCnt > CALC_ANALSE_CNT)
				{
					pCalcParam->iErr = 0x1004;
				}else
				{
					pCalcParam->op[pCalcParam->iOpCnt++] = iOp;
				}

			}
			break;

			
		case CALC_PARAM_OP_BRA2:

			while(TRUE)
			{
				if(pCalcParam->iOpCnt == 0)
				{
					pCalcParam->iErr = 0x1005;
					return -1;
				}

				if(pCalcParam->op[pCalcParam->iOpCnt-1] == CALC_PARAM_OP_BRA1)
				{
					pCalcParam->iOpCnt--;
					break;
				}

				switch(pCalcParam->op[pCalcParam->iOpCnt-1])
				{
					case CALC_PARAM_OP_ADD:
						pCalcParam->data[pCalcParam->iDataCnt-2] += pCalcParam->data[pCalcParam->iDataCnt-1];
						pCalcParam->iDataCnt--;
					break;

					case CALC_PARAM_OP_SUB:
						pCalcParam->data[pCalcParam->iDataCnt-2] -= pCalcParam->data[pCalcParam->iDataCnt-1];
						pCalcParam->iDataCnt--;
					break;
					
					case CALC_PARAM_OP_MUL:
						pCalcParam->data[pCalcParam->iDataCnt-2] *= pCalcParam->data[pCalcParam->iDataCnt-1];
						pCalcParam->iDataCnt--;
					break;

					case CALC_PARAM_OP_DIV:
						pCalcParam->data[pCalcParam->iDataCnt-2] /= pCalcParam->data[pCalcParam->iDataCnt-1];
						pCalcParam->iDataCnt--;
					break;
					
					case CALC_PARAM_OP_MOD:
						pCalcParam->data[pCalcParam->iDataCnt-2] %= pCalcParam->data[pCalcParam->iDataCnt-1];
						pCalcParam->iDataCnt--;
					break;
				}
				pCalcParam->iOpCnt--;
			}

			pCalcParam->iDataCnt--;
			PushData(pCalcParam, pCalcParam->data[pCalcParam->iDataCnt-1]);
			break;
		
		default:
			pCalcParam->iErr = 0x1006;
			break;
	}

	return 0;	
}

INT GetResult(PCalcParam pCalcParam)
{
	if(pCalcParam == NULL)
	{
		return 0;
	}
	
	return pCalcParam->data[0];
}

