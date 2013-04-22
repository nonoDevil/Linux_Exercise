/*
 * =====================================================================================
 *
 *       Filename:  judge_chinese.c
 *
 *    Description:  判断一个字符是否是中文
 *
 *        Version:  1.0
 *        Created:  2013年04月11日 09时16分59秒
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
#include <string.h>

int main(int argc, char *argv[])
{
	char str[100];
	int  len = 0;
	int  i = 0;

	printf("Pleas input a chinese character:");
	scanf("%s", str);
	printf("%s\n", str);
	len = strlen(str);
	printf("len = %d\n", len);

	for (i = 0; i < len; i++) {
		if (str[i]  < 0) {
			printf("It is a chinese character\n");
			i += 2;
		}
	}



	return EXIT_SUCCESS;
}


