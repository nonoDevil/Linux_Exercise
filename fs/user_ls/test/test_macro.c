/*
 * =====================================================================================
 *
 *       Filename:  test_macro.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年04月10日 01时27分07秒
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

#define L 0
#define HASL(p) ((p)&(L))

int main(int argc, char *argv[])
{
	int p = 0;

	printf("input p:\n");
	scanf("%d", &p);

	if (HASL(p)) {
		printf("true\n");
		printf("%d\n", HASL(p));
	} else {
		printf("false\n");
		printf("%d\n", HASL(p));
	}

	return EXIT_SUCCESS;
}


