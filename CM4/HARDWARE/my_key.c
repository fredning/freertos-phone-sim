#include "my_key.h"
#include "my_led.h"
#include "stdbool.h"
#include "string.h"

char code[5]={'@','@','@','@'};
char temp[11]={'0','1','2','3','4','5','6','7','8','9'};
char rightcode[]="1234";
void mycodefuc(){
    printf("*************************\r\n"); 
    printf("请输入密码，按KEY2确定。\r\n");
    printf("  \n");
    printf("  \n");
    printf("  \n");
    printf("  \n");
    printf("  \r\n");
    printf("*************************\r\n");
    //print();
    uint8_t i=0,j=0;
    bool flag1=false,flag2=false;
    while(i<5){
        if(key_1==down){
            HAL_Delay(5);
            if(key_1==down){
            flag1=true;
            if(flag1==true){
            if(j==11)   code[i]=temp[0];
            else   {
                code[i]=temp[j++];
                myprint();
            }
            }
            HAL_Delay(500);
            flag1=false; 
        }
        }
        if(key_2==down){
             HAL_Delay(5);
             if(key_2==down){
             i++;
             j=0;
             myprint();
             HAL_Delay(500);
        }
        
        }
    }
    if(i==5&&strcmp(code,rightcode)!=0)     printf("密码错误!请重新输入\r\n"),mycodefuc();
    if(i==5)    ledon();
    return 0;
    

}
void myprint(){
    for(int i=0;code[i]!='\0';i++)   
        printf("%c",code[i]);
    printf("\r\n");
}

