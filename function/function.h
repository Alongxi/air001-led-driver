#ifndef __FUNCTION_H
#define __FUNCTION_H
#include "main.h"

#define MAX_PWM_DUTY 1200 //最大占空比
#define MIN_PWM_DUTY 60  //最小占空比

#define MAX_ColorTemp 6500 //最大色温
#define MIN_ColorTemp 2700  //最小色温

#define Default_ColorTemp 4000  //默认色温

void function_handle(void);
void key_function(void);
void status_function(void);
#endif /* __MAIN_H */




