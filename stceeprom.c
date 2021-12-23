/*
 * @Author: Zero_Lei
 * @Date: 2021-12-18 16:30:11
 * @LastEditors: Zero_Lei
 * @LastEditTime: 2021-12-18 17:39:26
 * @Description: file content
 */

sfr isp_data=0xe2;
sfr isp_addrh=0xe3;
sfr isp_addrl=0xe4;
sfr isp_cmd=0xe5;
sfr isp_trig=0xe6;
sfr isp_contr=0xe7;

// void EEPROMSetAddress(unsigned int addr)
// {
//     addr+=0x2000; //��ʼ����ַΪ0x2000
//     isp_addrh=(unsigned char)(addr>>8); //���ö�д��ַ���ֽ�
//     isp_addrl=(unsigned char) addr; //���ö�д��ַ���ֽ�
// }
 
//����Ƭ��EEPROM��һ������
//����ֻ��������Ϊ��С��λ���У�û��ֻ����һ���ֽ�
//һ��������512���ֽ�
//��������������ĵ�ַ�����ĸ�������������������ݶ���������
//���磺STC89C51RCƬ��EEPROM��һ������ʼ��ַΪ0x2000��������ַΪ0x21ff
//������� eepromEraseSector(0x2001)�����һ���������ݶ���������
//�����ɹ��󣬸������ڸ��ֽڶ�����Ϊ0xff
void eepromEraseSector (unsigned int address)
{
	unsigned char i;
	isp_addrl=address;
	isp_addrh=address>>8;
	isp_contr=0x01; 
	isp_contr=isp_contr|0x81; // 0x80 if SYSCLK<40MHz, 0x81 if SYSCLK<20MHz, 0x82 if SYSCLK<10MHz, 0x83 if SYSCLK<5MHz
	isp_cmd=0x03; 
	isp_trig=0x46;
	isp_trig=0xb9;
	for(i=0;i<3;i++);
	isp_addrl=0xff;
	isp_addrh=0xff;
	isp_contr=0x00;
	isp_cmd=0x00;
	isp_trig=0x00;
}
 
//��STCƬ��EEPROM��ָ����ַд�����ݣ������ֽڱ�̣���
//ע�⣺�ֽڱ����ָ��eeprom��1д��1��0����0д��0�����޷���0д��1
//���ԣ���д������ǰ��һ��Ҫ�����������������ֽڱ�Ϊ0xff
void eepromWrite(unsigned int address, unsigned int write_data)
{
	unsigned int i;
	isp_data=write_data;
	isp_addrl=address;
	isp_addrh=address>>8;
	isp_contr=0x01; 
	isp_contr=isp_contr|0x81; // 0x80 if SYSCLK<40MHz, 0x81 if SYSCLK<20MHz, 0x82 if SYSCLK<10MHz, 0x83 if SYSCLK<5MHz
	isp_cmd=0x02;
	isp_trig=0x46;
	isp_trig=0xb9;
	for(i=0;i<3;i++);
	isp_addrl=0xff;
	isp_addrh=0xff;
	isp_contr=0x00;
	isp_cmd=0x00;
	isp_trig=0x00;
}
 
 
 
//��ȡSTC��Ƭ���ڲ�EEPROM��һ���ֽ�
//��Ҫ��ͬ��STC��Ƭ��EEPROM��ʼ��ַ��ͬ
//���磺STC89c52RC��Ƭ��EEPROM��ʼ��ַΪ0x2000
unsigned int eepromRead(unsigned int address)
{
	unsigned int i,z;
	isp_addrl=address;
	isp_addrh=address>>8;
	isp_contr=0x01;
	isp_contr=isp_contr|0x81; // 0x80 if SYSCLK<40MHz, 0x81 if SYSCLK<20MHz, 0x82 if SYSCLK<10MHz, 0x83 if SYSCLK<5MHz
	isp_cmd=0x01;
	isp_trig=0x46;
	isp_trig=0xb9;
	for(i=0;i<3;i++);
	isp_addrl=0xff;
	isp_addrh=0xff;
	isp_contr=0x00;
	isp_cmd=0x00;
	isp_trig=0x00;
	z=isp_data;
	return(z);
}
