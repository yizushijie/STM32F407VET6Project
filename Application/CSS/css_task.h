#ifndef CSS_TASK_H_
#define CSS_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
#include "css_lib.h"
//////////////////////////////////////////////////////////////////////////////////////
//===��������
	void CSSTask_Init(void);
	void CSSTask_DeInit(void);
	void CSSTask_NMI_IRQ(void);
	void CSSTask_RCC_IRQ(void);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*CSS_TASK_H_ */