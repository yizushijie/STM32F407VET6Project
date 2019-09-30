/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
  /* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
	/* USER CODE BEGIN NonMaskableInt_IRQn 0 */
	//CSSTask_NMI_IRQ();
	/* USER CODE END NonMaskableInt_IRQn 0 */
	/* USER CODE BEGIN NonMaskableInt_IRQn 1 */

	/* USER CODE END NonMaskableInt_IRQn 1 */
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� RCC�жϴ�������
//////////////////////////////////////////////////////////////////////////////
void RCC_IRQHandler(void)
{
	/* USER CODE BEGIN NonMaskableInt_IRQn 0 */
	//CSSTask_RCC_IRQ();
	/* USER CODE END NonMaskableInt_IRQn 0 */
	/* USER CODE BEGIN NonMaskableInt_IRQn 1 */

	/* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
	/* USER CODE BEGIN HardFault_IRQn 0 */
	HardFault_ErrIRQ();
	/* USER CODE END HardFault_IRQn 0 */
	while (1)
	{
		/* USER CODE BEGIN W1_HardFault_IRQn 0 */
		/* USER CODE END W1_HardFault_IRQn 0 */
	}
	/* USER CODE BEGIN HardFault_IRQn 1 */

	/* USER CODE END HardFault_IRQn 1 */
}

/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{
	/* USER CODE BEGIN MemoryManagement_IRQn 0 */

	/* USER CODE END MemoryManagement_IRQn 0 */
	while (1)
	{
		/* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
		/* USER CODE END W1_MemoryManagement_IRQn 0 */
	}
	/* USER CODE BEGIN MemoryManagement_IRQn 1 */

	/* USER CODE END MemoryManagement_IRQn 1 */
}

/**
* @brief This function handles Pre-fetch fault, memory access fault.
*/
void BusFault_Handler(void)
{
	/* USER CODE BEGIN BusFault_IRQn 0 */

	/* USER CODE END BusFault_IRQn 0 */
	while (1)
	{
		/* USER CODE BEGIN W1_BusFault_IRQn 0 */
		/* USER CODE END W1_BusFault_IRQn 0 */
	}
	/* USER CODE BEGIN BusFault_IRQn 1 */

	/* USER CODE END BusFault_IRQn 1 */
}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
	/* USER CODE BEGIN UsageFault_IRQn 0 */

	/* USER CODE END UsageFault_IRQn 0 */
	while (1)
	{
		/* USER CODE BEGIN W1_UsageFault_IRQn 0 */
		/* USER CODE END W1_UsageFault_IRQn 0 */
	}
	/* USER CODE BEGIN UsageFault_IRQn 1 */

	/* USER CODE END UsageFault_IRQn 1 */
}

/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void)
{
	/* USER CODE BEGIN SVCall_IRQn 0 */

	/* USER CODE END SVCall_IRQn 0 */
	/* USER CODE BEGIN SVCall_IRQn 1 */

	/* USER CODE END SVCall_IRQn 1 */
}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{
	/* USER CODE BEGIN DebugMonitor_IRQn 0 */

	/* USER CODE END DebugMonitor_IRQn 0 */
	/* USER CODE BEGIN DebugMonitor_IRQn 1 */

	/* USER CODE END DebugMonitor_IRQn 1 */
}

