#include "TimerStartWork.h"
#include "test.h"
#include "oled.h"
#include "Key.h"
#include "Max30102_Work.h"
uint8_t keynum=0,MODE=0,choiceNum=0,set=0;
extern uint8_t sec,min,hour;
void TimeWork()
{
    if(set==0)
     keynum=KEY();
     
        if(keynum==1)
        {
            choiceNum++;
            if(choiceNum==1)
            OLED_Clear();       
            if(choiceNum==2)
            choiceNum=0;
        }
     
            switch (choiceNum)
            {
            case 0:MODE1();break;
            case 1:MODE2();break;   
            }
        
       
}
void MODE1()
{ 
                  
        OLED_ShowInt32Num(1,0, hour, 2, 16);
        OLED_ShowChar(17, 0, ':',16);
        OLED_ShowInt32Num(32,0, min, 2, 16);
        OLED_ShowChar(50, 0, ':',16);
        OLED_ShowInt32Num(64,0, sec, 2, 16);
      if(keynum==2)                              
        {
           set++;
         if(set==3)
            set=0;                              
        }
          switch (set)
            {
            case 0:OLED_ShowChar(96,0,' ',16);break;
            case 1:HourSet();break;
            case 2:MinSet();break;   
            }

}
void MODE2()
{
set=0;
Max30102_Work();
}
void HourSet()
{

        keynum=KEY();
        OLED_ShowChar(96,0, 'H',16);
        OLED_ShowInt32Num(1,0, hour, 2, 16);
        OLED_ShowChar(17,0, ':',16);
        OLED_ShowInt32Num(33,0, min, 2, 16);
        OLED_ShowChar(50,0, ':',16);
        OLED_ShowInt32Num(66,0, sec, 2, 16);
        switch (keynum)
        {
            case 3:hour++;break;
            case 4:hour--;break;
        }
    
}
void MinSet()
{

        keynum=KEY();
        OLED_ShowChar(96,0, 'M',16);
        OLED_ShowInt32Num(1,0, hour, 2, 16);
        OLED_ShowChar(17,0, ':',16);
        OLED_ShowInt32Num(32,0, min, 2, 16);
        OLED_ShowChar(50,0, ':',16);
        OLED_ShowInt32Num(64,0,sec,2, 16);
        switch (keynum)
        {
            case 3:min++;break;
            case 4:min--;break;
        }
    
}
