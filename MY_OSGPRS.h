#ifndef  __OS_GPRS_H
#define  __OS_GPRS_H
#include "MY_SYS.h"

u8 OS_GPRS_CMDsend(char *CMD,char *Response,u32 Timerout,u8 Retry);
void OS_InitGPRS(void);



#endif /*__OS_GPRS_H*/


