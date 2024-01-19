#include "function.h"


uint8_t ONOFF_flag = 0;//���ػ�flag
uint8_t LIGHT_flag = 0;//Ĭ��ȫ��   1���׵�   2���Ƶ�    3���ư�ͬʱ��
uint8_t Func_flag = 0;//���嵱ǰ������������ģʽ   0 Ĭ��ģʽ   1 ����ģʽ ��ģʽֻ�����������,���еƹ�Ĭ������������У����򿪷���
uint16_t ColorTemp = Default_ColorTemp;
float Brightness = 0;//����






// ����ɫ�¼��� PWM ռ�ձȲ����Ƶƹ�
//ɫ�¡�����
// ����ɫ�¼��� PWM ռ�ձȲ����Ƶƹ�
void SetLightByColorTemp(uint16_t u16ColorTemp, float brightness)
{
    uint16_t u8Ratio;

    // ���� PWM ռ�ձȵı���
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

    // ���� PWM ռ�ձ�
    LL_TIM_OC_SetCompareCH2(TIM3, (uint16_t)(u8Ratio * brightness) + MIN_PWM_DUTY);
    LL_TIM_OC_SetCompareCH3(TIM3, (uint16_t)((MAX_PWM_DUTY - u8Ratio) * brightness) + MIN_PWM_DUTY);
}

void function_handle(void)//���ܺ���
{

    if(pwm_duty > MAX_PWM_DUTY / 2) //����50%���ʿ�������
    {
        LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_2);
    }
    else
    {
        LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_2);
    }
    switch(LIGHT_flag)
    {

    case 0://�ر����еƹ�
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


    if(KEY_ENTER_FLAG == 1)//�̰��м�
    {
        if(LIGHT_flag != 4)
        {
            if(ONOFF_flag == 2)
            {
                LIGHT_flag++;
                if(LIGHT_flag > 3)
                {
                    LIGHT_flag = 1;//�̰���ʱ���ڰ� ��  �׻�����״̬��ѭ��������ػ�   ֻ�г����м��Ż����ػ�
                }
            }
        }
        KEY_ENTER_FLAG = 0;
    }
    if(KEY_QUIT_FLAG == 1)//�����м�
    {
        if(ONOFF_flag == 2) //�Ѿ�����
        {
            if(Func_flag == 0)
            {
                ONOFF_flag = 3;//�����ػ�
            }
        }
        else if(ONOFF_flag == 0) //�ػ�״̬��
        {

            Func_flag = 0;
            ONOFF_flag = 1;//��������
            LIGHT_flag = 3;
        }
        KEY_QUIT_FLAG = 0;
    }

    if(KEY_Dbclick_FLAG == 1)//˫��
    {

        if(ONOFF_flag == 2) //�Ѿ�����
        {
            if(Func_flag == 1)
            {
                ONOFF_flag = 3;//�����ػ�

            }
        }
        else if(ONOFF_flag == 0) //�ػ�״̬��
        {

            Func_flag = 1;
            ONOFF_flag = 1;//��������
            LIGHT_flag = 4;//ȫ��ģʽ ��ģʽ��ֻ���Ե����� �����Ե�ɫ��
            pwm_duty = MIN_PWM_DUTY;

        }
        //DDL_Printf("˫��,ʱ��:%d ms  ��־λ��%d\r\n", READ_key_hold_ms, READ_Key_press_flag);
        KEY_Dbclick_FLAG = 0;
    }


}
void key_function(void)
{

    if((KEY_QUIT_FLAG != 1) && (KEY_Dbclick_FLAG != 1) && (KEY_ENTER_FLAG != 1) && (ONOFF_flag == 2))//����ʽ����״̬��  ��ʹ���м�ʱ ��������Ч
    {
        if(KEY_UP_LONG_FLAG == 1)//�����ϼ�
        {
            //DDL_Printf("�̰��ϼ�\r\n");
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
        if(KEY_DOWN_LONG_FLAG == 1)//�����¼�
        {
            //DDL_Printf("�̰��¼�\r\n");
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
void status_function(void)//���ػ�״̬���ܺ���
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
                ONOFF_flag = 2;//��ʽ����ϵͳ

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
                ONOFF_flag = 2;//��ʽ����ϵͳ
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
                LIGHT_flag = 0;//�ػ�
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
                LIGHT_flag = 0;//�ػ�
                ColorTemp = Default_ColorTemp;
                Brightness = 0;
                pwm_duty = MIN_PWM_DUTY;
            }
        }
    }
}



