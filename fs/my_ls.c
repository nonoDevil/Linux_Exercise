/*
 * =====================================================================================
 *
 *       Filename:  my_ls.c
 *
 *    Description:  Realize my ls command
 *
 *        Version:  1.0
 *        Created:  2013年04月08日 08时51分07秒
 *       Revision:  
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


#define __DIR_NAME_LENTH__ 255

void do_ls(const char *dirname);
void print_err();
void print_format();

int main(int argc, char *argv[])
{
	char dirname[__DIR_NAME_LENTH__];

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

	if ((dir_ptr = opendir(dirname)) == NULL) {
		print_err("opendir", __LINE__);
	} else {
		while ((dir_cur = readdir(dir_ptr)) != NULL) {
			printf("%s\n", dir_cur->d_name);
		}
		closedir(dir_ptr);
	}

	return ;
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
 * Description: 打印正确格式
 */
void print_format()
{
	return ;
}

