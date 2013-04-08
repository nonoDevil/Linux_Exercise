/*
 * =====================================================================================
 *
 *       Filename:  ls1.c
 *
 *    Description:  实现ls命令
 *
 *        Version:  1.0 
 *        Created:  2013/04/08/ 08:51:07
 *       Revision:  1.0  (增加打印目录，错误处理函数)
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
static  int cmpstring(const void *p1, const void *p2);

int main(int argc, char *argv[])
{
	char dirname[__DIR_NAME_LEN__];

	if (argc == 1) {
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
	char filename[__DIR_ARRAY_MAX__][__DIR_NAME_LEN__]; //[1000][255] 
	int count = 0;	//统计目录下的文件数
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
 * Description: qsort()函数中的比较函数
 */
static  int cmpstring(const void *p1, const void *p2)
{
	return strcmp((char *)p1, (char *)p2);
}

/*
 * Date: 2013/4/8
 * Description: 打印错误信息
 */
void print_err(char *err_string, int line)
{
	fprintf(stderr, "line: %d", line);
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

