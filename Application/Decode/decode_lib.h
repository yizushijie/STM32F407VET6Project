#ifndef DECODE_LIB_H_
#define DECODE_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "decode_cfg.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===��������
	void DecodeLib_Init(void);
	void DecodeLib_ActivateSites(UINT8_T activateSites);
	void DecodeLib_ClearActivateSites(void);
	void DecodeLib_ClearState(void);
	void DecodeLib_START(void);
	void DecodeLib_STOP(void);
	UINT8_T DecodeLib_ScanRST(void);
	void DecodeLib_IRQTask(void);
	void DecodeLib_Quency(void);
	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*DECODE_LIB_H_ */