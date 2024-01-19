#include "function.h"


uint8_t ONOFF_flag = 0;//开关机flag
uint8_t LIGHT_flag = 0;//默认全关   1：白灯   2：黄灯    3：黄白同时打开
uint8_t Func_flag = 0;//定义当前处于哪种运行模式   0 默认模式   1 常亮模式 此模式只允许调整亮度,所有灯光默认以最大功率运行，并打开风扇
uint16_t ColorTemp = Default_ColorTemp;
float Brightness = 0;//亮度






// 根据色温计算 PWM 占空比并控制灯光
//色温、亮度
// 根据色温计算 PWM 占空比并控制灯光
void SetLightByColorTemp(uint16_t u16ColorTemp, float brightness)
{
    uint16_t u8Ratio;

    // 计算 PWM 占空比的比例
    if(u16ColorTemp < MIN_ColorTemp)
    {
        u8Ratio = MIN_PWM_DUTY;
    }
    else if(u16ColorTemp > MAX_ColorTemp)
    {
        u8Ratio = MAX_PWM_DUTY;
    }
    else
    {
        u8Ratio = (u16ColorTemp - MIN_ColorTemp) * (MAX_PWM_DUTY - MIN_PWM_DUTY) / (MAX_ColorTemp - MIN_ColorTemp) ;
    }

    // 设置 PWM 占空比
    LL_TIM_OC_SetCompareCH2(TIM3, (uint16_t)(u8Ratio * brightness) + MIN_PWM_DUTY);
    LL_TIM_OC_SetCompareCH3(TIM3, (uint16_t)((MAX_PWM_DUTY - u8Ratio) * brightness) + MIN_PWM_DUTY);
}

