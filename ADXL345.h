#ifndef __ADXL345_H_
#define __ADXL345_H_
void IIC_Init1(void);
void SDA_IN1(void);
void SDA_OUT1(void);
void ADXL345_Start();
void ADXL345_Stop();
void ADXL345_SendByte(uint8_t dat);
uint8_t ADXL345_RecvByte();
void Single_Write_ADXL345(uint8_t REG_Address,uint8_t REG_data);
uint8_t Single_Read_ADXL345(uint8_t REG_Address);
 void Multiple_read_ADXL345(void);
void Init_ADXL345();
 void display_x(void);
 void display_y(void);
 void display_z(void);
 void ADXL345_Work(void);
//  void Angel_data();
#endif