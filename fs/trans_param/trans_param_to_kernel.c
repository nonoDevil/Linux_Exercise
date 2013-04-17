/*
 * =====================================================================================
 *
 *       Filename:  trans_param_to_kernel.c
 *
 *    Description:  给内核传递参数
 *
 *        Version:  1.0
 *        Created:  2013年04月15日 10时00分28秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  nonoDevil, linux.kakit@gmail.com
 *        Company:  Xiyou Linux Group
 *
 * =====================================================================================
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/version.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("linux.kakit@gmail.com");

static int p_int;
module_param(p_int, int, 0644);
MODULE_PARM_DESC(p_int, "int param!\n");

static char *p_pchar = "nothing parsed!";
module_param(p_pchar, charp, 0644);
MODULE_PARM_DESC(p_pchar, "char *param!\n");

static int __init param_init(void)
{
	printk(KERN_INFO "p_int = %d\n", p_int);
	printk(KERN_INFO "p_pchar = %s\n", p_pchar);

	return 0;
}

static void __init param_exit(void)
{
	return ;
}


module_init(param_init);
module_exit(param_exit);





