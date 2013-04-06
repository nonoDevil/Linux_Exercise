/*
 * =====================================================================================
 *
 *       Filename:  wait_case.c
 *
 *    Description:  使用wait()函数的代码
 *
 *        Version:  1.0
 *        Created:  2013年04月07日 00时04分36秒
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
	int status = 0;

	pid = fork();

	if (pid == -1) {
		print_err("fork()", __LINE__);
	} else if (pid == 0) {	
		printf("I am child process! My pid is %d.\n", getpid());
		sleep(5);
		exit(0);
	} else {
		printf("I am parent process! My pid is %d.\n", getpid());
		wait(&status);
		printf("Child process exit code is %d.\n", status);
	}
	return EXIT_SUCCESS;
}


void print_err(const char *err_string, int line)
{
	fprintf(stderr, "line: %d  ", line);
	perror(err_string);
	exit(1);
}
