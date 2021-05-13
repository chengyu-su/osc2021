#include "tools.h"
#include "uart.h"
void print_int(int t)
{
    char c[20];
    if(t == 0)
    {
        uart_puts("0");
        return ;
    }
    else
    {
        int index = 0;
        while( t > 0)
        {
            c[index] = '0' + (t % 10);
            t = t / 10;
            index = index + 1;
        }
        while(index--)
        {
            uart_send(c[index]);
        }
    }
}

void print_int_alig(int t,int y)
{
    char c[20];
    if(t == 0)
    {
        for(int i=0;i<y;i++)
        {
            uart_puts("0");
        }
        return ;
    }
    else
    {
        int index = 0;
        while( t > 0)
        {
            c[index] = '0' + (t % 10);
            t = t / 10;
            index = index + 1;
        }
        for(int i=0;i<(y-index);i++)
        {
            uart_puts("0");
        }
        while(index--)
        {
            uart_send(c[index]);
        }
    }
}

void print_mem(void* t)
{
    unsigned long int tmp = (unsigned long int) t;
    if(tmp==0)
    {
        uart_puts("0x0000000000000000");
        return;
    }
    else
    {
        char c[50];
        int index = 0;
        while(tmp>0)
        {   
            if((tmp % 16 ) > 9)
            {
                c[index] = 'A' + (tmp % 16 -10);
            }
            else
            {
                c[index] = '0' + (tmp % 16); 
            }
            index = index +1;
            tmp = tmp / 16;
        }
        uart_puts("0x");
        for(int i=0 ;i<(16-index);i++)
        {
            uart_send('0');
        }
        while(index--)
        {
            uart_send(c[index]);
        }
    }
}

int my_pow(int a,int b)
{
    int c = 1;
    for(int i=0;i<b;i++)
    {
        c = c * a;
    }
    return c;
}

int my_quar(int a,int b)
{
    int c = 1,d=0;
    while(c < b)
    {
        c = c * a;
        d = d + 1;
    }
    return d;
}

int strcmp(const char *input,const char *command)
{
    while(*input != '\0')
    {
        if(*input != *command)
        {
            return 0;
        }
        input = input + 1;
        command = command +1;
    }
    if (*input != *command)
    {
        return 0;
    }
    return 1;
}

int atoi(unsigned char* s, int base) {
    int i = 0;
    int num = 0;
    int negative = 0;

    while(s[i] != '\0') {
        if(i == 0 && s[i] == '-') {
            negative = 1;
        }
        if(base == 10) {
            int digit = s[i] - '0';
            num = num*10 + digit;
        }
        if(base == 16) {
            int digit = s[i] >= 'A' ? s[i] - 'A'+ 10 : s[i] - '0';
            num = num*16 + digit;
        }
        i++;
    }
    
    if(negative) return num *= -1;
    return num;
}

unsigned char *subStr(unsigned char *s, int length) {
    static unsigned char cRes[1024];
    unsigned char *pRes = cRes;
    int i;
    for(i = 0; i < length; i++) {
        *pRes = s[i];
        pRes++;
    }
    *pRes = '\0';
    return cRes;
}