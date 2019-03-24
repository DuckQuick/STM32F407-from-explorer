#include "snake.h"

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

u8 snake_pos = RIGHT;
u8 key;
short snake_live = 0;
u16 snake_x[100];
u16 snake_y[100];
u16 snake_speed;
u16 snake_shape;
short i; //计数器，记录两次移动间隔时间
u16 apple_x;
u16 apple_y;
short apple = 0;
u16 snake_length = 1;
short m; //计数器，记录snake的长度

void snake_scan(void){  //按键检测及方向确定
		key=KEY_Scan(0);
		if(key){						   
				switch(key){				 
					case WKUP_PRES:
						snake_pos = UP;
						break;
					case KEY0_PRES:
						snake_pos = RIGHT;
						break;
					case KEY1_PRES: 
						snake_pos = DOWN;
						break;
					case KEY2_PRES:
						snake_pos = LEFT;
						break;
				}
			}
}

void apple_init(void){	//苹果生成
	while(!apple && !RNG_Init()){
		apple_x=RNG_Get_RandomRange(1,(lcddev.width - snake_shape * 2) / snake_shape / 2) * snake_shape * 2;
		delay_ms(10);
		apple_y=RNG_Get_RandomRange(1,(lcddev.height - snake_shape * 2) / snake_shape / 2) * snake_shape * 2;
		delay_ms(10);
		apple++;
		for(m = snake_length;m >= 0;m--){
		if(apple_x == snake_x[m] && apple_y == snake_y[m]) {apple--;break;}
		}
	}
}

void snake_eat(void){			//判断是否吃到苹果
	if(snake_x[0] == apple_x && snake_y[0] == apple_y){
		apple--;
		snake_length++;
		snake_x[snake_length] = snake_x[snake_length - 1];
		snake_y[snake_length] = snake_y[snake_length - 1];
	}
}

void snake_move(void){	//移动
		switch(snake_pos){
			case UP:snake_y[0] -= snake_shape * 2;break;
			case DOWN:snake_y[0] += snake_shape * 2;break;
			case LEFT:snake_x[0] -= snake_shape * 2;break;
			case RIGHT:snake_x[0] += snake_shape * 2;break;
		}
}

void snake_init(u16 x,u16 y,u16 speed,u16 shape){ //主运行函数
	if(x % shape != 0) snake_x[0]=shape * 2;
	else snake_x[0]=x;
	if(y % shape != 0) snake_y[0]=shape * 2;
	else snake_y[0]=y;
	snake_speed = speed;snake_shape = shape;
	i = 0;
	while(!snake_live){
		POINT_COLOR=BLACK;
		snake_scan();	
		if(i<snake_speed){
			delay_ms(10);
			i++;
		}
		else{
			delay_ms(10);
			i = 0;
			snake_eat();
			snake_move();		
			if(snake_y[0] < snake_shape * 2 || snake_y[0] > lcddev.height - snake_shape || snake_x[0] < snake_shape * 2 || snake_x[0] > lcddev.width - snake_shape) snake_live = 1;
			LCD_Clear(WHITE);
			apple_init();
			while(snake_live) {
				LCD_ShowString(lcddev.width / 2 - 40,lcddev.height / 2 - 16,200,16,16,"Game Over!");
				LCD_ShowString(lcddev.width / 2 - 100,lcddev.height / 2,200,16,16,"Press KEY0 To Play Again!");
				if(KEY_Scan(0) == KEY0_PRES) {
					snake_live=0;
					snake_pos = RIGHT;
					if(x % shape != 0) snake_x[0]=shape * 2;
					else snake_x[0]=x;
					if(y % shape != 0) snake_y[0]=shape * 2;
					else snake_y[0]=y;				
					LCD_Clear(WHITE);
			}
		}		
			if(apple > 0){
				POINT_COLOR=RED;
				LCD_Draw_ALLCircle(apple_x,apple_y,snake_shape);
			}
			POINT_COLOR=BLACK;
			LCD_DrawRectangle(snake_shape - 1,snake_shape - 1,lcddev.width - snake_shape + 1,lcddev.height - snake_shape + 1);
			for(m = snake_length;m >= 0;m--) {
				if(m > 0){
					snake_x[m] = snake_x[m-1];snake_y[m] = snake_y[m-1];
				}
				LCD_Draw_ALLCircle(snake_x[m],snake_y[m],snake_shape);
			}
		}
	}
}
