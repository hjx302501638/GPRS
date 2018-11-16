#include  "MY_OSGPRS.h"
#include  "MY_OSuart.h"

OSuartContorler GPRS_UART;

//��ʼ��GPRSģ��
 void OS_InitGPRS(void)
{
	OS_uartInit(&GPRS_UART);//��ʼ�����ڿ�����
}


//���͵�����Ϣ
void Dug_msg(char *data)
{
	#ifdef Open_Dug
	Dug_Uart((char *)data);
	#endif
}
//�������ݵ�GPRSģ��
u8 OS_GPRS_CMDsend(char *CMD,char *Response,u32 Timerout,u8 Retry)
{
	u8 i;
	u32 delay_timer=0;
	char  now_buff[50]={0};
	GPRS_UART.ReceivClean();//�������
	for(i=0;i<Retry;i++)//�����ظ�����
		{
			UART_send(CMD);//����GPRS����
			Dug_msg(CMD);
			while(!GPRS_UART.Get_ReciveState())//�ȴ��������
				{
					delay_timer++;
					OS_delay_ms(1);
					if(delay_timer > Timerout)break;//�ȴ�ʱ�����
					Dug_Uart("GPRS Timer out\r\n");
				}
			//�ȽϷ��ص������Ƿ�����
			GPRS_UART.GetByte(0,(u8 *)now_buff,GPRS_UART.Get_buffLen());
			Dug_msg(now_buff);
			if(!OS_strstr((char *)now_buff, Response))
				{
					return 1;//ִ�гɹ�
				}
			GPRS_UART.ReceivClean();       //�����´ν���
			OS_memset(now_buff,null,50);//�����ǰbuff
				
			
		}
	return 0;//ִ��ʧ��
}


//�쳣״̬��ʾ����
void  OS_ErroLoop(u8 loop)
{
	switch (loop)
		{
			case 0:Dug_msg("Module detection error!\r\n"); break;			 //ģ���޷�����ͨѶ
			case 1:Dug_msg("Wrong installation of phone card!\r\n"); break;  //sim����װ����
			case 2:Dug_msg("Network registration error!\r\n"); break;		//����ע��ʧ��
			case 3:Dug_msg("To locate failure!\r\n"); break;			   //��λ��Ϣ��ȡʧ��
			default:break;
		}
}





