/*
 * =====================================================================================
 *
 *       Filename:  test_flip_open.c
 *
 *    Description:  测试flip_open 
 *
 *        Version:  1.0
 *        Created:  2013年04月15日 11时55分53秒
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
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("linux.kakit@gmail.com");

static int __init t_flip_open_init(void)
{
	struct file *fp;

	if ((fp = filp_open("./haha", O_RDONLY | O_DIRECTORY, 0)) == NULL) {
		printk("filp_open error\n");
		return -1;
	}


	filp_close(fp, NULL);

	return 0;
}

static void __exit t_flip_open_exit(void)
{
	printk("Unloading t_flip_open...\n");

	return ;
}


module_init(t_flip_open_init);
module_exit(t_flip_open_exit);

