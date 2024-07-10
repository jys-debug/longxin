#include "oled.h"
#include "iic.h"
#include "ls1x_latimer.h"
#include "UserGpio.h"
#include "math.h"
uint8_t BUF[8];
char str1[50];
char str2[50];
char str3[50];
char str4[50];
short jiasu[3];
float angel_xyz[3];
extern int fanzhuan1;
void IIC_Init1(void)
{ 
	gpio_pin_remap(GPIO_PIN_4, GPIO_FUNC_GPIO);
	gpio_pin_remap(GPIO_PIN_5, GPIO_FUNC_GPIO);

	gpio_set_direction(GPIO_PIN_4, GPIO_Mode_Out);  
	gpio_set_direction(GPIO_PIN_5, GPIO_Mode_Out); 

	// 初始上拉，I2C默认空闲状态
	I2C_SCL1_HIGH;
	I2C_SDA1_HIGH;
}

void SDA_IN1(void)
{
	gpio_set_direction(I2C_Soft1_SDA, GPIO_Mode_In); // 配置输入模式
}

void SDA_OUT1(void)
{
	gpio_set_direction(I2C_Soft1_SDA, GPIO_Mode_Out); // 配置输出模式
	I2C_SDA1_HIGH;
}

void ADXL345_Start()
{
I2C_SCL1_HIGH;
I2C_SDA1_HIGH;
delay_us(8);
I2C_SDA1_LOW;
delay_us(8);
I2C_SCL1_LOW;

}
void ADXL345_Stop()
{
I2C_SDA1_LOW;
I2C_SCL1_LOW;
delay_us(8);
I2C_SCL1_HIGH;
I2C_SDA1_HIGH;
delay_us(8);
}
void ADXL345_SendByte(uint8_t dat)
{
   uint8_t i;

    for (i=0; i<8; i++)         
    {
     if((dat<<i)&0x80)
     {I2C_SDA1_HIGH;}
	else {I2C_SDA1_LOW;}
	delay_us(4);
	I2C_SCL1_HIGH;
	delay_us(4);
	I2C_SCL1_LOW;
	delay_us(4);
    }  
}
uint8_t ADXL345_RecvByte(uint8_t ack)
{
uint8_t dat=0,i;
SDA_IN1();
I2C_SDA1_HIGH;
delay_us(60);
for(i=0;i<8;i++)
{
I2C_SCL1_LOW;
delay_us(8);
I2C_SCL1_HIGH;
delay_us(4);
dat<<=1;
if(I2C_SDA1_READ)dat++;
delay_us(4);
}
SDA_OUT1();
if(!ack)
IIC_NAck1();
else
IIC_Ack1();
return dat;
}
void Single_Write_ADXL345(uint8_t REG_Address,uint8_t REG_data)
{
    ADXL345_Start();                 
    ADXL345_SendByte(0XA6);
    IIC_Wait1_Ack();   
    ADXL345_SendByte(REG_Address);
    IIC_Wait1_Ack();    
    ADXL345_SendByte(REG_data);
    IIC_Wait1_Ack();       
    ADXL345_Stop();
    delay_ms(10);                   
}
uint8_t Single_Read_ADXL345(uint8_t REG_Address)
{  uint8_t REG_data;
    ADXL345_Start();                          
    ADXL345_SendByte(0XA6);
    IIC_Wait1_Ack();           
    ADXL345_SendByte(REG_Address);            	
    IIC_Wait1_Ack();
    ADXL345_Start();                          
    ADXL345_SendByte(0XA7);
    IIC_Wait1_Ack();         
    REG_data=ADXL345_RecvByte(0);   
	ADXL345_Stop();                           
    return REG_data; 
}
void Multiple_read_ADXL345(void)
{   
    uint8_t i;
    for(i=0;i<6;i++)
    {
    BUF[i]=Single_Read_ADXL345(0X32+i);
    }

}

void Init_ADXL345()
{
   IIC_Init1();
   Single_Write_ADXL345(0x31,0x0B);   
   Single_Write_ADXL345(0x2C,0x0A);   
   Single_Write_ADXL345(0x2E,0x00);   
   Single_Write_ADXL345(0x1D,0x0F);  
   Single_Write_ADXL345(0x21,0xFF);   
   Single_Write_ADXL345(0x2F,0x00);   
   Single_Write_ADXL345(0x2A,0x07);
   Single_Write_ADXL345(0x2E,0x40); 
   Single_Write_ADXL345(0x2D,0x08); 
   Single_Write_ADXL345(0x1E,0x00);
   Single_Write_ADXL345(0x1F,0x00); 
   Single_Write_ADXL345(0x20,0x05);

   delay_ms(500);     
}
void display_x(void)
{   

    jiasu[0]=(BUF[1]<<8)+BUF[0];
    if(jiasu[0]<0)
    {
    jiasu[0]=-jiasu[0];
    jiasu[0]=4*jiasu[0];
    // sprintf(str1,"-%4d",jiasu[0]);   
    // OLED_Show_Str(0,6,str1,16);
    }
    else
    {
    jiasu[0]=4*jiasu[0];
    // sprintf(str1,"+%4d",jiasu[0]);   
    // OLED_Show_Str(0,6,str1,16);
    }
    
}
void display_y(void)
{   
      
    jiasu[1]=(BUF[3]<<8)+BUF[2];
    if(jiasu[1]<0)
    {
        jiasu[1]=-jiasu[1];
        jiasu[1]=4*jiasu[1];
    // sprintf(str2, "-%4d",jiasu[1]);   
    // OLED_Show_Str(0,2,str2,16);
    }
    else
    {
    jiasu[1]=4*jiasu[1];
    // sprintf(str2, "+%4d",jiasu[1]);   
    // OLED_Show_Str(0,2,str2,16);
    }
    
}
void display_z(void)
{   
     
       
    jiasu[2]=(BUF[5]<<8)+BUF[4];
    if(jiasu[2]<0)
    {
        jiasu[2]=-jiasu[2];
        jiasu[2]=4*jiasu[2];
    sprintf(str3, "-%4d",jiasu[2]);   
    OLED_Show_Str(0,6,str3,16);
    }
    else
    {
    jiasu[2]=4*jiasu[2];
    sprintf(str3, "+%4d",jiasu[2]);   
    OLED_Show_Str(0,6,str3,16);
    }
}
// void Angel_data()
// {
    
    
//     angel_xyz[0]=(((atan2(jiasu[2],jiasu[0])*180)/3.14159265)+180);    
// 	angel_xyz[1]=(((atan2(jiasu[2],jiasu[1])*180)/3.14159265)+180);    
// 	angel_xyz[2]=(((atan2(jiasu[0],jiasu[2])*180)/3.14159265)+180);


// }
void ADXL345_Work(void)
{
   if(fanzhuan1==1) 
    { Multiple_read_ADXL345();
     display_x();
     display_y();
     display_z();
    //  Angel_data();
    fanzhuan1=0;
    }
}
        