/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void)
{
	/* USER CODE BEGIN PendSV_IRQn 0 */

	/* USER CODE END PendSV_IRQn 0 */
	/* USER CODE BEGIN PendSV_IRQn 1 */

	/* USER CODE END PendSV_IRQn 1 */
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
	/* USER CODE BEGIN SysTick_IRQn 0 */
	SysTickTask_IRQTick();
	/* USER CODE END SysTick_IRQn 0 */

	/* USER CODE BEGIN SysTick_IRQn 1 */

	/* USER CODE END SysTick_IRQn 1 */
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����WWDG �жϸ����������������˴��жϣ���ʾ�����Ѿ������˹��ϣ�
////////////// ����һ����ǰ�жϡ��ڴ��жϷ��������Ӧ�ø�����Ҫ���£�
////////////// ���籣����Ҫ�����ݵȣ����ʱ������ж೤��Ҫ
////////////// ��WDGTB ��ֵ��
//////////////////////////////////////////////////////////////////////////////
void WWDG_IRQHandler()
{
	////---ˢ�µݼ���������ֵ���������˾��,���ڿ��Ź���������λ
	//LL_WWDG_SetCounter(WWDG, 0x7F);
	//---�����ǰ�����жϱ�־
	LL_WWDG_ClearFlag_EWKUP(WWDG);
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ����1���жϴ�������
//////////////////////////////////////////////////////////////////////////////
void USART1_IRQHandler(void)
{
	//---���ݽ����жϴ�������---���ռĴ�����Ϊ��
	if (LL_USART_IsActiveFlag_RXNE(pUSART1->msgUSART) && LL_USART_IsEnabledIT_RXNE(pUSART1->msgUSART))
	{
		USARTTask_ITRead_Task(pUSART1, LL_USART_ReceiveData8(USART1));

		//---����жϱ�־λ
		LL_USART_ClearFlag_RXNE(USART1);
	}

	//---���ݷ��ͼĴ����շ����жϴ�������
	if (LL_USART_IsActiveFlag_TXE(pUSART1->msgUSART) && LL_USART_IsEnabledIT_TXE(pUSART1->msgUSART))
	{
		USARTTask_ITWrite_TXETask(pUSART1);
	}

	//---���ݷ�������жϴ�������
	if (LL_USART_IsActiveFlag_TC(pUSART1->msgUSART) && LL_USART_IsEnabledIT_TC(pUSART1->msgUSART))
	{
		USARTTask_IT_TCTask(pUSART1);
		//---����жϱ�־λ
		LL_USART_ClearFlag_TC(USART1);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ������жϺ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void HASH_RNG_IRQHandler(void)
{
	//===�������Ӵ���
	if (LL_RNG_IsActiveFlag_SEIS(RNG))
	{
		//---�������Ӵ����־
		LL_RNG_ClearFlag_SEIS(RNG);
		//---����ʹ�������
		LL_RNG_Disable(RNG);
		//---����ʹ��ʹ�������
		LL_RNG_Enable(RNG);
	}
	//===����ʱ�Ӵ���
	if (LL_RNG_IsActiveFlag_CEIS(RNG))
	{
		//---����ʱ�Ӵ����־
		LL_RNG_ClearFlag_CEIS(RNG);
	}
	//===���ݾ���
	if (LL_RNG_IsActiveFlag_DRDY(RNG))
	{
		g_HASH_RNG_Val = LL_RNG_ReadRandData32(RNG);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void DMA2_Stream0_IRQHandler(void)
{
	if (LL_DMA_IsActiveFlag_TC0(DMA2) && (LL_DMA_IsEnabledIT_TC(DMA2, LL_DMA_STREAM_0)))
	{
		//ADCTask_ADCTask_STOP(ADC1);
	}
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void DMA2_Stream1_IRQHandler(void)
{
	if (LL_DMA_IsActiveFlag_TC0(DMA2) && (LL_DMA_IsEnabledIT_TC(DMA2, LL_DMA_STREAM_1)))
	{
		//ADCTask_ADCTask_STOP(ADC3);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		������ʱ��2���ж�
//////////////////////////////////////////////////////////////////////////////
void TIM2_IRQHandler(void)
{
	//DecodeTask_IRQTask();
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		�����ɱ�̵�����
//////////////////////////////////////////////////////////////////////////////
void PVD_IRQHandler(void)
{
	LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_16);
	if (LL_PWR_IsActiveFlag_PVDO())
	{
		//---�����⴦������
		PVDTask_IRQTask();
	}
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/