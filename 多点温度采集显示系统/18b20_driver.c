#include <reg52.h>
sbit DQ0=P3^0;//������0
sbit DQ1=P3^1;
sbit DQ2=P3^2;
sbit DQ3=P3^3;
sbit DQ4=P3^4;
sbit DQ5=P3^5;
sbit DQ6=P3^6;
sbit DQ7=P3^7;
extern bit symbol;//main.c�е�symbol
//΢����ʱ
void delayus(unsigned int i)
{
	 while(i--);
}
//��ÿ�������߷ֿ�����
void DQoperate(unsigned char num,bit buff)
{
	switch(num)
	{
		case 0: if(buff==0) DQ0=0; else DQ0=1; break;
		case 1: if(buff==0) DQ1=0; else DQ1=1; break;
		case 2: if(buff==0) DQ2=0; else DQ2=1; break;
		case 3: if(buff==0) DQ3=0; else DQ3=1; break;
		case 4: if(buff==0) DQ4=0; else DQ4=1; break;
		case 5: if(buff==0) DQ5=0; else DQ5=1; break;
		case 6: if(buff==0) DQ6=0; else DQ6=1; break;
		case 7: if(buff==0) DQ7=0; else DQ7=1; break;
	}
}
//��������
unsigned char readDQ(unsigned char num)
{
	bit buff;
	switch(num)
	{
		case 0: buff=DQ0; break;
		case 1: buff=DQ1; break;
		case 2: buff=DQ2; break;
		case 3: buff=DQ3; break;
		case 4: buff=DQ4; break;
		case 5: buff=DQ5; break;
		case 6: buff=DQ6; break;
		case 7: buff=DQ7; break;
	}
	return buff;
}
//18b20��ʼ������
init_ds18b20(unsigned char num)
{
	 unsigned char x=0;
	 DQoperate(num,1);
	 delayus(8);  //������ʱ
	 DQoperate(num,0);
	 delayus(80); //��ȷ��ʱ ���� 480us
	 DQoperate(num,1);
	 delayus(14);
	 x=readDQ(num);      //������ʱ�� ���x=0���ʼ���ɹ� x=1���ʼ��ʧ��
	 delayus(20);
}
//��һ���ֽ�
unsigned char readonechar(unsigned char num)
{
	unsigned char i=0;
	unsigned char dat=0;
	for (i=8;i>0;i--)
	{
		DQoperate(num,0);
		dat>>=1;
		DQoperate(num,1);
		if(readDQ(num))
		dat|=0x80;
		delayus(4);
	}
return(dat);
}
//дһ���ֽ�
void writeonechar(unsigned char num,unsigned char dat)
{	
	unsigned char i=0;
	for (i=8; i>0; i--)
	{
		DQoperate(num,0);
		DQoperate(num,dat&0x01);
		delayus(5);
		DQoperate(num,1);
		dat>>=1;
	}
delayus(4);
}
//��ȡ�¶�
unsigned int readtemp(unsigned char num)
{
	unsigned char a=0;
	unsigned char b=0;
	unsigned int t=0;
	float tt=0;
	init_ds18b20(num);
	writeonechar(num,0xcc); // ����������кŵĲ���
	writeonechar(num,0x44); // �����¶�ת��
	init_ds18b20(num);
	writeonechar(num,0xcc); //����������кŵĲ���
	writeonechar(num,0xbe); //��ȡ�¶ȼĴ��������������¶�
	a=readonechar(num);
	b=readonechar(num);
	t=b;
	if(t<8)	//�����λΪ0����Ϊ����
	{
		symbol=0;
		t<<=8;
		t|=a;
	}
	else
	{
		symbol=1;
		t<<=8;
		t|=a;
		t=~t;//ȡ��+1ȡ�෴��
		t+=1;
	}	
	tt=t*0.0625;
	t= tt*10+0.5;
	return(t);
}