/*
 * =====================================================================================
 *
 *      file_name:  my_ls.c
 *
 *    Description:  实现ls命令
 *
 *        Version:  1.0 
 *        Created:  2013/04/08/ 08:51:07
 *       Revision:  2013/4/8 {
 *						增加打印目录，错误处理函数, 
 *						增加排序(使用qsort())
 *                  }
 *                  2013/4/9 {
 *						重构代码
 *						实现display_dir(),
 *						实现displau_file()
 *					}
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
#include <sys/stat.h>
#include <linux/limits.h>
#include "my_ls.h"

#define DEBUG 1

int handle_parameter(int argc, char *argv[]);
void display_dir(char *path_name);
void display_file(char *path_name);
void display_sigle(char *file_name);
void display_attribute(struct stat *buf, char *file_name);

void do_ls(const char *dirname);
void print_error();
void print_format();
static  int cmpstring(const void *p1, const void *p2);


int main(int argc, char *argv[])
{
	char path_name[__FILE_NAME_LEN__];
	int  param_count = 0;

	/*处理"-"，返回"第一个字符为"-"的参数个数"*/
	param_count = handle_parameter(argc, argv);
	
#ifdef DEBUG
	printf("param_count: %d\n", param_count);
#endif

	/* 如果没有目标路径，那么输出当前路径的内容 */
	if (param_count == (argc - 1)) {
		printf("I am in\n");
		strcpy(path_name, "./");
		display_dir(path_name);	
	}



	//do_ls(dirname);

	return EXIT_SUCCESS;
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

	/* 解析命令，存入param数组*/
	k = 0;
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

	/* 根据param[]设置命令 eg: -l -a */
	for (i = 0; i < k; i++) {
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
			printf("Can not recognize the parameter \"%c\"\n", param[i]);
			printf("Please try to ls --help to get more help.\n");
			exit(0);
		}
	}

	return param_count;
}

/*
 * Date: 2013/4/9 Tues
 * Description: 输出目录内容
 * Parameters: path_name目录名
 */
void display_dir(char *path_name)
{
	DIR *dir = NULL;
	struct dirent *dir_cur = NULL;
	char file_name[__FILE_COUNT_MAX__][PATH_MAX+1];
	int path_len = 0; 
	int file_len = 0;
	int count = 0;
	int i = 0;

	if ((dir = opendir(path_name)) == NULL) {
		print_error("opendir", __LINE__);
		exit(-1);
	}

	/*获取该目录下的所有文件名*/
	while ((dir_cur = readdir(dir)) != NULL) {
		path_len = strlen(path_name);
		strncpy(file_name[count], path_name, path_len);
		file_name[count][path_len] = '\0';
		file_len = strlen(dir_cur->d_name);
		strncat(file_name[count], dir_cur->d_name, file_len);		
		count++;
	}
	closedir(dir);

#ifdef DEBUG
	for (i = 0; i < count; i++) {
		printf("%s\n", file_name[i]);
	}
#endif
	
	for (i = 0; i < count; i++) {
		display_file(file_name[i]);
	}

	return ;
}

/*
 * Date: 2013/4/9
 * Description: 打印文件信息，根据是否有-l 来输出不同的文件信息格式
 * Parameters: path_name文件路径名
 */
void display_file(char *path_name)
{
	int i = 0, j = 0;
	int path_len = 0, file_len = 0;
	char file_name[NAME_MAX+1]; 

	/*解析路径，只取最后一个"/"后的文件名*/	
	path_len = strlen(path_name);
	for (i = 0; i < path_len; i++) {
		if (path_name[i] == '/') {
			j = 0;
			continue;
		}
		file_name[j] = path_name[i];
		j++;
	}		
	file_name[j] = '\0';
#ifdef DEBUG
	printf("file_name: %s\n", file_name);
#endif

	return ;
}

/*
 * Date: 2013/4/9
 * Description: 没有-l选项时候的普通打印方式
 * Parameters: file_name文件明
 */
void display_sigle(char *file_name)
{
	return ;
}

/*
 * Date: 2013/4/9
 * Description: 有-l选项时，打印文件stat结构体的信息 
 * Parameters: buf 文件stat信息， file_name 文件名
 */
void display_attribute(struct stat *buf, char *file_name)
{
	return ;
}

/*
 * Date: 2013/4/8
 * Description: 打印目录
 */
void do_ls(const char *dirname)
{
	DIR *dir_ptr = NULL;
	struct dirent *dir_cur = NULL;
	char file_name[__FILE_COUNT_MAX__][__FILE_NAME_LEN__]; /*[1000][255]*/ 
	int count = 0;	/*统计目录下的文件数*/
	int i = 0;

	if ((dir_ptr = opendir(dirname)) == NULL) {
		print_error("opendir", __LINE__);
	} else {
		while ((dir_cur = readdir(dir_ptr)) != NULL) {
			strncpy(file_name[count], dir_cur->d_name, strlen(dir_cur->d_name));
			count++;
		}
		closedir(dir_ptr);
	}
	
	printf("sizeof(file_name[0]) = %d\n", sizeof(file_name[0]));
	qsort(file_name, count, sizeof(file_name[0]), cmpstring);

	for (i = 0; i < count; i++) {
		printf("%s\n", file_name[i]);
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
 * Date: 2013/4/8
 * Description: 打印错误信息
 */
void print_error(char *err_string, int line)
{
	fprintf(stderr, "line: %d\n", line);
	perror(err_string);

	return ;
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

