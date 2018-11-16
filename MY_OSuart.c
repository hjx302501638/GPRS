#include "MY_OSuart.h"
OSuartData UartData;



/***********************************************
*修改时间：18-11-8
*函数功能：向数据缓存中添加单个数据 或者替换掉
单个数据
*返回参数：返回替换位置
*参数说明：byte 字符 addr替换位置 		 	
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
*修改时间：18-11-8
*函数功能：向数据缓存中添加多个连续数据
*返回参数：返回替换位置
*参数说明：*byte 字符串 addr替换位置  bytelen 
替换长度		 	
***********************************************/
u16 ReceivByte(u8 *byte,u16 addr,u16 bytelen)
{
	OS_memcpy(&UartData.uart_buff[addr], byte, bytelen);	
	return addr;
}

/***********************************************
*修改时间：18-11-8
*函数功能：读取指定标号位置数据
*返回参数：单个数据
*参数说明：addr读取位置 		 	
***********************************************/
u8  GetOneByte(u16 addr)
{
	return UartData.uart_buff[addr];
}

/***********************************************
*修改时间：18-11-8
*函数功能：读取指定标号开始多个数据
*返回参数：数据容器首地址
*参数说明：addr读取位置 *dataout数据输出 datalen
读出长度 		 	
***********************************************/
u8  *GetByte(u16 addr,u8 *dataout,u16 datalen )
{
	OS_memcpy(dataout,&UartData.uart_buff[addr], datalen);	
	return &dataout[addr];
}


/***********************************************
*修改时间：18-11-8
*函数功能：数据接收完成
*返回参数：无
*参数说明：无 		 	
***********************************************/
void ReceiveOK(void)
{
	UartData.uart_buff_len |= 1<<15;
}

/***********************************************
*修改时间：18-11-8
*函数功能：清除标记位从0标号位置继续接收数据
*返回参数：无
*参数说明：无 		 	
***********************************************/
void ReceiveClean(void)
{
	UartData.uart_buff_len = 0;
}

/***********************************************
*修改时间：18-11-8
*函数功能：判断是否接收完成
*返回参数：0 接收未完成  1接收完成
*参数说明：无 		 	
***********************************************/
u8 Get_ReciveState(void)
{
	if(UartData.uart_buff_len &0x8000)
		return 1;
	else 
		return 0;
}

/***********************************************
*修改时间：18-11-8
*函数功能：获取当前数据长度
*返回参数：无
*参数说明：无 		 	
***********************************************/
u16 Get_buffLen(void)
{
	return UartData.uart_buff_len&0x3fff;
}

/***********************************************
*修改时间：18-11-8
*函数功能：函数控制器
*返回参数：无
*参数说明：无 		 	
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