void function_handle(void)//功能函数
{

    if(pwm_duty > MAX_PWM_DUTY / 2) //超出50%功率开启风扇
    {
        LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_2);
    }
    else
    {
        LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_2);
    }
    switch(LIGHT_flag)
    {

    case 0://关闭所有灯光
        LED1_Duty = 0;
        LED2_Duty = 0;
        break;
    case 1:
        LED1_Duty = pwm_duty;
        LED2_Duty = 0;

        break;
    case 2:
        LED1_Duty = 0;
        LED2_Duty = pwm_duty;
        break;
    case 3:
        SetLightByColorTemp(ColorTemp, Brightness);
        break;
    case 4:
        LED1_Duty = pwm_duty;
        LED2_Duty = pwm_duty;
        break;


    case 5:
        SetLightByColorTemp(ColorTemp, Brightness);
        break;
    }
    if(LIGHT_flag != 3)
    {
        LL_TIM_OC_SetCompareCH2(TIM3, LED1_Duty);
        LL_TIM_OC_SetCompareCH3(TIM3, LED2_Duty);
    }


    if(KEY_ENTER_FLAG == 1)//短按中键
    {
        if(LIGHT_flag != 4)
        {
            if(ONOFF_flag == 2)
            {
                LIGHT_flag++;
                if(LIGHT_flag > 3)
                {
                    LIGHT_flag = 1;//短按的时候在白 黄  白黄三种状态中循环，不会关机   只有长按中键才会进入关机
                }
            }
        }
        KEY_ENTER_FLAG = 0;
    }
    if(KEY_QUIT_FLAG == 1)//长按中键
    {
        if(ONOFF_flag == 2) //已经开机
        {
            if(Func_flag == 0)
            {
                ONOFF_flag = 3;//渐渐关机
            }
        }
        else if(ONOFF_flag == 0) //关机状态下
        {

            Func_flag = 0;
            ONOFF_flag = 1;//渐渐开机
            LIGHT_flag = 3;
        }
        KEY_QUIT_FLAG = 0;
    }

    if(KEY_Dbclick_FLAG == 1)//双击
    {

        if(ONOFF_flag == 2) //已经开机
        {
            if(Func_flag == 1)
            {
                ONOFF_flag = 3;//渐渐关机

            }
        }
        else if(ONOFF_flag == 0) //关机状态下
        {

            Func_flag = 1;
            ONOFF_flag = 1;//渐渐开机
            LIGHT_flag = 4;//全亮模式 此模式下只可以调亮度 不可以调色温
            pwm_duty = MIN_PWM_DUTY;

        }
        //DDL_Printf("双击,时长:%d ms  标志位：%d\r\n", READ_key_hold_ms, READ_Key_press_flag);
        KEY_Dbclick_FLAG = 0;
    }


}
void key_function(void)
{

    if((KEY_QUIT_FLAG != 1) && (KEY_Dbclick_FLAG != 1) && (KEY_ENTER_FLAG != 1) && (ONOFF_flag == 2))//仅正式开机状态下  不使用中键时 本功能生效
    {
        if(KEY_UP_LONG_FLAG == 1)//长按上键
        {
            //DDL_Printf("短按上键\r\n");
            if(LIGHT_flag == 3)
            {
                if(ColorTemp > MIN_ColorTemp)
                {
                    ColorTemp -= 100;
                }
                else
                {
                    ColorTemp = MIN_ColorTemp;
                }
                LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_3);
            }
            else
            {
                if(pwm_duty > MIN_PWM_DUTY)
                {
                    pwm_duty -= 10;
                }
                else
                {
                    pwm_duty = MIN_PWM_DUTY;
                }
                Brightness = (float)pwm_duty / 1200.0f;
            }

            KEY_UP_LONG_FLAG = 0;
        }
        if(KEY_DOWN_LONG_FLAG == 1)//长按下键
        {
            //DDL_Printf("短按下键\r\n");
            if(LIGHT_flag == 3)
            {
                if(ColorTemp < MAX_ColorTemp)
                {
                    ColorTemp += 100;
                }
                else
                {
                    ColorTemp = MAX_ColorTemp;
                }
                LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_3);
            }
            else
            {
                if(pwm_duty < MAX_PWM_DUTY)
                {
                    pwm_duty += 10;
                }
                else
                {
                    pwm_duty = MAX_PWM_DUTY;
                }
                Brightness = (float)pwm_duty / 1200.0f;
            }

            KEY_DOWN_LONG_FLAG = 0;
        }

    }

}
void status_function(void)//开关机状态功能函数
{
    if(ONOFF_flag == 1)
    {
        if(LIGHT_flag != 4)
        {
            if(Brightness < 0.6f)
            {
                Brightness += 0.012;
                LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_3);
            }
            else
            {
                ONOFF_flag = 2;//正式进入系统

                pwm_duty  = (uint16_t)(Brightness * 1200.0f);
                LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_3);
                LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_2);
            }
        }
        else
        {
            if(pwm_duty < MAX_PWM_DUTY)
            {
                pwm_duty += 20;

                LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_3);
            }
            else
            {
                ONOFF_flag = 2;//正式进入系统
                LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_3);
                LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_2);
            }
        }
    }
    else if(ONOFF_flag == 0)
    {
        LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_2);
        LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_3);
    }
    else if(ONOFF_flag == 3)
    {
        if(LIGHT_flag == 3)
        {
            Brightness -= 0.012;
            if(Brightness <= 0)
            {
                ONOFF_flag = 0;
                LIGHT_flag = 0;//关机
                ColorTemp = Default_ColorTemp;
                Brightness = 0;
                pwm_duty = MIN_PWM_DUTY;
            }
            //SetLightByColorTemp(ColorTemp,Brightness);
        }
        else
        {
            pwm_duty -= 20;
            if(pwm_duty <= 0)
            {
                ONOFF_flag = 0;
                LIGHT_flag = 0;//关机
                ColorTemp = Default_ColorTemp;
                Brightness = 0;
                pwm_duty = MIN_PWM_DUTY;
            }
        }
    }
}



