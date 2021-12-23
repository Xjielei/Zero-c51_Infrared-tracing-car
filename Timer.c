/*
 * @Author: Zero_Lei
 * @Date: 2021-12-02 21:35:17
 * @LastEditors: Zero_Lei
 * @LastEditTime: 2021-12-23 12:51:38
 * @Description: file content
 */
#include <reg52.h>
#include "show_state.h"

sbit ENR = P2^0;        //�� ʹ��
sbit ENL = P2^1;        //�� ʹ��

// unsigned int PWMR=100, PWML=100, t=0;
//���֡�����ռ�ձ��Լ��趨�ıȽ�ֵ

unsigned int t = 0, PWMR = 3,PWML = 3;
void PWM_Init(unsigned int Pwm)
{
    PWMR = Pwm;
    PWML = Pwm;
}

void Timer0_Init()           //��ֵ100΢��
{
    TMOD |= 0x01;    //��ʱ��0��������ʽ1������TR0������

    TH0 = (65536-100)/256;   //�߰�λ
    TL1 = (65536-100)%256;    //�Ͱ�λ

    ET0 = 1;  //�ж�����
    TR0 = 1;  //�򿪶�ʱ��
    EA = 1;
}

//�ж�
void Timer0_Routinue() interrupt 1
{
    t++;
    if(t < PWML) ENL = 1;
    else ENL = 0;
    if(t < PWMR) ENR = 1;
    else ENR = 0;
    if(t > 4) t = 0;
}