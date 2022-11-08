#include "my_ap3216c.h"
#include "i2c.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "task.h"

uint8_t AP3216_Init(void)
{
	uint8_t ret_value = 0;
	AP3216_WriteOneByte(SYS_CONFIG_ADDR, SYS_SW_RESET);	// 系统软件复位
	HAL_Delay(50);

	AP3216_WriteOneByte(SYS_CONFIG_ADDR, SYS_ALS_PS_IR_ACT);	// IR+PS+ALS三个都激活使用
	HAL_Delay(50);
	ret_value = AP3216_ReadOneByte(SYS_CONFIG_ADDR);	// 读取配置字
	if(ret_value != SYS_ALS_PS_IR_ACT)	// 判断是否与设置的一致
	{
		return 1;
	}
	return 0;
}
uint8_t AP3216_WriteOneByte(uint8_t reg, uint8_t data)
{
	uint16_t write_data = reg | (data<<8);

	if(HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDR | SLAVE_W , (uint8_t*)&write_data, 2,300) != HAL_OK)
	{
		Error_Handler();
	}
	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);

	return 0;
}
uint8_t AP3216_ReadOneByte(uint8_t reg)
{
	uint8_t read_data = 0;

	if(HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDR | SLAVE_W , (uint8_t*)&reg, 1,300) != HAL_OK)
	{
		Error_Handler();
	}
	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);

	 if(HAL_I2C_Master_Receive(&hi2c1, SLAVE_ADDR | SLAVE_R , (uint8_t*)&read_data, 1,200) != HAL_OK)
	{
		Error_Handler();
	} 
    return read_data;
}
void AP3216_Read_PS_Data(uint16_t *pPS)
{
	taskENTER_CRITICAL();
	uint8_t ps_l = 0, ps_h = 0;

	ps_l = AP3216_ReadOneByte(PS_L_ADDR);
	ps_h = AP3216_ReadOneByte(PS_H_ADDR);

	if( (ps_l&0x40)==0x40)
	{
		*pPS = 0;
	}
	else	
	{
		*pPS = ((ps_h&0x1F)<<8) | (ps_l&0x0F);
	}
	taskEXIT_CRITICAL();
}

void AP3216_Read_ALS_Data(uint16_t *pALS)
{ 
	taskENTER_CRITICAL();
	uint8_t als_l = 0, als_h = 0;

	als_l = AP3216_ReadOneByte(ALS_L_ADDR);
	als_h = AP3216_ReadOneByte(ALS_H_ADDR);

	*pALS = (als_h<<8) | (als_l);
	taskEXIT_CRITICAL();
}


