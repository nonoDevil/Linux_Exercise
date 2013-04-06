/*
 * =====================================================================================
 *
 *       Filename:  print_pid.c
 *
 *    Description:  print parent's pid & child's pid
 *
 *        Version:  1.0
 *        Created:  2013年04月06日 23时49分35秒
 *       Revision:  none
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
#include <sys/types.h>
#include <sys/wait.h>


void print_err(const char *err_string, int line);

int main(int argc, char *argv[])
{
	pid_t pid;

	pid = fork();

	if (pid == -1) {		//出错
		print_err("fork()", __LINE__);		
	} else if (pid == 0) {	//子进程
		printf("I am child process! My pid is %d.\n", getpid());
	} else {				//父进程
		printf("I am parent process! My pid is %d.\n", getpid());
	}

	return EXIT_SUCCESS;
}

/*
 * 自定义错误处理函数
 */
void print_err(const char *err_string, int line)
{
	fprintf(stderr, "line: %d  ", line);
	perror(err_string);
	exit(1);
}
