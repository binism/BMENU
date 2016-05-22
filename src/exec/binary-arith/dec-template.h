#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "eflags.h"
#define length (DATA_BYTE*8-1)

make_helper(concat(dec_r_,SUFFIX)) {
   ModR_M m;
   m.val = instr_fetch(eip + 1,1);
   DATA_TYPE tmp = REG(m.reg);
   DATA_TYPE MSB_1 = MSB(REG(m.reg)); 
   REG(m.R_M)=REG(m.reg) - 1;
   DATA_TYPE MSB_2 = MSB(REG(m.reg)); 
   dec_eflags_change(tmp,MSB_1,MSB_2);
   print_asm("dec" " $0x1,%%%s",REG_NAME(m.reg));
   return 1 + 1 ;
}

make_helper(concat(dec_rm_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
	if(m.mod == 3) {
		DATA_TYPE tmp = REG(m.R_M);
		DATA_TYPE MSB_1 = MSB(REG(m.R_M));
       REG(m.R_M)=REG(m.R_M) - 1;
	   DATA_TYPE MSB_2 = MSB(REG(m.R_M));
       dec_eflags_change(tmp,MSB_1,MSB_2);
       print_asm("dec" " $0x1,%%%s",REG_NAME(m.R_M));
       return 1 + 1 ;
	}
 else {
        swaddr_t addr;
        DATA_TYPE len = read_ModR_M(eip + 1,&addr);
		DATA_TYPE tmp = MEM_R(addr);
		DATA_TYPE MSB_1 = MSB(MEM_R(addr));
        MEM_W(addr,MEM_R(addr) - 1 );
		DATA_TYPE MSB_2 = MSB(MEM_R(addr));
	    dec_eflags_change(tmp,MSB_1,MSB_2);
        print_asm("dec" " $0x1,%%%s",ModR_M_asm);
        return len + 1 ;
     }	
}


#include "exec/template-end.h"
