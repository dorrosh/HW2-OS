#include <asm/current.h>
#include <linux/kernel.h>
#include "sched/sched.h"
#include <linux/errno.h>
#include <linux/rbtree.h>

asmlinkage long sys_hello(void) {
	printk("Hello, World!");
	return 0;
}

asmlinkage long sys_get_vruntime(void) {
	return ((current)->se).vruntime;
}

asmlinkage long sys_increment_vruntime(long delta) {
	struct rq *run_queue;
	if(delta < 0)
		return -EINVAL;
	run_queue = this_rq();
	deactivate_task(run_queue, current, ENQUEUE_REPLENISH);
	(current->se).vruntime += delta;
	activate_task(run_queue, current, ENQUEUE_REPLENISH);
	return 0;
}


