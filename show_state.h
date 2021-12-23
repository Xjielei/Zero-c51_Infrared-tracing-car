/*
 * @Author: Zero_Lei
 * @Date: 2021-12-16 10:25:23
 * @LastEditors: Zero_Lei
 * @LastEditTime: 2021-12-18 16:11:41
 * @Description: file content
 */

#ifndef _SHOW_STATE_H
#define _SHOW_STATE_H

void init_lcd();
void fast_display();
void slow_display();
void forward_display();
void back_display();
void left_display();
void right_display();
void stop_display(unsigned int n);
void stop_display1();
void stoptimes_display(unsigned int n);
void vzero_display();

#endif
