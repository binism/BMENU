#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "eflags.h"
#define length (DATA_BYTE*8-1)

make_helper(concat(add_i2ra_,SUFFIX)) { 
   DATA_TYPE imm =instr_fetch(eip + 1,DATA_BYTE);
    DATA_TYPE tmp = REG(0x0);
   DATA_TYPE MSB_1 = MSB(imm);
   DATA_TYPE MSB_2 = MSB(REG(0x0));
    cpu.eax = REG(0x0) + imm;
   DATA_TYPE MSB_3 = MSB(cpu.eax);
   add_eflags_change(imm,tmp, MSB_1, MSB_2, MSB_3);
   long long sum = tmp + imm;
   if(((sum>>(length+1)&0x1)==1))
	cpu.EFLAGS.CF=1;
   else
	cpu.EFLAGS.CF=0;
   print_asm("add" " $0x%x,%%%s",imm,REG_NAME(0x0));
   return DATA_BYTE + 1;
}


make_helper(concat(add_i2rm_,SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1,1);
 	if(m.mod == 3) {  
	imm =instr_fetch(eip + 1 + 1,DATA_BYTE);
        DATA_TYPE tmp = REG(m.R_M);
        DATA_TYPE MSB_1 = MSB(imm);
        DATA_TYPE MSB_2 = MSB(REG(m.R_M));   
        REG(m.R_M)=REG(m.R_M) + imm;
        DATA_TYPE MSB_3 = MSB(REG(m.R_M));
        add_eflags_change(imm,tmp,MSB_1,MSB_2,MSB_3);
        long long sum = tmp + imm;
        if(((sum>>(length+1)&0x1)==1))
		  cpu.EFLAGS.CF=1;
	    else
		  cpu.EFLAGS.CF=0;
        print_asm("add" " $0x%x,%%%s",imm,REG_NAME(m.R_M));
        return 1 + 1 + DATA_BYTE;
	}
        else {
          swaddr_t addr;
          DATA_TYPE len = read_ModR_M(eip + 1,&addr);
	      imm = instr_fetch(eip + 1 + len,DATA_BYTE);
          DATA_TYPE tmp = MEM_R(addr);
          DATA_TYPE MSB_1 = MSB(imm);
          DATA_TYPE MSB_2 = MSB(MEM_R(addr));
          MEM_W(addr,MEM_R(addr) + imm);
          DATA_TYPE MSB_3 = MSB(tmp + imm );
          add_eflags_change(imm,tmp,MSB_1,MSB_2,MSB_3);
          long long sum = tmp + imm;
          if(((sum>>(length+1)&0x1)==1))
	         cpu.EFLAGS.CF=1;
          else
	         cpu.EFLAGS.CF=0;
          print_asm("add" " $0x%x,%s",imm,ModR_M_asm);
          return len + 1 + DATA_BYTE;
       }	
} 

make_helper(concat(add_ib2rm_,SUFFIX)) {
	ModR_M m;
	short imm;
	m.val = instr_fetch(eip + 1,1);
 	if(m.mod == 3) {
	imm =instr_fetch(eip + 1 + 1,1);
        DATA_TYPE tmp = REG(m.R_M);
        DATA_TYPE MSB_1 = MSB(imm);
        DATA_TYPE MSB_2 = MSB(REG(m.R_M));
        REG(m.R_M)= REG(m.R_M)+ imm;
        DATA_TYPE MSB_3 = MSB(REG(m.R_M));
        add_eflags_change(imm,tmp,MSB_1,MSB_2,MSB_3);
        long long sum = tmp + imm;
        if(((sum>>(length+1)&0x1)==1))
	       cpu.EFLAGS.CF=1;
        else
	       cpu.EFLAGS.CF=0;        
        print_asm("add" " $0x%x,%%%s",imm,REG_NAME(m.R_M));
        return 1 + 1 + 1;
	}
        else { 
          swaddr_t addr;
          DATA_TYPE len = read_ModR_M(eip + 1,&addr);
	  imm = instr_fetch(eip + 1 + len,1);
          DATA_TYPE tmp = MEM_R(addr);
          DATA_TYPE MSB_1 = MSB(imm);
          DATA_TYPE MSB_2 = MSB(MEM_R(addr));
          MEM_W(addr,MEM_R(addr) + imm);
          DATA_TYPE MSB_3 = MSB(tmp + imm);
          add_eflags_change(imm,tmp,MSB_1,MSB_2,MSB_3);
          long long sum = tmp + imm;
          if(((sum>>(length+1)&0x1)==1))
	        cpu.EFLAGS.CF=1;
          else
	        cpu.EFLAGS.CF=0;
          print_asm("add" " $0x%x,%s",imm,ModR_M_asm);
          return len + 1 + 1;
      }	
}


