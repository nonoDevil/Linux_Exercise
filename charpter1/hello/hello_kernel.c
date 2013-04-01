/*
 * =====================================================================================
 *
 *       Filename:  hello_kernel.c
 *
 *    Description:  my first kernel program
 *
 *        Version:  1.0
 *        Created:  2013年03月21日 15时16分29秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  nonoDevil, linux.kakit@gmail.com
 *        Company:  Xiyou Linux Group
 *
 * =====================================================================================
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init hello_init(void)
{
	printk("<1>Hello kernel! from the kernel space\n");

	return 0;
}

static void __exit hello_cleanup(void)
{
	printk("<1>Goodbye! leaving the kernel space\n");
}

module_init(hello_init);
moudle_exit(hello_cleanup);
MODULE_LICENSE("GPL");

