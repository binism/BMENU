#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#define length (DATA_BYTE*8-1)

make_helper(concat(imul_rm2ra_,SUFFIX)) {
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
	  print_asm("imul" " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(0x0));
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
	  print_asm("imul" " %s, %%%s",ModR_M_asm,REG_NAME(0x0));
	  return len + 1;
 	}
} 


make_helper(concat(imul_rm2r_,SUFFIX)) {
    ModR_M m;
   if(DATA_BYTE==1)
       m.val = instr_fetch(eip + 1,1);
   else 
       m.val = instr_fetch(eip + 1 + 1,1);
   if(m.mod==3) {
     DATA_TYPE temp1 = REG(m.reg);
     DATA_TYPE temp2 = REG(m.R_M);
     long long prod = temp1 * temp2;
     switch (DATA_BYTE)
	{
	  case 2: REG(m.reg)=prod&0xff;  break;
	  case 4: REG(m.reg)=prod;  break;
	  default : assert(0);
	}
     if (prod>>(length+1)==0)
      {   cpu.EFLAGS.CF=0;
	  cpu.EFLAGS.OF=0;
      }
       print_asm("imul" " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
      if(DATA_BYTE==1)
         return 1 + 1;
      else
         return 1 + 1 + 1;
     }
    else {
	swaddr_t addr;
        int len;
        if(DATA_BYTE==1)
           len = read_ModR_M(eip + 1, &addr);
        else
           len = read_ModR_M(eip + 1 + 1, &addr);
        DATA_TYPE temp1 = REG(m.reg);
	DATA_TYPE temp2 = MEM_R(addr);
	long long prod = temp1 * temp2;
	switch (DATA_BYTE)
		{ 
		  case 2: REG(m.reg)=prod&0xff; break;
		  case 4: REG(m.reg)=prod; break;
		  default : assert(0);
		}
	 if (prod>>(length+1)==0)
		 {   cpu.EFLAGS.CF=0;
		     cpu.EFLAGS.OF=0;
	     }
	  print_asm("imul" " %s, %%%s",ModR_M_asm,REG_NAME(m.reg));
          if(DATA_BYTE==1)
	      return len + 1;
          else 
              return len + 1 + 1;
	}
}     


make_helper(concat(imul_ib2rm2r_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
	short imm = instr_fetch(eip + 1 + 1,1);
	if(m.mod==3) {
		long long prod = REG(m.R_M) * imm;
		switch (DATA_BYTE)
		{ case 2: REG(m.reg)=prod&0xff; break;
		  case 4: REG(m.reg)=prod; break;
		  default : assert(0);
		}
	 if (prod>>(length+1)==0)
		       {   cpu.EFLAGS.CF=0;
					  cpu.EFLAGS.OF=0;
					        }
    print_asm("imul" " $0x%x,%%%s,%%%s",imm,REG_NAME(m.R_M),REG_NAME(m.reg));
   return 1 + 1 + 1;
   }
   else {
	   swaddr_t addr;
	   DATA_TYPE len = read_ModR_M(eip + 1,&addr);
	   long long prod = MEM_R(addr) * imm;
	   switch (DATA_BYTE)
	   { case 2: REG(m.reg) = prod&0xff; break;
		 case 4: REG(m.reg) = prod; break;
		 default : assert(0);
	   }
	   if (prod>>(length+1)==0)
		{   cpu.EFLAGS.CF=0;
		    cpu.EFLAGS.OF=0;
		}
	   print_asm("imul" " $0x%x,%s, %%%s",imm,ModR_M_asm,REG_NAME(m.reg));
	   return len + 1 + 1;
	}
}


make_helper(concat(imul_i2rm2r_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
	DATA_TYPE imm = instr_fetch(eip + 1 + 1,DATA_BYTE);
	if(m.mod==3) {
		long long prod = REG(m.R_M) * imm;
		switch (DATA_BYTE)
		{ case 2: REG(m.reg)=prod&0xff; break;
		  case 4: REG(m.reg)=prod; break;
		  default : assert(0);
		}
	 if (prod>>(length+1)==0)
		       {   cpu.EFLAGS.CF=0;
					  cpu.EFLAGS.OF=0;
					        }
    print_asm("imul" " $0x%x,%%%s,%%%s",imm,REG_NAME(m.R_M),REG_NAME(m.reg));
   return 1 + 1 + DATA_BYTE;
   }
   else {
	   swaddr_t addr;
	   DATA_TYPE len = read_ModR_M(eip + 1,&addr);
	   long long prod = MEM_R(addr) * imm;
	   switch (DATA_BYTE)
	   { case 2: REG(m.reg) = prod&0xff; break;
		 case 4: REG(m.reg) = prod; break;
		 default : assert(0);
	   }
	   if (prod>>(length+1)==0)
		{   cpu.EFLAGS.CF=0;
		    cpu.EFLAGS.OF=0;
		}
	   print_asm("imul" " $0x%x,%s, %%%s",imm,ModR_M_asm,REG_NAME(m.reg));
	   return len + 1 + DATA_BYTE;
	}
}



#include "exec/template-end.h"
