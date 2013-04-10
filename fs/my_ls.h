/*
 * =====================================================================================
 *
 *       Filename:  ls1.h
 *
 *    Description:  ls1的头文件 
 *
 *        Version:  1.0
 *        Created:  2013年04月08日 10时16分38秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  nonoDevil, linux.kakit@gmail.com
 *        Company:  Xiyou Linux Group
 *
 * =====================================================================================
 */

#ifndef __MY_LS_H__
#define __MY_LS_H__

//#define __FILE_NAME_LEN__	255
#define __FILE_COUNT_MAX__	1000

/*
 * 默认是小写参数，如果参数为大写，则加上U(表示upper)
 */
#define __PARAM_A__			1		/*-a 打印出隐藏文件*/
#define __PARAM_L__			2		/*-l 列出文件属性*/
#define __PARAM_UR__		4		/*-R 递归输出目标路径下所有目录的内容*/
#define __PARAM_R__			8		/*-r 逆序输出*/
#define __PARAM_U__			16		/* with -lt: sort by, and show, access time with  -l:  show  access time and sort by name otherwise: sort by access time*/
#define __PARAM_I__			32		/*-i 打印出每个文件的inode*/
#define __PARAM_T__			64		/*-t 根据修改时间修改*/
#define __PARAM_US__		128		/*-s 根据文件大小排序*/
#define __PARAM_Q__			256		/*-q 不排序输出*/

#define __S_IFMSB__			07000	/*mask of special bit*/

/*判断是否含有某种参数的宏*/
#define P_HASA(p)  ((p)&(__PARAM_A__))
#define P_HASL(p)  ((p)&(__PARAM_L__))
#define P_HASUR(p) ((p)&(__PARAM_UR__))
#define P_HASR(p)  ((p)&(__PARAM_R__))
#define P_HASU(p)  ((p)&(__PARAM_U__))
#define P_HASI(p)  ((p)&(__PARAM_I__))
#define P_HAST(p)  ((p)&(__PARAM_T__))
#define P_HASUS(p) ((p)&(__PARAM_US__))  
#define P_HASQ(p)  ((p)&(__PARAM_Q__))

/*判断特殊权限位的宏 special bit*/
#define S_ISSBIT(mode, mask) (((mode) & __S_IFMSB__) == (mask))

static int g_parameter				= 0;		/*用来记录用户输入的ls - 的参数*/
static int g_row_len				= 80;		/*终端行可显示字符数*/
static int g_row_len_rest			= 80;		/*终端一行剩余可显示字符数*/
static int g_dir_longest_file_name	= 0;		/*目录文件下最长的文件名长度*/
static int g_file_longest_file_name	= 0;		/*最长的文件名长度*/

#endif 
