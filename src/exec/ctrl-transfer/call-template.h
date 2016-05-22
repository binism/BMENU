#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(CALL_rel_,SUFFIX)) {
	DATA_TYPE rel;
	rel = instr_fetch(eip + 1,DATA_BYTE);
    cpu.esp=cpu.esp-4;
    swaddr_t addr;
    addr = cpu.esp;
    MEM_W(addr,cpu.eip  + DATA_BYTE);
    if(DATA_BYTE==2)
		cpu.eip = (cpu.eip+rel)&0xffff;
	else if(DATA_BYTE==4)
		cpu.eip = cpu.eip + rel;
        
	print_asm("call" " 0x%x",cpu.eip + 1 + DATA_BYTE);
	return 1 + DATA_BYTE;
}	



#include "exec/template-end.h"
