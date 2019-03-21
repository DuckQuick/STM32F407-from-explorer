注：增加 画实心圆 函数，请与正点原子F407探索者官方库函数配套使用并在lcd.h里增加声明函数。

//在指定位置画一个实心圆
//(x,y):坐标
//r    :半径
void LCD_Draw_ALLCircle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		int i = a,p = b;
		while(i>0){		
			LCD_DrawPoint(x0+b,y0-i);
			LCD_DrawPoint(x0-i,y0+b);
			i--;
	}		
		while(p>0){		
			LCD_DrawPoint(x0-a,y0-p);
			LCD_DrawPoint(x0-p,y0-a);
			LCD_DrawPoint(x0+a,y0-p);
			LCD_DrawPoint(x0-p,y0+a);
			LCD_DrawPoint(x0+a,y0+p);
			LCD_DrawPoint(x0+p,y0+a);
			p--;
	}
		a++;
		//Bresenham算法画圆    
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
	LCD_DrawPoint(x0,y0); //圆心坐标
}
