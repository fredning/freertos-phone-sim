#include "my_pwm.h"
#include "my_ap3216c.h"
#include "my_led.h"
#include "my_key.h"
#include "tim.h"
#include "string.h"
#include "stdio.h" 
#include "my_led.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "timers.h"
#include "cmsis_os2.h"

char* dec;
extern osMessageQueueId_t myQueue01Handle;
extern osTimerId_t myTimer01Handle;
extern osThreadId_t defaultTaskHandle;
extern osThreadId_t myTask02Handle;
void mypwmfunc(){
    uint16_t als,ps;
    while(1){
        AP3216_Read_ALS_Data(&als);
        AP3216_Read_PS_Data(&ps);
        if(myQueue01Handle!=0){
            if(xQueueSend(myQueue01Handle,&ps,1)!=pdTRUE){
                xQueueReset(myQueue01Handle); 
            }
        } 
        sprintf(dec,"%x",als);
        uint16_t ret=hexToDec(dec);
        pwmon();
        __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,ret);
        if(key_1==down||key_2==down){   
            xTimerReset(myTimer01Handle,100);
        }
    } 
}
uint32_t hexToDec(char *source)
{
    uint32_t sum=0;
    uint32_t t=1;
    int32_t i,len;
    len=strlen(source);
    for(i=len-1;i>=0;i--)
    { 
        sum+=t*getIndexOfSigns(*(source+i));
        t*= 16;
    } 
    return sum;
}

int32_t getIndexOfSigns(uint8_t ch)
{
    if(ch>='0'&&ch<='9')
    {
        return ch-'0';
    }
    if(ch>='A'&&ch<='F') 
    {
        return ch-'A'+10;
    }
    if(ch>='a'&&ch<='f')
    {
        return ch-'a'+10;
    }
    return -1;
}
void mypsfunc(){
    uint16_t ps=0;
	if(myQueue01Handle!=0){
	 if(xQueueReceive(myQueue01Handle,&ps,1)==pdTRUE){
		if(ps>0x1000){
			vTaskDelay(50);
			if(ps>0x1000){
        		ledoff();     //合盖熄屏
				vTaskSuspend(myTask02Handle);
        		pwmoff();     //PWM调光也关闭
        		printf("************屏幕上边界*********\r\n");
        		printf("  \n");
        		printf("  \n");
        		printf("  \n");
        		printf("  \n");
        		printf("  \r\n");
        		printf("************屏幕下边界*********\r\n");
        		printf("已锁屏.  \r\n");
				vTaskSuspend(defaultTaskHandle);
				xQueueReset(myQueue01Handle);
			}
    	}
	 } 
	}
}

