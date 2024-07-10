#include "max30102_math.h"
#include "stdbool.h"
#include "max30102.h"
#include "iicStart.h"
#include "oled.h"
#include "ls1x_latimer.h"
#define MAX_BRIGHTNESS 255
int32_t n_ir_buffer_length = 150; //data length
int32_t i,j,k;
uint32_t aun_ir_buffer[150]; //infrared LED sensor data
uint32_t aun_red_buffer[150];  //red LED sensor data
uint32_t un_min = 0x3fff, un_max = 0 ,un_prev_data,un_brightness;
int shibai=0;
int32_t n_spo2;  //SPO2 value
int8_t ch_spo2_valid;  //indicator to show if the SPO2 calculation is valid
int32_t n_heart_rate; //heart rate value
int8_t  ch_hr_valid;  //indicator to show if the heart rate calculation is valid
unsigned char manle;
int f_temp;
char str1[50];
char str2[50];
char str3[50];
char str4[500];
int32_t hrTimeout = 0;
int32_t hrValidCnt = 0;
int32_t hrThrowOutSamp = 0;
int32_t hr_buf[16];

int32_t hrBuffFilled;
int32_t hrSum;
int32_t hrAvg;

int32_t spo2Timeout = 0;
int32_t spo2ValidCnt = 0;
int32_t spo2ThrowOutSamp = 0;
int32_t spo2_buf[16];
int32_t spo2Sum;
int32_t spo2Avg;
int32_t spo2BuffFilled;     
uint8_t uch_dummy;
int32_t spo2Avg_arg1[30];      		 	//注意注意  我的spo2Avg_arg1[15] 就是最后获取的血氧数据
int32_t hrAvg_arg1[30],temp;    			 //注意注意  我的hrAvg_arg1[15] 就是最后获取的心率数据
uint8_t data;
extern uint8_t choiceNum;
//--------------------------心率和血氧的变量---------------------------------------------------------
/* Private function prototypes -----------------------------------------------*/

void Gain_Hr_Spo(void);


int Max30102chushi()
{
bsp_InitI2C();       //初始化IIC接口
	
	maxim_max30102_reset(); //resets the MAX30102
	maxim_max30102_read_reg(REG_INTR_STATUS_1, &uch_dummy); //Reads/clears the interrupt status register
 	maxim_max30102_init();  //initialize the MAX30102
	
	
	 //read the first 150 samples, and determine the signal range
	for(i = 0; i < n_ir_buffer_length; i++)//n_ir_buffer_length
	{
			maxim_max30102_read_fifo(&aun_red_buffer[i], &aun_ir_buffer[i]); //read from MAX30102 FIFO
            // sprintf(str4,"%d",aun_ir_buffer[i]);
			// OLED_Show_Str(0,0,str4,16);
			// delay_ms(100);
			if(un_min > aun_red_buffer[i])
					un_min = aun_red_buffer[i]; //update signal min
			if(un_max < aun_red_buffer[i])
					un_max = aun_red_buffer[i]; //update signal max
	}
	gpio_write_pin(GPIO_PIN_26,1);
	un_prev_data = aun_red_buffer[i];
	//calculate heart rate and SpO2 after first 150 samples (first 3 seconds of samples)
	maxim_heart_rate_and_oxygen_saturation(aun_ir_buffer, n_ir_buffer_length, aun_red_buffer, &n_spo2, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid);
}
int Max30102_Work(void)
{

	 Gain_Hr_Spo();//使用这个函数   spo2Avg_arg1[15]，hrAvg_arg1[15]就会有心率血氧值了
// 	maxim_max30102_read_reg(0XFF,&data);
// 	sprintf(str3,"%d",data);
// 	OLED_Show_Str(0,0,str3,16);
//
 }

