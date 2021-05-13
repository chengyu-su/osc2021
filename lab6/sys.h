
// define system call table
#define __NR_syscalls	    17

#define SYS_WRITE_NUMBER    0 		// syscal numbers 
#define SYS_MALLOC_NUMBER   1 	
#define SYS_CLONE_NUMBER    2 	
#define SYS_EXIT_NUMBER     3 	
#define SYS_CHK_EXL         4 
#define SYS_ENABLE_TIME     5
#define SYS_CHK_EXL_INFO    6
#define SYS_GET_TASKID      7
#define SYS_READ_NUMBER     8
#define SYS_WRITE_CHAR_NUMBER 9
#define SYS_FORK           10
#define SYS_EXEC           11
#define SYS_FILE_OPEN      12
#define SYS_FILE_CLOSE     13
#define SYS_FILE_READ      14
#define SYS_FILE_WRITE     15
#define SYS_UART_PRINTF    16



#ifndef __ASSEMBLER__
void sys_write(char * buf);


extern void call_sys_write(char * buf);
extern void call_sys_write_char(char buf);
extern char call_sys_read();
extern int call_sys_clone(unsigned long fn);
extern unsigned long call_sys_malloc();
extern void call_sys_exit();
extern void call_sys_chk_exl();
extern void call_sys_chk_exl_info();
extern void call_sys_enable_time();
extern int call_sys_get_taskid();
extern int call_fork();
extern void call_exec();
extern int call_file_open();
extern void call_file_close();
extern int call_file_read();
extern int call_file_write();
extern void call_uart_printf();

#endif