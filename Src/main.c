/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
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
#include "air001_ll_Core_Board.h"
LL_UTILS_ClkInitTypeDef UTILS_ClkInitStruct;
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_GpioConfig(void);
int pwm_duty = 0;
int LED1_Duty,LED2_Duty = 0;
uint8_t Toggle_flag = 0;
/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
    /* 配置系统时钟 */
    APP_SystemClockConfig();
    //LL_GPIO_AF_DisableRemap_SWJ();
    /* 配置LED引脚 */
    APP_GpioConfig();
    MX_TIM3_Init();
    MX_TIM16_Init();
    MX_GPIO_Init();
    /* LED灭*/

    while (1)
    {

        function_handle();
    }
}

/**
  * @brief  系统时钟配置函数
  * @param  无
  * @retval 无
  */
static void APP_SystemClockConfig(void)
{
    /* HSI使能及初始化 */
    LL_RCC_HSI_Enable();
    LL_RCC_HSI_SetCalibFreq(LL_RCC_HSICALIBRATION_24MHz);
    while(LL_RCC_HSI_IsReady() != 1)
    {
    }

    LL_PLL_ConfigSystemClock_HSI(&UTILS_ClkInitStruct);

    /* 设置AHB分频 */
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

    /* 配置HSISYS为系统时钟及初始化 */
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
    {
    }

    /* 设置APB1分频及初始化 */
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
    /* 更新系统时钟全局变量SystemCoreClock(也可以通过调用SystemCoreClockUpdate函数更新) */
    LL_SetSystemCoreClock(48000000);
}


/**
  * @brief  GPIO配置函数
  * @param  无
  * @retval 无
  */
static void APP_GpioConfig(void)
{
    /* 使能时钟 */
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
    /* 将PA11引脚配置为输出 */
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_7, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_0, LL_GPIO_MODE_OUTPUT);
    /* 默认（复位后）为推挽输出 */
    /* LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_11, LL_GPIO_OUTPUT_PUSHPULL); */
    /* 默认（复位后）是非常低的输出速度 */
    /* LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_11, LL_GPIO_SPEED_FREQ_LOW); */
    /* 默认（复位后）为无上拉 */
    /* LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_11, LL_GPIO_PULL_NO); */
}

/**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
  */
void Error_Handler(void)
{
    /* 无限循环 */
    while (1)
    {
    }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  输出产生断言错误的源文件名及行号
  * @param  file：源文件名指针
  * @param  line：发生断言错误的行号
  * @retval 无
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* 用户可以根据需要添加自己的打印信息,
       例如: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* 无限循环 */
    while (1)
    {
    }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT AirM2M *****END OF FILE******************/
