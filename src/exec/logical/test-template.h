#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "eflags.h"
#define length (DATA_BYTE*8-1)
/*make_helper(test_i2ra_b) {
DATA_TYPE imm = instr_fetch(eip + 1,DATA_BYTE);
if((imm&REG(0x0))==0)
 { cpu.OF=0;                                                            
	 cpu.CF=0;                                                              
      cpu.SF=~cpu.SF;                                                   
      cpu.ZF=~cpu.ZF;                                                      
 }                                                             
      print_asm("test" str(SUFFIX) " $0x%x,%%%s", imm, REG_NAME(0x000));
     return DATA_BYTE + 1;
}*/

make_helper(concat(test_i2ra_,SUFFIX)) {
   DATA_TYPE imm = instr_fetch(eip + 1,DATA_BYTE);
   DATA_TYPE MSB = MSB(imm & REG(0x0));
   and_eflags_change(imm,REG(0x0),MSB);
   print_asm("test" str(SUFFIX) " $0x%x,%%%s", imm, REG_NAME(0x000));
   return DATA_BYTE + 1;
}
make_helper(concat(test_i2rm_,SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1,1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1,DATA_BYTE);
        DATA_TYPE MSB = MSB(imm & REG(m.R_M));
        and_eflags_change(imm,REG(m.R_M),MSB); 
		print_asm("test" str(SUFFIX) " $0x%x,%%%s",imm, REG_NAME(m.R_M));
		return 1 + DATA_BYTE + 1;
	}
	else {
	       swaddr_t addr;
		   int len = read_ModR_M(eip + 1,&addr);
		   imm = instr_fetch(eip + 1 + len,DATA_BYTE);
          DATA_TYPE MSB = MSB(imm & MEM_R(addr));
          and_eflags_change(imm,MEM_R(addr),MSB);
		   print_asm("test" str(SUFFIX) " $0x%x,%s", imm, ModR_M_asm);
		   return len + DATA_BYTE + 1;
		   }
}
make_helper(concat(test_r2rm_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
           DATA_TYPE MSB = MSB(REG(m.R_M) & REG(m.reg));
	   and_eflags_change(REG(m.reg),REG(m.R_M),MSB);
		print_asm("test" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.reg),REG_NAME(m.R_M));
		return 2;
	}
	else {
	      swaddr_t addr;
              int len = read_ModR_M(eip + 1, &addr);
                   DATA_TYPE MSB = MSB(MEM_R(addr)&REG(m.reg));
	and_eflags_change(REG(m.reg),MEM_R(addr),MSB);     
	      print_asm("test" str(SUFFIX) " %%%s.%s", REG_NAME(m.reg), ModR_M_asm);
              return len + 1;	 
	   }
}
#include "exec/template-end.h"
