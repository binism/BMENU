#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"


make_helper(concat(xchg_r2ra_,SUFFIX)) {
	int reg_code = instr_fetch(eip,1) & 0x7;
	DATA_TYPE temp = REG(0x0);
	REG(0x0) = REG(reg_code);
	REG(reg_code)=temp;
	print_asm("xchg" str(SUFFIX) " %%%s,%%%s",REG_NAME(reg_code),REG_NAME(0x0));
	return 1;
}


make_helper(concat(xchg_r2rm_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
	if(m.mod == 3) {
		DATA_TYPE temp = REG(m.R_M);
		REG(m.R_M) = REG(m.reg);
		REG(m.reg) = temp;
		print_asm("xchg" str(SUFFIX) " %%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		DATA_TYPE temp = MEM_R(addr);
		MEM_W(addr,REG(m.reg));
		REG(m.reg)=temp;
		print_asm("xchg"str(SUFFIX) " %s,%%%s",ModR_M_asm,REG_NAME(m.reg));
		return len + 1;
	}
}





#include "exec/template-end.h"
