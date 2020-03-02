#ifndef	W5500_CFG_H_
#define	W5500_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "spi_task.h"
	//////////////////////////////////////////////////////////////////////////////////////

	//===定义结构体
	typedef struct _W5500_HandleType			W5500_HandleType;
	//===定义指针结构体
	typedef	struct _W5500_HandleType			* pW5500_HandleType;
	//===定义结构体
	struct _W5500_HandleType
	{
		SPI_HandleType		msgSPI;																						//---使用的SPI模式
		GPIO_HandleType		msgHWRST;																					//---硬件复位信号
		GPIO_HandleType		msgHWINT;																					//---硬件中断信号
		void(*pMsgDelayms)(UINT32_T delay);																				//---延时参数
	};
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*W5500_CFG_H_ */