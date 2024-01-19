#include "main.h"
#include "air001_ll_Core_Board.h"

#define KEY_OK          LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_3)
#define KEY_UP          LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_5)
#define KEY_DOWN        LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_6)

uint8_t KEY_UP_FLAG, KEY_DOWN_FLAG, KEY_OK_FLAG = 0;
uint16_t key_hold_ms, key_Dbhold_ms  = 0;

uint8_t KEY_ENTER_FLAG, KEY_QUIT_FLAG, KEY_Dbclick_FLAG = 0;
uint8_t KEY_UP_LONG_FLAG, KEY_UP_SHORT_FLAG = 0;
uint8_t KEY_DOWN_LONG_FLAG, KEY_DOWN_SHORT_FLAG = 0;
uint8_t Key_press_flag = 0;



void MX_GPIO_Init(void)
{
    /* GPIO Ports Clock Enable */
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);

    /* Configure PA5 as input with pull-up */
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_INPUT);
    LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_5, LL_GPIO_PULL_UP);

    /* Configure PA6 as input with pull-up */
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_6, LL_GPIO_MODE_INPUT);
    LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_6, LL_GPIO_PULL_UP);

    /* Configure PB3 as input with pull-up */
    LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_3, LL_GPIO_MODE_INPUT);
    LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_3, LL_GPIO_PULL_UP);

    /* Configure PA0 as push-pull output with default low level */
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_0, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_0, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_0, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_0); // Set the default level to low

    /* Configure PA2 as push-pull output with default low level */
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_2, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_2, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_2, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_2); // Set the default level to low

    /* Configure PA3 as push-pull output with default low level */
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_3, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_3, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_3, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_3); // Set the default level to low

    /* Configure PB2 as push-pull output with default low level */
    LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_2, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_2, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_2, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_2); // Set the default level to low


//    /* Configure PB1 as push-pull output with default low level */
//    LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_1, LL_GPIO_MODE_OUTPUT);
//    LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_1, LL_GPIO_OUTPUT_PUSHPULL);
//    LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_1, LL_GPIO_SPEED_FREQ_HIGH);
//    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_1); // Set the default level to low
}


void key_press_handle(void)
{
    if(0 == KEY_UP)
    {
        KEY_UP_FLAG = 1;

    }
    else
    {
        KEY_UP_FLAG = 0;
    }
    if(0 == KEY_DOWN)
    {

        KEY_DOWN_FLAG = 1;
    }
    else
    {
        KEY_DOWN_FLAG = 0;
    }
    if(0 == KEY_OK)
    {

        KEY_OK_FLAG = 1;
    }
}
//按键处理函数 将三个按键长按短按转换成六个状态
void key_handle(void)
{
    if(Key_press_flag != 0)
    {
        key_Dbhold_ms++;
        if(key_Dbhold_ms > 9999)  //限幅
        {
            key_Dbhold_ms = 9999;
        }
    }
    else
    {
        key_Dbhold_ms = 0;
    }

    if(KEY_OK_FLAG == 1)
    {
        if(KEY_OK == 0)
        {
            key_hold_ms++; //假如一直保持按下状态

            if(key_hold_ms > 9999)  //限幅
            {
                key_hold_ms = 9999;
            }

            if(key_hold_ms == KEEP_ENTER_MS)  //长按
            {
                KEY_QUIT_FLAG = 1;
                Key_press_flag = 0;
                KEY_OK_FLAG = 0;
            }

            if(Key_press_flag == 1)
            {
                Key_press_flag = 2;
            }
        }
        else
        {
            if((key_hold_ms < 500) && (key_hold_ms > 20))
            {
                if(Key_press_flag == 0)
                {
                    Key_press_flag = 1;
                }
            }
            else if((key_hold_ms > 500) && (key_hold_ms < KEEP_ENTER_MS))
            {
                if(Key_press_flag != 1)
                {
                    KEY_ENTER_FLAG = 1;
                    key_Dbhold_ms = 0;
                    key_hold_ms = 0;
                    Key_press_flag = 0;
                    KEY_OK_FLAG = 0;
                }
            }
            else
            {
                key_hold_ms = 0;
            }

            if(key_Dbhold_ms > 200)
            {
                if(Key_press_flag == 1)
                {
                    KEY_ENTER_FLAG = 1;
                    key_Dbhold_ms = 0;
                    key_hold_ms = 0;
                    Key_press_flag = 0;
                    KEY_OK_FLAG = 0;
                }
                else if(Key_press_flag == 2)
                {
                    KEY_Dbclick_FLAG = 1;
                    key_Dbhold_ms = 0;
                    key_hold_ms = 0;
                    Key_press_flag = 0;
                    KEY_OK_FLAG = 0;
                }
                else
                {
                    KEY_OK_FLAG = 0;
                }
            }
        }
    }

    //--------------------------------------------------------//

    if(KEY_UP_FLAG == 1)
    {
        if(KEY_UP == 0)
        {

            if(key_hold_ms <= KEEP_MS)
            {
                key_hold_ms ++;//假如一直保持按下状态
            }
            else if(key_hold_ms > KEEP_MS)//长按
            {
                key_hold_ms = 0;
                KEY_UP_LONG_FLAG = 1;
                KEY_UP_FLAG = 0;
            }
        }

    }
//    else//KEY_DOWN_FLAG = 0
//    {
//        if(KEY_UP != 0)
//        {
//            KEY_UP_LONG_FLAG = 0;
//        }
//    }

    //--------------------------------------------------------//
    if(KEY_DOWN_FLAG == 1)
    {

        if(KEY_DOWN == 0)
        {

            if(key_hold_ms <= KEEP_MS)
            {
                key_hold_ms ++;//假如一直保持按下状态
            }
            else if(key_hold_ms > KEEP_MS)//长按
            {
                key_hold_ms = 0;
                KEY_DOWN_LONG_FLAG = 1;
                KEY_DOWN_FLAG = 0;
            }
        }


    }
//    else//KEY_DOWN_FLAG = 0
//    {
//        if(KEY_DOWN != 0)
//        {
//            KEY_DOWN_LONG_FLAG = 0;
//        }
//    }

}



