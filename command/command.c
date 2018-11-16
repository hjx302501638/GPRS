#include "command.h"

cmd_tbl_s  cmd_tbl[max_tal_val];//命令列表
EX_CMD_Str cat_data;

//命令注册函数
int MY_OS_CMD(char *name,u8 maxargs,my_cmd_func cmd,char *mesage)
{
	u8 i;
	for(i=0;i<max_tal_val;i++)
	{
			if(cmd_tbl[i].cmd == 0)
			{
					OS_memcpy(cmd_tbl[i].name,name,OS_strlen(name));//拷贝名字
					cmd_tbl[i].maxargs  = maxargs;
					cmd_tbl[i].cmd = cmd;
					OS_memcpy(cmd_tbl[i].mesage,mesage,OS_strlen(mesage));//拷贝帮助信息
					cmd_tbl[i].val = i;
					return i;
			}
	}
	
	return max_tal_val+1;	
}

//查找命令 
//返回当前匹配命令表标号
u8 MY_OS_CMDFind(char *name)
{
		u8 i;
		for(i=0;i<max_tal_val;i++)
			{
				if(!OS_strcmp(cmd_tbl[i].name,name))
					{
						return i;
					}
			}
		return max_tal_val+1;
}



//分割命令与参数
//将对应数据写入命令块中
void Cat_CMD(char *data,u16 conut)
{
	u8 temp=0;
	while(*data == 0x20){data ++;conut--;if(conut== 0)return;}//去除数据前空格
	while(*data != 0x20)//拷贝出命令
		{
			cat_data.CMD[temp++] = *(data++);			
			conut--;
			if((conut  == 0)||(temp == max_tel_name))//命令错误
				{
					Dug_Uart("no paramerter\r\n");
					return ;
				}			
		}
		temp=0;
	while(*data == 0x20){data ++;conut--;if(conut== 0)return;}//去除数据前空格
	while(1)//拷贝出参数
		{
			while(*data != 0x20)//拷贝出命令
				{
					if(cat_data.val == max_paramer)
					{
						Dug_Uart("Too many parameters\r\n");
							return ;	
					}
					if(temp == max_paramer_len)//命令错误
						{
							Dug_Uart("paramerter erro\r\n");
							return ;
						}
					if(conut == 0)
						return ;
					cat_data.Parameter[cat_data.val][temp++] = *(data++);				
					conut--;
					
				}
			temp=0;
			cat_data.val++;
			while(*data == 0x20){data ++;conut--;if(conut== 0)return;}//去除数据前空格
		}
}

//释放命令块
void free_CMD(void)
{
	u8 i;
	OS_memset(cat_data.CMD,0,OS_strlen(cat_data.CMD));
	for(i=0;i<=cat_data.val;i++)
	OS_memset(&cat_data.Parameter[i][0],0,OS_strlen(&cat_data.Parameter[i][0]));
	cat_data.val = 0;	
}
int Test_func(cmd_tbl_s * cmd_tbl_t,u8 flag,EX_CMD_Str * t)
{
		u8 i;
		Dug_Uart(cmd_tbl[flag].mesage);
	  Dug_Uart(cat_data.CMD);
		Dug_Uart("\r\n");
		for(i=0;i<=cat_data.val;i++)
			Dug_Uart(&cat_data.Parameter[i][0]);
		return 0;
}
//命令初始化
void MY_OS_CMD_Init(void)
{		
		MY_OS_CMD("test",2,Test_func,"this is test cmd\r\n");
		Cat_CMD("     abc 123 456  ",OS_strlen("     abc 123  456  "));
}

//测试函数
void CMD_test(void)
{
		cmd_tbl_s *temp;
		u8 Event_val;
		Event_val = MY_OS_CMDFind("test");
		cmd_tbl[Event_val].cmd(temp,Event_val,&cat_data);
}





