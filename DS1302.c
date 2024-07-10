// #include "DS1302.h"
// #include "test.h"
// #include "ls1x_latimer.h"
// #include "UserGpio.h"
// #include "oled.h"
// struct TIMEData TimeData;
// u8 read_time[7];
// u8 min=0;
// char str1[50];
// char str2[50];
// char str3[50];
// char str4[50];
// char str5[50];
// char str6[50];
// char str7[50];
// void ds1302_gpio_init()//CE,SCLK端口初始化
// {
// 	gpio_pin_remap(GPIO_PIN_40, GPIO_FUNC_GPIO);
// 	gpio_pin_remap(GPIO_PIN_18, GPIO_FUNC_GPIO);

// 	gpio_set_direction(GPIO_PIN_40, GPIO_Mode_Out);  
// 	gpio_set_direction(GPIO_PIN_18, GPIO_Mode_Out); 
// }
 
// void ds1032_DATAOUT_init()//配置双向I/O端口为输出态
// {
// gpio_set_direction(GPIO_PIN_19, GPIO_Mode_Out); // 配置输入模式
// }
 
// void ds1032_DATAINPUT_init()//配置双向I/O端口为输入态
// {
// gpio_set_direction(GPIO_PIN_19, GPIO_Mode_In); // 配置输入模式
// }
 
 
// void ds1302_write_onebyte(u8 data)//向DS1302发送一字节数据
// {
// ds1032_DATAOUT_init();
// u8 count=0;
// SCLK_L;
// for(count=0;count<8;count++)
// 	{	SCLK_L;
// 		if(data&0x01)
// 		{DATA_H;}
// 		else{DATA_L;}//先准备好数据再发送
// 		SCLK_H;//拉高时钟线，发送数据
// 		data>>=1;
// 	}
// }
 
// void ds1302_wirte_rig(u8 address,u8 data)//向指定寄存器地址发送数据
// {
// u8 temp1=address;
// u8 temp2=data;
// CE_L;SCLK_L;delay_us(1);
// CE_H;delay_us(2);
// ds1302_write_onebyte(temp1);
// ds1302_write_onebyte(temp2);
// CE_L;SCLK_L;delay_us(2);
// }
 
// u8 ds1302_read_rig(u8 address)//从指定地址读取一字节数据
// {
// u8 temp3=address;
// u8 count=0;
// u8 return_data=0x00;
// CE_L;SCLK_L;delay_us(3);
// CE_H;delay_us(3);
// ds1302_write_onebyte(temp3);
// ds1032_DATAINPUT_init();//配置I/O口为输入
// delay_us(2);
// for(count=0;count<8;count++)
// 	{
// 	delay_us(2);//使电平持续一段时间
// 	return_data>>=1;
// 	SCLK_H;delay_us(4);//使高电平持续一段时间
// 	SCLK_L;delay_us(14);//延时14us后再去读取电压，更加准确
// 	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10))
// 	{return_data=return_data|0x80;}
	
// 	}
// delay_us(2);
// CE_L;DATA_L;
// return return_data;
// }
 
// void ds1032_init()
// {
// ds1302_wirte_rig(0x8e,0x00);//关闭写保护
// ds1302_wirte_rig(0x80,0x37);//seconds37秒
// ds1302_wirte_rig(0x82,0x58);//minutes58分
// ds1302_wirte_rig(0x84,0x23);//hours23时
// ds1302_wirte_rig(0x86,0x20);//date30
// ds1302_wirte_rig(0x88,0x06);//months9月
// ds1302_wirte_rig(0x8a,0x07);//days星期日
// ds1302_wirte_rig(0x8c,0x24);//year2020年
// ds1302_wirte_rig(0x8e,0x80);//关闭写保护
// }
 
// void ds1032_read_time()
// {
// read_time[0]=ds1302_read_rig(0x81);//读秒
// read_time[1]=ds1302_read_rig(0x83);//读分
// read_time[2]=ds1302_read_rig(0x85);//读时
// read_time[3]=ds1302_read_rig(0x87);//读日
// read_time[4]=ds1302_read_rig(0x89);//读月
// read_time[5]=ds1302_read_rig(0x8B);//读星期
// read_time[6]=ds1302_read_rig(0x8D);//读年
// }
 
// void ds1032_read_realTime()
// {
// ds1032_read_time();  //BCD码转换为10进制
// TimeData.second=(read_time[0]>>4)*10+(read_time[0]&0x0f);
// TimeData.minute=((read_time[1]>>4)&(0x07))*10+(read_time[1]&0x0f);
// TimeData.hour=(read_time[2]>>4)*10+(read_time[2]&0x0f);
// TimeData.day=(read_time[3]>>4)*10+(read_time[3]&0x0f);
// TimeData.month=(read_time[4]>>4)*10+(read_time[4]&0x0f);
// TimeData.week=read_time[5];
// TimeData.year=(read_time[6]>>4)*10+(read_time[6]&0x0f)+2000;
// }
// void Ds1302_Init(void)
// {
// ds1302_gpio_init();delay_ms(5); //初始化ds1302端口
// ds1032_init();delay_ms(5);      //ds1302初始化
// ds1032_read_realTime();         //读取实时数据
// min=TimeData.minute;            //记录此时分钟值
// delay_ms(5);
// sprintf(str1,"T:%2d",TimeData.hour);
// OLED_Show_Str(0,0,str1,16);
// sprintf(str2,":%2d",TimeData.minute);
// OLED_Show_Str(60,0,str2,16);
// sprintf(str3,":%2d",TimeData.second);
// OLED_Show_Str(96,0,str3,16);
// // sprintf(str4,"time:%d",TimeData.hour);
// // OLED_Show_Str(0,0,str4,16);
// // sprintf(str5,"time:%d",TimeData.hour);
// // OLED_Show_Str(0,0,str5,16);
// // sprintf(str6,"time:%d",TimeData.hour);
// // OLED_Show_Str(0,0,str6,16);

// }
// void Ds1302_Work(void)
// {
// ds1032_read_realTime();    //读取此时时刻
// if(min==TimeData.minute)//判断分钟数是否有更新
// {delay_ms(5);//没有更新便延时5ms
// }
// else{min=TimeData.minute;//分钟数有更新，则将变量min更新
// //分钟数更新了使OLED屏更新显示
// OLED_Clear();
// sprintf(str1,"T:%2d",TimeData.hour);
// OLED_Show_Str(0,0,str1,16);
// sprintf(str2,":%2d",TimeData.minute);
// OLED_Show_Str(60,0,str2,16);
// sprintf(str3,":%2d",TimeData.second);
// OLED_Show_Str(96,0,str3,16);
// }

// }