make_helper(concat(add_r2rm_,SUFFIX)) {
        ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
        if(m.mod == 3) {
           DATA_TYPE tmp = REG(m.R_M);
           DATA_TYPE MSB_1 = MSB(REG(m.reg));
           DATA_TYPE MSB_2 = MSB(REG(m.R_M));
           REG(m.R_M) = REG(m.R_M) + REG(m.reg);
           DATA_TYPE MSB_3 = MSB(REG(m.R_M));
           add_eflags_change(REG(m.reg),tmp,MSB_1,MSB_2,MSB_3);
           long long sum = tmp + REG(m.reg);
           if(((sum>>(length+1)&0x1)==1))
	          cpu.EFLAGS.CF=1;
           else
	          cpu.EFLAGS.CF=0;
           print_asm("add" " %%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));
           return 2;       
	}
	else {
	       swaddr_t addr;
	       DATA_TYPE len = read_ModR_M(eip + 1, &addr); 
           DATA_TYPE tmp = MEM_R(addr);   
           DATA_TYPE MSB_1 = MSB(REG(m.reg));
           DATA_TYPE MSB_2 = MSB(MEM_R(addr));
          MEM_W(addr,MEM_R(addr) + REG(m.reg));
          DATA_TYPE MSB_3= MSB(tmp + REG(m.reg));
           add_eflags_change(REG(m.reg),tmp,MSB_1,MSB_2,MSB_3);
           long long sum = tmp + REG(m.reg);
           if(((sum>>(length+1)&0x1)==1))
	    cpu.EFLAGS.CF=1;
           else
	    cpu.EFLAGS.CF=0;
          print_asm("add" " %%%s, %s",REG_NAME(m.reg),ModR_M_asm);
          return len + 1;     
        }
}     


make_helper(concat(add_rm2r_,SUFFIX)) {
        ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
        if(m.mod == 3) {
           DATA_TYPE tmp = REG(m.reg);
           DATA_TYPE MSB_1 = MSB(REG(m.R_M));
           DATA_TYPE MSB_2 = MSB(REG(m.reg));
           REG(m.reg) = REG(m.reg) + REG(m.R_M);
           DATA_TYPE MSB_3 = MSB(REG(m.reg));
           add_eflags_change(REG(m.R_M),tmp,MSB_1,MSB_2,MSB_3);
           long long sum = tmp + REG(m.R_M);
           if(((sum>>(length+1)&0x1)==1))
	          cpu.EFLAGS.CF=1;
           else
	          cpu.EFLAGS.CF=0;
           print_asm("add" " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
           return 2;       
	}
	else {
	       swaddr_t addr;
	       DATA_TYPE len = read_ModR_M(eip + 1, &addr); 
           DATA_TYPE tmp = REG(m.reg);  
           DATA_TYPE MSB_1 = MSB(REG(m.reg));
           DATA_TYPE MSB_2 = MSB(MEM_R(addr));
	       REG(m.reg)=MEM_R(addr) + REG(m.reg);
           DATA_TYPE MSB_3= MSB(MEM_R(addr) + REG(m.reg));
           add_eflags_change(REG(m.reg),tmp,MSB_1,MSB_2,MSB_3);
           long long sum = MEM_R(addr) + tmp;
           if(((sum>>(length+1)&0x1)==1))
	          cpu.EFLAGS.CF=1;
           else
	          cpu.EFLAGS.CF=0;
           print_asm("add" " %s,%%%s",ModR_M_asm,REG_NAME(m.reg));
           return len + 1;     
        }
}     




#include "exec/template-end.h"

