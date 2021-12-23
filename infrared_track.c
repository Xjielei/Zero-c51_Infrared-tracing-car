/*
 * @Author: Zero_Lei
 * @Date: 2021-12-02 21:48:49
 * @LastEditors: Zero_Lei
 * @LastEditTime: 2021-12-23 13:03:16
 * @Description: file content
 */

#include <reg52.h>
#include "movestate.h"
#include "Timer.h"
#include "delay.h"
#include <sendbit.h>
#include "show_state.h"

#define on 0
#define off 1

sbit left1 = P1^4;
sbit left2 = P1^5;
sbit middle = P2^2;
sbit right1 = P2^7;
sbit right2 = P3^7;

void case1()
{
   UART_SendStr("STOP N");
   UART_SendStr("\r\n");
}

// void delay_ms(unsigned int n)

// {

// unsigned int i,j;

// for(j=n;j>0;j--)

// for(i=112;i>0;i--);

// }

unsigned int Track(unsigned int n, unsigned int *sd_ptr,unsigned int count)
{
    unsigned int state; //1停，2、3前进，4左转，5右转
    unsigned int states2;
    unsigned int states1;

   if(left1 == on && left2 == on && right1 == on && right2 == on) //0000
   {
      state = 2;
   }
   if(left1 == on && left2 == on && right1 == on && right2 == off) //0001
   {
      state = 2;
   }
   if(left1 == on && left2 == on && right1 == off && right2 == on) //0010
   {
      state = 2;
   }
   if(left1 == on && left2 == on && right1 == off && right2 == off) //0011
   {
      state = 4;
   }
   if(left1 == on && left2 == off && right1 == on && right2 == on) //0100
   {
      state = 2;
   }
   if(left1 == on && left2 == off && right1 == on && right2 == off) //0101
   {
      state = 4;
   }
   if(left1 == on && left2 == off && right1 == off && right2 == on) //0110
   {
      state = 2;
   }
   if(left1 == on && left2 == off && right1 == off && right2 == off) //0111
   {
      state = 4;
   }
   if(left1 == off && left2 == on && right1 == on && right2 == on) //1000
   {
      state = 2;
   }
   if(left1 == off && left2 == on && right1 == on && right2 == off) //1001
   {
      state = 2;
   }
   if(left1 == off && left2 == on && right1 == off && right2 == on) //1010
   {
      state = 5;
   }
   if(left1 == off && left2 == on && right1 == off && right2 == off) //1011
   {
      state = 6;
   }
   if(left1 == off && left2 == off && right1 == on && right2 == on) //1100
   {
      state = 5;
   }
   if(left1 == off && left2 == off && right1 == on && right2 == off) //1101
   {
      state = 7;
   }
   if(left1 == off && left2 == off && right1 == off && right2 == on) //1110
   {
      state = 5;
   }
   if(left1 == off && left2 == off && right1 == off && right2 == off) //1111
   {
      state = 2;
   }
   if(left1 == off && left2 == on && middle == on && right1 == on && right2 == off) state = 1;
   
    states2 = state;

	 switch (state)
   {
    case 0: Car_Back();
       break;
    case 1: Car_Stop_n(n);
       break;
    case 2: Car_Go();
       break;
   //  case 3: Car_Go();
   //     break;
    case 4: Car_Trun_Left1();
       break;
    case 5: Car_Trun_Right1();
       break;
   case 6: Car_Trun_Left2();
       break;
    case 7: Car_Trun_Right2();
       break;
       
    default:
       break;
   }

    if(state == 1)
    {
       count++;
       *sd_ptr = 3;
    }

   if(states1 != states2)
   {
      switch (state)
   {
    case 0: UART_SendStr("BACK \r\n");
       break;
    case 1: case1();
       break;
    case 2: UART_SendStr("FORWARD \r\n");;
       break;
    case 3: UART_SendStr("FORWARD \r\n");
       break;
    case 4: UART_SendStr("TRUN LEFT \r\n");
       break;
    case 5: UART_SendStr("TURN RIGHT \r\n");
       break;
       
    default:
       break;
   }
   states1 = state;
   }
   return count;
   
}

unsigned int Counter(unsigned int count)
{
   // if((left1 == on && left2 == on && right1 == on && right2 == off) || (left1 == on && left2 == on && right1 == off && right2 == on)||
   //       (left1 == on && left2 == off && right1 == on && right2 == on) ||(left1 == on && left2 == off && right1 == off && right2 == on)||
   //       (left1 == off && left2 == on && right1 == on && right2 == on)) count++;

   if(left1 == off && left2 == on && middle == on && right1 == on && right2 == off) count++;
   return count;
}
