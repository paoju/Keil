#include <reg52.h>
void comm_init()
{	//REN=1; //��������
	SCON=0x50;
	TMOD=0X20;//���ö�ʱ��1������ʽ
	PCON=0x00;
	TH1=0XF3;//װ��ֵ
	TL1=0XF3;//װ��ֵ
	EA=1;
	EX0=1; IT0=1;
	ES=0;
	IP=0X10;
	TR1=1;//�򿪶�ʱ��1
	SM0=0;
	SM1=1;
	REN=1;
}