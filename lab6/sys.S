#include "sys.h"

.globl call_sys_write
call_sys_write:
	mov w8, #SYS_WRITE_NUMBER	
	svc #0
	ret

.globl call_sys_write_char
call_sys_write_char:
	mov w8, #SYS_WRITE_CHAR_NUMBER	
	svc #0
	ret

.globl call_sys_read
call_sys_read:
	mov w8, #SYS_READ_NUMBER	
	svc #0
	ret

.globl call_sys_malloc
call_sys_malloc:
	mov w8, #SYS_MALLOC_NUMBER	
	svc #0
	ret

.globl call_sys_exit
call_sys_exit:
	mov w8, #SYS_EXIT_NUMBER	
	svc #0
	ret

.globl  call_sys_chk_exl
call_sys_chk_exl:
    mov w8, #SYS_CHK_EXL	
	svc #0
	ret

.globl  call_sys_chk_exl_info
call_sys_chk_exl_info:
    mov w8, #SYS_CHK_EXL_INFO	
	svc #0
	ret

.globl  call_sys_enable_time
call_sys_enable_time:
    mov w8, #SYS_ENABLE_TIME	
	svc #0
	ret

.globl  call_sys_get_taskid
call_sys_get_taskid:
    mov w8, #SYS_GET_TASKID	
	svc #0
	ret

.globl  call_fork
call_fork:
    mov w8, #SYS_FORK
	svc #0
	ret

.globl  call_exec
call_exec:
    mov w8, #SYS_EXEC
	svc #0
	ret

.globl  call_file_open
call_file_open:
    mov w8, #SYS_FILE_OPEN
	svc #0
	ret

.globl  call_file_close
call_file_close:
    mov w8, #SYS_FILE_CLOSE
	svc #0
	ret

.globl  call_file_read
call_file_read:
    mov w8, #SYS_FILE_READ
	svc #0
	ret

.globl  call_file_write
call_file_write:
    mov w8, #SYS_FILE_WRITE
	svc #0
	ret

.global call_uart_printf
call_uart_printf:
	mov w8, #SYS_UART_PRINTF
	svc #0
	ret
