#include <stdio.h>
#include <reg52.h>
void comm_init()
{
	REN=1; //��������
	SCON=0x52;
	TMOD=0X21;//���ö�ʱ��1������ʽ
	TH1=0XFF;//װ��ֵ
	TL1=0XFF;//װ��ֵ
	TR1=1;//�򿪶�ʱ��1
	SM0=0; //���÷�ʽ1
	SM1=1;
	EA=1;
}
void delay(int z)
{
	int i,j;
        for(i=z;i>0;i--)
         for(j=110;j>0;j--);
}
void main()
{
	unsigned char i;
	i='x';
	comm_init();
	while(1)
	{
		puts("23332");
		delay(1000);
	}
}