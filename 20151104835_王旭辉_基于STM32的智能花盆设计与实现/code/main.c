#include "led.h"
#include "delay.h"
#include "sys.h"


#define INIT 			0x00
#define JIAOSHUI 	0x01
#define BUGUANG		0x02
#define GETMESG		0x03
#define SOMEONE   0x09

char tab[16];
u8 readDhtFlag=0;		//��ȡ��ʪ�ȱ�־  ��ʱ���д���
u8 lighFlag=0;			//���ձ�־


int main(void)
 {
 	unsigned int i;
	delay_init();	    	 //��ʱ������ʼ��
	NVIC_Configuration();//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);   //���ڳ�ʼ��

 	LED_Init();		   //LED�˿ڳ�ʼ��
	KEY_Init();          //�����˿ڳ�ʼ��
	TIM3_Int_Init(499,7199);//10Khz�ļ���Ƶ�ʣ�������500Ϊ50ms 
	 
	led_gsm=0;//�򿪷�����
	 

	ligh=1;		//�ƹ�
	relay=1;		//�̵���
	delay_ms(200);
	ligh=0;		//�رյƹ�
	relay=0;		//�رռ̵���

	for(i=0;i<50;i++)
	delay_ms(100);          //��ʱ�������ȶ�

	UART_SendStr(USART1 , "AT+CMGF=1\r\n",11);   //�����ַ���
	for(i=0;i<5;i++)
	delay_ms(100);          //��ʱ�������ȶ�


	
	led_gsm=1;//�ر�led
	while(1)
	{
		if(readDhtFlag==1)
		{
			readDhtFlag=0;
			DHT11_ReadData();	//�Ƿ��ȡ����ʪ��			
			
			if(check_ligh==1)			//�鿴����ǿ��
				{lighFlag = 'L';}
				else
				{lighFlag = 'H';}	
				
				sprintf(tab,"Temp:%02d DH:%02d %c ",(u16)DHT11.Tem_H,(u16)DHT11.Hum_H,lighFlag);
	   		Lcd_Puts(0,1,(unsigned char *)tab);	//��ʼ����ʾ 
								
				if(mesgJiaoShuiFlag==0)	//���Ų��ڿ���ʱ				
				{
					if(DHT11.Hum_H<35)			  //
					{relay=1;}		//�򿪼̵���											
					else
					{relay=0;}		//�رռ̵���										
				}			
				
				if(mesgBuguangFlag==0)	//���Ų��ڿ���ʱ		
				{			
					if(check_ligh==1)
					{ligh=1;}		//�򿪵ƹ�									
					else
					{ligh=0;}		//�رյƹ�											
				}	
		}
		

	}
}

