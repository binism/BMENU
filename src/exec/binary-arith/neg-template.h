#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#define length (DATA_BYTE*8-1)


make_helper(concat(neg_rm_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
	if(m.mod == 3) {
        DATA_TYPE temp = - REG(m.R_M);
	cpu.EFLAGS.SF=temp>>length;
	DATA_TYPE i=0,sum=0;
     for(; i<8; i++)
     { DATA_TYPE tmp = temp & 0x1;
	   sum = sum + tmp;
	   temp=temp>>1;
     }		
	if(sum%2==0)
		cpu.EFLAGS.PF=1;
	else
		cpu.EFLAGS.PF=0;
	if ( - REG(m.R_M)  == 0)
		cpu.EFLAGS.ZF=1;
	else 
		cpu.EFLAGS.ZF=0;
    DATA_TYPE tmp=0x1;
    tmp = tmp<<length;
    if(REG(m.R_M)==tmp)
		cpu.EFLAGS.OF=1;
	else 
		cpu.EFLAGS.OF=0;
	if(REG(m.R_M)==0)
		cpu.EFLAGS.CF=0;
	else
		cpu.EFLAGS.CF=1;
   REG(m.R_M)= - REG(m.R_M);
   print_asm("neg" " %%%s",REG_NAME(m.R_M));
   return 1 + 1 ;
	}
 else {
        swaddr_t addr;
        DATA_TYPE len = read_ModR_M(eip + 1,&addr);
        DATA_TYPE temp= - MEM_R(addr) ;
	cpu.EFLAGS.SF=temp>>length;
	DATA_TYPE i=0,sum=0;
        for(; i<8; i++)
         { DATA_TYPE tmp = temp & 0x1;
	   sum = sum + tmp;
	   temp=temp>>1;
	 }		
	if(sum%2==0)
		cpu.EFLAGS.PF=1;
	else
		cpu.EFLAGS.PF=0;
	if (- MEM_R(addr)  == 0)
		cpu.EFLAGS.ZF=1;
	else 
		cpu.EFLAGS.ZF=0;
       DATA_TYPE tmp=0x1;
       tmp = tmp<<length;
       if(REG(m.R_M)==tmp)
		cpu.EFLAGS.OF=1;
	else 
		cpu.EFLAGS.OF=0;
	if(MEM_R(addr)==0)
		cpu.EFLAGS.CF=0;
	else
		cpu.EFLAGS.CF=1;
        MEM_W(addr, - MEM_R(addr) );
        print_asm("neg" " %s",ModR_M_asm);
        return len + 1 ;
     }	
}



#include "exec/template-end.h"
