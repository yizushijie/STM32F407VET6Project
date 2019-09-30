#include "systick_lib.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T	SysTickLib_Init(void)
{
	return SysTick_msInit();
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ע����ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T	SysTickLib_DeInit(void)
{
	return SysTick_DeInit();
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T	SysTickLib_CreateTickTask(void(*pFuncTick)(void))
{
	return SysTick_CreateTickTask(pFuncTick);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTickLib_DeleteTickTask(void(*pFuncTick)(void))
{
	return SysTick_DeleteTickTask(pFuncTick);
}

/*
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T	SysTickLib_FuncTick(void(*pFuncTick)(void))
{
	return SysTick_FuncTick(pFuncTick);
}
*/
///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTickLib_IRQDecTick(UINT32_T waitDecTick)
{
	return SysTick_IRQDecTick(waitDecTick);
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTickLib_DecTick(UINT32_T waitDecTick)
{
	return SysTick_DecTick(waitDecTick);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT32_T SysTickLib_GetTick(void)
{
	return SysTick_GetTick();
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T	SysTickLib_IRQTick(void)
{
	return SysTick_IRQTick();
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T	SysTickLib_WaitTick(UINT32_T usTime)
{
	return SysTick_WaitTick(usTime);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  SysTickLib_WaitusTick(UINT32_T usTime)
{
	return SysTick_WaitusTick(usTime);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  SysTickLib_1msIncTick(void)
{
	return SysTick_1msIncTick();
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT32_T SysTickLib_GetTickOVF(void)
{
	return SysTick_GetTickOVF();
}