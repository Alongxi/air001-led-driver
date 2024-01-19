/**
  ******************************************************************************
  * @file    main.h
  * @author  MCU Application Team
  * @brief   Header for main.c file.
  *          This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "air001xx_ll_rcc.h"
#include "air001xx_ll_bus.h"
#include "air001xx_ll_system.h"
#include "air001xx_ll_exti.h"
#include "air001xx_ll_cortex.h"
#include "air001xx_ll_utils.h"
#include "air001xx_ll_pwr.h"
#include "air001xx_ll_dma.h"
#include "air001xx_ll_gpio.h"
#include "air001xx_ll_tim.h"
#include "function.h"
#if defined(USE_FULL_ASSERT)
#include "air001_assert.h"
#endif /* USE_FULL_ASSERT */

#define KEEP_MS 25     //其他按键响应时间

#define KEEP_ENTER_MS 2000  //中键响应时间

extern uint8_t KEY_ENTER_FLAG, KEY_QUIT_FLAG, KEY_Dbclick_FLAG ;

extern uint8_t KEY_UP_LONG_FLAG, KEY_UP_SHORT_FLAG ;
extern uint8_t KEY_DOWN_LONG_FLAG, KEY_DOWN_SHORT_FLAG ;

/* Private includes ----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Exported variables prototypes ---------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void MX_TIM3_Init(void);
void MX_TIM16_Init(void);
void MX_GPIO_Init(void);




void key_press_handle(void);
void key_handle(void);
void SetLightByColorTemp(uint16_t u16ColorTemp,float brightness);//修改色温
extern int pwm_duty;
extern int LED1_Duty,LED2_Duty;
extern uint16_t ColorTemp;
extern float Brightness;
extern uint8_t LIGHT_flag;
extern uint8_t ONOFF_flag;
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT AirM2M *****END OF FILE******************/
