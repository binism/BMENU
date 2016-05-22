#include "ui/ui.h"
#include "exec/func-name.h"
#include "nemu.h"
#include "memory.h"
#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int nemu_state = END;
void cpu_exec(uint32_t);
void restart();
void new_bp();
void free_all_bp();
void free_bp();
void print_info_b();
uint32_t expr();

/* We use the readline library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(nemu) ");

	if (line_read && *line_read) {
		add_history(line_read);
	}

	return line_read;
}

/* This function will be called when you press <C-c>. And it will return to 
 * where you press <C-c>. If you are interesting in how it works, please
 * search for "Unix signal" in the Internet.
 */
static void control_C(int signum) {
	if(nemu_state == RUNNING) {
		nemu_state = INT;
	}
}

void init_signal() {
	/* Register a signal handler. */
	struct sigaction s;
	memset(&s, 0, sizeof(s));
	s.sa_handler = control_C;
	int ret = sigaction(SIGINT, &s, NULL);
	assert(ret == 0);
}

static void cmd_c() {
	if(nemu_state == END) {
		puts("The Programe does not start.Use 'r' command to start the program.");
		return;
	}

	nemu_state = RUNNING;
	cpu_exec(-1);
	if(nemu_state != END) { nemu_state = STOP; }
}
static void cmd_si(uint32_t n){//[BINISM added]
    if(nemu_state==END){
		restart();
		nemu_state=RUNNING;
        nemu_state = STOP;
	}
	cpu_exec(n);
}//9.21 17:20
static void cmd_r() {
	if(nemu_state != END) { 
		char c;
		while(1) {
			printf("The program is already running. Restart the program? (y or n)");
			scanf("%c", &c);
			switch(c) {
				case 'y': goto restart_;
				case 'n': return;
				default: puts("Please answer y or n.");
			}
		}
	}

restart_:
	restart();
	nemu_state = STOP;
	cmd_c();
}
static void cmd_b(char *exp) {
	if (!exp) {
		puts("Bad input!");
		return;
	}
	bool val = true;
	swaddr_t addr = expr(exp,&val);
	new_bp(addr,swaddr_read(addr,1));
	swaddr_write(addr,1,0xcc);
}

	
/*-------------------binism-------------------------------------*/
static void print_smemory(swaddr_t eip,int len)
{ 
      int i;
	  printf("%8x:  ",eip);
	  for(i=0; i<len; i++){
	  printf("%02x  ",swaddr_read(eip+i,1));
	  }
      printf("\n");
}
/*-------------------binism-------------------------------------------*/
static void cmd_bt(){
        if(!cpu.eip) {
		puts("No stack.");
		return;
	}
	swaddr_t addr=cpu.eip;
	swaddr_t ebp=cpu.ebp;
	bool find_suc=1;
	char* func_name=NULL;
        int i = 1;
	find_suc=find_func_name(addr,&func_name);
	do{
		printf("#%d\t0x%08x in func:%s\n",i,addr,func_name);
                i ++;
		addr=swaddr_read(ebp+4,4);
		ebp=swaddr_read(ebp,4);
		find_suc=find_func_name(addr,&func_name);
	}while(find_suc);
}

void main_loop() {
	char *cmd;
	while(1) { 
		cmd = rl_gets();
		char *p = strtok(cmd, " ");

		if(p == NULL) { continue; }

		if(strcmp(p, "c") == 0) { cmd_c(); }
		else if(strcmp(p, "r") == 0) { cmd_r(); }
		else if(strcmp(p, "q") == 0) { return; }
        else if(strcmp(p,"si") == 0) {//[BINISM added]
           p=strtok(NULL," ");
		   if (p==NULL)
		   cmd_si(1);
		   else{uint32_t n;
			   sscanf(p,"%u",&n);
		   cmd_si(n);}
		 //9.21 17:26
		}//[BINISM added]
		else if(strcmp(p,"info")==0){
			p=strtok(NULL," ");
            if(strcmp(p,"r")==0){
					printf("eax-----------------0x%x\n",cpu.eax);
					printf("ecx-----------------0x%x\n",cpu.ecx);
				    printf("edx-----------------0x%x\n",cpu.edx);
				 	printf("ebx-----------------0x%x\n",cpu.ebx);
					printf("esp-----------------0x%x\n",cpu.esp);
					printf("ebp-----------------0x%x\n",cpu.ebp);
					printf("esi-----------------0x%x\n",cpu.esi);
					printf("edi-----------------0x%x\n",cpu.edi);
                                        printf("eip-----------------0x%x\n",cpu.eip);
                                        printf("EFLAGS--------------0x%x\n",cpu.EFLAGS.val);
                                        printf("ZF-----------------0x%x\n",cpu.EFLAGS.ZF);
                                        printf("CF-----------------0x%x\n",cpu.EFLAGS.CF);
                                        printf("PF-----------------0x%x\n",cpu.EFLAGS.PF);
                                        printf("SF-----------------0x%x\n",cpu.EFLAGS.SF);
                                        printf("IF-----------------0x%x\n",cpu.EFLAGS.IF);
                                        printf("DF-----------------0x%x\n",cpu.EFLAGS.DF);
                                        printf("OF-----------------0x%x\n",cpu.EFLAGS.OF);

			}
			else if(strcmp(p,"b")==0)
				print_info_b();
            else printf("Unknown commod!");
		}//9.21 17:29
		/*当前:扫描内存-------binism------------------------
		 */ else if(strcmp(p,"x")==0){
			p=strtok(NULL," ");
            uint32_t N=0;
			if (p==NULL)
			{printf("Please input length N after 'x'!"); assert(0);}
			else
			    sscanf(p,"%u",&N);
			p=strtok(NULL," ");
            uint32_t addr;
			if (p==NULL)
			{printf("Please input address after 'N'!"); assert(0);}
            else
            sscanf(p,"%x",&addr);
		    print_smemory(addr,N);
		 }
		 /*-------------------------------------------------*/
		else if (strcmp(p,"b")==0) {
			p=strtok(NULL," ");
			/*uint32_t addr;
			sscanf(p,"*0x%x",&addr);
            new_bp(addr,swaddr_read(addr,1));
            swaddr_write(addr,1,0xcc);  */
			cmd_b(p);
		}
		else if (strcmp(p,"d")==0){
		p=strtok(NULL," ");
        if (p==NULL)
			free_all_bp();
		else 
		  {  uint32_t num;
			sscanf(p,"%u",&num);
			free_bp(num);
		  }
 		}
        else if (strcmp(p,"p")==0){
		p=strtok(NULL,"");
		bool suc=true;
	   int m=expr(p,&suc);
	   printf("The result is %d.\n",m);
		}
        else if (strcmp(p,"bt")==0){
                cmd_bt();
                 }
		/* TODO: Add more commands */

		else { printf("Unknown command '%s'\n", p); }
	

 	}
}
