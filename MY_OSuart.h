#ifndef  __MY_OSUART_H
#define  __MY_OSUART_H
#include "MY_SYS.h"

#define Open_Dug 1
#define uart_MAXbuffLen  200

extern  void UART_sendData(char *data);
#define UART_send UART_sendData  //串口发送数据接口
extern  void Dug_UartSend(char *data);
#define Dug_Uart  Dug_UartSend	 //调试串口


typedef struct OSuartData 
{
	u8  uart_buff[uart_MAXbuffLen];
	u16 uart_buff_len;
}OSuartData,*pOSuartData;


typedef struct OSuartContorler
{
	u16  (*ReceivOneByte)(u8 byte,u16 addr);
	u16  (*ReceivByte)(u8 *byte,u16 addr,u16 bytelen);
	u8   (*GetOneByte)(u16 addr);
	u8*   (*GetByte)(u16 addr,u8 *dataout,u16 datalen);
  u8   (*Get_ReciveState)(void);
	u16  (*Get_buffLen)(void);
	void (*ReceivOK)(void);
	void (*ReceivClean)(void);
	
}OSuartContorler,*pOSuartContorler;


void OS_uartInit(OSuartContorler *fp);//接口函数


#endif /*__MY_UART_H*/

