#include "main.h"
#include "air001_ll_Core_Board.h"

void MX_TIM3_Init(void)
{
    /* Peripheral clock enable */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);

    LL_TIM_InitTypeDef TIM_InitStruct = {0};
    LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};
    //48000000/2/2400 = 10khz
    /* Set the TIM3 parameters */
    TIM_InitStruct.Prescaler = 1;  // 48MHz主频下，预分频值为47，所以计数频率为48MHz / (47 + 1) = 1MHz
    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload = 2399;  // 计数器重载值，用于设置PWM周期
    TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    LL_TIM_Init(TIM3, &TIM_InitStruct);

    /* Configure TIM3 CH2 (PA7) for PWM output */
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    GPIO_InitStruct.Pin = LL_GPIO_PIN_7;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
    TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_ENABLE;
    TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
    TIM_OC_InitStruct.CompareValue = 0;  // 初始化占空比为0，需要根据具体需求进行调整
    LL_TIM_OC_Init(TIM3, LL_TIM_CHANNEL_CH2, &TIM_OC_InitStruct);
    LL_TIM_OC_EnablePreload(TIM3, LL_TIM_CHANNEL_CH2);

    /* Configure TIM3 CH3 (PB0) for PWM output */
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
    GPIO_InitStruct.Pin = LL_GPIO_PIN_0;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
    TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_ENABLE;
    TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
    TIM_OC_InitStruct.CompareValue = 0;  // 初始化占空比为0，需要根据具体需求进行调整
    LL_TIM_OC_Init(TIM3, LL_TIM_CHANNEL_CH3, &TIM_OC_InitStruct);
    LL_TIM_OC_EnablePreload(TIM3, LL_TIM_CHANNEL_CH3);

    /* Enable TIM3 counter and PWM outputs */
    LL_TIM_EnableCounter(TIM3);
    LL_TIM_EnableAllOutputs(TIM3);
    LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH2);
    LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH3);
}
void MX_TIM16_Init(void)
{

    /* USER CODE BEGIN TIM16_Init 0 */

    /* USER CODE END TIM16_Init 0 */

    LL_TIM_InitTypeDef TIM_InitStruct = {0};

    LL_RCC_LSE_SetDriveCapability(LL_RCC_LSEDRIVE_LOW);

    /* Peripheral clock enable */
    LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM16);

    /* TIM16 interrupt Init */
    NVIC_SetPriority(TIM16_IRQn, 1);
    NVIC_EnableIRQ(TIM16_IRQn);

    /* USER CODE BEGIN TIM16_Init 1 */
    //8000000/
    /* USER CODE END TIM16_Init 1 */
    TIM_InitStruct.Prescaler = 47;
    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload = 999;
    TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    TIM_InitStruct.RepetitionCounter = 0;
    LL_TIM_Init(TIM16, &TIM_InitStruct);
    LL_TIM_DisableARRPreload(TIM16);
    LL_TIM_SetClockSource(TIM16, LL_TIM_CLOCKSOURCE_INTERNAL);
    LL_TIM_SetTriggerOutput(TIM16, LL_TIM_TRGO_RESET);
    LL_TIM_DisableMasterSlaveMode(TIM16);
    /* USER CODE BEGIN TIM16_Init 2 */
    LL_TIM_EnableIT_UPDATE(TIM16);
    LL_TIM_EnableCounter(TIM16);
    /* USER CODE END TIM16_Init 2 */

}


