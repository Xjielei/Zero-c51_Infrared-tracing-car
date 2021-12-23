/*
 * @Author: Zero_Lei
 * @Date: 2021-12-18 16:30:04
 * @LastEditors: Zero_Lei
 * @LastEditTime: 2021-12-18 17:30:20
 * @Description: file content
 */

#ifndef __EEPROM_H__
#define __EEPROM_H__
 
#define STC_EEPROM_START_ADDR 0x2000  //STC89C52RC片内EEPROM起始地址
 
unsigned char eepromRead( unsigned int address );
void eepromWrite( unsigned int address, unsigned char writeData );
void eepromEraseSector( unsigned int address );
 
#endif
