#include <REG2051.H>
#define k1 P3_4
#define csbout    P3_5 			//����������
#define csbint    P3_7 			//����������
#define bg  P3_3 
#define LED P1 
#define LED1 P3_0 //LED����
#define LED2 P3_1 //LED����
#define LED3 P3_2 //LED����

unsigned char cl,mqzd,csbs,csbds,buffer[3],xm1,xm2,xm0,jpjs;//��ʾ��ʶ
unsigned char convert[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};//0~9����
unsigned int s,t,i,xx,j,sj1,sj2,sj3,mqs,sx1;
int tempreture;
int csbc;
int code sonic[][2]={{-30,313},{-20,319},{-10,325},{0,323},{10,338},{20,344},{30,349},{100,386}};
				
void csbcj();
void delay(j);					//��ʱ����
void scanLED();					//��ʾ����
void timeToBuffer();			//��ʾת������
void keyscan();
void k1cl();
void k2cl();
void k3cl();
void k4cl();
void offmsd();
int readtemp();
void main()					//������
{
	unsigned char i;
	EA=1;		   			//���ж�
  	TMOD=0x11; 				//�趨ʱ��0Ϊ�������趨ʱ��1��ʱ
	ET0=1; 					//��ʱ��0�ж����� 
	ET1=1; 					//��ʱ��1�ж����� 
	TH0=0x00;
	TL0=0x00;
	TH1=0x9E;
	TL1=0x57;
	csbds=0;
	csbout=1;
	cl=0;
	csbs=8;
	jpjs=0;
	sj1=50;
	sj2=200;
	sj3=580;
	k4cl();
	TR1=1; 				//�趨ʱֵ1Ϊ20ms 
	while(1)
  	{
		keyscan();
		if(jpjs<1)
		{
			tempreture=readtemp();
			for(i=0;i<7;i++)
			{
				if(tempreture>=sonic[i][0])
				{
					if(tempreture<=sonic[i+1][0])
					{
						csbc=sonic[i][1];
						csbc/=10000;
						break;
					}
				}
			}
			csbcj();		//���ó�����������
			if(s>sj3)		//����ʱ��ʾ��CCC��
			{
				buffer[2]=0xC6;	
				buffer[1]=0xC6;	
				buffer[0]=0xC6;	
			}
			else if(s<sj1)	//С��ʱ��ʾ��- - -��
			{
				buffer[2]=0xBF;	
				buffer[1]=0xBF;	
				buffer[0]=0xBF;
			}
			else timeToBuffer();	
		}
		else timeToBuffer();		//��ֵת����LED����
		offmsd();
	  	scanLED();			//��ʾ����
		if(s<sj2)
		bg=0;
		bg=1;
	}
}

void scanLED()			     //��ʾ����ģ��
{
 	LED=buffer[0];
	LED3=0;
	delay(200);
	LED3=1;

	LED=buffer[1];
	LED2=0;
	delay(200);
	LED2=1;
	
	LED=buffer[2];
	LED1=0;
	delay(200);
	LED1=1;
}

void timeToBuffer()		    //ת�����빦��ģ��
{
	xm0=s/100;	
	xm1=(s-100*xm0)/10;
	xm2=s-100*xm0-10*xm1;
	buffer[2]=convert[xm2];	
	buffer[1]=convert[xm1];
	buffer[0]=convert[xm0];
}

void delay(i)					
{
    while(--i);
}

void timer1int (void)  interrupt 3  using 2 
{
	TH1=0x9E;
	TL1=0x57;
	csbds++;
	if(csbds>=40)
	{
		csbds=0;
		cl=1;
	}		
}

void csbcj()
{
	if(cl==1)
	{
   		TR1=0;
		TH0=0x00;
		TL0=0x00;
		i=csbs;
		while(i--)
		{
			csbout=!csbout;
		}
		TR0=1;			
   		i=mqs;					//ä��
		while(i--)
		{
		}
		i=0;
		while(csbint)
		{
			i++;
			if(i>=4000)			//����ֵ
			csbint=0;
		}
		TR0=0;
		TH1=0x9E;
		TL1=0x57;
		t=TH0;
		t=t*256+TL0;
		t=t-29;		
		s=t*csbc/2;
		TR1=1;
		cl=0;
		csbint=1;
		if(s<sj1)
		{
			if(csbs>6)
			{
				csbs=csbs-2;
				sj1=40;
			}
			sj1=sj1+2;
			k4cl();
		}
		else if(s>=sj3)
		{
			if(csbs<32)
			{
				csbs=csbs+2;
				sj1=sj1+10;
				k4cl();
			}
		}
	}
}

void keyscan()				//���̴�����
{
	xx=0;
	if(k1!=1)					// �жϿ����Ƿ���
	{
		delay(100);				//��ʱȥ����
		if(k1!=1)					// �жϿ����Ƿ���	
		{		
			while(!k1)
			{
				delay(25);	
				xx++;
			}
			if(xx>1000)		
			{
				jpjs++;
				if(jpjs>3)
				{
					k4cl();
					jpjs=0;
				}
			}
			xx=0;
			switch(jpjs)
			{
				case 1: k1cl();break;		
				case 2: k2cl();break;
				case 3: k3cl();break;
			}
		}
	}
}

void k1cl()
{
	sj1=sj1+1;
	if(sj1>100)
	sj1=50;
	s=sj1;
}
void k2cl()
{
	sj2=sj2+5;
	if(sj2>500)
	sj2=40;
	s=sj2;
}

void k3cl()
{
	sj3=sj3+10;
	if(sj3>600)
	sj3=600;
	s=sj3;
}

void k4cl()
{
	sx1=sj1-1;
	sx1=sx1/csbc;
	mqs=sx1/4.5;
}

void offmsd()							    //Сʱ��ʮλΪ0�ж�ģ��
{
    if (buffer[0] == 0xC0)    				//���ֵΪ��ʱС��ʮλ����ʾ
    buffer[0] = 0xFF;
}
