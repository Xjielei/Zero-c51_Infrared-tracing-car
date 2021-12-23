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

#define USART_RX_LEN 20  //接收缓存长度(请勿超过芯片rom剩余空间大小)  
#define USART_TX_LEN 20  //发送缓存长度

typedef struct      //串口相关结构体定义(主要用于接收)：
{
    u8 RX_BUFF[USART_RX_LEN]; //接收缓存
    u8 TX_BUFF[USART_TX_LEN]; //发送缓存
    u16 RX_COUNT;
}UART;
extern UART Uart;//声明结构体


//外部可调用的函数声明：
void UART_Configure(u16 BaudRate); //初使化函数
void UART_SendByte(u8 dat); //单字符发送
void UART_Send(u8* arr,u16 len);//多字符发送
void UART_SendStr(u8* str);//字符串发送
void UART_RX_BUFF_Clear(void);//接收缓存数据清除
void UART_TX_BUFF_Clear(void);//发送缓存数据清除

#endif