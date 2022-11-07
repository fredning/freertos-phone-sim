#ifndef __MY_KEY_H__
#define __MY_KEY_H__

#include "main.h"

#define key_1 HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_2)
#define key_2 HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_3)

#define down GPIO_PIN_RESET
#define up GPIO_PIN_SET

void mycodefuc(void);
void myprint(void);
#endif
