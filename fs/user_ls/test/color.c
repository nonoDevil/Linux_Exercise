/*
 * =====================================================================================
 *
 *       Filename:  color.c
 *
 *    Description:  颜色测试
 *
 *        Version:  1.0
 *        Created:  2013年04月12日 01时00分21秒
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

int main(int argc, char *argv[])
{
	char str[255];
	printf("请输入一句话:\n");
	scanf("%s", str);

	printf("\033[1;30;1m%s\n\033[0m", str);
	printf("\033[1;31;1m%s\n\033[0m", str);
	printf("\033[1;32;1m%s\n\033[0m", str);
	printf("\033[1;33;1m%s\n\033[0m", str);
	printf("\033[1;34;1m%s\n\033[0m", str);
	printf("\033[1;35;1m%s\n\033[0m", str);
	printf("\033[1;36;1m%s\n\033[0m", str);
	printf("\033[1;37;1m%s\n\033[0m", str);
	printf("\033[1;38;1m%s\n\033[0m", str);
	printf("\033[1;39;1m%s\n\033[0m", str);

	printf("\033[1;39;40m%s\n\033[0m", str);
	printf("\033[1;39;41m%s\n\033[0m", str);
	printf("\033[1;39;42m%s\n\033[0m", str);
	printf("\033[1;39;43m%s\n\033[0m", str);
	printf("\033[1;39;44m%s\n\033[0m", str);
	printf("\033[1;39;45m%s\n\033[0m", str);
	printf("\033[1;39;46m%s\n\033[0m", str);
	printf("\033[1;39;47m%s\n\033[0m", str);
	printf("\033[1;39;48m%s\n\033[0m", str);
	printf("\033[1;39;49m%s\n\033[0m", str);
	printf("\033[1;39;50m%s\n\033[0m", str);



	return EXIT_SUCCESS;
}


