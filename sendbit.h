/*
 * @Author: Zero_Lei
 * @Date: 2021-12-04 10:09:59
 * @LastEditors: Zero_Lei
 * @LastEditTime: 2021-12-04 15:07:25
 * @Description: file content
 */
#ifndef _SENDBIT_H
#define _SENDBIT_H

#include "reg52.h"

#define u8  unsigned char
#define u16 unsigned int

#define USART_RX_LEN 20  //���ջ��泤��(���𳬹�оƬromʣ��ռ��С)  
#define USART_TX_LEN 20  //���ͻ��泤��

typedef struct      //������ؽṹ�嶨��(��Ҫ���ڽ���)��
{
    u8 RX_BUFF[USART_RX_LEN]; //���ջ���
    u8 TX_BUFF[USART_TX_LEN]; //���ͻ���
    u16 RX_COUNT;
}UART;
extern UART Uart;//�����ṹ��


//�ⲿ�ɵ��õĺ���������
void UART_Configure(u16 BaudRate); //��ʹ������
void UART_SendByte(u8 dat); //���ַ�����
void UART_Send(u8* arr,u16 len);//���ַ�����
void UART_SendStr(u8* str);//�ַ�������
void UART_RX_BUFF_Clear(void);//���ջ����������
void UART_TX_BUFF_Clear(void);//���ͻ����������

#endif