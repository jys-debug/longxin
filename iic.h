#ifndef __IIC_H
#define __IIC_H



#include "ls1x_gpio.h"
#include "ls1x_latimer.h"



// #define I2C_Soft_SCL GPIO_PIN_1
// #define I2C_Soft_SDA GPIO_PIN_57
 
#define I2C_Soft_SCL GPIO_PIN_57
#define I2C_Soft_SDA GPIO_PIN_1

#define I2C_SCL_LOW     gpio_write_pin(I2C_Soft_SCL, 0);
#define I2C_SCL_HIGH 	gpio_write_pin(I2C_Soft_SCL, 1);
#define I2C_SDA_LOW  	gpio_write_pin(I2C_Soft_SDA, 0);
#define I2C_SDA_HIGH	gpio_write_pin(I2C_Soft_SDA, 1);
#define I2C_SDA_READ	gpio_get_pin(I2C_Soft_SDA)

#define I2C_Soft1_SCL GPIO_PIN_4
#define I2C_Soft1_SDA GPIO_PIN_5

#define I2C_SCL1_LOW     gpio_write_pin(I2C_Soft1_SCL, 0);
#define I2C_SCL1_HIGH 	gpio_write_pin(I2C_Soft1_SCL, 1);
#define I2C_SDA1_LOW  	gpio_write_pin(I2C_Soft1_SDA, 0);
#define I2C_SDA1_HIGH	gpio_write_pin(I2C_Soft1_SDA, 1);
#define I2C_SDA1_READ	gpio_get_pin(I2C_Soft1_SDA)


//IIC所有操作函数
void IIC_Delay(void);				        
void IIC_Init(void);                        				 
void IIC_Start(void);				       
void IIC_Stop(void);	  			        
void IIC_Send_Byte(uint8_t txd);			
uint8_t IIC_Read_Byte(unsigned char ack);   
uint8_t IIC_Wait_Ack(void); 				
void IIC_Ack(void);					        
void IIC_NAck(void);				        
void IIC_NAck1(void);
void IIC_Ack1(void);
uint8_t IIC_Wait1_Ack(void);
#endif 
