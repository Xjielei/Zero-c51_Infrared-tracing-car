/*
 * @Author: Zero_Lei
 * @Date: 2021-12-04 10:04:25
 * @LastEditors: Zero_Lei
 * @LastEditTime: 2021-12-04 15:07:48
 * @Description: file content
 */
//**********************************************************

#include "sendbit.h"
                                                                
UART Uart;//新建一个结构体

void UART_Configure(u16 BaudRate) //初使化函数
{
    u8 TH1_Dat;
    
  switch(BaudRate) //采用switch方式能直观知道支持哪几种具体的波特率，增加可读性
    {
       case 1200:  TH1_Dat=0xE8; break;
       case 2400:  TH1_Dat=0xF4; break;
       case 4800:  TH1_Dat=0xFA; break;
       case 9600:  TH1_Dat=0xFD; break;
       case 14400: TH1_Dat=0xFE; break;
    }
		TMOD &= 0x0F; //清除高4位数据
    TMOD |= 0x20; //定时器工作模式，高4位控制定时器1，低4位制定时器0，0x2-工作方式2：8位自动重装载定时器模式 (用或|屏蔽对定时器0的影响)
    SCON = 0x50;  //串行口控制寄存器,Bit[7:6]=串口工作模式，0:1为工作模式1：8位数据位，Bit-4=串口接收允许位，1-允许 0-禁止
    TH1 = TH1_Dat; //8位自动重装载定时器模式下，TH1被用作自动重装载值寄存器
    TL1 = TH1;     //TL1为计数寄存器(向上计数，当计数溢出时，自动从TH1寄存器里装载初值到TL1)
    PCON |= 0x00; //Bit7-波特率倍增位：0-不培增  1-培增
    EA = 1;       //全局中断允许
    ES = 1;       //串口中断允许
    TR1 = 1;      //定时器1开始工作 
}

void UART_SendByte(u8 dat) //单字符发送
{
    SBUF=dat;
    while(!TI);  //等待发送数据完成
    TI=0;        //清除发送完成标志位
}
void UART_Send(u8* arr,u16 len)//多字符发送
{
  u16 i;
    for(i=0;i<len;i++)
    {
        SBUF=arr[i];
      while(!TI);  //等待发送数据完成
      TI=0;                //清除发送完成标志位  
    }
}
void UART_SendStr(u8* str)//字符串发送
{
  while(1)
    {
      if(*str=='\0') break;
        SBUF=*str++;
        while(!TI);  //等待发送数据完成
      TI=0;                //清除发送完成标志位
    }
}

void UART_RX_BUFF_Clear(void) //接收缓存数据清除
{
  u16 i;
	for(i=0;i<USART_RX_LEN;i++)
	{
	  Uart.RX_BUFF[i]=0;//用于数据处理
		//Uart.RX_BUFF[i]='\0';//用于文本处理
	}
}

void UART_TX_BUFF_Clear(void) //发送缓存数据清除
{
  u16 i;
	for(i=0;i<USART_TX_LEN;i++)
	{
	  Uart.TX_BUFF[i]=0;//用于数据处理
		//Uart.RX_BUFF[i]='\0';//用于文本处理
	}
}

void UART_IRQHandler(void) interrupt 4  //串口中断函数
{          
  if(RI==1)    //判断是否为接收中断(串口中断分为发送中断和接收中断，均用同一个中断服务函数入口)
    {
        RI = 0;    //清除RI硬件接收中断标志 
        Uart.RX_BUFF[Uart.RX_COUNT++]=SBUF;
        if(Uart.RX_COUNT>=USART_RX_LEN) Uart.RX_COUNT=0;
    }    
}

