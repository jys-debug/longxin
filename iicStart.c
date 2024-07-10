#include "iicStart.h"
#include "test.h"
#include "UserGpio.h"
#include "ls1x_latimer.h"

#define theclock  GPIO_PIN_2
#define thedata   GPIO_PIN_3
#define I2C_SCL_1  gpio_write_pin(theclock,1)				/* SCL = 1 */
#define I2C_SCL_0  gpio_write_pin(theclock,0)				/* SCL = 0 */
#define I2C_SDA_1  gpio_write_pin(thedata,1)				/* SDA = 1 */
#define I2C_SDA_0  gpio_write_pin(thedata,0)				/* SDA = 0 */
#define I2C_SDA_READ1  gpio_get_pin(thedata)	
#define I2C_SCL_READ1  gpio_get_pin(theclock)	

/*
*********************************************************************************************************
*	函 数 名: bsp_InitI2C
*	功能说明: 配置I2C总线的GPIO，采用模拟IO的方式实现
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_InitI2C(void)
{
	gpio_pin_remap(theclock, GPIO_FUNC_GPIO);
	gpio_pin_remap(thedata, GPIO_FUNC_GPIO);

	gpio_set_direction(theclock, GPIO_Mode_Out);  
	gpio_set_direction(thedata, GPIO_Mode_Out); 


	I2C_SCL_1;
	I2C_SDA_1;
}

void SDA_INX(void)
{
	gpio_set_direction(thedata, GPIO_Mode_In); // 配置输入模式
}

void SDA_OUTX(void)
{
	gpio_set_direction(thedata, GPIO_Mode_Out); // 配置输出模式
	I2C_SDA_1;
}

void i2c_Start(void)
{
	/* 当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号 */
	I2C_SDA_1;
	I2C_SCL_1;
	delay_us(4);
	I2C_SDA_0;
	delay_us(4);
	I2C_SCL_0;
	delay_us(4);
}

/*
*********************************************************************************************************
*	函 数 名: i2c_Start
*	功能说明: CPU发起I2C总线停止信号
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void i2c_Stop(void)
{
	/* 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号 */
	I2C_SDA_0;
	I2C_SCL_1;
	delay_us(4);
	I2C_SDA_1;
	delay_us(4);
}

/*
*********************************************************************************************************
*	函 数 名: i2c_SendByte
*	功能说明: CPU向I2C总线设备发送8bit数据
*	形    参:  _ucByte ： 等待发送的字节
*	返 回 值: 无
*********************************************************************************************************
*/
void i2c_SendByte(uint8_t _ucByte)
{
	uint8_t i;

	/* 先发送字节的高位bit7 */
	for (i = 0; i < 8; i++)
	{
		if (_ucByte & 0x80)
		{
			I2C_SDA_1;
		}
		else
		{
			I2C_SDA_0;
		}
		delay_us(4);
		I2C_SCL_1;
		delay_us(4);
		I2C_SCL_0;
		if (i == 7)
		{
			 I2C_SDA_1; // 释放总线
		}
		_ucByte <<= 1;	/* 左移一个bit */
		delay_us(4);
	}
}

/*
*********************************************************************************************************
*	函 数 名: i2c_ReadByte
*	功能说明: CPU从I2C总线设备读取8bit数据
*	形    参:  无
*	返 回 值: 读到的数据
*********************************************************************************************************
*/
uint8_t i2c_ReadByte(void)
{
	uint8_t i;
	uint8_t value;

	/* 读到第1个bit为数据的bit7 */
	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		I2C_SCL_1;
		delay_us(4);
		if (I2C_SDA_READ1)
		{
			value++;
		}
		I2C_SCL_0;
		delay_us(4);
	}
	return value;
}

