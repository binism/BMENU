#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "eflags.h"
#define length (DATA_BYTE*8-1)

make_helper(concat(sbb_i2ra_,SUFFIX)) {
   DATA_TYPE imm =instr_fetch(eip + 1,DATA_BYTE);
   DATA_TYPE tmp = REG(0x0);
   DATA_TYPE MSB_1 = MSB(imm+cpu.EFLAGS.CF);
   DATA_TYPE MSB_2 = MSB(REG(0x0));
   cpu.eax = REG(0x0) - (imm+cpu.EFLAGS.CF);
   DATA_TYPE MSB_3 = MSB(cpu.eax);
   sbb_eflags_change(imm,tmp,MSB_1,MSB_2,MSB_3);
   print_asm("sbb" " $0x%x,%%%s",imm,REG_NAME(0x0));
   return DATA_BYTE + 1;
}




make_helper(concat(sbb_i2rm_,SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1,1);
 	if(m.mod == 3) {
	imm =instr_fetch(eip + 1 + 1,DATA_BYTE);
        DATA_TYPE tmp = REG(m.R_M);
        DATA_TYPE MSB_1 = MSB(imm+cpu.EFLAGS.CF);
        DATA_TYPE MSB_2 = MSB(REG(m.R_M));
        REG(m.R_M)=REG(m.R_M) - (imm + cpu.EFLAGS.CF);
        DATA_TYPE MSB_3 = MSB(REG(m.R_M));
        sbb_eflags_change(imm,tmp,MSB_1,MSB_2,MSB_3);
        print_asm("sbb" " $0x%x,%%%s",imm,REG_NAME(m.R_M));
        return 1 + 1 + DATA_BYTE;
	}
        else {
          swaddr_t addr;
          DATA_TYPE len = read_ModR_M(eip + 1,&addr);
	  imm = instr_fetch(eip + 1 + len,DATA_BYTE);
          DATA_TYPE tmp = MEM_R(addr); 
          DATA_TYPE MSB_1 = MSB(imm+cpu.EFLAGS.CF);
          DATA_TYPE MSB_2 = MSB(MEM_R(addr));
          MEM_W(addr,MEM_R(addr) - (imm + cpu.EFLAGS.CF));
          DATA_TYPE MSB_3 = MSB(tmp - (imm + cpu.EFLAGS.CF));
          sbb_eflags_change(imm,tmp,MSB_1,MSB_2,MSB_3);
          print_asm("sbb" " $0x%x,%s",imm,ModR_M_asm);
          return len + 1 + DATA_BYTE;
      }	
}

make_helper(concat(sbb_ib2rm_,SUFFIX)) {
	ModR_M m;
	short imm;
	m.val = instr_fetch(eip + 1,1);
 	if(m.mod == 3) {
	imm =instr_fetch(eip + 1 + 1,1);
        DATA_TYPE tmp = REG(m.R_M); 
        DATA_TYPE MSB_1 = MSB(imm+cpu.EFLAGS.CF);
        DATA_TYPE MSB_2 = MSB(REG(m.R_M));
        REG(m.R_M)=REG(m.R_M) - (imm + cpu.EFLAGS.CF);
        DATA_TYPE MSB_3 = MSB(REG(m.R_M));
        sbb_eflags_change(imm,tmp,MSB_1,MSB_2,MSB_3);
        print_asm("sbb" " $0x%x,%%%s",imm,REG_NAME(m.R_M));
        return 1 + 1 + 1;
	}
        else {
          swaddr_t addr;
          DATA_TYPE len = read_ModR_M(eip + 1,&addr);
	  imm = instr_fetch(eip + 1 + len,1);
          DATA_TYPE tmp = MEM_R(addr);
          DATA_TYPE MSB_1 = MSB(imm+cpu.EFLAGS.CF);
          DATA_TYPE MSB_2 = MSB(MEM_R(addr));
          MEM_W(addr,MEM_R(addr) - (imm + cpu.EFLAGS.CF));
          DATA_TYPE MSB_3 = MSB(tmp -( imm + cpu.EFLAGS.CF));
          sbb_eflags_change(imm,tmp,MSB_1,MSB_2,MSB_3);
          print_asm("sbb" " $0x%x,%s",imm,ModR_M_asm);
          return len + 1 + 1;
      }	
}

make_helper(concat(sbb_r2rm_,SUFFIX)) {
        ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
        if(m.mod == 3) {
           DATA_TYPE tmp = REG(m.R_M);
           DATA_TYPE MSB_1 = MSB(REG(m.reg)+cpu.EFLAGS.CF);
           DATA_TYPE MSB_2 = MSB(REG(m.R_M));
           REG(m.R_M) = REG(m.R_M) - (REG(m.reg)+cpu.EFLAGS.CF);
           DATA_TYPE MSB_3 = MSB(REG(m.R_M));
           sbb_eflags_change(REG(m.reg),tmp,MSB_1,MSB_2,MSB_3);
           print_asm("sbb" " %%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));
           return 2;       
	}
	else {
	   swaddr_t addr;
	   DATA_TYPE len = read_ModR_M(eip + 1, &addr);  
           DATA_TYPE tmp = MEM_R(addr);
           DATA_TYPE MSB_1 = MSB(REG(m.reg)+cpu.EFLAGS.CF);
           DATA_TYPE MSB_2 = MSB(MEM_R(addr));
           MEM_W(addr,MEM_R(addr) - (REG(m.reg)+cpu.EFLAGS.CF));//REG(m.reg) = MEM_R(addr);
           DATA_TYPE MSB_3= MSB(tmp - (REG(m.reg) + cpu.EFLAGS.CF));
           sbb_eflags_change(REG(m.reg),tmp,MSB_1,MSB_2,MSB_3);
        print_asm("sbb" " %%%s, %s",REG_NAME(m.reg),ModR_M_asm);
        return len + 1;     
        }
}     


make_helper(concat(sbb_rm2r_,SUFFIX)) {
        ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
        if(m.mod == 3) {
           DATA_TYPE tmp = REG(m.reg);
           DATA_TYPE MSB_1 = MSB(REG(m.R_M)+cpu.EFLAGS.CF);
           DATA_TYPE MSB_2 = MSB(REG(m.reg));
           REG(m.reg) = REG(m.reg) - (REG(m.R_M)+cpu.EFLAGS.CF);
           DATA_TYPE MSB_3 = MSB(REG(m.reg));
           sbb_eflags_change(REG(m.R_M),tmp,MSB_1,MSB_2,MSB_3);
           print_asm("sbb" " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
           return 2;       
	}
	else {
	   swaddr_t addr;
	   DATA_TYPE len = read_ModR_M(eip + 1, &addr);  
           DATA_TYPE tmp = REG(m.reg);
           DATA_TYPE MSB_1 = MSB(MEM_R(addr)+cpu.EFLAGS.CF);
           DATA_TYPE MSB_2 = MSB(REG(m.reg));
           REG(m.reg)=REG(m.reg)-(MEM_R(addr)+cpu.EFLAGS.CF);
           DATA_TYPE MSB_3 = MSB(REG(m.reg));
           sbb_eflags_change(MEM_R(addr),tmp,MSB_1,MSB_2,MSB_3);
        print_asm("sbb" " %s,%%%s",ModR_M_asm,REG_NAME(m.reg));
        return len + 1;     
        }
}     



#include "exec/template-end.h"
