#ifndef __MY_AP3216C_H
#define __MY_AP3216C_H


#include "main.h"

#define SLAVE_ADDR   (0x3c)
#define SLAVE_W      (0x00)
#define SLAVE_R      (0x01)



#define SYS_CONFIG_ADDR			(0x00)	
#define IR_L_ADDR               (0X0A)
#define IR_H_ADDR               (0X0B)
#define ALS_L_ADDR              (0X0C)
#define ALS_H_ADDR              (0X0D)
#define PS_L_ADDR               (0X0E)
#define PS_H_ADDR               (0X0F)


#define SYS_POWER_DOWN			(0x00)	
#define SYS_ALS_ACT				(0x01)  
#define SYS_PS_IR_ACT			(0x02)	
#define SYS_ALS_PS_IR_ACT		(0x03)
#define SYS_SW_RESET			(0x04)

uint8_t AP3216_Init(void);
void AP3216_ReadDataTest(void);
uint8_t AP3216_ReadOneByte(uint8_t reg);
uint8_t AP3216_WriteOneByte(uint8_t reg, uint8_t data);
void AP3216_Read_IR_Data(uint16_t *pIR);
void AP3216_Read_PS_Data(uint16_t *pPS);
void AP3216_Read_ALS_Data(uint16_t *pALS);
void my_i2cfunc(void);



#endif
