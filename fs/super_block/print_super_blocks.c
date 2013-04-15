/*
 * =====================================================================================
 *
 *       Filename:  print_super_blocks.c
 *
 *    Description:  打印super_block结构中一些域的值
 *
 *        Version:  1.0
 *        Created:  2013年04月15日 08时42分36秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  nonoDevil, linux.kakit@gmail.com
 *        Company:  Xiyou Linux Group
 *
 * =====================================================================================
 */

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/spinlock.h>
#include <linux/kdev_t.h>

#define SUPER_BLOCKS_ADDRESS 0xc07d9f58
#define SB_LOCK_ADDRESS      0xc0992420

static int __init my_init(void)		
{
	struct super_block *sb;
	struct list_head *pos;
	struct list_head *linode;
	struct inode *pinode;
	unsigned long long count = 0;

	printk("\nPrint some fields of super_blocks:\n");
	spin_lock((spinlock_t *)SB_LOCK_ADDRESS);	/* 加锁 */
	list_for_each(pos, (struct list_head *)SUPER_BLOCKS_ADDRESS) {
		sb = list_entry(pos, struct super_block, s_list);
		printk("dev_t: %d %d", MAJOR(sb->s_dev), MINOR(sb->s_dev));		/* 打印文件系统所在设备的主设备号和次设备号 */
		printk("file_type name: %s\n", sb->s_type->name);	/* 打印文件系统名 */
	}

	list_for_each(linode, &sb->s_inodes) {
		pinode = list_entry(linode, struct inode, i_sb_list);
		count++;
		printk("%lu\t", pinode->i_ino);	/* 打印索引结点 */
	}
	
	spin_unlock((spinlock_t *)SB_LOCK_ADDRESS);
	printk("The number of inode: %llu\n", sizeof(struct inode) * count);

	return 0;
}

static void __exit my_exit(void)
{
	printk("unloading...\n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");










