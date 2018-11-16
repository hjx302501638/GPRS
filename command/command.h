#ifndef  __COMMAND_H
#define  __COMMAND_H
#include "../MY_OSLib/MY_SYS.h"
#include  "../MY_OSLib/MY_OSuart.h"


#define max_tal_val 50  
#define max_tel_name 20    //命令最大长度 
#define max_paramer  4     //最大数据个数
#define max_paramer_len 20 //单条最大长度



//外部传入字符结构
typedef  struct EX_CMD_Str
{
	char val;
	char CMD[max_tel_name];
	char Parameter[max_paramer][max_paramer_len];
}EX_CMD_Str,*pEX_CMD_Str;


//命令结构体
typedef struct cmd_tbl_s{
	char  name[max_tel_name];//命令名称 
	int maxargs;//最大参数个数
	int (*cmd)(struct cmd_tbl_s * cmd_tbl_t,u8 flag,EX_CMD_Str * t);//函数指针
	char mesage[max_tel_name];//提示信息
	char val;
}cmd_tbl_s,*pcmd_tbl_s;
//命令相应函数
typedef int (*my_cmd_func)(struct cmd_tbl_s * cmd_tbl_t,u8 falg,EX_CMD_Str * t);





void MY_OS_CMD_Init(void);
void CMD_test(void);


#endif /*__COMMAND_H*/

