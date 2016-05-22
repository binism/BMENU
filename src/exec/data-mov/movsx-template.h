#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(movsx_rmb2r_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
                 int8_t tmp = REG(m.R_M);
		 REG(m.reg) = tmp;
		 print_asm("movsx" " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
		 return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		int8_t tmp = MEM_R(addr);
		REG(m.reg) = tmp;
		print_asm("movsx" " %s,%%%s",ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}

make_helper(concat(movsx_rmw2r_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if (m.mod == 3) {
		int16_t tmp = REG(m.R_M);
       REG(m.reg) = tmp;
	   print_asm("movsx" "%%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
	   return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		int16_t tmp = MEM_R(addr);
		REG(m.reg) = tmp;
		print_asm("movsx""%s,%%%s",ModR_M_asm,REG_NAME(m.reg));
		return len + 1;
	}
}



#include "exec/template-end.h"

