#include "my_led.h"
#include "gpio.h"
#include "tim.h"

void ledon(){
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,GPIO_PIN_RESET);
    
}
void ledoff(){
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,GPIO_PIN_SET);
    
}
void pwmon(){
    pwmmode1();
    HAL_TIM_Base_Start_IT(&htim2);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
}
void pwmoff(){
    pwmmode2();
    HAL_TIM_Base_Start_IT(&htim2);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
}
 