#include "my_pwm.h"
#include "my_ap3216c.h"
#include "my_led.h"
#include "tim.h"
#include "string.h"
#include "stdio.h" 


char* temp11;
void mypwmfunc(){
    uint16_t als;
    AP3216_Read_ALS_Data(&als);
    sprintf(temp11,"%x",als);
    uint16_t ret=hexToDec(temp11);
    printf("ret=%d\r\n",ret);
    pwm1on();
    __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,ret*mypresclar);
    //printf("als=%x\r\n",als);
    return 0;
}

long hexToDec(char *source)
{
    long sum = 0;
    long t = 1;
    int i, len;
 
    len = strlen(source);
    for(i=len-1; i>=0; i--)
    { 
        sum += t * getIndexOfSigns(*(source + i));
        t *= 16;
    }  
 
    return sum;
}

int getIndexOfSigns(char ch)
{
    if(ch >= '0' && ch <= '9')
    {
        return ch - '0';
    }
    if(ch >= 'A' && ch <='F') 
    {
        return ch - 'A' + 10;
    }
    if(ch >= 'a' && ch <= 'f')
    {
        return ch - 'a' + 10;
    }
    return -1;
}
