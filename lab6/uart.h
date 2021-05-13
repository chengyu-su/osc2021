void uart_init();
void uart_send(unsigned int c);
char uart_getc();
void uart_puts(char *s);
unsigned long uart_getX(int display);

unsigned int uart_printf(char* fmt,...);
