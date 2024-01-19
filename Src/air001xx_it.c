/**
  ******************************************************************************
  * @file    air001xx_it.c
  * @author  MCU Application Team
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) AirM2M.
  * All rights reserved.</center></h2>
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "air001xx_it.h"

/* Private includes ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/

/******************************************************************************/
/*           Cortex-M0+ Processor Interruption and Exception Handlers         */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
    while(1)
    {
    }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
}
uint16_t TIM16_COUNTER = 0;
void TIM16_IRQHandler(void)
{
    /* USER CODE BEGIN TIM16_IRQn 0 */
    if(LL_TIM_IsActiveFlag_UPDATE(TIM16) == SET)
    {
        LL_TIM_ClearFlag_UPDATE(TIM16);
        TIM16_COUNTER++;
        key_press_handle();
        key_handle();

        if(TIM16_COUNTER % 10 == 0) //50ms
        {
            key_function();
        }
        //
        //LL_GPIO_TogglePin
        if(TIM16_COUNTER % 50 == 0) //50ms
        {
            status_function();
        }
        if(TIM16_COUNTER == 1000)//1s
        {
            //LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_0);
            TIM16_COUNTER = 0;
        }
    }

    //////////////////////////////////////////////////
    /* USER CODE END TIM16_IRQn 0 */
    /* USER CODE BEGIN TIM16_IRQn 1 */

    /* USER CODE END TIM16_IRQn 1 */
}
/******************************************************************************/
/* AIR001xx Peripheral Interrupt Handlers                                     */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file.                                          */
/******************************************************************************/

/************************ (C) COPYRIGHT AirM2M *****END OF FILE******************/