/*
*********************************************************************************************************
*	函 数 名: i2c_WaitAck
*	功能说明: CPU产生一个时钟，并读取器件的ACK应答信号
*	形    参:  无
*	返 回 值: 返回0表示正确应答，1表示无器件响应
*********************************************************************************************************
*/
uint8_t i2c_WaitAck(void)
{
	uint8_t re;

	I2C_SDA_0;	/* CPU释放SDA总线 */  //让它必须应答  自己修改的
	delay_us(4);
	I2C_SCL_1;	/* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
	delay_us(4);
	
	re = I2C_SDA_READ1;/* CPU读取SDA口线状态 */

	I2C_SCL_0;
	delay_us(4);
	return re;
}

/*
*********************************************************************************************************
*	函 数 名: i2c_Ack
*	功能说明: CPU产生一个ACK信号
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void i2c_Ack(void)
{
	I2C_SDA_0;	/* CPU驱动SDA = 0 */
	delay_us(4);
	I2C_SCL_1;	/* CPU产生1个时钟 */
	delay_us(4);
	I2C_SCL_0;
	delay_us(4);
	I2C_SDA_1;	/* CPU释放SDA总线 */
}

/*
*********************************************************************************************************
*	函 数 名: i2c_NAck
*	功能说明: CPU产生1个NACK信号
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void i2c_NAck(void)
{
	I2C_SDA_1;	/* CPU驱动SDA = 1 */
	delay_us(4);
	I2C_SCL_1;	/* CPU产生1个时钟 */
	delay_us(4);
	I2C_SCL_0;
	delay_us(4);
}

/*
*********************************************************************************************************
*	函 数 名: i2c_CheckDevice
*	功能说明: 检测I2C总线设备，CPU向发送设备地址，然后读取设备应答来判断该设备是否存在
*	形    参:  _Address：设备的I2C总线地址
*	返 回 值: 返回值 0 表示正确， 返回1表示未探测到
*********************************************************************************************************
*/
uint8_t i2c_CheckDevice(uint8_t _Address)
{
	uint8_t ucAck;

	if (I2C_SDA_READ1 && I2C_SCL_READ1)
	{
		i2c_Start();		/* 发送启动信号 */

		/* 发送设备地址+读写控制bit（0 = w， 1 = r) bit7 先传 */
		i2c_SendByte(_Address | I2C_WR);
		ucAck = i2c_WaitAck();	/* 检测设备的ACK应答 */

		i2c_Stop();			/* 发送停止信号 */

		return ucAck;
	}
	return 1;	/* I2C总线异常 */
}

/*
*********************************************************************************************************
*	函 数 名: i2c_Start
*	功能说明: CPU发起I2C总线启动信号
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/


// void i2c_Start(void)
// {
// 	/* 当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号 */
// 	I2C_SDA_1;
// 	I2C_SCL_1;
// 	delay_us(8);
// 	I2C_SDA_0;
// 	delay_us(8);
// 	I2C_SCL_0;
// }

// /*
// *********************************************************************************************************
// *	函 数 名: i2c_Start
// *	功能说明: CPU发起I2C总线停止信号
// *	形    参:  无
// *	返 回 值: 无
// *********************************************************************************************************
// */
// void i2c_Stop(void)
// {
// 	/* 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号 */
// 	I2C_SDA_0;
// 	I2C_SCL_0;
// 	delay_us(8);
// 	I2C_SDA_1;
// 	I2C_SCL_1;
// 	delay_us(8);
// }

// /*
// *********************************************************************************************************
// *	函 数 名: i2c_SendByte
// *	功能说明: CPU向I2C总线设备发送8bit数据
// *	形    参:  _ucByte ： 等待发送的字节
// *	返 回 值: 无
// *********************************************************************************************************
// */
// void i2c_SendByte(uint8_t _ucByte)
// {
// 	uint8_t i;

//     for (i=0; i<8; i++)         
//     {
//      if((_ucByte<<i)&0x80)
//      {I2C_SDA_1;}
// 	else {I2C_SDA_0;}
// 	delay_us(4);
// 	I2C_SCL_1;
// 	delay_us(4);
// 	I2C_SCL_0;
// 	delay_us(4);
//     }  
// }

