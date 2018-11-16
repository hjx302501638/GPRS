#ifndef  __COMMAND_H
#define  __COMMAND_H
#include "../MY_OSLib/MY_SYS.h"
#include  "../MY_OSLib/MY_OSuart.h"


#define max_tal_val 50  
#define max_tel_name 20    //������󳤶� 
#define max_paramer  4     //������ݸ���
#define max_paramer_len 20 //������󳤶�



//�ⲿ�����ַ��ṹ
typedef  struct EX_CMD_Str
{
	char val;
	char CMD[max_tel_name];
	char Parameter[max_paramer][max_paramer_len];
}EX_CMD_Str,*pEX_CMD_Str;


//����ṹ��
typedef struct cmd_tbl_s{
	char  name[max_tel_name];//�������� 
	int maxargs;//����������
	int (*cmd)(struct cmd_tbl_s * cmd_tbl_t,u8 flag,EX_CMD_Str * t);//����ָ��
	char mesage[max_tel_name];//��ʾ��Ϣ
	char val;
}cmd_tbl_s,*pcmd_tbl_s;
//������Ӧ����
typedef int (*my_cmd_func)(struct cmd_tbl_s * cmd_tbl_t,u8 falg,EX_CMD_Str * t);





void MY_OS_CMD_Init(void);
void CMD_test(void);


#endif /*__COMMAND_H*/

