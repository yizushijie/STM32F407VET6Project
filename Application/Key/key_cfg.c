#include "key_cfg.h"

//===>>MultiButton START=========================================================
//===�����¼��б�
KeyButton_HandlerType * pHeadHandle = NULL;

//===���ڼ���
UINT32_T(*keyButtonFuncTimeTick)(void) = NULL;

//===�¼���ѵ�Ŀ���
UINT8_T g_KeyButtonTimeSpan = 0;
UINT32_T g_KeyButtonTickTime = 0;

//===���廷�λ�����ʱ
UINT8_T g_keyButtonLoopBuffer[256] = { 0 };

//===���廷�λ�����д����
UINT32_T g_keyLoopWriteIndex = 0;

//===���廷�λ�����������
UINT32_T g_KeyLoopReadIndex = 0;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void KeyButton_Init(KeyButton_HandlerType* handle, UINT8_T(*pPinReadLevel)(), UINT8_T pinActiveLevel)
{
	memset(handle, 0, sizeof(KeyButton_HandlerType));
	handle->msgEvent = (UINT8_T)NONE_PRESS;
	handle->msgFuncReadPinLevel = pPinReadLevel;
	handle->msgButtonLevel = handle->msgFuncReadPinLevel();
	handle->msgActiveLevel = pinActiveLevel;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void KeyButton_Attach(KeyButton_HandlerType *handle, KeyButtonPressEvent event, KeyButtonCallBack cb)
{
	handle->msgCB[event] = cb;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
KeyButtonPressEvent KeyButton_GetButtonEvent(KeyButton_HandlerType* handle)
{
	return (KeyButtonPressEvent)(handle->msgEvent);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������: 0---�¼�������1---�¼��Ѿ�����
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T KeyButton_START(KeyButton_HandlerType *btn)
{
	KeyButton_HandlerType* target = pHeadHandle;
	while (target)
	{
		if (target == btn)
		{
			//---�����¼��Ѿ�����
			return 1;
		}
		target = target->msgNext;
	}
	btn->msgNext = pHeadHandle;
	pHeadHandle = btn;
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void KeyButton_STOP(KeyButton_HandlerType* btn)
{
	KeyButton_HandlerType** curr;
	for (curr = &pHeadHandle; *curr; )
	{
		KeyButton_HandlerType* entry = *curr;
		if (entry == btn)
		{
			*curr = entry->msgNext;
		}
		else
		{
			curr = &entry->msgNext;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void KeyButton_CallBackHandlerEvent(KeyButton_HandlerType* handle, UINT8_T event)
{
	if (handle->msgCB[event] != NULL)
	{
		handle->msgCB[event]((KeyButton_HandlerType*)handle);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void KeyButton_HandlerEvent(KeyButton_HandlerType* handle)
{
	UINT32_T read_gpio_level = handle->msgFuncReadPinLevel();

	//ticks counter working..
	if ((handle->msgState) > 0)
	{
		handle->msgTicks++;
	}

	//---��������
	if (read_gpio_level != handle->msgButtonLevel)
	{
		//---������ΰ�����״̬������״̬��һ�£����������ȶ�
		if (++(handle->msgDebounceCNT) >= DEBOUNCE_TICKS)
		{
			handle->msgButtonLevel = read_gpio_level;
			handle->msgDebounceCNT = 0;
		}
	}
	else
	{
		//---���������ȶ������¼�������
		handle->msgDebounceCNT = 0;
	}

	//---״̬����
	switch (handle->msgState)
	{
		case 0:
			if (handle->msgButtonLevel == handle->msgActiveLevel)
			{
				//---��������
				handle->msgEvent = (UINT8_T)PRESS_DOWN;

				//---�ص��¼���������
				KeyButton_CallBackHandlerEvent(handle, PRESS_DOWN);
				handle->msgTicks = 0;
				handle->msgRepeat = 1;
				handle->msgState = 1;
			}
			else
			{
				handle->msgEvent = (UINT8_T)NONE_PRESS;
			}
			break;

		case 1:
			if (handle->msgButtonLevel != handle->msgActiveLevel)
			{
				//---�ͷŰ�������������
				handle->msgEvent = (UINT8_T)PRESS_UP;

				//---�ص��¼���������
				KeyButton_CallBackHandlerEvent(handle, PRESS_UP);
				handle->msgTicks = 0;
				handle->msgState = 2;
			}
			else if (handle->msgTicks > LONG_TICKS)
			{
				//---������ʱ�䰴��
				handle->msgEvent = (UINT8_T)LONG_RRESS_START;

				//---�ص��¼���������
				KeyButton_CallBackHandlerEvent(handle, LONG_RRESS_START);
				handle->msgState = 5;
			}
			break;

		case 2:
			if (handle->msgButtonLevel == handle->msgActiveLevel)
			{
				//---�����ٴΰ���
				handle->msgEvent = (UINT8_T)PRESS_DOWN;

				//---�ص��¼���������
				KeyButton_CallBackHandlerEvent(handle, PRESS_DOWN);
				handle->msgRepeat++;
				if (handle->msgRepeat == 2)
				{
					//---�ص��¼���������
					KeyButton_CallBackHandlerEvent(handle, DOUBLE_CLICK);
				}

				//---������ΰ���
				//---�ص��¼���������
				KeyButton_CallBackHandlerEvent(handle, PRESS_REPEAT);
				handle->msgTicks = 0;
				handle->msgState = 3;
			}
			else if (handle->msgTicks > SHORT_TICKS)
			{
				if (handle->msgRepeat == 1)
				{
					//---����
					handle->msgEvent = (UINT8_T)SINGLE_CLICK;

					//---�ص��¼���������
					KeyButton_CallBackHandlerEvent(handle, SINGLE_CLICK);
				}
				else if (handle->msgRepeat == 2)
				{
					handle->msgEvent = (UINT8_T)DOUBLE_CLICK;
				}
				handle->msgState = 0;
			}
			break;

		case 3:
			if (handle->msgButtonLevel != handle->msgActiveLevel)
			{
				//---�ͷŰ���
				handle->msgEvent = (UINT8_T)PRESS_UP;

				//---�ص��¼���������
				KeyButton_CallBackHandlerEvent(handle, PRESS_UP);
				if (handle->msgTicks < SHORT_TICKS)
				{
					//---�����̰�
					handle->msgTicks = 0;
					handle->msgState = 2;
				}
				else
				{
					handle->msgState = 0;
				}
			}

			break;

		case 5:
			if (handle->msgButtonLevel == handle->msgActiveLevel)
			{
				//---������ʱ�䰴��
				handle->msgEvent = (UINT8_T)LONG_PRESS_HOLD;

				//---�ص��¼���������
				KeyButton_CallBackHandlerEvent(handle, LONG_PRESS_HOLD);
			}
			else
			{
				//---�����ͷ�
				handle->msgEvent = (UINT8_T)PRESS_UP;

				//---�ص��¼���������
				KeyButton_CallBackHandlerEvent(handle, PRESS_UP);

				//---״̬����
				handle->msgState = 0; //reset
			}
			break;
		default:

			//---״̬����
			handle->msgState = 0; //reset
			handle->msgEvent = (UINT8_T)NONE_PRESS;
			break;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ʱ������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void KeyButton_TimeTicks()
{
	KeyButton_HandlerType* target;
	for (target = pHeadHandle; target; target = target->msgNext)
	{
		KeyButton_HandlerEvent(target);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ѵ���ȵĳ�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void KeyButton_PollInit(UINT32_T(*pFuncTimerTick)(void), UINT8_T timeSpan)
{
	keyButtonFuncTimeTick = pFuncTimerTick;
	g_KeyButtonTimeSpan = timeSpan;
	if (keyButtonFuncTimeTick != NULL)
	{
		g_KeyButtonTickTime = keyButtonFuncTimeTick();
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���������ѵ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void KeyButton_PollTicks()
{
	UINT32_T nowTime = 0;
	UINT32_T cnt = 0;
	KeyButton_HandlerType* target;
	if (keyButtonFuncTimeTick != NULL)
	{
		//---��ȡ��ǰʱ�����
		nowTime = keyButtonFuncTimeTick();

		//---�жϵδ�ʱ�Ƿ����������
		if (nowTime < g_KeyButtonTickTime)
		{
			cnt = (0xFFFFFFFF - g_KeyButtonTickTime + nowTime);
		}
		else
		{
			cnt = nowTime - g_KeyButtonTickTime;
		}

		//---�ж���ѯʱ���Ƿ񵽴�
		if (cnt >= g_KeyButtonTimeSpan)
		{
			//---�����¼�����
			for (target = pHeadHandle; target; target = target->msgNext)
			{
				KeyButton_HandlerEvent(target);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����λ�����дһ�ֽ�����
//////�������:
//////�������:
//////˵		����0---�ɹ���1---ʧ��
//////////////////////////////////////////////////////////////////////////////
UINT8_T KeyButton_WriteKeyLoopBuffer(UINT8_T dat)
{
	UINT32_T next_wp;

	next_wp = (g_keyLoopWriteIndex + 1) & 255;//11 1111 1111

	if (next_wp == g_KeyLoopReadIndex)
	{
		return 1;
	}
	g_keyButtonLoopBuffer[g_keyLoopWriteIndex] = dat;
	g_keyLoopWriteIndex = next_wp;

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��ӻ��λ�������һ�ֽ�����
//////�������:
//////�������:
//////˵		����0---�ɹ���1---ʧ��
//////////////////////////////////////////////////////////////////////////////
UINT8_T KeyButton_ReadKeyLoopBuffer(UINT8_T *dat)
{
	if (g_KeyLoopReadIndex == g_keyLoopWriteIndex)
	{
		return 1;
	}

	*dat = g_keyButtonLoopBuffer[g_KeyLoopReadIndex];
	g_KeyLoopReadIndex = (g_KeyLoopReadIndex + 1) & 255;

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void KeyButton_ClearKeyLoop(void)
{
	memset(g_keyButtonLoopBuffer, 0, sizeof(g_keyButtonLoopBuffer));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���������
//////�������:
//////�������:
//////˵		����0---�޼�ֵ��1---�м�ֵ
//////////////////////////////////////////////////////////////////////////////
UINT8_T KeyButton_GetKeyVal(void) //��ȡ��ֵ
{
	UINT8_T key_val;

	if (KeyButton_ReadKeyLoopBuffer(&key_val) == 1) //��ȡ���гɹ�
	{
		return key_val;
	}
	else
	{
		return 0;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void KeyButton1_PRESS_DOWN_Handler(void* btn)
{
	//---��������1���µ��¼�
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void KeyButton1_PRESS_UP_Handler(void* btn)
{
	//---��������1�����¼�
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void KeyButton2_PRESS_DOWN_Handler(void* btn)
{
	//---��������1���µ��¼�
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void KeyButton2_PRESS_UP_Handler(void* btn)
{
	//---��������1�����¼�
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void KeyButton3_PRESS_DOWN_Handler(void* btn)
{
	//---��������1���µ��¼�
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void KeyButton4_PRESS_UP_Handler(void* btn)
{
	//---��������1�����¼�
}

//===<<MultiButton END=========================================================

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Key_BINInit(void)
{
	//---ʹ��GPIO��ʱ��
	GPIOTask_Clock(BINA_CTR_PORT, 1);
	GPIOTask_Clock(BINB_CTR_PORT, 1);
	GPIOTask_Clock(BINC_CTR_PORT, 1);
	GPIOTask_Clock(BIND_CTR_PORT, 1);

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;			//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
#endif

//---BINA_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = BINA_CTR_BIT;
	LL_GPIO_Init(BINA_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(BINA_CTR_PORT, BINA_CTR_BIT);

	//---BINB_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = BINB_CTR_BIT;
	LL_GPIO_Init(BINB_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(BINB_CTR_PORT, BINB_CTR_BIT);

	//---BINC_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = BINC_CTR_BIT;
	LL_GPIO_Init(BINC_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(BINC_CTR_PORT, BINC_CTR_BIT);

	//---BIND_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = BIND_CTR_BIT;
	LL_GPIO_Init(BIND_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(BIND_CTR_PORT, BIND_CTR_BIT);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Key_SOTInit(void)
{
	//---ʹ��GPIO��ʱ��
	GPIOTask_Clock(SOTA_CTR_PORT, 1);
	GPIOTask_Clock(SOTB_CTR_PORT, 1);
	GPIOTask_Clock(SOTC_CTR_PORT, 1);
	GPIOTask_Clock(SOTD_CTR_PORT, 1);

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;			//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
#endif

//---SOTA_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = SOTA_CTR_BIT;
	LL_GPIO_Init(SOTA_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(SOTA_CTR_PORT, SOTA_CTR_BIT);

	//---SOTB_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = SOTB_CTR_BIT;
	LL_GPIO_Init(SOTB_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(SOTB_CTR_PORT, SOTB_CTR_BIT);

	//---SOTC_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = SOTC_CTR_BIT;
	LL_GPIO_Init(SOTC_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(SOTC_CTR_PORT, SOTC_CTR_BIT);

	//---SOTD_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = SOTD_CTR_BIT;
	LL_GPIO_Init(SOTD_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(SOTD_CTR_PORT, SOTD_CTR_BIT);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Key_EOTInit(void)
{
	//---ʹ��GPIO��ʱ��
	GPIOTask_Clock(EOTA_CTR_PORT, 1);
	GPIOTask_Clock(EOTB_CTR_PORT, 1);
	GPIOTask_Clock(EOTC_CTR_PORT, 1);
	GPIOTask_Clock(EOTD_CTR_PORT, 1);

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;			//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
#endif

//---EOTA_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = EOTA_CTR_BIT;
	LL_GPIO_Init(EOTA_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(EOTA_CTR_PORT, EOTA_CTR_BIT);

	//---EOTB_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = EOTB_CTR_BIT;
	LL_GPIO_Init(EOTB_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(EOTB_CTR_PORT, EOTB_CTR_BIT);

	//---EOTC_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = EOTC_CTR_BIT;
	LL_GPIO_Init(EOTC_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(EOTC_CTR_PORT, EOTC_CTR_BIT);

	//---EOTD_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = EOTD_CTR_BIT;
	LL_GPIO_Init(EOTD_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(EOTD_CTR_PORT, EOTD_CTR_BIT);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Key_Init(void)
{
	//Key_BINInit();
	//Key_SOTInit();
	//Key_EOTInit();
	Key_GenSelInit();
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ��ȡSOT��״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T Key_GetSOT(void)
{
	UINT8_T _return = 0;

	//---���SOT
	if (SOTA_CTR_STATE == 0)
	{
		_return |= 0x01;
	}
	if (SOTB_CTR_STATE == 0)
	{
		_return |= 0x02;
	}
	if (SOTC_CTR_STATE == 0)
	{
		_return |= 0x04;
	}
	if (SOTD_CTR_STATE == 0)
	{
		_return |= 0x08;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T Key_ScanSOT(void)
{
	//---��ȡSOT��״̬
	UINT8_T _return = Key_GetSOT();
	if (_return != 0)
	{
	#ifndef USE_FT_CP_TEST

		//---��ʱ�ȴ�������ģʽ��������������ͬʱ���ڵȴ�����SITE�Ĵ����źŵĵ���
		//DelayTask_ms(10);
	#endif

	//---��ȡSOT��״̬
		_return = Key_GetSOT();
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Key_EOTSTART(void)
{
	//---��λSOT
	EOTA_CTR_OUT_1;
	EOTB_CTR_OUT_1;
	EOTC_CTR_OUT_1;
	EOTD_CTR_OUT_1;

	//---��λBIN
	BINA_CTR_OUT_1;
	BINB_CTR_OUT_1;
	BINC_CTR_OUT_1;
	BIND_CTR_OUT_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Key_EOTSTOP(void)
{
	EOTA_CTR_OUT_0;
	EOTB_CTR_OUT_0;
	EOTC_CTR_OUT_0;
	EOTD_CTR_OUT_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Key_BINAPass(UINT8_T isPass)
{
	if (isPass == 0)
	{
		//---SITEA�ϸ�
		BINA_CTR_OUT_0;
	}
	else
	{
		//---SITEA���ϸ�
		BINA_CTR_OUT_1;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Key_BINBPass(UINT8_T isPass)
{
	if (isPass == 0)
	{
		//---SITEB�ϸ�
		BINB_CTR_OUT_0;
	}
	else
	{
		//---SITEB���ϸ�
		BINB_CTR_OUT_1;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Key_BINCPass(UINT8_T isPass)
{
	if (isPass == 0)
	{
		//---SITEC�ϸ�
		BINC_CTR_OUT_0;
	}
	else
	{
		//---SITEC���ϸ�
		BINC_CTR_OUT_1;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Key_BINDPass(UINT8_T isPass)
{
	if (isPass == 0)
	{
		//---SITED�ϸ�
		BIND_CTR_OUT_0;
	}
	else
	{
		//---SITED���ϸ�
		BIND_CTR_OUT_1;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Key_GenSelInit(void)
{
	//---ʹ��GPIO��ʱ��
	GPIOTask_Clock(GEN_SEL0_PORT, 1);
	GPIOTask_Clock(GEN_SEL1_PORT, 1);
	GPIOTask_Clock(GEN_SEL2_PORT, 1);
	//GPIOTask_Clock(GEN_SEL3_PORT, 1);
	//GPIOTask_Clock(GEN_SEL4_PORT, 1);
	//GPIOTask_Clock(GEN_SEL5_PORT, 1);
	//GPIOTask_Clock(GEN_SEL6_PORT, 1);

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode  =LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;			//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
#endif

	//---GEN_SEL0_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = GEN_SEL0_BIT;
	LL_GPIO_Init(GEN_SEL0_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(GEN_SEL0_PORT, GEN_SEL0_BIT);

	//---GEN_SEL1_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = GEN_SEL1_BIT;
	LL_GPIO_Init(GEN_SEL1_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(GEN_SEL1_PORT, GEN_SEL1_BIT);

	//---GEN_SEL2_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = GEN_SEL2_BIT;
	LL_GPIO_Init(GEN_SEL2_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(GEN_SEL2_PORT, GEN_SEL2_BIT);
}

//===�����ź�Դ�İ���ɨ�����ֵ
VLTUINT8_T g_KeyGenSelNowVal = 0xFF;
//===�����ź�Դ�İ���ɨ��ľ�ֵ
VLTUINT8_T g_KeyGenSelOldVal = 0xFF;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����SEL0---FT_RLY18��SEL2---FT_RLY22
//////////////////////////////////////////////////////////////////////////////
UINT8_T Key_GenSelScan(void)
{
	UINT8_T _return = 0x04;
	//---�ж�SEL0
	if (GEN_SEL2_STATE==0)
	{
		g_KeyGenSelNowVal &= 0xFE;
		_return&=0x02;
	}
	else
	{
		g_KeyGenSelNowVal |= 0x01;
		_return &= 0x03;
		_return |= 0x01;
	}
	////---�ж�SEL1
	//if (GEN_SEL1_STATE==0)
	//{
	//	g_KeyGenSelNowVal &= 0xFE;
	//}
	//else
	//{
	//	g_KeyGenSelNowVal |= 0x02;
	//}
	//---�ж�SEL2
	if (GEN_SEL0_STATE == 0)
	{
		g_KeyGenSelNowVal &= 0xFB;
		_return&=0x01;
	}
	else
	{
		g_KeyGenSelNowVal |= 0x04;
		_return &= 0x03;
		_return |= 0x02;
	}

	if (g_KeyGenSelNowVal!=g_KeyGenSelOldVal)
	{
		g_KeyGenSelOldVal = g_KeyGenSelNowVal;
	}
	else
	{
		_return = 0x04;
	}
	return _return ;
}