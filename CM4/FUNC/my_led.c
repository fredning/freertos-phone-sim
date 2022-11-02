#include "my_led.h"
#include "gpio.h"
#include "tim.h"
#include "usart.h"
#include "stdio.h"


void ledon(){
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,GPIO_PIN_RESET);
    
}
void ledoff(){
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,GPIO_PIN_SET);
}
void pwm1on(){
    PWM_Func1();
    HAL_TIM_Base_Start_IT(&htim2);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
    //printf("低功耗模式：  关闭\r\n");
    //printf("*************************\r\n");
}
void pwm2on(){
    PWM_Func2();
    HAL_TIM_Base_Start_IT(&htim2);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
}
