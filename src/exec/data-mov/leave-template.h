#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(leave_r_,SUFFIX)) {
	cpu.esp = cpu.ebp;
	swaddr_t addr = cpu.ebp;
	if(DATA_BYTE==2)
	{ cpu.ebp = MEM_R(addr) & 0xffff;
	  cpu.esp = cpu.esp+2;
	}
	else if(DATA_BYTE==4)
	{	cpu.ebp = MEM_R(addr);
		cpu.esp = cpu.esp+4;
	}
    print_asm("leave");
    return 1;
}	

#include "exec/template-end.h"
