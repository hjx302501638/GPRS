#ifndef  __MY_SYS_H
#define  __MY_SYS_H


typedef char *  va_list;
#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )

#define va_start(ap,v)  ( ap = (va_list)&v + _INTSIZEOF(v) )
#define va_arg(ap,t)    ( *(t *)( ap=ap + _INTSIZEOF(t), ap- _INTSIZEOF(t)) )
#define va_end(ap)      ( ap = (va_list)0 )



#define null 0 
#define u8  unsigned char
#define u16 unsigned short
#define u32 unsigned int 


extern void delay_ms(u16 nms);
#define OS_delay_ms  delay_ms   //延时函数接口

int   OS_strcmp(const char * cs,const char * ct);
int   OS_strlen(const char *StrDest);
char *OS_strstr(char* src,char *sub);
void * OS_memcpy(void * dest,const void *src,u16 count);
void * OS_memmove(void * dest,const void *src,u16 count);//

unsigned int hatoi(char *p, char **errp);
u32 os_atoi (char s[]);
char * OS_strcat(char * dest, const char * src);//拼接两个字符串
char * OS_strncat(char *dest, const char *src, u16 count);//在字符串结尾添加n个数据
void * OS_memset(void *s, int c, u16 n);//给一个字符串赋初值
char * OS_strrchr(const char * s, int c);//查找S数组中最后一次出现字符C的位置
char * OS_strchr(const char * s, int c);//查找S数组中第一次出现字符C的位置
int OS_strncmp(const char * cs,const char * ct,u16 count);//比较两个数组指定长度的数据


#endif /*__MY_SYS_H*/
