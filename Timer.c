/*
 * @Author: Zero_Lei
 * @Date: 2021-12-02 21:35:17
 * @LastEditors: Zero_Lei
 * @LastEditTime: 2021-12-23 12:51:38
 * @Description: file content
 */
#include <reg52.h>
#include "show_state.h"

sbit ENR = P2^0;        //右 使能
sbit ENL = P2^1;        //左 使能

// unsigned int PWMR=100, PWML=100, t=0;
//右轮、左轮占空比以及设定的比较值

unsigned int t = 0, PWMR = 3,PWML = 3;
void PWM_Init(unsigned int Pwm)
{
    PWMR = Pwm;
    PWML = Pwm;
}

void Timer0_Init()           //初值100微秒
{
    TMOD |= 0x01;    //定时器0，工作方式1，仅用TR0打开启动

    TH0 = (65536-100)/256;   //高八位
    TL1 = (65536-100)%256;    //低八位

    ET0 = 1;  //中断允许
    TR0 = 1;  //打开定时器
    EA = 1;
}

//中断
void Timer0_Routinue() interrupt 1
{
    t++;
    if(t < PWML) ENL = 1;
    else ENL = 0;
    if(t < PWMR) ENR = 1;
    else ENR = 0;
    if(t > 4) t = 0;
}