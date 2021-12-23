/*
 * @Author: Zero_Lei
 * @Date: 2021-12-02 21:29:38
 * @LastEditors: Zero_Lei
 * @LastEditTime: 2021-12-23 11:43:58
 * @Description: file content
 */
#include <reg52.h>
#include "motordriver.h"
#include "delay.h"
#include "show_state.h"
#include "Timer.h"

//运动姿态

void Car_Go()	        //前进
{
    // UART_SendStr("FORWARD \r\n\r\n");
    //PWM_Init(5);
    right_forward();
    left_forward();
    forward_display();
}

void Car_Back()	        //后退
{
    // UART_SendStr("BACK \r\n\r\n");
    //PWM_Init(5);
    right_back();
    left_back();
    back_display();
}

void Car_Trun_Left1()   //左转
{
    // UART_SendStr("TRUN LEFT \r\n\r\n");
    //PWM_Init(3);
    	
    right_forward();
    left_stop();
    left_display();
    
}

void Car_Trun_Left2()   //左转
{
    // UART_SendStr("TRUN LEFT \r\n\r\n");
    //PWM_Init(3);
    	
    right_forward();
    left_back();
    left_display();
    
}

void Car_Trun_Right1()	//右转
{
    // UART_SendStr("TURN RIGHT \r\n\r\n");
    //PWM_Init(3);
    
    left_forward();
    right_stop();
    right_display();
}
void Car_Trun_Right2()	//右转
{
    // UART_SendStr("TURN RIGHT \r\n\r\n");
    //PWM_Init(3);
    
    left_forward();
    right_back();
    right_display();
}

void Car_Stop()		  	//停止
{
    // UART_SendStr("STOP \r\n\r\n");
    
    right_stop();
    left_stop();
    stop_display1();
}

void Car_Stop_n( unsigned int n )		  	//停止ns
{
    unsigned int i;
    right_stop();
    left_stop();

    vzero_display();

	for(i = n; i > 0; i--)
    {
        stop_display(i);
        delay(1);
    }  

    Car_Go();
    delay(3);
    
}