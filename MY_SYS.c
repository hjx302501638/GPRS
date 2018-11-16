#include "MY_SYS.h"

int OS_strcmp(const char * cs,const char * ct)
{
	register signed char __res;

	while (1) {
		if ((__res = *cs - *ct++) != 0 || !*cs++)
			break;
	}

	return __res;
}


int OS_strlen(const char *StrDest)
{
	int i;
	i=0;
	while((*StrDest++)!='\0')
	{ 
		i++;
	}//这个循环体意思是从字符串第一个字符起计数，只遇到字符串结束标志'\0’才停止计数
	return i;
}


/***********************************************
*修改时间：18-11-7
*函数功能：比较字符串中是否有子串
*返回参数：有返回所在首地址 否则返回0
*参数说明：stc 字符串 sub子串 		 	
***********************************************/
char *OS_strstr(char* src,char *sub)
{
	  const char *bp=src;
    const char *sp=sub;
    if(src==null||null==sub)
    {
        return src;
    }    
    while(*src)
    {
        bp=src;
        sp=sub;
        do{
            if(!*sp)
                return src;
            }while(*bp++==*sp++);
        src+=1;
    }
    
    return null;
}

/***********************************************
*修改时间：18-11-7
*函数功能：拷贝指定长度的数据
*返回参数：目的地址
*参数说明：dest 目的  src 源地址 count 长度 		 	
***********************************************/
void * OS_memcpy(void * dest,const void *src,u16 count)
{
	char *tmp = (char *) dest, *s = (char *) src;

	while (count--)
		*tmp++ = *s++;

	return dest;
}




/***********************************************
*修改时间：18-11-7
*函数功能：字符串转十六进制
*返回参数：十六进制数
*参数说明：*p 字符串   *errop 错误标记
***********************************************/
unsigned int hatoi(char *p, char **errp)
{
	unsigned int res = 0;

	while (1) {
				switch (*p) {
				case 'a':
				case 'b':
				case 'c':
				case 'd':
				case 'e':
				case 'f':
					res |= (*p - 'a' + 10);
					break;
				case 'A':
				case 'B':
				case 'C':
				case 'D':
				case 'E':
				case 'F':
					res |= (*p - 'A' + 10);
					break;
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					res |= (*p - '0');
					break;
				default:
					if (errp) {
						*errp = p;
					}
				return res;
				}
				p++;
				if (*p == 0) {
					break;
				}
				res <<= 4;
			}
	
	if (errp) {
		*errp = null;
	}

	return res;
}

//拼接两个字符串
char * OS_strcat(char * dest, const char * src)
{
	char *tmp = dest;

	while (*dest)
		dest++;
	while ((*dest++ = *src++) != '\0')
		;

	return tmp;
}

//在字符串结尾添加n个数据
char * OS_strncat(char *dest, const char *src, u16 count)
{
	char *tmp = dest;

	if (count) {
		while (*dest)
			dest++;
		while ((*dest++) == (*src++)) {
			if (--count == 0) {
				*dest = '\0';
				break;
			}
		}
	}

	return tmp;
}

//比较两个数组指定长度的数据
int OS_strncmp(const char * cs,const char * ct,u16 count)
{
	register signed char __res = 0;

	while (count) {
		if ((__res = *cs - *ct++) != 0 || !*cs++)
			break;
		count--;
	}

	return __res;
}



//查找S数组中第一次出现字符C的位置
char * OS_strchr(const char * s, int c)
{
	for(; *s != (char) c; ++s)
		if (*s == '\0')
			return null;
	return (char *) s;
}


//查找S数组中最后一次出现字符C的位置
char * OS_strrchr(const char * s, int c)
{
       const char *p = s + OS_strlen(s);
       do {
	   if (*p == (char)c)
	       return (char *)p;
       } while (--p >= s);
       return null;
}


//给一个字符串赋初值
void * OS_memset(void * s,int c,u16 count)
{
	unsigned long *sl = (unsigned long *) s;
	unsigned long cl = 0;
	char *s8;
	int i;

	/* do it one word at a time (32 bits or 64 bits) while possible */
	if ( ((unsigned long)s & (sizeof(*sl) - 1)) == 0) {
		for (i = 0; i < sizeof(*sl); i++) {
			cl <<= 8;
			cl |= c & 0xff;
		}
		while (count >= sizeof(*sl)) {
			*sl++ = cl;
			count -= sizeof(*sl);
		}
	}
	/* fill 8 bits at a time */
	s8 = (char *)sl;
	while (count--)
		*s8++ = c;

	return s;
}

//覆盖内存
void * OS_memmove(void * dest,const void *src,u16 count)
{
	char *tmp, *s;

	if (src == dest)
		return dest;

	if (dest <= src) {
		tmp = (char *) dest;
		s = (char *) src;
		while (count--)
			*tmp++ = *s++;
		}
	else {
		tmp = (char *) dest + count;
		s = (char *) src + count;
		while (count--)
			*--tmp = *--s;
		}

	return dest;
}


