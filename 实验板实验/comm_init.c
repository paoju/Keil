#include <reg52.h>
void comm_init()
{
	REN=1; //��������
	SCON=0x52;
	TMOD=0X21;//���ö�ʱ��1������ʽ
	TH1=0XF3;//װ��ֵ
	TL1=0XF3;//װ��ֵ
	TR1=1;//�򿪶�ʱ��1
	SM0=0; //���÷�ʽ1
	SM1=1;
	EA=1;
}