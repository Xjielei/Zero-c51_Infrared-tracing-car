/*
 * @Author: Zero_Lei
 * @Date: 2021-12-02 22:07:08
 * @LastEditors: Zero_Lei
 * @LastEditTime: 2021-12-21 18:55:49
 * @Description: file content
 */
#include <reg52.h>

//—” ±n√Î
//12MHZæß’Ò

void delay(unsigned int n)
{
    unsigned int i = 0, j = 0;
    for(i = 0;i < n; i++)
    {
        for(j = 0; j < 21738; j++);
    }
}
