#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"



make_helper(concat(not_rm_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
	if(m.mod==3) {
		REG(m.R_M)=~REG(m.R_M);
		print_asm("not" " %%%s",REG_NAME(m.R_M));
		return 1 + 1;
	}
	else {
		swaddr_t addr;
		DATA_TYPE len = read_ModR_M(eip + 1,&addr);
		MEM_W(addr,~MEM_R(addr));
		print_asm("not"" %s",ModR_M_asm);
		return len + 1;
	}
}


#include "exec/template-end.h"
