void dumpArchive();
void* fbaseGet();
int fmodeGet(void* _addr);
char* fdataGet(void* _addr,unsigned long* size);
char* fnameGet(void* _addr,unsigned long* size);
void* nextfGet(void* _addr);
void fDump();
unsigned long argv_puts(char **argv, unsigned long stack_top);
unsigned long load_user_program_withArgv(char *name, char **argv);