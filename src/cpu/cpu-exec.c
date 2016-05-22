#include "ui/ui.h"

#include "nemu.h"

#include <setjmp.h>

#define LOADER_START 0x100000

int exec(swaddr_t);
void load_prog();
void init_dram();
uint32_t find_bpaddr(uint32_t addr);
char assembly[40];
jmp_buf jbuf;	/* Make it easy to perform exception handling */
int jg;
uint32_t tmp_eip;
extern uint8_t loader [];
extern uint32_t loader_len;

extern int quiet;

void restart() {
	/* Perform some initialization to restart a program */
	load_prog();
	memcpy(hwa_to_va(LOADER_START), loader, loader_len);

	cpu.eip = LOADER_START;
        cpu.ebp = 0x0;
        cpu.esp = 0x8000000;
	cpu.EFLAGS.val=0x2;//binism added 10.26

	init_dram();
}

static void print_bin_instr(swaddr_t eip, int len) {
	int i;
	printf("%8x:   ", eip);
	for(i = 0; i < len; i ++) { 
		printf("%02x ", swaddr_read(eip + i, 1));
	}
	printf("%*.s", 50 - (12 + 3 * len), "");
}

void cpu_exec(volatile uint32_t n) {
	volatile uint32_t n_temp = n;

	setjmp(jbuf);
	for(; n > 0; n --) { 
		swaddr_t eip_temp = cpu.eip;
		int instr_len = exec(cpu.eip);

		cpu.eip += instr_len;

		if(n_temp != -1 || (enable_debug && !quiet)) {
			print_bin_instr(eip_temp, instr_len);
			puts(assembly);
 		}
        if(nemu_state==BREAK){
		    uint32_t bpaddr=find_bpaddr(cpu.eip-1);
            swaddr_write(cpu.eip-1,1,bpaddr);
			printf("Breakpoint at 0x%x.\n",cpu.eip-1);
            tmp_eip=cpu.eip;
			cpu.eip--;
			tmp_eip--;
		    jg=1;
			return;
		}
	    if (jg==1){
	    swaddr_write(tmp_eip,1,0xcc);	
		}	
 		if(nemu_state == INT) {
			printf("\n\nUser interrupt\n");
			return;
		} 
		else if(nemu_state == END) { return; }
	}
}
