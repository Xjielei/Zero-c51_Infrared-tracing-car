/*
 * @Author: Zero_Lei
 * @Date: 2021-12-04 10:04:25
 * @LastEditors: Zero_Lei
 * @LastEditTime: 2021-12-04 15:07:48
 * @Description: file content
 */
//**********************************************************

#include "sendbit.h"
                                                                
UART Uart;//�½�һ���ṹ��

void UART_Configure(u16 BaudRate) //��ʹ������
{
    u8 TH1_Dat;
    
  switch(BaudRate) //����switch��ʽ��ֱ��֪��֧���ļ��־���Ĳ����ʣ����ӿɶ���
    {
       case 1200:  TH1_Dat=0xE8; break;
       case 2400:  TH1_Dat=0xF4; break;
       case 4800:  TH1_Dat=0xFA; break;
       case 9600:  TH1_Dat=0xFD; break;
       case 14400: TH1_Dat=0xFE; break;
    }
		TMOD &= 0x0F; //�����4λ����
    TMOD |= 0x20; //��ʱ������ģʽ����4λ���ƶ�ʱ��1����4λ�ƶ�ʱ��0��0x2-������ʽ2��8λ�Զ���װ�ض�ʱ��ģʽ (�û�|���ζԶ�ʱ��0��Ӱ��)
    SCON = 0x50;  //���пڿ��ƼĴ���,Bit[7:6]=���ڹ���ģʽ��0:1Ϊ����ģʽ1��8λ����λ��Bit-4=���ڽ�������λ��1-���� 0-��ֹ
    TH1 = TH1_Dat; //8λ�Զ���װ�ض�ʱ��ģʽ�£�TH1�������Զ���װ��ֵ�Ĵ���
    TL1 = TH1;     //TL1Ϊ�����Ĵ���(���ϼ��������������ʱ���Զ���TH1�Ĵ�����װ�س�ֵ��TL1)
    PCON |= 0x00; //Bit7-�����ʱ���λ��0-������  1-����
    EA = 1;       //ȫ���ж�����
    ES = 1;       //�����ж�����
    TR1 = 1;      //��ʱ��1��ʼ���� 
}

void UART_SendByte(u8 dat) //���ַ�����
{
    SBUF=dat;
    while(!TI);  //�ȴ������������
    TI=0;        //���������ɱ�־λ
}
void UART_Send(u8* arr,u16 len)//���ַ�����
{
  u16 i;
    for(i=0;i<len;i++)
    {
        SBUF=arr[i];
      while(!TI);  //�ȴ������������
      TI=0;                //���������ɱ�־λ  
    }
}
void UART_SendStr(u8* str)//�ַ�������
{
  while(1)
    {
      if(*str=='\0') break;
        SBUF=*str++;
        while(!TI);  //�ȴ������������
      TI=0;                //���������ɱ�־λ
    }
}

void UART_RX_BUFF_Clear(void) //���ջ����������
{
  u16 i;
	for(i=0;i<USART_RX_LEN;i++)
	{
	  Uart.RX_BUFF[i]=0;//�������ݴ���
		//Uart.RX_BUFF[i]='\0';//�����ı�����
	}
}

void UART_TX_BUFF_Clear(void) //���ͻ����������
{
  u16 i;
	for(i=0;i<USART_TX_LEN;i++)
	{
	  Uart.TX_BUFF[i]=0;//�������ݴ���
		//Uart.RX_BUFF[i]='\0';//�����ı�����
	}
}

void UART_IRQHandler(void) interrupt 4  //�����жϺ���
{          
  if(RI==1)    //�ж��Ƿ�Ϊ�����ж�(�����жϷ�Ϊ�����жϺͽ����жϣ�����ͬһ���жϷ��������)
    {
        RI = 0;    //���RIӲ�������жϱ�־ 
        Uart.RX_BUFF[Uart.RX_COUNT++]=SBUF;
        if(Uart.RX_COUNT>=USART_RX_LEN) Uart.RX_COUNT=0;
    }    
}

