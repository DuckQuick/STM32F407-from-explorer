#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "snake.h"
#include "key.h"

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);      //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200
 	LCD_Init();           //初始化LCD FSMC接口
	KEY_Init();
	snake_init(30,30,100,20); //void snake_init(u16 x,u16 y,u16 speed,u16 shape);
	delay_ms(1000);
}
