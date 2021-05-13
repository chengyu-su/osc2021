#include "sched.h"
#include "exception.h"
#include "allocater.h"
#include "allocator.h"
#include "uart.h"
#include "sys.h"
#include "tools.h"
#include "vfs.h"
#include "error.h"
#include "cpio.h"
//#include "irq.h"
//#include "printf.h"

static struct task_struct init_task = INIT_TASK;
struct task_struct *current = &(init_task);
struct task_struct * task[NR_TASKS] = {&(init_task), };
struct task_struct * u_task[NR_TASKS] = {&(init_task), };

int n_tasks = 1;
int n_task_id = 1;

void enable_preempt()
{
    current->preempt_count++;
}
void disable_preempt()
{
    current->preempt_count--;
}


void _schedule(void)
{
	//disable_preempt();
	int next,c;
	struct task_struct * p;
	while (1) {
		c = -1;
		next = 0;
		for (int i = 0; i < NR_TASKS; i++){
			p = task[i];
			if (p && p->state == TASK_RUNNING && p->counter > c) {
				c = p->counter;
				next = i;
			}
		}
		if (c) {
			break;
		}
		for (int i = 0; i < NR_TASKS; i++) {
			p = task[i];
			if (p) {
				p->counter = (p->counter >> 1) + p->priority;
			}
		}
	}
	switch_to(task[next]);
	//enable_preempt();
}

void schedule(void)
{
	current->counter = 0;
	_schedule();
}

void switch_to(struct task_struct * next) 
{
	//uart_puts("haha\n");
	if (current == next) 
		return;
	struct task_struct * prev = current;
	current = next;
	cpu_switch_to(prev, next);
}

void schedule_tail(void) 
{
	enable_preempt();
}

int thread_create(void (*func)())
{
	//disable_preempt();
	struct task_struct *p;

	p = (struct task_struct *)falloc(THREAD_SIZE);
	if (!p)
		return 1;
	p->priority = current->priority;
	p->state = TASK_RUNNING;
	p->counter = p->priority;
	p->preempt_count = 1; //disable preemtion until schedule_tail

	p->cpu_context.x19 = (unsigned long)func;
	p->cpu_context.pc = (unsigned long)ret_from_fork;
	p->cpu_context.sp = (unsigned long)p + THREAD_SIZE;
	p->taskid =n_task_id;
	p->parentid = current->taskid;
	n_task_id++;
	for(int i=0;i<FD_TABLE_SIZE;++i)p->fd_table[i]=0;

	p->storeid = n_tasks;
	struct task_struct *new_utask = (struct task_struct *)falloc(THREAD_SIZE);
    u_task[n_tasks] = new_utask;
	task[n_tasks] = p;

	//printf
	// print_mem(u_task[n_tasks]);
	// uart_puts("\n");
	// print_mem(task[n_tasks]);
	// uart_puts("\nEND!!! \n");

    n_tasks++; 
    n_tasks%=NR_TASKS;

	uart_puts("Create new Task: ");
    print_int(p->taskid);
	uart_puts("\n");
	//enable_preempt();
	return p->taskid;
}

void foo(){
    for(int i = 0; i < 10; i++) {
        uart_puts("Thread id: ");
		print_int(current->taskid);
		uart_puts(" ");
		print_int(i);
		uart_puts("\n");
        delay(1000000);
        schedule();
    }
	my_exit();
}

void idle()
{
    while(1)
    {
		//uart_puts("Idel Stage\n");
        kill_zombies();
        schedule();
    }
}

void kernel_main_1() {
    for(int i = 0; i < 3; ++i) 
	{ // N should > 2
        thread_create(foo);
    }
    idle();
}