/*
函数功能：获取心率和血氧
函数参数：无
函数返回值：无
函数描述：无
*/
void Gain_Hr_Spo(void)
{
	i = 0;
	un_min = 0x3FFFF;
	un_max = 0;
    

		for(i = 50; i < 150; i++)
		{
				aun_red_buffer[i - 50] = aun_red_buffer[i];
				aun_ir_buffer[i - 50] = aun_ir_buffer[i];

				//update the signal min and max
				if(un_min > aun_red_buffer[i])
						un_min = aun_red_buffer[i];
				if(un_max < aun_red_buffer[i])
						un_max = aun_red_buffer[i];
		}

		//take 50 sets of samples before calculating the heart rate.
		for(i = 100; i < 150; i++)
		{
				un_prev_data = aun_red_buffer[i - 1];
                
				maxim_max30102_read_fifo((aun_red_buffer + i), (aun_ir_buffer + i));
//  sprintf(str4,"%d",aun_ir_buffer[i]);
// 			OLED_Show_Str(0,0,str4,16);
// 			delay_ms(100);
				//calculate the brightness of the LED
				if(aun_red_buffer[i] > un_prev_data)
				{
						f_temp = aun_red_buffer[i] - un_prev_data;
						// if((un_max - un_min)==0)break;
						f_temp = f_temp/(un_max - un_min+1);
						f_temp *= MAX_BRIGHTNESS;
						f_temp = un_brightness - f_temp;
						if(f_temp < 0)
								un_brightness = 0;
						else
								un_brightness = f_temp;
				}
				else
				{
						f_temp = un_prev_data - aun_red_buffer[i];
						// if((un_max - un_min)==0)break;
						f_temp = f_temp/(un_max - un_min+1);
						f_temp *= MAX_BRIGHTNESS;
						un_brightness += f_temp;
						if(un_brightness > MAX_BRIGHTNESS)
								un_brightness = MAX_BRIGHTNESS;
				}
				
		}
		
        // if((un_max - un_min)==0){goto cmd_NO;}
		maxim_heart_rate_and_oxygen_saturation(aun_ir_buffer, n_ir_buffer_length, aun_red_buffer, &n_spo2, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid);
        
		if ((ch_hr_valid == 1) && (n_heart_rate < 190) && (n_heart_rate > 40))
		{
				hrTimeout = 0;

				// Throw out up to 1 out of every 5 valid samples if wacky
				if (hrValidCnt == 4)
				{
						hrThrowOutSamp = 1;
						hrValidCnt = 0;
						for (i = 12; i < 16; i++)
						{
								if (n_heart_rate < hr_buf[i] + 10)
								{
										hrThrowOutSamp = 0;
										hrValidCnt   = 4;
								}
						}
				}
				else
				{
						hrValidCnt = hrValidCnt + 1;
				}

				if (hrThrowOutSamp == 0)
				{

						// Shift New Sample into buffer
						for(i = 0; i < 15; i++)
						{
								hr_buf[i] = hr_buf[i + 1];
						}
						hr_buf[15] = n_heart_rate;

						// Update buffer fill value
						if (hrBuffFilled < 16)
						{
								hrBuffFilled = hrBuffFilled + 1;
						}

						// Take moving average
						hrSum = 0;
						if (hrBuffFilled < 2)
						{
								hrAvg = 0;
						}
						else if (hrBuffFilled < 4)
						{
								for(i = 14; i < 16; i++)
								{
										hrSum = hrSum + hr_buf[i];
								}
								hrAvg = hrSum >> 1;
						}
						else if (hrBuffFilled < 8)
						{
								for(i = 12; i < 16; i++)
								{
										hrSum = hrSum + hr_buf[i];
								}
								hrAvg = hrSum >> 2;
						}
						else if (hrBuffFilled < 16)
						{
								for(i = 8; i < 16; i++)
								{
										hrSum = hrSum + hr_buf[i];
								}
								hrAvg = hrSum >> 3;
						}
						else
						{
								for(i = 0; i < 16; i++)
								{
										hrSum = hrSum + hr_buf[i];
								}
								hrAvg = hrSum >> 4;
						}
				}
				hrThrowOutSamp = 0;
		}
		else
		{
				hrValidCnt = 0;
				if (hrTimeout == 4)
				{
						hrAvg = 0;
						hrBuffFilled = 0;
				}
				else
				{
						hrTimeout++;
				}
		}

		if ((ch_spo2_valid == 1) && (n_spo2 > 59))
		{
				spo2Timeout = 0;

				// Throw out up to 1 out of every 5 valid samples if wacky
				if (spo2ValidCnt == 4)
				{
						spo2ThrowOutSamp = 1;
						spo2ValidCnt = 0;
						for (i = 12; i < 16; i++)
						{
								if (n_spo2 > spo2_buf[i] - 10)
								{
										spo2ThrowOutSamp = 0;
										spo2ValidCnt   = 4;
								}
						}
				}
				else
				{
						spo2ValidCnt = spo2ValidCnt + 1;
				}

				if (spo2ThrowOutSamp == 0)
				{

						// Shift New Sample into buffer
						for(i = 0; i < 15; i++)
						{
								spo2_buf[i] = spo2_buf[i + 1];
						}
						spo2_buf[15] = n_spo2;

						// Update buffer fill value
						if (spo2BuffFilled < 16)
						{
								spo2BuffFilled = spo2BuffFilled + 1;
						}

						// Take moving average
						spo2Sum = 0;
						if (spo2BuffFilled < 2)
						{
								spo2Avg = 0;
						}
						else if (spo2BuffFilled < 4)
						{
								for(i = 14; i < 16; i++)
								{
										spo2Sum = spo2Sum + spo2_buf[i];
								}
								spo2Avg = spo2Sum >> 1;
						}
						else if (spo2BuffFilled < 8)
						{
								for(i = 12; i < 16; i++)
								{
										spo2Sum = spo2Sum + spo2_buf[i];
								}
								spo2Avg = spo2Sum >> 2;
						}
						else if (spo2BuffFilled < 16)
						{
								for(i = 8; i < 16; i++)
								{
										spo2Sum = spo2Sum + spo2_buf[i];
								}
								spo2Avg = spo2Sum >> 3;
						}
						else
						{
								for(i = 0; i < 16; i++)
								{
										spo2Sum = spo2Sum + spo2_buf[i];
								}
								spo2Avg = spo2Sum >> 4;
						}
				}
				spo2ThrowOutSamp = 0;
		}
		else
		{
				spo2ValidCnt = 0;
				if (spo2Timeout == 4)
				{
						spo2Avg = 0;
						spo2BuffFilled = 0;
				}
				else
				{
						spo2Timeout++;
				}
		}
		if(hrAvg != 0 && spo2Avg != 0)
		{

			hrAvg_arg1[j] = hrAvg;
			if(spo2Avg<88)spo2Avg==88;
			spo2Avg_arg1[j++] = spo2Avg;

			if(j == 30)                        //我觉得模块本身算法不是很精确 所以我自己弄了个本人而言还过得去的算法
			{																		//当j=30 代表已经获取了30次心率 血氧值了  然后我取30次里中间的值
				for(j = 0;j < 30;j++)        //这里两个循环是冒泡排序 30次数据分大小排好 取中间
				{
					for(k = j+1;k < 30;k++)
					{
						if(hrAvg_arg1[k] < hrAvg_arg1[j])
						{
							temp = hrAvg_arg1[j];
							hrAvg_arg1[j] = hrAvg_arg1[k];
							hrAvg_arg1[k] = temp;
						}
						if(spo2Avg_arg1[k] < spo2Avg_arg1[j])
						{
							temp = spo2Avg_arg1[j];
							spo2Avg_arg1[j] = spo2Avg_arg1[k];
							spo2Avg_arg1[k] = temp;
						}
					}
				}
                 sprintf(str1,"%2d",hrAvg_arg1[10]+5);
                 sprintf(str2,"%2d",spo2Avg_arg1[10]+3);
                 OLED_Show_Str(0,0,str1,16);
                 OLED_Show_Str(0,2,str2,16);

                				// printf("%d %d\r\n",hrAvg_arg1[15],spo2Avg_arg1[15]); 
				j = 0;             //30次获取够了  让变量再为0 获取下次30次数据
			}
			if(choiceNum==1)
		{
	    sprintf(str3,"Yes");
		OLED_Show_Str(0,4,str3,16);
		}

		}
		else{
		
		if(choiceNum==1)
		{
	    sprintf(str4,"NO   ");
		OLED_Show_Str(0,4,str4,16);
		}
		}	
		// cmd_NO:shibai=1;
			
}
