#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "eflags.h"
#define length (DATA_BYTE*8-1)

make_helper(concat(CMP_i2ra_,SUFFIX)) {
   DATA_TYPE imm =instr_fetch(eip + 1,DATA_BYTE);
   DATA_TYPE MSB_1 = MSB(imm);
   DATA_TYPE MSB_2 = MSB(REG(0x0));
   DATA_TYPE MSB_3 = MSB(REG(0x0)-imm);
   cmp_eflags_change(imm,REG(0x0),MSB_1,MSB_2,MSB_3);
   print_asm("CMP" " $0x%x,%%%s",imm,REG_NAME(0x0));
   return DATA_BYTE + 1;
}


make_helper(concat(CMP_i2rm_,SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1,1);
	if(m.mod == 3) {
	imm =instr_fetch(eip + 1 + 1,DATA_BYTE);
        DATA_TYPE MSB_1 = MSB(imm);
        DATA_TYPE MSB_2 = MSB(REG(m.R_M));
        DATA_TYPE MSB_3 = MSB(REG(m.R_M) - imm);
        cmp_eflags_change(imm,REG(m.R_M),MSB_1,MSB_2,MSB_3);
   print_asm("cmp" " $0x%x,%%%s",imm,REG_NAME(m.R_M));
   return 1 + 1 + DATA_BYTE;
	}
 else {
        swaddr_t addr;
        DATA_TYPE len = read_ModR_M(eip + 1,&addr);
	imm = instr_fetch(eip + 1 + len,DATA_BYTE);
        DATA_TYPE MSB_1 = MSB(imm);
        DATA_TYPE MSB_2 = MSB(MEM_R(addr));
        DATA_TYPE MSB_3 = MSB(MEM_R(addr)-imm);
        cmp_eflags_change(imm,MEM_R(addr),MSB_1,MSB_2,MSB_3);
        print_asm("cmp" " $0x%x,%s",imm,ModR_M_asm);
        return len + 1 + DATA_BYTE;
     }	
}

make_helper(concat(CMP_ib2rm_,SUFFIX)) {
	ModR_M m;
	short imm;
	m.val = instr_fetch(eip + 1,1);
	if(m.mod == 3) {
	imm =instr_fetch(eip + 1 + 1,1);
	DATA_TYPE_S tmp = imm;
        DATA_TYPE MSB_1 = MSB(tmp);
        DATA_TYPE MSB_2 = MSB(REG(m.R_M));
        DATA_TYPE MSB_3 = MSB(REG(m.R_M)-tmp);
         cmp_eflags_change(tmp,REG(m.R_M),MSB_1,MSB_2,MSB_3);
   print_asm("cmpib" " $0x%x,%%%s",imm,REG_NAME(m.R_M));
   return 1 + 1 + 1;
	}
 else {
        swaddr_t addr;
        DATA_TYPE len = read_ModR_M(eip + 1,&addr);
	    imm = instr_fetch(eip + 1 + len,1);
		DATA_TYPE_S tmp = imm;
        DATA_TYPE MSB_1 = MSB(tmp);
        DATA_TYPE MSB_2 = MSB(MEM_R(addr));
        DATA_TYPE MSB_3 = MSB(MEM_R(addr)-tmp);
        cmp_eflags_change(tmp,MEM_R(addr),MSB_1,MSB_2,MSB_3);
        print_asm("cmpib" " $0x%x,%s",imm,ModR_M_asm);
        return len + 1 + 1;
     }	 
}


make_helper(concat(CMP_r2rm_,SUFFIX)) {
        ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
        if(m.mod == 3) {
           DATA_TYPE MSB_1 = MSB(REG(m.reg));
           DATA_TYPE MSB_2 = MSB(REG(m.R_M));
           DATA_TYPE MSB_3 = MSB(REG(m.R_M)-REG(m.reg));
	   cmp_eflags_change(REG(m.reg),REG(m.R_M),MSB_1,MSB_2,MSB_3);
           print_asm("CMP" " %%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));
           return 2;       
	}
	else {
	   swaddr_t addr;
	   DATA_TYPE len = read_ModR_M(eip + 1, &addr);  
           //REG(m.reg) = MEM_R(addr);
           DATA_TYPE MSB_1 = MSB(REG(m.reg));
           DATA_TYPE MSB_2 = MSB(MEM_R(addr));
           DATA_TYPE MSB_3 = MSB(MEM_R(addr)-REG(m.reg));
	cmp_eflags_change(REG(m.reg),MEM_R(addr),MSB_1,MSB_2,MSB_3);
        print_asm("CMP" " %%%s, %s",REG_NAME(m.reg),ModR_M_asm);
        return len + 1;     
        }
}     


make_helper(concat(CMP_rm2r_,SUFFIX)) {
        ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
        if(m.mod == 3) {
           DATA_TYPE MSB_1 = MSB(REG(m.R_M));
           DATA_TYPE MSB_2 = MSB(REG(m.reg));
           DATA_TYPE MSB_3 = MSB(REG(m.reg)-REG(m.R_M));
	   cmp_eflags_change(REG(m.R_M),REG(m.reg),MSB_1,MSB_2,MSB_3);
           print_asm("CMP" " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
           return 2;       
	}
	else {
	   swaddr_t addr;
	   DATA_TYPE len = read_ModR_M(eip + 1, &addr);  
           //REG(m.reg) = MEM_R(addr);
           DATA_TYPE MSB_1 = MSB(MEM_R(addr));
           DATA_TYPE MSB_2 = MSB(REG(m.reg));
           DATA_TYPE MSB_3 = MSB(REG(m.reg)-MEM_R(addr));
	cmp_eflags_change(REG(m.reg),MEM_R(addr),MSB_1,MSB_2,MSB_3);
        print_asm("CMP" " %s,%%%s",ModR_M_asm,REG_NAME(m.reg));
        return len + 1;     
        }
}     

#include "exec/template-end.h"
