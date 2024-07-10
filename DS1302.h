
// #ifndef __DS1302_H 
// #define __DS1302_H  
 
// #include "test.h" 
 
// #define CE_L gpio_write_pin(GPIO_PIN_40,0)//拉低使能位
// #define CE_H GPIO_SetBits(GPIO_PIN_40,1)//拉高使能位
// #define SCLK_L GPIO_ResetBits(GPIO_PIN_18,0)//拉低时钟线
// #define SCLK_H  GPIO_SetBits(GPIO_PIN_18,1)//拉高时钟线
// #define DATA_L  GPIO_ResetBits(GPIO_PIN_19,0)//拉低数据线
// #define DATA_H  GPIO_SetBits(GPIO_PIN_19,1)//拉高数据线
 
// struct TIMEData
// {
// 	u16 year;
// 	u8  month;
// 	u8  day;
// 	u8  hour;
// 	u8  minute;
// 	u8  second;
// 	u8  week;
// };//创建TIMEData结构体方便存储时间日期数据
// extern struct TIMEData TimeData;//全局变量
// void ds1302_gpio_init();//ds1302端口初始化
// void ds1302_write_onebyte(u8 data);//向ds1302发送一字节数据
// void ds1302_wirte_rig(u8 address,u8 data);//向指定寄存器写一字节数据
// u8 ds1302_read_rig(u8 address);//从指定寄存器读一字节数据
// void ds1032_init();//ds1302初始化函数
// void ds1032_DATAOUT_init();//IO端口配置为输出
// void ds1032_DATAINPUT_init();//IO端口配置为输入
// void ds1032_read_time();//从ds1302读取实时时间（BCD码）
// void ds1032_read_realTime();//将BCD码转化为十进制数据
// void Ds1302_Work(void);
// void Ds1302_Init(void);
 
// #endif