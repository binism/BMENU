#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
int exec(swaddr_t);

make_helper(concat(rep_,SUFFIX)) {
	int32_t code=instr_fetch(eip+1,1);
	int instr_len=1;
	switch(code){
		case 0xA4:
		  while(reg_l(1)>0)
			{ instr_len=exec(eip+1);
                           reg_l(1)--;
                        }
			print_asm("rep movs %%%s,%%%s",REG_NAME(R_ESI),REG_NAME(R_EDI));
			return instr_len+1;
			break;
		case 0xA5:
			 while(reg_l(1)>0)
			{ instr_len=exec(eip+1);
                           reg_l(1)--;
                        }
			print_asm("rep movs %%%s,%%%s",REG_NAME(R_ESI),REG_NAME(R_EDI));
			return instr_len+1;
			break;
		default :
			assert(0);
	}
}

#include "exec/template-end.h"
