#include  "MY_OSGPRS.h"
#include  "MY_OSuart.h"

OSuartContorler GPRS_UART;

//初始化GPRS模块
 void OS_InitGPRS(void)
{
	OS_uartInit(&GPRS_UART);//初始化串口控制器
}


//发送调试信息
void Dug_msg(char *data)
{
	#ifdef Open_Dug
	Dug_Uart((char *)data);
	#endif
}
//发送数据到GPRS模块
u8 OS_GPRS_CMDsend(char *CMD,char *Response,u32 Timerout,u8 Retry)
{
	u8 i;
	u32 delay_timer=0;
	char  now_buff[50]={0};
	GPRS_UART.ReceivClean();//清除缓存
	for(i=0;i<Retry;i++)//发送重复次数
		{
			UART_send(CMD);//发送GPRS命令
			Dug_msg(CMD);
			while(!GPRS_UART.Get_ReciveState())//等待接收完成
				{
					delay_timer++;
					OS_delay_ms(1);
					if(delay_timer > Timerout)break;//等待时间溢出
					Dug_Uart("GPRS Timer out\r\n");
				}
			//比较返回的数据是否满足
			GPRS_UART.GetByte(0,(u8 *)now_buff,GPRS_UART.Get_buffLen());
			Dug_msg(now_buff);
			if(!OS_strstr((char *)now_buff, Response))
				{
					return 1;//执行成功
				}
			GPRS_UART.ReceivClean();       //开启下次接收
			OS_memset(now_buff,null,50);//清除当前buff
				
			
		}
	return 0;//执行失败
}


//异常状态提示函数
void  OS_ErroLoop(u8 loop)
{
	switch (loop)
		{
			case 0:Dug_msg("Module detection error!\r\n"); break;			 //模块无法正常通讯
			case 1:Dug_msg("Wrong installation of phone card!\r\n"); break;  //sim卡安装错误
			case 2:Dug_msg("Network registration error!\r\n"); break;		//网络注册失败
			case 3:Dug_msg("To locate failure!\r\n"); break;			   //定位消息获取失败
			default:break;
		}
}





