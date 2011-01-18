#include<reg52.h>
#include "code.h"
#include "code1.h"
#define uchar unsigned char
#define uint unsigned int 
#define AddressSend {}
sbit ce=P2^7;
sbit rw=P3^6;
sbit rd=P3^7;
sbit cd=P2^6;
sbit rst=P2^5;
uint address;
uchar data1,data2,cmd;
void clear();
void delay(uint z)
{
	uint i,j;
	for(i=z;i>0;i--)
		for(j=110;j>0;j--);
}
void delayus(uint z)
{
	while(z--);
}
void WriteData(uchar dat)           //д����    
{    ce=1;
     cd=0;
    rw=0;
     P0=dat; 
   delayus(12);

	ce=0;
     rw=1;
}   
void WriteCommand(uchar cmd)           //д����    
{   ce=1;
     cd=1;
     rw=0;
     P0=cmd;
delayus(12);
	ce=0;
     rw=1;
} 
void WriteDC(uchar dat,uchar cmd)      //дһ�����ݺ�һ��ָ�� 
{   
     WriteData(dat);   
     WriteCommand(cmd);   
} 
void WriteDDC(uchar data1, uchar data2, uchar cmd)   //д�������ݺ�һ��ָ�� 
{   
     WriteData(data1);         
     WriteData(data2);   
     WriteCommand(cmd);     
}   
void LCD_Init(void)         //Һ����ʼ�� 
{   
     uchar data1,data2,cmd;    
   		rw=1;
        
     
     data1 = 0x00;   
     data2 = 0x10;              //ͼ����ʾռ��32*128=0xfff�����ı���0x1000��ʼ
     cmd = 0x40;                //�����ı���ʾ���׵�ַ    
     WriteDDC(data1,data2,cmd);   
     data1 = 0x20;              //����������ʾ
     data2 = 0x00;   
     cmd = 0x41;                //�����ı���ʾ�����    
     WriteDDC(data1,data2,cmd);   
     data1 = 0x00;   
     data2 = 0x00;   
     cmd = 0x42;                //����ͼ����ʾ���׵�ַ    
     WriteDDC(data1,data2,cmd);   
     data1 = 0x1e;   
     data2 = 0x00;   
     cmd = 0x43;                //����ͼ����ʾ�����    
     WriteDDC(data1,data2,cmd); 
   cmd =0xa2;                 //���ù����״ 
   WriteCommand(cmd); 
     cmd = 0x80;                //��ʾ��ʽ����
                              //�����ⲿ�ַ�������,��ʾ��ʽ���ı���ͼ���� 
     WriteCommand(cmd); 
     cmd = 0x9e;                //���ù����˸,��겻��ʾ,�ı���ʾ��ͼ����ʾ    
     WriteCommand(cmd);   
}



void WriteOneChinese(uchar *codes)
{
	uchar i=0,j=0;
	for(i=0;i<32;i++)
	{
		WriteData(codes[i]);
		j++;
		if(j==2)
		{
			WriteCommand(0xb2);           //�˳��Զ�дģʽ
		    address=address+30;
		    data1 = address;                 //ȡ��ַ�Ͱ�λ    
		    data2 = address>>8;                //ȡ��ַ�߰�λ    
		    cmd = 0x24; 
		    WriteDDC(data1,data2,cmd);
		    j=0;
		    WriteCommand(0xb0);         //�����Զ�дģʽ		
		}
	}
}
void writezi(uchar row,uchar rol)
{
	uint k,h=0,total;
	uchar t;
	total=sizeof(CG_code)/32/15-6;
	for(t=0;t<total;t++)
	{
		address = row*30+rol;
		data1 = address;                 //ȡ��ַ�Ͱ�λ    
		data2 = address>>8;                //ȡ��ַ�߰�λ    
		cmd = 0x24; 
		WriteDDC(data1,data2,cmd);
	//	WriteCommand(0xb0);//�Զ�дģʽ
		for(k=1;k<121;k++)
		{   
			h++;
			WriteCommand(0xb2); 
		    address = row*30+rol+2*(h-1);
			data1 = address;                 //ȡ��ַ�Ͱ�λ    
			data2 = address>>8;                //ȡ��ַ�߰�λ    
			cmd = 0x24; 
			
			WriteDDC(data1,data2,cmd);
		    WriteCommand(0xb0);
			WriteOneChinese(&CG_code[((k-1)+15*t)*32]);
			if((t==total-1)&&(k==(sizeof(CG_code)/32%15)+105)) break;
			if(((t>0)&&(k>107))||(t==0))
		   		 delay(1000);
			if(k%15==0)
		    {row=row+16;h=0;}
		}
		row=0;rol=0;
		if(t<total-1)
		clear();
	}
}
void WriteImage(uchar row,uchar rol,uchar hight,uchar width)
{
	uint i;
	address=row*30+rol;
	data1=address;
	data2=address>>8;
	WriteDDC(data1,data2,0x24);
	WriteCommand(0xb0);
	for(i=0;i<(hight*width)/8;i++)
	{
		WriteData(Image_code[i]);
		delay(10);
	}
	WriteCommand(0xb2);
}
void clear()
{
	uint i;
	WriteCommand(0xb2);
	data1 = 0x00;                 //ȡ��ַ�Ͱ�λ    
	data2 = 0x00;                //ȡ��ַ�߰�λ    
	cmd = 0x24; 
	WriteDDC(data1,data2,cmd);
	WriteCommand(0xb0);//�Զ�дģʽ
	for(i=0;i<5000;i++)
	{
		WriteData(0x00);
	}
		WriteCommand(0xb2);
}
void main()   
{   
	rst=0;
	delay(5);
	rst=1;
	rd=1;  
	LCD_Init();
	clear();
	WriteImage(0,0,240,128);
	delay(10000);
	clear();
	writezi(0,0);
	while(1);
}

