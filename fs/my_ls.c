/*
 * =====================================================================================
 *
 *       Filename:  ls1.c
 *
 *    Description:  实现ls命令
 *
 *        Version:  1.0 
 *        Created:  2013/04/08/ 08:51:07
 *       Revision:  1.0  (增加打印目录，错误处理函数, )
 *					增加排序(使用qsort())
 *       Compiler:  gcc
 *
 *         Author:  nonoDevil, linux.kakit@gmail.com
 *        Company:  Xiyou Linux Group
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include "ls1.h"


#define DEBUG 1

void do_ls(const char *dirname);
void print_err();
void print_format();
int handle_parameter(int argc, char *argv[]);
static  int cmpstring(const void *p1, const void *p2);


int main(int argc, char *argv[])
{
	char dirname[__FILE_NAME_LEN__];
	char path[__FILE_NAME_LEN__];
	int  param_count = 0;

	/*处理"-"，返回"-的个数"*/
	param_count = handle_parameter(argc, argv);

	if (param_count == (argc - 1)) {
		strcpy(dirname, "./");
	} else {
		strcpy(dirname, argv[1]);
	}

	do_ls(dirname);

	return EXIT_SUCCESS;
}

/*
 * Date: 2013/4/8
 * Description: 打印目录
 */
void do_ls(const char *dirname)
{
	DIR *dir_ptr = NULL;
	struct dirent *dir_cur = NULL;
	char filename[__FILE_COUNT_MAX__][__FILE_NAME_LEN__]; /*[1000][255]*/ 
	int count = 0;	/*统计目录下的文件数*/
	int i = 0;

	if ((dir_ptr = opendir(dirname)) == NULL) {
		print_err("opendir", __LINE__);
	} else {
		while ((dir_cur = readdir(dir_ptr)) != NULL) {
			strncpy(filename[count], dir_cur->d_name, strlen(dir_cur->d_name));
			count++;
		}
		closedir(dir_ptr);
	}
	
	printf("sizeof(filename[0]) = %d\n", sizeof(filename[0]));
	qsort(filename, count, sizeof(filename[0]), cmpstring);

	for (i = 0; i < count; i++) {
		printf("%s\n", filename[i]);
	}

#ifdef DEBUG
	printf("the total file number is %d\n", count);
#endif 

	return ;
}

/*
 * Date: 2013/4/8
 * Description: qsort()函数中的比较函数, 按字典顺序进行排序
 */
static int cmpstring(const void *p1, const void *p2)
{
	return strcmp((char *)p1, (char *)p2);
}

/*
 * Date; 2013/4/8
 * Description: 处理参数, 设置命令属性
 * Return: 返回"-"的个数
 */
int handle_parameter(int argc, char *argv[])
{
	char param[100];
	int i = 0, j = 0, k = 0;
	int param_count = 0;

	/*
	 * argc < 2 说明命令是 $ ls 
	 * 列出当前目录下的文件/目录，并且不打印隐藏文件
	 */
	if (argc < 2) {
		return ;
	}

	/*
	 * 解析命令，存入param数组
	 */
	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			for (j = 1; j < strlen(argv[i]); j++, k++) {
				param[k] = argv[i][j];
			}
			param_count++;
		}
	}
#ifdef DEBUG
	printf("parameters is : ");
	for (i = 0; i < k; i++) {
		printf("%c ", param[i]);
	}
	printf("\n");
#endif

	/*
	 * 根据param[]设置命令 eg: -l -a
	 */
	for (i = 0; i < j; i++) {
		if (param[i] == 'a') {
			g_parameter |= __PARAM_A__;
		} else if (param[i] == 'l') {
			g_parameter |= __PARAM_L__;
		} else if (param[i] == 'R') {
			g_parameter |= __PARAM_R__;
		} else if (param[i] == 'r') {
			g_parameter |= __PARAM_UR__;
		} else if (param[i] == 'u') {
			g_parameter |= __PARAM_U__;
		} else if (param[i] == 'i') {
			g_parameter |= __PARAM_I__;
		} else if (param[i] == 't') {
			g_parameter |= __PARAM_T__;
		} else if (param[i] == 's') {
			g_parameter |= __PARAM_S__;
		} else if (param[i] == 'q') {
			g_parameter |= __PARAM_Q__;
		} else {
			printf("Can not recognise the parameter \"%c\"\n", param[i]);
			printf("Please try to ls --help to get more help.\n");
			exit(0);
		}
	}

	return param_count;
}


/*
 * Date: 2013/4/8
 * Description: 打印错误信息
 */
void print_err(char *err_string, int line)
{
	fprintf(stderr, "line: %d\n", line);
	perror(err_string);
	exit(-1);
}

/*
 * Date: 2013/4/8
 * Description: 打印ls的正确使用方法
 */
void print_format()
{
	printf("Usage: ./ls1 \n");

	return ;
}

