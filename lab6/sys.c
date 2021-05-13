#include "allocater.h"
#include "allocator.h"
#include "uart.h"
#include "sched.h"
#include "exception.h"
#include "tmpfs.h"
void sys_write(char * buf){
	uart_puts(buf);
}
void sys_write_char(char buf){
	uart_send(buf);
}
int sys_read(){
	return uart_getc();
}

int sys_fork(){
	return fork();
}
void sys_exec(void (*func)(),int argc,char **argv){
	exec(func,argc,argv);
}

int sys_clone(unsigned long stack){
	// return copy_process(0, 0, 0, stack);
    return 0;
}

unsigned long sys_malloc(){
	unsigned long addr = (unsigned long int)falloc(THREAD_SIZE);
	if (!addr) {
		return -1;
	}
	return addr;
}

void sys_exit(){
    my_exit();
}

void sys_chk_exl_info(){
    int address, syndrome;
    asm volatile ("mrs %0, elr_el1\n"
            "mrs %1, esr_el1\n":"=r" (address), "=r" (syndrome));
    int iss = syndrome & 0x01ffffff;
    int ec = (syndrome & 0xfc000000) >> 26;
	// uart_puts("Exception return address: ");
    // uart_hex(address);
    // uart_send('\n');
    // uart_puts("Exception class (EC): ");
    // uart_hex(ec);
    // uart_send('\n');    
    // uart_puts("Instruction specific syndrome (ISS): ");
    // uart_hex(iss);
    // uart_send('\n');
}
void sys_chk_exl(){
    uart_puts("Exception level: ");               
    int el = get_el();
    // uart_send_int(el);
    // uart_puts("\n");
}
void sys_enable_time(){
	core_timer_enable();
}

int sys_get_taskid(){
	return get_taskid();
}

int sys_file_open(const char* pathname, int flags){
    return my_open(pathname,flags);
}

int sys_file_close(int fd){
    return my_close(fd);
}

int sys_file_write(int fd,const void* buf,unsigned long len){
    return my_write(fd,buf,len);
}

int sys_file_read(int fd,void* buf,unsigned long len){
    return my_read(fd,buf,len);
}

unsigned int sys_uart_printf(char* fmt,...){
    return uart_printf(fmt);
}

void * const sys_call_table[] = {
    sys_write,
    sys_malloc, 
    sys_clone, 
    sys_exit, 
    sys_chk_exl, 
    sys_enable_time, 
    sys_chk_exl_info, 
    sys_get_taskid, 
    sys_read, 
    sys_write_char, 
    sys_fork, 
    sys_exec,
    sys_file_open,
    sys_file_close,
    sys_file_read,
    sys_file_write,
    sys_uart_printf,
};



/*

file* vfs_open(const char* pathname, int flags);
int vfs_close(file* f);
int vfs_write(file* f,const void* buf,unsigned long len);
int vfs_read(file* f,void* buf,unsigned long len);
void vfs_init(void* setup_mount_f,void* write_f,void* read_f);

*/