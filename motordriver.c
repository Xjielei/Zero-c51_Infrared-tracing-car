/*
 * @Author: Zero_Lei
 * @Date: 2021-12-02 21:16:17
 * @LastEditors: Zero_Lei
 * @LastEditTime: 2021-12-02 21:47:54
 * @Description: file content
 */
#include <reg52.h>

//����
sbit IN1 = P2^6;
sbit IN2 = P2^5;
//����
sbit IN3 = P2^4;
sbit IN4 = P2^3;

void right_forward()    //����ǰ��
{
    IN3 = 0;
    IN4 = 1;
}

void right_back()       //���ֺ���
{
    IN3 = 1;
    IN4 = 0;
}

void left_forward()     //����ǰ��
{
    IN1 = 1;
    IN2 = 0;
}

void left_back()        //���ֺ���
{
    IN1 = 0;
    IN2 = 1;
}

void right_stop()       //����ֹͣ
{
    IN3 = 1;
    IN4 = 1;
}

void left_stop()        //����ֹͣ
{
    IN1 = 1;
    IN2 = 1;
}