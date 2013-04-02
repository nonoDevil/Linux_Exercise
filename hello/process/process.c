/*
 * =====================================================================================
 *
 *       Filename:  process.c
 *
 *    Description:  print task_struct's member
 *
 *        Version:  1.0
 *        Created:  2013年03月21日 16时03分01秒
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
#include <linux/sched.h>


static int print_pid(void)
{
	struct	task_struct *task, *p;
	struct	list_head *pos;
	int		count = 0;
	
	printk("Hello World enter begin:\n");
	task = &init_task;
	list_for_each(pos, &task->tasks)
	{
		p = list_entry(pos, struct task_struct, tasks);
		count++;
		printk("1 pid: %d--->%s\n", p->pid , p->comm);
		printk("2 p->static_prio: %d\n", p->static_prio);
		printk("3 p->policy: %d\n", p->policy);
		printk("4 p->prio: %d\n", p->prio);
		printk("5 p->state: %ld\n", p->state);
		printk("6 p->flags: %u\n", p->flags);
		printk("7 p->ptrace: %u\n", p->ptrace);
		printk("8 p->locak_depth: %d\n", p->lock_depth);
		printk("9 p->fpu_counter: %s\n", p->fpu_counter);
		printk("10p->exit_code: %d\n", p->exit_code);

	}

	printk("the number of process is :%d\n", count);

	return 0;
}


static int __init print_init(void)
{
	print_pid();

	return 0;
}

static void __exit print_cleanup(void)
{

	printk("Goodbye!\n");
}
module_init(print_init);
module_exit(print_cleanup);
MODULE_LICENSE("GPL");
