#ifndef  __MY_OSTimer_H
#define  __MY_OSTimer_H
#include "MY_SYS.h"

#define Timer_MSG_LEN 120
#define MAX_EVET      64
typedef void (*Timer_Event)(void);

/*��Ϣ���ݽṹ*/
typedef  struct MY_OSTimerMSG{
	u8 OSTimerMSG[Timer_MSG_LEN];//��Ϣ������
	u8 OSTimerMSG_Len;           //���ݳ���
}MY_OSTimerMSG,*pMY_OSTimerMSG;

/*��ʱ�¼��ṹ�� */
typedef struct MY_OSdelayTimer{
	//MY_OSTimerMSG delayTimer_Msg;//��Ϣ
	u8 OSTimerMSG[Timer_MSG_LEN];//��Ϣ������
	u8 OSTimerMSG_Len;           //���ݳ���
	u8 *name;
	u16 delay_Timer;
	u16 now_Timer;
	Timer_Event delayTimerFun;
}MY_OSdelayTimer,*pMY_OSdelayTimer;

/*�ⲿ���ýṹ*/
typedef struct MY_OSTimer  {
	MY_OSTimerMSG Timer_Msg;
	
}MY_OSTimer,*pMY_OSTimer;

/*��ʱ�¼����캯��*/
u8 OS_delayTimerCreate(		  u8 *name,
							  Timer_Event fp,
							  u16 timer,
							  u8 pri);
void Delay_Timer_Event(void);
void OS_SendMSG(char *name ,void *MSG,u16 len);
void OS_GetMSG(char *name,MY_OSTimerMSG *data);



#endif /*__MYOSTimer_H*/


