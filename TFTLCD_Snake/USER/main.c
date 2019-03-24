#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "snake.h"
#include "key.h"

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);      //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
 	LCD_Init();           //��ʼ��LCD FSMC�ӿ�
	KEY_Init();
	snake_init(30,30,100,20); //void snake_init(u16 x,u16 y,u16 speed,u16 shape);
	delay_ms(1000);
}
