#ifndef BKP_CFG_H_
#define BKP_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
#include "complier_lib.h"
//////////////////////////////////////////////////////////////////////////////////////

//===��������
	void BKP_Init(void);
	void BKP_DeInit(void);
	void BKP_WriteDataToReg(UINT32_T bkpReg, UINT32_T val);
	void BKP_WriteToReg(UINT32_T bkpReg, UINT32_T *pVal, UINT8_T length);
	UINT32_T BKP_ReadDataFromReg(UINT32_T bkpReg);
	void BKP_ReadFromReg(UINT32_T bkpReg, UINT32_T *pVal, UINT8_T length);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*BKP_CFG_H_ */