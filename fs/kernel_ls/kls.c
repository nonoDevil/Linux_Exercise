/*
 * =====================================================================================
 *
 *       Filename:  kls.c
 *
 *    Description:  内核态的ls,
 *                  传入的path_name为空时，打印当前目录的dentry
 *                  传入的path_name为目录，则打印其dentry信息
 *                  传入的path_name为文件, 则打印其inode信息
 *
 *        Version:  1.0
 *        Created:  2013年04月15日 11时13分24秒
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

static char *path_name = "./";			/*如果没有参数,打印当前目录*/
module_param(path_name, charp, 0644);
MODULE_PARM_DESC(path_name, "char param\n");

static int __init kernel_ls_init(void)
{
	printk(KERN_INFO "path_name = %s\n", path_name);	

	return 0;
}

static void __exit kernel_ls_exit(void)
{
	printk("unloading kernel_ls...\n");

	return ;
}


/*
 * Date: 2013/4/15
 * Description: 打印dentry信息
 */
void print_dentry(char *path_name)
{
	return ;
}

/*
 * Date: 2013/4/15
 * Description: 打印inode信息 
 */
void print_inode(char *path_name)
{
	return ;
}




module_init(kernel_ls_init);
module_exit(kernel_ls_exit);
