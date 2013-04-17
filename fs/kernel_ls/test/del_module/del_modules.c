/*
 * =====================================================================================
 *
 *       Filename:  del_modules.c
 *
 *    Description:  删除指定内核模块
 *
 *        Version:  1.0
 *        Created:  2013年04月15日 15时48分03秒
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
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/version.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("linux.kakit@gmail.com");

static int __init del_mod_init(void)
{
	struct list_head *modules=(struct list_head *)0xc07d4f44;
	struct module *mod = 0;
	struct module *list_mod;
	char *module_name = "test_flip_open";
	
	int i;
	int zero = 0;

	list_for_each_entry(list_mod, modules, list) {
		if (strcmp(list_mod->name, module_name) == 0) {
			mod = list_mod;
		}
	}

	mod->state = MODULE_STATE_LIVE;
	for (i = 0; i < NR_CPUS; i++) {
		mod->ref[i].count = *(local_t *)&zero;
	}

	return 0;
}

static void __exit del_mod_exit(void)
{
	printk("Unloading del_mod...\n");

	return ;
}


module_init(del_mod_init);
module_exit(del_mod_exit);
