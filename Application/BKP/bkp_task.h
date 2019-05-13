#ifndef BKP_TASK_H_
#define BKP_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
#include "bkp_lib.h"
//////////////////////////////////////////////////////////////////////////////////////

//===��������
	void BKPTask_Init(void);
	void BKPTask_DeInit(void);
	void BKPTask_WriteDataToReg(UINT32_T bkpReg, UINT32_T val);
	void BKPTask_WriteToReg(UINT32_T bkpReg, UINT32_T *pVal, UINT8_T length);
	UINT32_T BKPTask_ReadDataFromReg(UINT32_T bkpReg);
	void BKPTask_ReadFromReg(UINT32_T bkpReg, UINT32_T *pVal, UINT8_T length);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*BKP_TASK_H_ */