void kill_zombies()
{
	//disable_preempt();
	for(int i=0 ; i < n_tasks ; i++)
	{
		//print_int(task[i]->state);
		if(task[i]->state == TASK_ZOMBIE)
		{
			for(int i=0;i<FD_TABLE_SIZE;++i)
			{
				if(task[i]->fd_table[i])
				{
					vfs_close(task[i]->fd_table[i]);
				}
			}

			n_tasks = n_tasks - 1;
			uart_puts("KILL : pid ");
			print_int(task[i]->taskid);
			uart_puts("\n");
			ffree((unsigned long int)task[i]);
			for(int j = i ; j < n_tasks ; j++)
			{
				task[j] = task[j+1];
			}
		}
	}
	//uart_puts("\n");
	//enable_preempt();
}

void my_exit()
{
	//uart_puts("TASK_ZOMBIE\n");
	current -> state = TASK_ZOMBIE; 
	schedule();
}


int argv_test() 
{
	// int 
	// int argc = int* ;

	// char argv[argc]
	// print_int(argc);
	// uart_puts("argv_test\n");




    //printf("Argv Test, pid %d\n", getpid());
    //for (int i = 0; i < argc; ++i) {
    //    puts(argv[i]);
    //}
    //char *fork_argv[] = {"fork_test", 0};
    //exec("fork_test", fork_argv);
	my_exit();
}


void user_test()
{
	uart_puts("user_test\n");
    char* argv[] = {"argv_test", "-o", "arg2", 0};
	int argc = 0;
	while(argv[argc]!=0)
	{
		argc = argc + 1;
	}
	//print_int(argc);
	
    call_exec(argv_test,argc,argv);

	//uart_puts("After user_test\n");
	//schedule();
	//my_exit();

	schedule();
}

void kernel_main_2() 
{
	char* argv[] = {"argv_test", "-o", "arg2", 0};

	load_user_program_withArgv("app5",argv);
    // thread_create(user_test);
	// schedule();
    //idle();
}

int fork()
{
}

//0x8ca78
void exec(void (*func)(),int argc,char **argv)
{
	// print_int(argc);
	// uart_puts(argv[0]);
	//print_mem(u_task[current->taskid]);
    asm volatile("msr sp_el0, %0"::"r"(u_task[current->taskid]):);
	asm volatile("msr spsr_el1, %0"::"r"(0):);
	asm volatile("msr elr_el1, %0"::"r"(*func):);
	asm volatile("eret");
}
int get_taskid(){
    return current->taskid;
}


// void timer_tick()
// {

// 	--current->counter;
// 	if (current->counter>0 || current->preempt_count >0) {
// 		return;
// 	}
// 	current->counter=0;
// 	enable_irq();
// 	_schedule();
// 	disable_irq();
// }

void lab62()
{
	char* argv[] = {"argv_test", "-o", "arg2", 0};
	load_user_program_withArgv("app5",argv);
}

void demo62()
{
	thread_create(lab62);
	//schedule();
	idle();
}







int my_open(const char* pathname, int flags){
	//uart_puts("create\n");
	int ret=-1;
	for(int i=0;i<FD_TABLE_SIZE;++i){
		if(current->fd_table[i]==0){
			ret=i;
			current->fd_table[i]=vfs_open(pathname,flags);
			break;
		}
	}
	//uart_printf("%d\n",ret);
	return ret;

}

int my_close(int fd){
	if(fd<0||fd>=FD_TABLE_SIZE)ERROR("invalid fd!!");
	if(current->fd_table[fd]){
		vfs_close(current->fd_table[fd]);
		current->fd_table[fd]=0;
	}
	return 0;
}

int my_write(int fd,const void* buf,unsigned long len){
    if(fd<0||fd>=FD_TABLE_SIZE)ERROR("invalid fd!!");
	if(current->fd_table[fd]){
		return vfs_write(current->fd_table[fd],buf,len);
	}
	return 0;
}

int my_read(int fd,void* buf,unsigned long len){
    if(fd<0||fd>=FD_TABLE_SIZE)ERROR("invalid fd!!");
	if(current->fd_table[fd]){
		return vfs_read(current->fd_table[fd],buf,len);
	}
	return 0;
}