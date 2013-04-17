/*
 * =====================================================================================
 *
 *       Filename:  kls.c
 *
 *    Description:  内核态的ls
 *
 *        Version:  1.0
 *        Created:  2013年04月17日 08时19分41秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  nonoDevil, linux.kakit@gmail.com
 *        Company:  Xiyou Linux Group
 *
 * =====================================================================================
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
////#include <asm/unistd.h>
//#include <asm/uaccess.h>
//#include <linux/fcntl.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("linux.kakit@gmail.com");

static char *path_name = "/";
module_param(path_name, charp, 0644);
MODULE_PARM_DESC(path_name, "char *param\n");


int judge_file_type(char *path_name);
void display_dir(struct file *fp);
void display_file(struct file *fp);


static int __init kls_init(void)
{	
	judge_file_type(path_name);
	
	return 0;
}


static void __exit kls_exit(void)
{
	printk("Unloading kls...\n");

	return ;
}

int judge_file_type(char *path_name)
{
	struct file *fp = NULL;

	/*判断是否为目录*/	
	fp = filp_open(path_name, O_DIRECTORY, 0);
	if (IS_ERR(fp)) {
		/*判断是否为文件*/
		fp = filp_open(path_name, O_RDONLY, 0644);
		if (IS_ERR(fp)) {
			printk("%s is not a file or a directory\n", path_name);
			return -1;
		}
		display_file(fp);
		filp_close(fp, NULL);
	} else {
		display_dir(fp);
		filp_close(fp, NULL);
	}
	
	return 0;
}


/*打印目录的dentry信息*/
void display_dir(struct file *fp)
{
	struct dentry *dp = fp->f_dentry;

	printk("1.d_name: %s\n", dp->d_name.name);
	printk("2.len: %d\n", dp->d_name.len);
	printk("3.d_mounted: %d\n", dp->d_mounted);
	printk("4.hash_number: %d\n", dp->d_name.hash);
	printk("5.short name: %s\n", dp->d_iname);
	
	return ;
}

/*打印文件的inode信息*/
void display_file(struct file *fp)
{
	struct inode *ip = fp->f_dentry->d_inode;

	printk("1.inode number: %lu\n", ip->i_ino);
	printk("2.uid: %d\n", ip->i_uid);
	printk("3.gitd: %d\n", ip->i_gid);
	printk("4.name: %s\n", fp->f_dentry->d_name.name);


	return ;
}


module_init(kls_init);
module_exit(kls_exit);
