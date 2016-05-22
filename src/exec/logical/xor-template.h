#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "eflags.h"
#define length (DATA_BYTE*8-1)

make_helper(concat(xor_i2ra_,SUFFIX)) {
   DATA_TYPE imm =instr_fetch(eip + 1,DATA_BYTE);
   DATA_TYPE MSB = MSB(imm ^ REG(0x0));
   xor_eflags_change(imm,REG(0x0),MSB);
    cpu.eax = REG(0x0) ^ imm;
   print_asm("xor" " $0x%x,%%%s",imm,REG_NAME(0x0));
   return DATA_BYTE + 1;
}




make_helper(concat(xor_i2rm_,SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1,1);
 	if(m.mod == 3) {
	imm =instr_fetch(eip + 1 + 1,DATA_BYTE);
        DATA_TYPE MSB = MSB(imm ^ REG(m.R_M));
        xor_eflags_change(imm,REG(m.R_M),MSB);
        REG(m.R_M)=REG(m.R_M) ^ imm;
        print_asm("xor" " $0x%x,%%%s",imm,REG_NAME(m.R_M));
        return 1 + 1 + DATA_BYTE;
	}
        else {
          swaddr_t addr;
          DATA_TYPE len = read_ModR_M(eip + 1,&addr);
	  imm = instr_fetch(eip + 1 + len,DATA_BYTE);
          DATA_TYPE MSB = MSB(imm ^ MEM_R(addr));
          xor_eflags_change(imm,MEM_R(addr),MSB);
          MEM_W(addr,MEM_R(addr) ^ imm);
          print_asm("xor" " $0x%x,%s",imm,ModR_M_asm);
          return len + 1 + DATA_BYTE;
      }	
}

make_helper(concat(xor_ib2rm_,SUFFIX)) {
	ModR_M m;
	short imm;
	m.val = instr_fetch(eip + 1,1);
 	if(m.mod == 3) {
	imm =instr_fetch(eip + 1 + 1,1);
        DATA_TYPE MSB = MSB(imm ^ REG(m.R_M));
        xor_eflags_change(imm,REG(m.R_M),MSB);
        REG(m.R_M)=REG(m.R_M) ^ imm;
        print_asm("xor" " $0x%x,%%%s",imm,REG_NAME(m.R_M));
        return 1 + 1 + 1;
	}
        else {
          swaddr_t addr;
          DATA_TYPE len = read_ModR_M(eip + 1,&addr);
	  imm = instr_fetch(eip + 1 + len,1);
          DATA_TYPE MSB = MSB(MEM_R(addr) ^ imm);
          xor_eflags_change(imm,MEM_R(addr),MSB);
          MEM_W(addr,MEM_R(addr) ^ imm);
          print_asm("xor" " $0x%x,%s",imm,ModR_M_asm);
          return len + 1 + 1;
      }	
}


make_helper(concat(xor_r2rm_,SUFFIX)) {
        ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
        if(m.mod == 3) {
          DATA_TYPE MSB = MSB(REG(m.R_M) ^ REG(m.reg));
	   xor_eflags_change(REG(m.reg),REG(m.R_M),MSB);
           REG(m.R_M) = REG(m.R_M) ^ REG(m.reg);
           print_asm("xor" " %%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));
           return 2;       
	}
	else {
	   swaddr_t addr;
	   DATA_TYPE len = read_ModR_M(eip + 1, &addr);  
           //REG(m.reg) = MEM_R(addr);
                   DATA_TYPE MSB = MSB(MEM_R(addr) ^ REG(m.reg));
	xor_eflags_change(REG(m.reg),MEM_R(addr),MSB);       
        MEM_W(addr,MEM_R(addr) ^ REG(m.reg));
        print_asm("xor" " %%%s, %s",REG_NAME(m.reg),ModR_M_asm);
        return len + 1;     
        }
}     


make_helper(concat(xor_rm2r_,SUFFIX)) {
        ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
        if(m.mod == 3) {
            DATA_TYPE MSB = MSB(REG(m.reg) ^ REG(m.R_M));
	   xor_eflags_change(REG(m.R_M),REG(m.reg),MSB);
           REG(m.reg) = REG(m.reg) ^ REG(m.R_M);
           print_asm("xor" " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
           return 2;       
	}
	else {
	   swaddr_t addr;
	   DATA_TYPE len = read_ModR_M(eip + 1, &addr);  
           //REG(m.reg) = MEM_R(addr);
                   DATA_TYPE MSB = MSB(REG(m.reg) ^ MEM_R(addr));
	xor_eflags_change(MEM_R(addr),REG(m.reg),MSB);
	MEM_W(addr,REG(m.reg)^MEM_R(addr));
        print_asm("xor" " %s,%%%s",ModR_M_asm,REG_NAME(m.reg));
        return len + 1;     
        }
}     



#include "exec/template-end.h"
