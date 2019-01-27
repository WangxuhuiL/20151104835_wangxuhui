#include "led.h"
#include "delay.h"
#include "sys.h"


#define INIT 			0x00
#define JIAOSHUI 	0x01
#define BUGUANG		0x02
#define GETMESG		0x03
#define SOMEONE   0x09

char tab[16];
u8 readDhtFlag=0;		//读取温湿度标志  定时器中处理
u8 lighFlag=0;			//光照标志


int main(void)
 {
 	unsigned int i;
	delay_init();	    	 //延时函数初始化
	NVIC_Configuration();//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);   //串口初始化

 	LED_Init();		   //LED端口初始化
	KEY_Init();          //按键端口初始化
	TIM3_Int_Init(499,7199);//10Khz的计数频率，计数到500为50ms 
	 
	led_gsm=0;//打开蜂鸣器
	 

	ligh=1;		//灯光
	relay=1;		//继电器
	delay_ms(200);
	ligh=0;		//关闭灯光
	relay=0;		//关闭继电器

	for(i=0;i<50;i++)
	delay_ms(100);          //延时有助于稳定

	UART_SendStr(USART1 , "AT+CMGF=1\r\n",11);   //设置字符集
	for(i=0;i<5;i++)
	delay_ms(100);          //延时有助于稳定


	
	led_gsm=1;//关闭led
	while(1)
	{
		if(readDhtFlag==1)
		{
			readDhtFlag=0;
			DHT11_ReadData();	//是否读取到温湿度			
			
			if(check_ligh==1)			//查看光照强度
				{lighFlag = 'L';}
				else
				{lighFlag = 'H';}	
				
				sprintf(tab,"Temp:%02d DH:%02d %c ",(u16)DHT11.Tem_H,(u16)DHT11.Hum_H,lighFlag);
	   		Lcd_Puts(0,1,(unsigned char *)tab);	//初始化显示 
								
				if(mesgJiaoShuiFlag==0)	//短信不在控制时				
				{
					if(DHT11.Hum_H<35)			  //
					{relay=1;}		//打开继电器											
					else
					{relay=0;}		//关闭继电器										
				}			
				
				if(mesgBuguangFlag==0)	//短信不在控制时		
				{			
					if(check_ligh==1)
					{ligh=1;}		//打开灯光									
					else
					{ligh=0;}		//关闭灯光											
				}	
		}
		

	}
}

