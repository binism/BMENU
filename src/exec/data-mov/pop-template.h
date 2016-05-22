#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"


make_helper(concat(pop_r_,SUFFIX)) {
	int reg_code = instr_fetch(eip,1) & 0x7;
	swaddr_t addr;
	addr = cpu.esp;
    REG(reg_code) = MEM_R(addr);
	if(DATA_BYTE == 2)
	    cpu.esp = cpu.esp + 2;
	else if(DATA_BYTE == 4)
		cpu.esp = cpu.esp + 4;
	print_asm("pop" str(SUFFIX) " %%%s",REG_NAME(reg_code));
	return 1;
}

make_helper(concat(pop_m_,SUFFIX)) {
	DATA_TYPE temp;
	swaddr_t addr;
	int len = read_ModR_M(eip + 1,&addr);
	temp = MEM_R(cpu.esp);
	MEM_W(addr,temp);
	if(DATA_BYTE==2)
		cpu.esp = cpu.esp + 2;
	else if(DATA_BYTE==4)
		cpu.esp = cpu.esp + 4;
	print_asm("pop"str(SUFFIX) " %s",ModR_M_asm);
    return 1 + len;
}

#include "exec/template-end.h"
