#include "max961x_lib.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961XLib_I2C_Init(MAX961X_HandlerType* MAX961x, void(*pFuncDelayus)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C)
{
	return MAX961X_I2C_Init(MAX961x, pFuncDelayus, pFuncTimerTick, isHWI2C);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961XLib_I2C_CheckDevice(MAX961X_HandlerType* MAX961x)
{
	return MAX961X_I2C_CheckDevice(MAX961x);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961XLib_I2C_ReadRSVoltage(MAX961X_HandlerType* MAX961x)
{
	return MAX961X_I2C_ReadRSVoltage(MAX961x);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961XLib_I2C_ReadRSCurrent(MAX961X_HandlerType* MAX961x, UINT8_T currentGain)
{
	return MAX961X_I2C_ReadRSCurrent(MAX961x,currentGain);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961XLib_I2C_ReadOutVoltage(MAX961X_HandlerType* MAX961x)
{
	return MAX961X_I2C_ReadOutVoltage(MAX961x);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961XLib_I2C_ReadSetVoltage(MAX961X_HandlerType* MAX961x)
{
	return MAX961X_I2C_ReadSetVoltage(MAX961x);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961XLib_I2C_ReadTemp(MAX961X_HandlerType* MAX961x)
{
	return MAX961X_I2C_ReadTemp(MAX961x);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961XLib_I2C_ReadAll(MAX961X_HandlerType* MAX961x, UINT8_T currentGain)
{
	return MAX961X_I2C_ReadAll(MAX961x, currentGain);
}