/*
 * @Author: Zero_Lei
 * @Date: 2021-12-02 21:11:29
 * @LastEditors: Zero_Lei
 * @LastEditTime: 2021-12-23 13:03:58
 * @Description: file content
 */
#include <reg52.h>
#include <intrins.h>
#include <movestate.h>
#include <motordriver.h>
#include <Timer.h>
#include <infrared_track.h>
#include <sendbit.h>
#include <show_state.h>
#include <stceeprom.h>


void main()  //������
{

   unsigned int state1 = 10;
   unsigned int state2;

   unsigned int FLAG = 6;
   unsigned int CTRL = 0;

   unsigned int speed = 1;	 //0ͣ��1����2��, 3ͣ��վ��
   unsigned int speed_temp = 1;  //��������ֵ

   unsigned int n = 10;

   unsigned int count = 2;
  count = eepromRead(0x2088);
   if(count == 255) count = 0;

   init_lcd(); //��ʼ��LCD

    Timer0_Init();
	UART_Configure(9600);
    EA = 1;
    
    while (1)
    {
      //  count = Counter(count);
     //��ʾվ����
     stoptimes_display(count);

      if(speed != 0 && speed != 3) speed_temp = speed;

		if(Uart.RX_COUNT>=1) //�жϴ����Ƿ���յ�1���ַ�
      {  
	  	   if(Uart.RX_BUFF[0] >= 'a' && Uart.RX_BUFF[0] <= 'z')
         {
            n = Uart.RX_BUFF[0] - 0x60;     //����ͣ��ʱ��
         }

         if(Uart.RX_BUFF[0] >= 'A' && Uart.RX_BUFF[0] <= 'Z')
         {
            CTRL = 1;   //����λ������
            if(Uart.RX_BUFF[0]=='A') 
            {
               FLAG = 1;
               speed = speed_temp;
               CTRL = 1;   //����λ������					 
            }
            if(Uart.RX_BUFF[0]=='B') 
            {
               FLAG = 2;
               speed = speed_temp;
               CTRL = 1;   //����λ������					 
            }
            if(Uart.RX_BUFF[0]=='C')
            {
               FLAG = 3;
               speed = speed_temp;
               CTRL = 1;   //����λ������					 
            }
            if(Uart.RX_BUFF[0]=='D')
            {
               FLAG = 4;
               speed = speed_temp;
               CTRL = 1;   //����λ������				 
            }
            if(Uart.RX_BUFF[0]=='O')
            {
               FLAG = 5;
               speed = 0;
               CTRL = 1;   //����λ������					 
            }
            if(Uart.RX_BUFF[0]=='Q')
            {	
               FLAG = 6;
               CTRL = 0;				 
            }

            if(Uart.RX_BUFF[0]=='K')	//��
            {	
               PWM_Init(10);
               FLAG = FLAG; 
               speed = 2;
            }
            if(Uart.RX_BUFF[0]=='M')	//��
            {	
               PWM_Init(5);
               FLAG = FLAG;	
               speed = 1;		 
            }
            if(Uart.RX_BUFF[0]=='R')	//RESET
            {	
               count = 0;             //����count
               FLAG = FLAG;			 
            }

         }	

		   //������ݱ����ڴ������ĺ���
		   Uart.RX_COUNT=0; //���������0
		   UART_RX_BUFF_Clear();//������ջ���
         UART_TX_BUFF_Clear();//������ͻ���
      }

      if(CTRL != 1 )
	  {
         count = Track(n, &speed, count);
	  }

      if(FLAG != 6)
      {
         state2 = FLAG;
    
         if(state1 != state2)
         {
            switch (FLAG)
            {
               case 1: UART_SendStr("FORWARD \r\n");
                  break;
               case 2: UART_SendStr("BACK \r\n");
                  break;
               case 3: UART_SendStr("TURN RIGHT \r\n");
                  break;
               case 4: UART_SendStr("TURN LEFT \r\n");
                  break;
               case 5: UART_SendStr("STOP \r\n");
                  break;
               
               default:
                  break;
            }
         }
         state1 = FLAG;

         switch (FLAG)
         {
            case 1: Car_Go();
               break;
            case 2: Car_Back();
               break;
            case 3: Car_Trun_Right1();
               break;
            case 4: Car_Trun_Left1();
               break;
            case 5: Car_Stop();
               break;
            
            default:
               break;
         }

      }
      
	   if(speed == 0)
     {
        //ֹͣʱ���ٶ�Ϊ��
        vzero_display();
     }
     if(speed == 1)
     {
        slow_display();
     }
     if(speed == 2)
     {
        fast_display();
     }
     if(speed == 3)
     {
        //ͣ��վ�㣬�ٶ�Ϊ��
        vzero_display();
		  speed = speed_temp;
     }

    eepromEraseSector(0x2088);
    eepromWrite(0x2088,count);
    }
}
