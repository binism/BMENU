#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#define length (DATA_BYTE*8-1)

make_helper(concat(mul_rm2ra_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
    if(m.mod == 3) {
	DATA_TYPE temp1 = REG(0x0);
	DATA_TYPE temp2 = REG(m.R_M);
	long long prod = temp1 * temp2;
	uint16_t tmp,tmp0,tmp1;
	switch (DATA_BYTE)
	{ case 1:  tmp=prod; REG(0x0)=tmp&0xff; break;
	  case 2:  tmp0=prod;  tmp1=prod>>16; REG(0x0)=tmp0&0xff; REG(0x2)=tmp1&0xff; break;
	  case 4: REG(0x0)=prod; REG(0x2)=prod>>32; break;
	  default : assert(0);
	}
	 if (prod>>(length+1)==0)
	 {   cpu.EFLAGS.CF=0;
	    cpu.EFLAGS.OF=0;
	 }
	 else 
	 {  cpu.EFLAGS.CF=1;
	    cpu.EFLAGS.OF=1;
	 }
	  print_asm("mul" " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(0x0));
	 return 1 + 1;
    }
    else {
	swaddr_t addr;
    DATA_TYPE len = read_ModR_M(eip + 1, &addr);
    DATA_TYPE temp1 = REG(0x0);
	DATA_TYPE temp2 = MEM_R(addr);
	long long prod = temp1 * temp2;
	uint16_t tmp,tmp0,tmp1;
	switch (DATA_BYTE)
		{ case 1:  tmp=prod; REG(0x0)=tmp&0xff; break;
			case 2:  tmp0=prod;  tmp1=prod>>16; REG(0x0)=tmp0&0xff; REG(0x2)=tmp1&0xff; break;
		  case 4: REG(0x0)=prod; REG(0x2)=prod>>32; break;
		  default : assert(0);
		}
	 if (prod>>(length+1)==0)
		 {   cpu.EFLAGS.CF=0;
			 cpu.EFLAGS.OF=0;
	     }
	 else 
		 {  cpu.EFLAGS.CF=1;
		    cpu.EFLAGS.OF=1;
         }		
	  print_asm("mul" " %s, %%%s",ModR_M_asm,REG_NAME(0x0));
	  return len + 1;
	}
}
#include "exec/template-end.h"
