#include <reg51.h>
#include <intrins.h>
#include <stdlib.h>
#define uchar unsigned char
#define uint  unsigned int
/*端口定义*/

#define LCD_data P0
sbit LCD_RS  =  P1^0;            //寄存器选择输入 
sbit LCD_RW  =  P1^1;            //液晶读/写控制
sbit LCD_EN  =  P1^2;            //液晶使能控制
sbit LCD_PSB =  P1^6;            //串/并方式控制
sbit LCD_RST =  P1^3;
sbit LCD_NC	 =  P1^7;
sbit wela    =  P2^6;
sbit dula    =  P2^7;

uchar dis1[10];
uchar code dis2[]={"停止"};
uchar code dis3[]={"前进"};
uchar code dis4[]={"后退"};
uchar code dis5[]={"左转"};
uchar code dis6[]={"右转"};

uchar code dis[]={"倒计时:"};


uchar code dis18[]={"速度：FAST"};
uchar code dis19[]={"速度：SLOW"};
uchar code dis20[]={"速度：ZERO"};

uchar code dis21[]={"停靠"};
uchar code dis22[]={"次"};

void delay_1ms(uint x)
{
    uint i,j;
	for(j=0;j<x;j++)
	    for(i=0;i<110;i++);
}
void write_cmd(uchar cmd)
{
    LCD_RS=0;
	LCD_RW=0;
	LCD_EN=0;
	P0=cmd;
	delay_1ms(5);
	LCD_EN=1;
	delay_1ms(5);
	LCD_EN=0;
}
void write_dat(uchar dat)
{ 
    LCD_RS=1;
	LCD_RW=0;
	LCD_EN=0;
	P0=dat;
	delay_1ms(5);
	LCD_EN=1;
	delay_1ms(5);
	LCD_EN=0;
}
void lcd_pos(uchar X,uchar Y)
{
    uchar pos;
	if(X==0)
	    X=0x80;
	else if(X==1)
	    X=0x90;
	else if(X==2)
	    X=0x88;
	else if(X==3)
    	X=0x98;
	pos = X+Y;
	write_cmd(pos);
}

void makerand()
{
    uint ran;
	ran=rand();
	dis1[0]=ran/10000+0x30;
	dis1[1]=ran%10000/1000+0x30;
	dis1[2]=ran%1000/100+0x30;
	dis1[3]=ran%100/10+0x30;
	dis1[4]=ran%10+0x30;
	ran=rand();
	dis1[5]=ran/10000+0x30;
	dis1[6]=ran%10000/1000+0x30;
	dis1[7]=ran%1000/100+0x30;
	dis1[8]=ran%100/10+0x30;
	dis1[9]=ran%10+0x30;
	}

void lcd_init()
{
    LCD_PSB=1;
	write_cmd(0x30);
	delay_1ms(5);
	write_cmd(0x0C);
	delay_1ms(5);
	write_cmd(0x01);
	delay_1ms(5);
}

void init_lcd()			   //LCD初始化
{    
  	delay_1ms(10);
	lcd_init();  
}

void forward_display()    //前进显示
{
	uchar i;
	lcd_pos(0,0);
    for(i=0;i<4;i++)
	{
		write_dat(dis3[i]);
		delay_1ms(30);
	}
}

void back_display()    //后退显示
{
	uchar i;
	lcd_pos(0,0);
    for(i=0;i<4;i++)
	{
		write_dat(dis4[i]);
		delay_1ms(30);
	}
}


void fast_display()    //显示速度快
{
	uchar i;
	lcd_pos(2,0);
    for(i=0;i<10;i++)
	{
		write_dat(dis18[i]);
		delay_1ms(30);
	}
}

void slow_display()    //显示速度慢
{
	uchar i;
	lcd_pos(2,0);
    for(i=0;i<10;i++)
	{
		write_dat(dis19[i]);
		delay_1ms(30);
	}
}

void vzero_display()    //显示速度0
{
	uchar i;
	lcd_pos(2,0);
    for(i=0;i<10;i++)
	{
		write_dat(dis20[i]);
		delay_1ms(30);
	}
}

void left_display()    //左转显示
{
	uchar i;
	delay_1ms(10);
	lcd_init();
	lcd_pos(0,0);
    for(i=0;i<4;i++)
	{
		write_dat(dis5[i]);
		delay_1ms(30);
	}
}

void right_display()    //右转显示
{
	uchar i;
	delay_1ms(10);
	lcd_init();
	lcd_pos(0,0);
    for(i=0;i<4;i++)
	{
		write_dat(dis6[i]);
		delay_1ms(30);
	}
}

void stop_display1()    //停止，无倒计时
{
	uchar i;
	    lcd_pos(0,0);
        for(i=0;i<4;i++)
	    {
		write_dat(dis2[i]);
		delay_1ms(30);
	    }
}

void stop_display(unsigned int n)		   //停止，显示倒计时
{
	uchar i;
	delay_1ms(10);
	lcd_init();
	lcd_pos(0,0);
	for(i=0;i<4;i++)
    {
        write_dat(dis2[i]);
        delay_1ms(30);
    }
    lcd_pos(1,0);
    for(i=0;i<9;i++)
    {
    	write_dat(dis[i]);
    	delay_1ms(30);
    }
    lcd_pos(1,4);
    for(i=0;i<3;i++)
    {
        char ch[3]=0;
        ch[0]=n/100+48; //取百位
        ch[1]=(n/10)%10+48; //取十位
        ch[2]=n%10+48;
    	write_dat(ch[i]);
    	delay_1ms(30);
    }
    delay_1ms(10);
	lcd_init();
}

void stoptimes_display(unsigned int n)		   //停靠次数显示
{
	uchar i;
    lcd_pos(3,0);
    for(i=0;i<4;i++)
    {
    	write_dat(dis21[i]);
    	delay_1ms(30);
    }
    lcd_pos(3,2);
    for(i=0;i<3;i++)
    {
        char ch[3]=0;
        ch[0]=n/100+48; //取百位
        ch[1]=(n/10)%10+48; //取十位
        ch[2]=n%10+48;
    	write_dat(ch[i]);
    	delay_1ms(30);
    }
    lcd_pos(3,4);
    for(i=0;i<2;i++)
    {
    	write_dat(dis22[i]);
    	delay_1ms(30);
    }
}
