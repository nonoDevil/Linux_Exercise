/*
 * =====================================================================================
 *
 *       Filename:  test_qsort.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年04月08日 11时48分22秒
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

int comp(const void *p1, const void *p2);

int main(int argc, char *argv[])
{
	char s[4][20] = {"chenjiajie", "chenshuanglin", "baiyaxiong", "liudanyang"};
	int i = 0;

	qsort(s, 4, 20, comp);

	for (i= 0; i < 4; i++) {
		printf("%s\n", s[i]);
	}

	return EXIT_SUCCESS;
}


int comp(const void  *p1, const void *p2)
{
	return strcmp((char *)p1, (char *)p2);
}
