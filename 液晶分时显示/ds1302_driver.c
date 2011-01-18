#include <reg52.h>
#include "declare.h"
sbit  DS1302_CLK = P3^7;              //ʵʱʱ��ʱ�������� 
sbit  DS1302_IO  = P3^6;              //ʵʱʱ������������ 
sbit  DS1302_RST = P2^5;              //ʵʱʱ�Ӹ�λ������
sbit  ACC0 = ACC^0;
sbit  ACC7 = ACC^7;
void delay(int);
unsigned char read_add(unsigned char);
void write_add(unsigned char,unsigned char);
unsigned char bcdconvert(unsigned char bcd)
{
	unsigned char target;
	target=bcd>>4;
	target=target*10+(bcd&=0x0f);
	return(target);
}
unsigned char convertbcd(unsigned char ten)
{
	unsigned char bcd,a,b;
	a=ten/10;
	b=ten%10;
	a=a<<4;
	bcd=(a&=0xf0)+(b&=0x0f);
	return(bcd);
}
void DS1302InputByte(unsigned char d) 	//ʵʱʱ��д��һ�ֽ�(�ڲ�����)
{ 
    unsigned char i;
    ACC = d;
    for(i=8; i>0; i--)
    {
        DS1302_IO = ACC0;           	//�൱�ڻ���е� RRC
        DS1302_CLK = 1;
        DS1302_CLK = 0;
        ACC = ACC >> 1; 
    } 
}
unsigned char DS1302OutputByte(void) 	//ʵʱʱ�Ӷ�ȡһ�ֽ�(�ڲ�����)
{ 
    unsigned char i;
    for(i=8; i>0; i--)
    {
        ACC = ACC >>1;         			//�൱�ڻ���е� RRC 
        ACC7 = DS1302_IO;
        DS1302_CLK = 1;
        DS1302_CLK = 0;
    } 
    return(ACC); 
}
void write_clock(unsigned char ucAddr, unsigned char ucDa)	//ucAddr: DS1302��ַ, ucData: Ҫд������
{
    DS1302_RST = 0;
    DS1302_CLK = 0;
    DS1302_RST = 1;
    DS1302InputByte(ucAddr);       	// ��ַ������ 
    DS1302InputByte(convertbcd(ucDa));       	// д1Byte����
    DS1302_CLK = 1;
    DS1302_RST = 0;
} 
unsigned char read_clock(unsigned char ucAddr)	//��ȡDS1302ĳ��ַ������
{
    unsigned char ucData;
    DS1302_RST = 0;
    DS1302_CLK = 0;
    DS1302_RST = 1;
    DS1302InputByte(ucAddr|0x01);        // ��ַ������ 
    ucData = DS1302OutputByte();         // ��1Byte����
    DS1302_CLK = 1;
    DS1302_RST = 0;
    return(bcdconvert(ucData));
	delay(5);
}
void init_ds1302()
{
	/********��һ���ϵ��ʼ��*******/
/*	year=10; writeyear;
	month=3; writemonth;
	day=31; writeday;
	hour=21; writehour;
	minute=2; writeminute;
	second=13; writesecond;*/
	/*******��24c02��ȡ����*********/

	year=read_add(1); writeyear;
	month=read_add(2); writemonth;
	day=read_add(3); writeday;
	hour=read_add(4); writehour;
	minute=read_add(5); writeminute;
	second=read_add(6); writesecond;
	week=read_add(7);  writeweek;
	alarmhour=read_add(8);
	alarmminute=read_add(9);
}