// /*
// *********************************************************************************************************
// *	函 数 名: i2c_ReadByte
// *	功能说明: CPU从I2C总线设备读取8bit数据
// *	形    参:  无
// *	返 回 值: 读到的数据
// *********************************************************************************************************
// */
// uint8_t i2c_ReadByte(void)
// {
// 	uint8_t i;
// 	uint8_t value=0;
//     SDA_INX();
//     I2C_SDA_1;
//     delay_us(60);
// 	for (i = 0; i < 8; i++)
// 	{
		
// 		I2C_SCL_0;
//         delay_us(8);
//         I2C_SCL_1;
//         delay_us(4);
//         value<<=1;
//      if(I2C_SDA_READ1)value++;
//        delay_us(4);
     
// 	}
// 	return value;
// }

// /*
// *********************************************************************************************************
// *	函 数 名: i2c_WaitAck
// *	功能说明: CPU产生一个时钟，并读取器件的ACK应答信号
// *	形    参:  无
// *	返 回 值: 返回0表示正确应答，1表示无器件响应
// *********************************************************************************************************
// */
// uint8_t i2c_WaitAck(void)
// {
// 	uint8_t ucErrTime = 0;
// 	SDA_INX(); // SDA设置为输入
// 	I2C_SDA_1;
// 	delay_us(4);
// 	I2C_SCL_1;
// 	delay_us(4);
// 	while (I2C_SDA_READ1)
// 	{
// 		ucErrTime++;
// 		if (ucErrTime > 250)
// 		{
// 			i2c_Stop();
// 			SDA_OUTX();
// 			return 1;
// 		}
// 	}
// 	I2C_SCL_0;
// 	SDA_OUTX();
// 	return 0;
// }

// /*
// *********************************************************************************************************
// *	函 数 名: i2c_Ack
// *	功能说明: CPU产生一个ACK信号
// *	形    参:  无
// *	返 回 值: 无
// *********************************************************************************************************
// */
// void i2c_Ack(void)
// {
// 	I2C_SCL_0;
// 	delay_us(8);
// 	I2C_SDA_1;
// 	delay_us(8);
// 	I2C_SDA_0;
// 	delay_us(8);
// 	I2C_SCL_1;
// 	delay_us(8);
// 	I2C_SCL_0;
// 	delay_us(8);
// 	I2C_SDA_1;
// 	delay_us(8);
// }

// /*
// *********************************************************************************************************
// *	函 数 名: i2c_NAck
// *	功能说明: CPU产生1个NACK信号
// *	形    参:  无
// *	返 回 值: 无
// *********************************************************************************************************
// */
// void i2c_NAck(void)
// {
// 	I2C_SCL_0;
// 	delay_us(8);
// 	I2C_SDA_1;
// 	delay_us(8);
// 	I2C_SCL_1;
// 	delay_us(8);
// 	I2C_SCL_0;
// 	delay_us(8);
// 	I2C_SDA_0;
// 	delay_us(8);
// }

// /*
// *********************************************************************************************************
// *	函 数 名: i2c_CheckDevice
// *	功能说明: 检测I2C总线设备，CPU向发送设备地址，然后读取设备应答来判断该设备是否存在
// *	形    参:  _Address：设备的I2C总线地址
// *	返 回 值: 返回值 0 表示正确， 返回1表示未探测到
// *********************************************************************************************************
// */
// uint8_t i2c_CheckDevice(uint8_t _Address)
// {
// 	uint8_t ucAck;

// 	if (I2C_SDA_READ1 && I2C_SCL_READ1)
// 	{
// 		i2c_Start();		/* 发送启动信号 */

// 		/* 发送设备地址+读写控制bit（0 = w， 1 = r) bit7 先传 */
// 		i2c_SendByte(_Address | I2C_WR);
// 		ucAck = i2c_WaitAck();	/* 检测设备的ACK应答 */

// 		i2c_Stop();			/* 发送停止信号 */

// 		return ucAck;
// 	}
// 	return 1;	/* I2C总线异常 */
// }

