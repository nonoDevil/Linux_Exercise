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
 *						增加排序(使用qsort()),
 *                  }
 *                  2013/4/9 {
 *						重构代码
 *						实现display_dir(),
 *						实现display_file(),
 *					}
 *					2013/4/10 {
 *						实现display_attribute(),
 *						实现mode_to_letters(),
 *						实现uid_to_name(),
 *						实现gid_to_name(),
 *						实现time_to_letters(),
 *						实现cmpbystring(),
 *						实现cmpbysize(),
 *						实现cmpbymtime(),
 *						实现cmpbyatime(),
 *						实现处理多个目标路径内容显示 do_ls(),
 *						实现特殊位的处理,
 *					}
 *					2013/4/11 {
 *						实现文件分栏显示,
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
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "my_ls.h"

//#define DEBUG 1

int handle_parameter(int argc, char *argv[]);
void do_ls(int argc, char *argv[], int param_count);
void display_dir(char *path_name);
int cmpbystring(const void *p1, const void *p2);
int cmpbysize(const void *p1, const void *p2);
int cmpbymtime(const void *p1, const void *p2);
int cmpbyatime(const void *p1, const void *p2);

void display_file(char *path_name);
void display_sigle(struct stat *buf, char *file_name);
void display_attribute(struct stat *buf, char *file_name);
void mode_to_letters(const int mode, char *str);
char *uid_to_name(const uid_t uid);
char *gid_to_name(const gid_t gid);
void time_to_letters(time_t *time, char *time_str);

void print_error();
void print_format();
static  int cmpstring(const void *p1, const void *p2);


int main(int argc, char *argv[])
{
	int		param_count = 0;

	/*处理"-"，返回"第一个字符为"-"的参数个数"*/
	param_count = handle_parameter(argc, argv);
	
#ifdef DEBUG
	printf("param_count: %d\n", param_count);
#endif
	/*循环扫描argv， 判断需要打印的目标路径内容*/
	do_ls(argc, argv, param_count);

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
		if (param[i] == 'a')		g_parameter |= __PARAM_A__;
		else if (param[i] == 'l')	g_parameter |= __PARAM_L__;
		else if (param[i] == 'r')	g_parameter |= __PARAM_R__;
		else if (param[i] == 'R')	g_parameter |= __PARAM_UR__;
		else if (param[i] == 'u')	g_parameter |= __PARAM_U__;
		else if (param[i] == 'i')	g_parameter |= __PARAM_I__;
		else if (param[i] == 't')	g_parameter |= __PARAM_T__;
		else if (param[i] == 'S')	g_parameter |= __PARAM_US__;
		else if (param[i] == 'q')	g_parameter |= __PARAM_Q__;
		else {
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
	
	/*
	 * 设置目录下的最长文件名长度
	 * 由于不同目录下的最长文件名长度不同，
	 * 因此要在每个目录下都要初始化g_dir_longest_file_name 以及g_col_size_rest
	 */
	g_dir_longest_file_name = 0;
	g_row_len_rest = 80;

	/*打印目录的路径名*/
	printf("%s:\n", path_name);

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
		/*获取最长文件名长度*/
		if (file_len > g_dir_longest_file_name) {
			g_dir_longest_file_name = file_len;  	
		}
	}
	closedir(dir);

	/*排序,根据不同参数进行排序*/
	/*有-q 不排序输出，加快输出速度*/
	if (P_HASQ(g_parameter)) {
		goto Display;
	} else {
		if (P_HASU(g_parameter)) {
			qsort(file_name, count, PATH_MAX + 1, cmpbyatime);	
		} else if (P_HAST(g_parameter)) {
			qsort(file_name, count, PATH_MAX + 1, cmpbymtime);
		} else if (P_HASUS(g_parameter)) {
			qsort(file_name, count, PATH_MAX + 1, cmpbysize);
		} else {
			qsort(file_name, count, PATH_MAX + 1, cmpbystring);
		}
	}


#ifdef DEBUG
	for (i = 0; i < count; i++) {
		printf("%s\n", file_name[i]);
	}
#endif

Display:
	for (i = 0; i < count; i++) {
		display_file(file_name[i]);
	}
	/*
	 * 打印完目录下的所有文件后，输出一个换行
	 * 如果没有-l参数，才需要输出此换行，因为-l本身带有-l
	 */
	if (!P_HASL(g_parameter)) {
		printf("\n");
	}

	return ;
}

/* 
 * Date: 2013/4/10
 * Description: 根据访问时间排序
 */
int cmpbyatime(const void *p1, const void *p2)
{
	struct stat buf1;
	struct stat buf2;
	int value = 0;

	if (lstat((char *)p1, &buf1) == -1) {
		print_error("lstat", __LINE__);
	} 
	if (lstat((char *)p2, &buf2) == -1) {
		print_error("lstat", __LINE__);
	} 

	value = buf1.st_atime - buf2.st_atime;
	/*如果两个大小相等, 按字符串字段顺序排序*/
	if (value == 0) {
		return cmpbystring(p1, p2);
	} else {
		/*有-r参数逆序输出*/
		if (P_HASR(g_parameter)) {
			return (0 - value);
		} else {
			return value;
		}
	}
	
}

/* 
 * Date: 2013/4/10
 * Description: 根据修改时间排序
 */
int cmpbymtime(const void *p1, const void *p2)
{
	struct stat buf1;
	struct stat buf2;
	int value = 0;

	if (lstat((char *)p1, &buf1) == -1) {
		print_error("lstat", __LINE__);
	} 
	if (lstat((char *)p2, &buf2) == -1) {
		print_error("lstat", __LINE__);
	} 

	value = (int)(buf1.st_mtime - buf2.st_mtime);
	/*如果两个大小相等, 按字符串字段顺序排序*/
	if (value == 0) {
		return cmpbystring(p1, p2);
	} else {
		/*有-r参数逆序输出*/
		if (P_HASR(g_parameter)) {
			return (0 - value);
		} else {
			return value;
		}
	}
	
}

/* 
 * Date: 2013/4/10
 * Description: 根据文件大小排序
 */
int cmpbysize(const void *p1, const void *p2)
{
	struct stat buf1;
	struct stat buf2;
	int value = 0;

	if (lstat((char *)p1, &buf1) == -1) {
		print_error("lstat", __LINE__);
	} 
	if (lstat((char *)p2, &buf2) == -1) {
		print_error("lstat", __LINE__);
	} 

	value = buf1.st_size - buf2.st_size;
	/*如果两个大小相等, 按字符串字段顺序排序*/
	if (value == 0) {
		return cmpbystring(p1, p2);
	} else {
		/*有-r参数逆序输出*/
		if (P_HASR(g_parameter)) {
			return (0 - value);
		} else {
			return value;
		}
	}
}

/* 
 * Date: 2013/4/10
 * Description: 根据字典顺序排序
 */
int cmpbystring(const void *p1, const void *p2)
{
	/*有-r参数则逆序输出*/
	if (P_HASR(g_parameter)) {
		return strcmp((char *)p2, (char *)p1);
	} else {
		return strcmp((char *)p1, (char *)p2);
	}
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
	struct stat buf;

	/*获取文件信息*/
	if (lstat(path_name, &buf) == -1) {
		print_error("lstat", __LINE__);
		exit(-1);
	}

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
	printf("g_parameter = %d\n", g_parameter);
	printf("P_HASL(g_parameter) = %d\n", P_HASL(g_parameter));
#endif	




	/*判断是否有-l 来进行不同格式的输出*/
	if (P_HASL(g_parameter)) {
#ifdef DEBUG
		printf("I am in \n");
#endif
		display_attribute(&buf, file_name);		
	} else {
		display_sigle(&buf, file_name);	/*如果后期sigle模式需要-i的时候，需要更改接口增加struct stat buf*/
	}

	return ;
}

/*
 * Date: 2013/4/9
 * Description: 没有-l选项时候的普通打印方式
 * Parameters: file_name文件明
 */
void display_sigle(struct stat *buf, char *file_name)
{
	int i = 0, len = 0;

	/*如果不足以打印最长文件名则换行*/
	if (g_row_len_rest < g_dir_longest_file_name) {
		printf("\n");	
		g_row_len_rest = __ROW_LEN_MAX__;
	}

	len = strlen(file_name);
	len = g_dir_longest_file_name - len;
	printf("%-s", file_name);

	/*补齐空格*/
	for (i = 0; i < len; i++) {
		printf(" ");
	}
	/*打印两个空格区分相邻文件*/
	printf("  ");
	g_row_len_rest -= g_dir_longest_file_name + 2;

	return ;
}

/*
 * Date: 2013/4/9
 * Description: 有-l选项时，打印文件stat结构体的信息 
 * Parameters: buf 文件stat信息， file_name 文件名
 * Effect: mode links owner group size last-modified name
 */
void display_attribute(struct stat *buf, char *file_name)
{
	char mode_str[11];
	char time_str[32];

	/*判断是否有-a, 没有-a，则过滤隐藏文件*/
	if (!P_HASA(g_parameter)) {
		if (file_name[0] == '.') {
			return ;
		}
	}


	/*文件类型及权限位获取*/
	mode_to_letters((int)buf->st_mode, mode_str);
	time_to_letters(&(buf->st_mtime), time_str);

	/*打印文件信息*/
	if (P_HASI(g_parameter)) { /*如果有-i参数打印inode*/
		printf("%-7d ", buf->st_ino);;
	}
	printf("%s ",		mode_str);
	printf("%4d ",		(int )buf->st_nlink);
	printf("%-s ",		uid_to_name(buf->st_uid));
	printf("%-s ",		gid_to_name(buf->st_gid));
	printf("%10ld ",	(long )buf->st_size);
	printf("%s ",		time_str);
	printf("%s\n",		file_name);


	return ;
}


/*
 * Date: 2013/4/10
 * Description: 将属性权限转换成字母
 */
void mode_to_letters(const int mode, char *str)
{
	strncpy(str, "----------", 10);
	str[10] = '\0';
	
	/*文件类型判断*/
	if (S_ISDIR(mode))				str[0] = 'd';
	else if (S_ISCHR(mode))			str[0] = 'c';
	else if (S_ISBLK(mode))			str[0] = 'b';
	else if (S_ISREG(mode))			str[0] = '-';
	else if (S_ISFIFO(mode))		str[0] = 'f';
	else if (S_ISLNK(mode))			str[0] = 'l';
	else if (S_ISSOCK(mode))		str[0] = 's';	
	
	/*判断权限位*/
	/*user*/
	if (mode & S_IRUSR)				str[1] = 'r';
	if (mode & S_IWUSR)				str[2] = 'w';
	if (mode & S_IXUSR)				str[3] = 'x';
	/*set-user-ID*/
	if (S_ISSBIT(mode, S_ISUID))	str[3] = 's';
	/*group*/
	if (mode & S_IRGRP)				str[4] = 'r';
	if (mode & S_IWGRP)				str[5] = 'w';
	if (mode & S_IXGRP)				str[6] = 'x';
	/*set-group-ID*/
	if (S_ISSBIT(mode, S_ISGID))	str[6] = 'S';
	/*other*/
	if (mode & S_IROTH)				str[7] = 'r';
	if (mode & S_IWOTH)				str[8] = 'w';
	if (mode & S_IXOTH)				str[9] = 'x';
	/*set sticky*/
	if (S_ISSBIT(mode, S_ISVTX))	str[9] = 't';

#ifdef DEBUG
	printf("mode: %s\n", str);
#endif

	return ;
}

/*
 * Date: 2013/4/10
 * Description: 将uid转换成字符
 */
char *uid_to_name(const uid_t uid)
{
	struct passwd *pw_ptr = NULL;
	static char num_str[10];

	if ((pw_ptr = getpwuid(uid)) == NULL) {
		sprintf(num_str, "%d", uid);
		return num_str;
	} else {
		//return pw_ptr->pw_passwd;
		return pw_ptr->pw_name;
	}
}

/*
 * Date: 2013/4/10
 * Description:　将gid转换成字符
 */
char *gid_to_name(const gid_t gid)
{
	struct group *grp_ptr = NULL;
	static char num_str[10];

	if ((grp_ptr = getgrgid(gid)) == NULL) {
		sprintf(num_str, "%d", gid);
		return num_str;
	} else {
		return grp_ptr->gr_name;
	}
}

/*
 * Date: 2013/4/10
 * Description: 将时间转换成字符串格式
 */
void time_to_letters(time_t *time, char *time_str)
{

	strncpy(time_str, ctime(time), strlen(ctime(time)));
#ifdef DEBUG
	printf("strlen(cimte(time)) = %d\n", strlen(ctime(time)));
#endif
	/*去除time_str最后的\n*/
	time_str[strlen(ctime(time)) - 1] = '\0';
		
	return ;
}


/*
 * Date: 2013/4/8
 * Revision: 2013/4/10  {
 *				重构do_ls,
 *				循环扫描argv，输出一个或多个目标路径内容,
 *
 *			 }
 * Description: 打印目录
 */
void do_ls(int argc, char *argv[], int param_count)
{
	struct	stat buf;
	char	path_name[PATH_MAX + 1];
	int		path_len = 0;
	int		i = 0;


	/* 如果没有目标路径，那么输出当前路径的内容 */
	if (param_count == (argc - 1)) {
		strncpy(path_name, "./", 2);
		path_name[2] = '\0';
		display_dir(path_name);	
		return ;
	}

	/*循环扫描argv， 看是否需要打印多个目标路径内容*/
	i = 1;
	do {
		/*处理路径*/
		if (argv[i][0] == '-') {
			i++;
			continue;
		}
		path_len = strlen(argv[i]);
		strncpy(path_name, argv[i], path_len);
		path_name[path_len] = '\0';
#ifdef DEBUG
		printf("path_name = %s\n", path_name);
#endif
		if (lstat(path_name, &buf) == -1) {
			print_error("lstat", __LINE__);
			exit(-1);
		}

		/*根据type信息，判断是文件还是目录*/
		if (S_ISDIR(buf.st_mode)) {	/*判断是否是目录*/
			/*如果目录的最后一个字符不是"/"，则加上"/"*/
			if(path_name[path_len - 1] != '/') {
				path_name[path_len] = '/';
				path_name[path_len + 1] = '\0';
			}	
			display_dir(path_name);	
		} else {		/*说明是文件*/
			display_file(path_name);
		}

		i++;
	} while(i < argc);
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

