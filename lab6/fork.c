#include "allocater.h"
#include "sched.h"
#include "exception.h"

int copy_process(unsigned long fn, unsigned long arg)
{
	disable_preempt();
	struct task_struct *p;

	p = (struct task_struct *) require_buddy_mem(0);
	if (!p)
		return 1;
	p->priority = current->priority;
	p->state = TASK_RUNNING;
	p->counter = p->priority;
	p->preempt_count = 1; //disable preemtion until schedule_tail

	p->cpu_context.x19 = fn;
	p->cpu_context.x20 = arg;
	p->cpu_context.pc = (unsigned long)ret_from_fork;
	p->cpu_context.sp = (unsigned long)p + THREAD_SIZE;
	// int pid = n_tasks++;
	// task[pid] = p;	
	//p->taskid = pid;
	enable_preempt();
	return 0;
}