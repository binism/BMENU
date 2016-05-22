#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#define length (DATA_BYTE*8-1)




make_helper(concat(idiv_rm2ra_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
    if(m.mod == 3) {
	DATA_TYPE_S temp1 = REG(0x0);
	DATA_TYPE_S temp2 = REG(m.R_M);
	DATA_TYPE_S Quo= temp1 / temp2;
        DATA_TYPE_S Rem= temp1 % temp2;
        int16_t tmp = Quo;
	switch (DATA_BYTE)
	{ case 1: REG(0x0)=(tmp<<8)+Rem;  break;
	  case 2: REG(0x0)=Quo&0xff; REG(0x2)=Rem&0xff;  break;
	  case 4: REG(0x0)=Quo&0xffff; REG(0x2)=Rem&0xffff;  break;
	  default : assert(0);
	}
	  print_asm("idiv" " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(0x0));
	 return 1 + 1;
    }
    else {
	swaddr_t addr;
        DATA_TYPE_S len = read_ModR_M(eip + 1, &addr);
        DATA_TYPE_S temp1 = REG(0x0);
	DATA_TYPE_S temp2 = MEM_R(addr);
	DATA_TYPE_S Quo= temp1 / temp2;
        DATA_TYPE_S Rem= temp1 % temp2;
        int16_t tmp = Quo;
	switch (DATA_BYTE)
	{ case 1: REG(0x0)=(tmp<<8)+Rem;  break;
	  case 2: REG(0x0)=Quo&0xff; REG(0x2)=Rem&0xff;  break;
	  case 4: REG(0x0)=Quo&0xffff; REG(0x2)=Rem&0xffff;  break;
	  default : assert(0);
	}	
	  print_asm("idiv" " %s, %%%s",ModR_M_asm,REG_NAME(0x0));
	  return len + 1;
	}
}












#include "exec/template-end.h"
