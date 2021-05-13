#include "uart.h"
#include "allocater.h"
#include "tools.h"
#include "exception.h"
static int time = 0;

char *entry_error_messages[] = {
	"SYNC_INVALID_EL1t",
	"IRQ_INVALID_EL1t",		
	"FIQ_INVALID_EL1t",		
	"ERROR_INVALID_EL1T",		

	"SYNC_INVALID_EL1h",		
	"IRQ_INVALID_EL1h",		
	"FIQ_INVALID_EL1h",		
	"ERROR_INVALID_EL1h",		

	"SYNC_INVALID_EL0_64",		
	"IRQ_INVALID_EL0_64",		
	"FIQ_INVALID_EL0_64",		
	"ERROR_INVALID_EL0_64",	

	"SYNC_INVALID_EL0_32",		
	"IRQ_INVALID_EL0_32",		
	"FIQ_INVALID_EL0_32",		
	"ERROR_INVALID_EL0_32",

	"SYNC_ERROR"																																																							,
	"SYSCALL_ERROR"
};																																												

void timer_init()
{
	unsigned long int count,freq;
	asm volatile ("mrs %0, cntpct_el0" :"=r" (count));
	asm volatile ("mrs %0, cntfrq_el0" :"=r" (freq));
	//cntpct_el0,cntfrq_el0
	//print_int(count);
	//uart_puts("\n");
	//print_int(freq);
	//uart_puts("\n");
	time = count / freq;
}
void irq_router(void)
{
	//spsr_el1 : 0x0000000060000000
    //elr_el1 : 0x0000000000081640
    //esr_el1 : 0x0000000000000000

	uart_puts("core time : ");
	print_int(time);
	uart_puts("\n");
	time = time + 2;
	core_timer_handler();
}
void exception_handler (void)
{
    

    //spsr_el1, elr_el1, and esr_el1 
    unsigned long int spsr,elr,esr;
    asm volatile ("mrs %0, spsr_el1\n" :"=r" (spsr));//200003C0  --> 2 is C bit 
    asm volatile ("mrs %0, elr_el1\n" :"=r" (elr));
    asm volatile ("mrs %0, esr_el1\n" :"=r" (esr));
	    

	int iss = esr & 0x01ffffff;

	if(iss == 1)
	{
		timer_init();
		core_timer_enable();
	}
	if(iss == 0)
	{
		uart_puts("exception handler!!!\n");
		uart_puts("     spsr_el1 : ");
		print_mem((void*)spsr);
		uart_puts("\n");
			
		uart_puts("      elr_el1 : ");
		print_mem((void*)elr);
		uart_puts("\n");

		uart_puts("      esr_el1 : ");
		print_mem((void*)esr);
		uart_puts("\n");  
	}
}
void not_implemented ()
{
  uart_puts ("function not implemented!\n");
  while (1);
}


void show_invalid_entry_message(int type, unsigned long esr, unsigned long address)
{
  uart_puts (entry_error_messages[type]);
  uart_puts ("\n ESR: ");
  print_mem((void*)esr);
  uart_puts ("\n address: ");
  print_mem((void*)address);
  uart_puts ("\n ");
}
