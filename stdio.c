#include <stdio.h>
#include <reg52.h>
void main()
{
	char way;
	float a,b;
	REN=1; //��������
	SCON=0x52;
	TMOD=0X20;//���ö�ʱ��1������ʽ
	TH1=0XF3;//װ��ֵ
	TL1=0XF3;//װ��ֵ
	TR1=1;//�򿪶�ʱ��1
	SM0=0; //���÷�ʽ1
	SM1=1;
	printf("%s\n","what is your name?");
	while(1)
	{
		scanf("%f#%f#%d",a,b,way);
		
	}
}
