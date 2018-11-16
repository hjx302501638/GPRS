#include "MY_OSTimer.h"
//#include "string.h"

MY_OSdelayTimer OSdelayTimer[MAX_EVET];//�¼�����
/***********************************************
*�޸�ʱ�䣺18-11-6
*�������ܣ�
����һ����ʱ�¼�
*���ز�����-1ʧ��   0�ɹ�
*����˵����projet ���ܿ�
*		   name   ������
*		   fp     ����
*		   timer  ��ʱʱ��
*		   pri    ����λ��
***********************************************/
u8 OS_delayTimerCreate(		  u8 *name,
							  Timer_Event fp,
							  u16 timer,
							  u8 pri)
{
	u8 i;
		if(pri == 0)
			{
				for(i=0;i<MAX_EVET;i++)
					if((OSdelayTimer[i].name == null)&&(OSdelayTimer[i].delayTimerFun == null))
						{
							//memcpy(OSdelayTimer[i].name, name, strlen((const char *)name));
							OSdelayTimer[i].name= name;
							OSdelayTimer[i].delayTimerFun = fp;
							OSdelayTimer[i].delay_Timer = timer;
							OSdelayTimer[i].now_Timer = null;
							return 0;
						}
			}
		else 
			{
				if((OSdelayTimer[i].name == null)&&(OSdelayTimer[i].delayTimerFun == null))
					{
						OS_memcpy(OSdelayTimer[pri].name, name, OS_strlen((const char *)name));
						OSdelayTimer[pri].delayTimerFun = fp;
						OSdelayTimer[pri].delay_Timer = timer;
						OSdelayTimer[pri].now_Timer = null;
						return 0;
					}				
			}
			return 1;
}

/***********************************************
*�޸�ʱ�䣺18-11-6
*�������ܣ��Ƴ�һ����ʱ�¼�
*���ز�������
*����˵����
* 		 	dec	����λ�� 		 	
***********************************************/
void OS_RemovDealyTimer(u8 dec)
{
	OSdelayTimer[dec].name = null;
	OSdelayTimer[dec].delayTimerFun = null;
}


/***********************************************
*�޸�ʱ�䣺18-11-6
*�������ܣ���ʱ�¼�
*���ز�������
*����˵������ 		 	
***********************************************/
void Delay_Timer_Event(void)
{
	u8 i;
	for(i = 0 ;i < MAX_EVET;i++)
	{
		if(OSdelayTimer[i].delayTimerFun != null)
			{
				if(OSdelayTimer[i].now_Timer ==OSdelayTimer[i].delay_Timer )
					{
						OSdelayTimer[i].delayTimerFun();
						OS_RemovDealyTimer(i);					
					}
				else OSdelayTimer[i].now_Timer++;
			}
	}
}

/***********************************************
*�޸�ʱ�䣺18-11-7
*�������ܣ�����Ӧ����������Ϣ
*���ز�������
*����˵������ 		 	
***********************************************/
void OS_SendMSG(char *name ,void *MSG,u16 len)
{
	u8 i;
	u16 j;
	for(i=0;i<MAX_EVET;i++)
		{
			if(!OS_strcmp((const char *)OSdelayTimer[i].name,name))
				{
					for(j=0;j<OSdelayTimer[i].OSTimerMSG_Len;j++)
					OSdelayTimer[i].OSTimerMSG[j] = 0;
					OS_memcpy(OSdelayTimer[i].OSTimerMSG,MSG ,len);
					OSdelayTimer[i].OSTimerMSG_Len = len;
				}
		}
}

/***********************************************
*�޸�ʱ�䣺18-11-7
*�������ܣ���ȡ��Ϣ����
*���ز�������
*����˵������ 		 	
***********************************************/
void  OS_GetMSG(char *name,MY_OSTimerMSG *data)
{
	//pMY_OSTimerMSG ret;
	u8 i;
	for(i=0;i<MAX_EVET;i++)
		{
			if(!OS_strcmp((const char *)OSdelayTimer[i].name,name))
				{
					
					OS_memcpy(data->OSTimerMSG, OSdelayTimer[i].OSTimerMSG,\
							  OSdelayTimer[i].OSTimerMSG_Len);
					   data->OSTimerMSG_Len = OSdelayTimer[i].OSTimerMSG_Len;
				}
		}	
}


