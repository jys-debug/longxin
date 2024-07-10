#include "ls1x_gpio.h"
#include "ls1x_latimer.h"
#define KEY1    GPIO_PIN_22
#define KEY2    GPIO_PIN_23
#define KEY3    GPIO_PIN_24
#define KEY4    GPIO_PIN_25
void KEY_Init()
{
    gpio_set_direction(KEY1, GPIO_Mode_In); 
    gpio_set_direction(KEY2, GPIO_Mode_In); // 璁剧疆鎸夐敭2鐨凣PIO涓鸿緭鍏?
    gpio_set_direction(KEY3, GPIO_Mode_In); // 璁剧疆鎸夐敭3鐨凣PIO涓鸿緭鍏?
    gpio_set_direction(KEY4, GPIO_Mode_In); // 璁剧疆鎸夐敭4鐨凣PIO涓鸿緭鍏?
}

uint8_t KEY()
{
    if (!gpio_get_pin(KEY1))// 璇诲彇鎸夐敭鐘舵€?
    {   
        delay_ms(20);
        while (!gpio_get_pin(KEY1));
        delay_ms(20);
        return 1;
    }
    if(!gpio_get_pin(KEY2))
    {
        delay_ms(20);
        while (!gpio_get_pin(KEY2));
        delay_ms(20);
        return 2;
    }
    if(!gpio_get_pin(KEY3))
    {
        delay_ms(20);
        while (!gpio_get_pin(KEY3));
        delay_ms(20);
        return 3;
    }
    if(!gpio_get_pin(KEY4))
    {
        delay_ms(20);
        while (!gpio_get_pin(KEY4));
        delay_ms(20);
        return 4;
    }
    return 0;
}