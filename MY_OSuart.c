#include "MY_OSuart.h"
OSuartData UartData;



/***********************************************
*�޸�ʱ�䣺18-11-8
*�������ܣ������ݻ�������ӵ������� �����滻��
��������
*���ز����������滻λ��
*����˵����byte �ַ� addr�滻λ�� 		 	
***********************************************/
u16 ReceivOneByte(u8 byte,u16 addr)
{
	if((addr < uart_MAXbuffLen)&&(addr != 0))
     	UartData.uart_buff[addr] = byte;
	else 
		{
			UartData.uart_buff[UartData.uart_buff_len&0x3fff] = byte;
			UartData.uart_buff_len++;
		}
	return addr;
}

/***********************************************
*�޸�ʱ�䣺18-11-8
*�������ܣ������ݻ�������Ӷ����������
*���ز����������滻λ��
*����˵����*byte �ַ��� addr�滻λ��  bytelen 
�滻����		 	
***********************************************/
u16 ReceivByte(u8 *byte,u16 addr,u16 bytelen)
{
	OS_memcpy(&UartData.uart_buff[addr], byte, bytelen);	
	return addr;
}

/***********************************************
*�޸�ʱ�䣺18-11-8
*�������ܣ���ȡָ�����λ������
*���ز�������������
*����˵����addr��ȡλ�� 		 	
***********************************************/
u8  GetOneByte(u16 addr)
{
	return UartData.uart_buff[addr];
}

/***********************************************
*�޸�ʱ�䣺18-11-8
*�������ܣ���ȡָ����ſ�ʼ�������
*���ز��������������׵�ַ
*����˵����addr��ȡλ�� *dataout������� datalen
�������� 		 	
***********************************************/
u8  *GetByte(u16 addr,u8 *dataout,u16 datalen )
{
	OS_memcpy(dataout,&UartData.uart_buff[addr], datalen);	
	return &dataout[addr];
}


/***********************************************
*�޸�ʱ�䣺18-11-8
*�������ܣ����ݽ������
*���ز�������
*����˵������ 		 	
***********************************************/
void ReceiveOK(void)
{
	UartData.uart_buff_len |= 1<<15;
}

/***********************************************
*�޸�ʱ�䣺18-11-8
*�������ܣ�������λ��0���λ�ü�����������
*���ز�������
*����˵������ 		 	
***********************************************/
void ReceiveClean(void)
{
	UartData.uart_buff_len = 0;
}

/***********************************************
*�޸�ʱ�䣺18-11-8
*�������ܣ��ж��Ƿ�������
*���ز�����0 ����δ���  1�������
*����˵������ 		 	
***********************************************/
u8 Get_ReciveState(void)
{
	if(UartData.uart_buff_len &0x8000)
		return 1;
	else 
		return 0;
}

/***********************************************
*�޸�ʱ�䣺18-11-8
*�������ܣ���ȡ��ǰ���ݳ���
*���ز�������
*����˵������ 		 	
***********************************************/
u16 Get_buffLen(void)
{
	return UartData.uart_buff_len&0x3fff;
}

/***********************************************
*�޸�ʱ�䣺18-11-8
*�������ܣ�����������
*���ز�������
*����˵������ 		 	
***********************************************/
void OS_uartInit(OSuartContorler *fp)
{
	fp->ReceivOneByte = ReceivOneByte;
	fp->ReceivByte = ReceivByte;
	fp->GetOneByte = GetOneByte;
	fp->GetByte  = GetByte;
	fp->ReceivClean = ReceiveClean;
	fp->ReceivOK = ReceiveOK;
	fp->Get_ReciveState = Get_ReciveState;
	fp->Get_buffLen =Get_buffLen;
}



