#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"


make_helper(concat(JMP_rel_,SUFFIX)) {
   DATA_TYPE_S rel;
   rel = instr_fetch(eip + 1,DATA_BYTE);
   cpu.eip += rel;
   if (DATA_BYTE==2)
	   cpu.eip = cpu.eip & 0xffff;
   print_asm("jmp" " 0x%x",cpu.eip + 1 + DATA_BYTE);
   return 1 + DATA_BYTE;
}


make_helper(concat(JMP_rm_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
	if(m.mod==3)  {
		if(DATA_BYTE==2)
			cpu.eip = REG(m.R_M)&0xffff;
		else if (DATA_BYTE==4)
			cpu.eip = REG(m.R_M);
		print_asm("jmp"" 0x%x",REG(m.R_M));
		return 1 + 1;
	}
	else { 
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		if(DATA_BYTE==2)
			cpu.eip = MEM_R(addr)&0xffff;
		else if(DATA_BYTE==4)
			cpu.eip = MEM_R(addr);
		print_asm("jmp" " $0x%x",addr);
		return 1 + len;
	}
}





#include "exec/template-end.h"
