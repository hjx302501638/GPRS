#ifndef  __MY_OSTimer_H
#define  __MY_OSTimer_H
#include "MY_SYS.h"

#define Timer_MSG_LEN 120
#define MAX_EVET      64
typedef void (*Timer_Event)(void);

/*信息传递结构*/
typedef  struct MY_OSTimerMSG{
	u8 OSTimerMSG[Timer_MSG_LEN];//信息缓存区
	u8 OSTimerMSG_Len;           //数据长度
}MY_OSTimerMSG,*pMY_OSTimerMSG;

/*延时事件结构体 */
typedef struct MY_OSdelayTimer{
	//MY_OSTimerMSG delayTimer_Msg;//消息
	u8 OSTimerMSG[Timer_MSG_LEN];//信息缓存区
	u8 OSTimerMSG_Len;           //数据长度
	u8 *name;
	u16 delay_Timer;
	u16 now_Timer;
	Timer_Event delayTimerFun;
}MY_OSdelayTimer,*pMY_OSdelayTimer;

/*外部调用结构*/
typedef struct MY_OSTimer  {
	MY_OSTimerMSG Timer_Msg;
	
}MY_OSTimer,*pMY_OSTimer;

/*延时事件构造函数*/
u8 OS_delayTimerCreate(		  u8 *name,
							  Timer_Event fp,
							  u16 timer,
							  u8 pri);
void Delay_Timer_Event(void);
void OS_SendMSG(char *name ,void *MSG,u16 len);
void OS_GetMSG(char *name,MY_OSTimerMSG *data);



#endif /*__MYOSTimer_H*/


