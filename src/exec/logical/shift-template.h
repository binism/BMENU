#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#define length (DATA_BYTE*8-1)


make_helper(concat(sal_ib2rm_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
	uint8_t imm = instr_fetch(eip + 1 + 1,1);
	if (m.mod == 3) {
		DATA_TYPE temp = REG(m.R_M);
		int p=0;
		for (; p<imm;p++)
		{   cpu.EFLAGS.CF = temp >> length;
            temp = temp * 2;
		}
		switch (DATA_BYTE)
		{ case 1: REG(m.R_M) = temp & 0xff; break;
		  case 2: REG(m.R_M) = temp & 0xffff; break;
		  case 4: REG(m.R_M) = temp & 0xffffffff; break;
		  default : assert(0);
		}
		cpu.EFLAGS.SF = temp >> length;
		int i=0,sum=0,temp1=temp;
		for (; i<8; i++)
		{ DATA_TYPE tmp = temp1 & 0x1;
		  sum = sum + tmp;
		  temp1 = temp1 >> 1;
		}
		if (sum%2==0)
			cpu.EFLAGS.PF=0;
		else 
			cpu.EFLAGS.PF=1;
		if(temp==0)
			cpu.EFLAGS.ZF=1;
		else 
			cpu.EFLAGS.ZF=0;
                print_asm("sal" " $0x%x,%%%s",imm,REG_NAME(m.R_M));
                return 1 + 1 + 1;
	}
	else {
		swaddr_t addr;
		DATA_TYPE len = read_ModR_M(eip + 1,&addr);
        DATA_TYPE temp = MEM_R(addr);
		int p = 0;
		for(; p<imm;p++)
		{    cpu.EFLAGS.CF = temp >> length ;
                     temp = temp * 2;
		}
		switch (DATA_BYTE)
		{  case 1: MEM_W(addr,temp&0xff); break;
		   case 2: MEM_W(addr,temp&0xffff); break;
		   case 4: MEM_W(addr,temp&0xffffffff); break;
		   default: assert(0);
		}
		cpu.EFLAGS.SF = temp >> length;
		int i=0,sum=0,temp1=temp;
		for (; i<8; i++)
		{ DATA_TYPE tmp = temp1 & 0x1;
		  sum = sum + tmp;
		  temp1 = temp1 >> 1;
		}
		if (sum%2==0)
			cpu.EFLAGS.PF=0;
		else 
			cpu.EFLAGS.PF=1;
		if(temp==0)
			cpu.EFLAGS.ZF=1;
		else 
			cpu.EFLAGS.ZF=0;
		 print_asm("sal" " $0x%x,%s",imm,ModR_M_asm);
		 return 1 + 1 + len;
	}
}


make_helper(concat(sar_ib2rm_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
	uint8_t imm = instr_fetch(eip + 1 + 1,1);
	if (m.mod == 3) {
		DATA_TYPE_S temp = REG(m.R_M);
		int p=0;
		for (; p<imm;p++)
		{   cpu.EFLAGS.CF = temp & 0x1;
            temp = temp / 2;
		}
		switch (DATA_BYTE)
		{ case 1: REG(m.R_M) = temp & 0xff; break;
		  case 2: REG(m.R_M) = temp & 0xffff; break;
		  case 4: REG(m.R_M) = temp & 0xffffffff; break;
		  default : assert(0);
		}
		cpu.EFLAGS.SF = temp >> length;
		int i=0,sum=0,temp1=temp;
		for (; i<8; i++)
		{ DATA_TYPE tmp = temp1 & 0x1;
		  sum = sum + tmp;
		  temp1 = temp1 >> 1;
		}
		if (sum%2==0)
			cpu.EFLAGS.PF=0;
		else 
			cpu.EFLAGS.PF=1;
		if(temp==0)
			cpu.EFLAGS.ZF=1;
		else 
			cpu.EFLAGS.ZF=0;
                print_asm("sar" " $0x%x,%%%s",imm,REG_NAME(m.R_M));
                return 1 + 1 + 1;
	}
	else {
		swaddr_t addr;
		DATA_TYPE len = read_ModR_M(eip + 1,&addr);
        DATA_TYPE_S temp = MEM_R(addr);
		int p = 0;
		for(; p<imm;p++)
		{    cpu.EFLAGS.CF = temp & 0x1;
                     temp = temp / 2;
		}
		switch (DATA_BYTE)
		{  case 1: MEM_W(addr,temp&0xff); break;
		   case 2: MEM_W(addr,temp&0xffff); break;
		   case 4: MEM_W(addr,temp&0xffffffff); break;
		   default: assert(0);
		}
		cpu.EFLAGS.SF = temp >> length;
		int i=0,sum=0,temp1=temp;
		for (; i<8; i++)
		{ DATA_TYPE tmp = temp1 & 0x1;
		  sum = sum + tmp;
		  temp1 = temp1 >> 1;
		}
		if (sum%2==0)
			cpu.EFLAGS.PF=0;
		else 
			cpu.EFLAGS.PF=1;
		if(temp==0)
			cpu.EFLAGS.ZF=1;
		else 
			cpu.EFLAGS.ZF=0;
		 print_asm("sar" " $0x%x,%s",imm,ModR_M_asm);
		 return 1 + 1 + len;
	}
}


make_helper(concat(shr_ib2rm_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
	uint8_t imm = instr_fetch(eip + 1 + 1,1);
	if (m.mod == 3) {
		DATA_TYPE temp = REG(m.R_M);
		int p=0;
		for (; p<imm;p++)
		{   cpu.EFLAGS.CF = temp & 0x1;
            temp = temp / 2;
		}
		switch (DATA_BYTE)
		{ case 1: REG(m.R_M) = temp & 0xff; break;
		  case 2: REG(m.R_M) = temp & 0xffff; break;
		  case 4: REG(m.R_M) = temp & 0xffffffff; break;
		  default : assert(0);
		}
		cpu.EFLAGS.SF = temp >> length;
		int i=0,sum=0,temp1=temp;
		for (; i<8; i++)
		{ DATA_TYPE tmp = temp1 & 0x1;
		  sum = sum + tmp;
		  temp1 = temp1 >> 1;
		}
		if (sum%2==0)
			cpu.EFLAGS.PF=0;
		else 
			cpu.EFLAGS.PF=1;
		if(temp==0)
			cpu.EFLAGS.ZF=1;
		else 
			cpu.EFLAGS.ZF=0;
                print_asm("shr" " $0x%x,%%%s",imm,REG_NAME(m.R_M));
                return 1 + 1 + 1;
	}
	else {
		swaddr_t addr;
		DATA_TYPE len = read_ModR_M(eip + 1,&addr);
        DATA_TYPE temp = MEM_R(addr);
		int p = 0;
		for(; p<imm;p++)
		{    cpu.EFLAGS.CF = temp & 0x1;
                     temp = temp / 2;
		}
		switch (DATA_BYTE)
		{  case 1: MEM_W(addr,temp&0xff); break;
		   case 2: MEM_W(addr,temp&0xffff); break;
		   case 4: MEM_W(addr,temp&0xffffffff); break;
		   default: assert(0);
		}
		cpu.EFLAGS.SF = temp >> length;
		int i=0,sum=0,temp1=temp;
		for (; i<8; i++)
		{ DATA_TYPE tmp = temp1 & 0x1;
		  sum = sum + tmp;
		  temp1 = temp1 >> 1;
		}
		if (sum%2==0)
			cpu.EFLAGS.PF=0;
		else 
			cpu.EFLAGS.PF=1;
		if(temp==0)
			cpu.EFLAGS.ZF=1;
		else 
			cpu.EFLAGS.ZF=0;
		 print_asm("shr" " $0x%x,%s",imm,ModR_M_asm);
		 return 1 + 1 + len;
	}
}

make_helper(concat(sal_12rm_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
	if (m.mod == 3) {
		DATA_TYPE temp = REG(m.R_M);
		cpu.EFLAGS.OF = (temp >> length) != cpu.EFLAGS.CF;
                cpu.EFLAGS.CF = temp >> length;
                temp = temp * 2;
		switch (DATA_BYTE)
		{ case 1: REG(m.R_M) = temp & 0xff; break;
		  case 2: REG(m.R_M) = temp & 0xffff; break;
		  case 4: REG(m.R_M) = temp & 0xffffffff; break;
		  default : assert(0);
		}
		cpu.EFLAGS.SF = temp >> length;
		int i=0,sum=0,temp1=temp;
		for (; i<8; i++)
		{ DATA_TYPE tmp = temp1 & 0x1;
		  sum = sum + tmp;
		  temp1 = temp1 >> 1;
		}
		if (sum%2==0)
			cpu.EFLAGS.PF=0;
		else 
			cpu.EFLAGS.PF=1;
		if(temp==0)
			cpu.EFLAGS.ZF=1;
		else 
			cpu.EFLAGS.ZF=0;
                print_asm("sal" " $0x1,%%%s",REG_NAME(m.R_M));
                return 1 + 1 ;
	}
	else {
		swaddr_t addr;
		DATA_TYPE len = read_ModR_M(eip + 1,&addr);
        DATA_TYPE temp = MEM_R(addr);
		cpu.EFLAGS.OF = (temp >> length) != cpu.EFLAGS.CF;
                cpu.EFLAGS.CF = temp >> length;
                temp = temp * 2;
		switch (DATA_BYTE)
		{  case 1: MEM_W(addr,temp&0xff); break;
		   case 2: MEM_W(addr,temp&0xffff); break;
		   case 4: MEM_W(addr,temp&0xffffffff); break;
		   default: assert(0);
		}
		cpu.EFLAGS.SF = temp >> length;
		int i=0,sum=0,temp1=temp;
		for (; i<8; i++)
		{ DATA_TYPE tmp = temp1 & 0x1;
		  sum = sum + tmp;
		  temp1 = temp1 >> 1;
		}
		if (sum%2==0)
			cpu.EFLAGS.PF=0;
		else 
			cpu.EFLAGS.PF=1;
		if(temp==0)
			cpu.EFLAGS.ZF=1;
		else 
			cpu.EFLAGS.ZF=0;
		 print_asm("sal" " $0x1,%s",ModR_M_asm);
		 return 1 + len;
	}
}

make_helper(concat(sar_12rm_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
	if (m.mod == 3) {
		DATA_TYPE_S temp = REG(m.R_M);
		cpu.EFLAGS.OF = 0;
                cpu.EFLAGS.CF = temp & 0x1;
                temp = temp / 2;
		switch (DATA_BYTE)
		{ case 1: REG(m.R_M) = temp & 0xff; break;
		  case 2: REG(m.R_M) = temp & 0xffff; break;
		  case 4: REG(m.R_M) = temp & 0xffffffff; break;
		  default : assert(0);
		}
		cpu.EFLAGS.SF = temp >> length;
		int i=0,sum=0,temp1=temp;
		for (; i<8; i++)
		{ DATA_TYPE tmp = temp1 & 0x1;
		  sum = sum + tmp;
		  temp1 = temp1 >> 1;
		}
		if (sum%2==0)
			cpu.EFLAGS.PF=0;
		else 
			cpu.EFLAGS.PF=1;
		if(temp==0)
			cpu.EFLAGS.ZF=1;
		else 
			cpu.EFLAGS.ZF=0;
                print_asm("sar" " $0x1,%%%s",REG_NAME(m.R_M));
                return 1 + 1 ;
	} 
	else { 
		swaddr_t addr;
		DATA_TYPE len = read_ModR_M(eip + 1,&addr);
        DATA_TYPE_S temp = MEM_R(addr);
		cpu.EFLAGS.OF = 0;
                cpu.EFLAGS.CF = temp & 0x1;
                temp = temp / 2;
		switch (DATA_BYTE)
		{  case 1: MEM_W(addr,temp&0xff); break;
		   case 2: MEM_W(addr,temp&0xffff); break;
		   case 4: MEM_W(addr,temp&0xffffffff); break;
		   default: assert(0);
		}
		cpu.EFLAGS.SF = temp >> length;
		int i=0,sum=0,temp1=temp;
		for (; i<8; i++)
		{ DATA_TYPE tmp = temp1 & 0x1;
		  sum = sum + tmp;
		  temp1 = temp1 >> 1;
		}
		if (sum%2==0)
			cpu.EFLAGS.PF=0;
		else 
			cpu.EFLAGS.PF=1;
		if(temp==0)
			cpu.EFLAGS.ZF=1;
		else 
			cpu.EFLAGS.ZF=0;
		 print_asm("sar" " $0x1,%s",ModR_M_asm);
		 return 1 + len;
	}
}

make_helper(concat(shr_12rm_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
	if (m.mod == 3) {
		DATA_TYPE temp = REG(m.R_M);
		cpu.EFLAGS.OF = (temp >> length);
                cpu.EFLAGS.CF = temp & 0x1;
                temp = temp / 2;
		switch (DATA_BYTE)
		{ case 1: REG(m.R_M) = temp & 0xff; break;
		  case 2: REG(m.R_M) = temp & 0xffff; break;
		  case 4: REG(m.R_M) = temp & 0xffffffff; break;
		  default : assert(0);
		}
		cpu.EFLAGS.SF = temp >> length;
		int i=0,sum=0,temp1=temp;
		for (; i<8; i++)
		{ DATA_TYPE tmp = temp1 & 0x1;
		  sum = sum + tmp;
		  temp1 = temp1 >> 1;
		}
		if (sum%2==0)
			cpu.EFLAGS.PF=0;
		else 
			cpu.EFLAGS.PF=1;
		if(temp==0)
			cpu.EFLAGS.ZF=1;
		else 
			cpu.EFLAGS.ZF=0;
                print_asm("shr" " $0x1,%%%s",REG_NAME(m.R_M));
                return 1 + 1 ;
	} 
	else { 
		swaddr_t addr;
		DATA_TYPE len = read_ModR_M(eip + 1,&addr);
        DATA_TYPE temp = MEM_R(addr);
		cpu.EFLAGS.OF = temp >> length;
                cpu.EFLAGS.CF = temp & 0x1;
                temp = temp / 2;
		switch (DATA_BYTE)
		{  case 1: MEM_W(addr,temp&0xff); break;
		   case 2: MEM_W(addr,temp&0xffff); break;
		   case 4: MEM_W(addr,temp&0xffffffff); break;
		   default: assert(0);
		}
		cpu.EFLAGS.SF = temp >> length;
		int i=0,sum=0,temp1=temp;
		for (; i<8; i++)
		{ DATA_TYPE tmp = temp1 & 0x1;
		  sum = sum + tmp;
		  temp1 = temp1 >> 1;
		}
		if (sum%2==0)
			cpu.EFLAGS.PF=0;
		else 
			cpu.EFLAGS.PF=1;
		if(temp==0)
			cpu.EFLAGS.ZF=1;
		else 
			cpu.EFLAGS.ZF=0;
		 print_asm("shr" " $0x1,%s",ModR_M_asm);
		 return 1 + len;
	}
}


make_helper(concat(sal_rc2rm_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
	if (m.mod == 3) {
		DATA_TYPE temp = REG(m.R_M);
		int p=0;
		for (; p<REG(0x1);p++)
		{   cpu.EFLAGS.CF = temp >> (length);
            temp = temp * 2;
		}
		switch (DATA_BYTE)
		{ case 1: REG(m.R_M) = temp & 0xff; break;
		  case 2: REG(m.R_M) = temp & 0xffff; break;
		  case 4: REG(m.R_M) = temp & 0xffffffff; break;
		  default : assert(0);
		}
		cpu.EFLAGS.SF = temp >> length;
		int i=0,sum=0,temp1=temp;
		for (; i<8; i++)
		{ DATA_TYPE tmp = temp1 & 0x1;
		  sum = sum + tmp;
		  temp1 = temp1 >> 1;
		}
		if (sum%2==0)
			cpu.EFLAGS.PF=0;
		else 
			cpu.EFLAGS.PF=1;
		if(temp==0)
			cpu.EFLAGS.ZF=1;
		else 
			cpu.EFLAGS.ZF=0;
                print_asm("sal" " %%%s,%%%s",REG_NAME(0x1),REG_NAME(m.R_M));
                return 1 + 1;
	} 
	else {
		swaddr_t addr;
		DATA_TYPE len = read_ModR_M(eip + 1,&addr);
        DATA_TYPE temp = MEM_R(addr);
		int p = 0;
		for(; p<REG(0x1);p++)
		{    cpu.EFLAGS.CF = temp >> length ;
                     temp = temp * 2;
		}
		switch (DATA_BYTE)
		{  case 1: MEM_W(addr,temp&0xff); break;
		   case 2: MEM_W(addr,temp&0xffff); break;
		   case 4: MEM_W(addr,temp&0xffffffff); break;
		   default: assert(0);
		}
		cpu.EFLAGS.SF = temp >> length;
		int i=0,sum=0,temp1=temp;
		for (; i<8; i++)
  		{ DATA_TYPE tmp = temp1 & 0x1;
		  sum = sum + tmp;
		  temp1 = temp1 >> 1;
		}
		if (sum%2==0)
			cpu.EFLAGS.PF=0;
		else 
			cpu.EFLAGS.PF=1;
		if(temp==0)
			cpu.EFLAGS.ZF=1;
		else 
			cpu.EFLAGS.ZF=0;
		 print_asm("sal" " %%%s,%s",REG_NAME(0x1),ModR_M_asm);
		 return 1  + len;
	} 
}
 

make_helper(concat(sar_rc2rm_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
	if  (m.mod == 3) {
		DATA_TYPE_S temp = REG(m.R_M);
		int p=0;
		for (; p<REG(0x1);p++)
		{   cpu.EFLAGS.CF = temp & 0x1;
            temp = temp / 2;
		}
		switch (DATA_BYTE)
		{ case 1: REG(m.R_M) = temp & 0xff; break;
		  case 2: REG(m.R_M) = temp & 0xffff; break;
		  case 4: REG(m.R_M) = temp & 0xffffffff; break;
		  default : assert(0);
		}
		cpu.EFLAGS.SF = temp >> length;
		int i=0,sum=0,temp1=temp;
		for (; i<8; i++)
		{ DATA_TYPE tmp = temp1 & 0x1;
		  sum = sum + tmp;
		  temp1 = temp1 >> 1;
		}
		if (sum%2==0)
			cpu.EFLAGS.PF=0;
		else 
			cpu.EFLAGS.PF=1;
		if(temp==0)
			cpu.EFLAGS.ZF=1;
		else 
			cpu.EFLAGS.ZF=0;
                print_asm("sar" " %%%s,%%%s",REG_NAME(0x1),REG_NAME(m.R_M));
                return 1 + 1;
	}
	else {
		swaddr_t addr;
		DATA_TYPE len = read_ModR_M(eip + 1,&addr);
        DATA_TYPE_S temp = MEM_R(addr);
		int p = 0;
		for(; p<REG(0x1);p++)
		{    cpu.EFLAGS.CF = temp & 0x1;
                     temp = temp / 2;
		}
		switch (DATA_BYTE)
		{  case 1: MEM_W(addr,temp&0xff); break;
		   case 2: MEM_W(addr,temp&0xffff); break;
		   case 4: MEM_W(addr,temp&0xffffffff); break;
		   default: assert(0);
		}
		cpu.EFLAGS.SF = temp >> length;
		int i=0,sum=0,temp1=temp;
		for (; i<8; i++)
		{ DATA_TYPE tmp = temp1 & 0x1;
		  sum = sum + tmp;
		  temp1 = temp1 >> 1;
		}
		if (sum%2==0)
			cpu.EFLAGS.PF=0;
		else 
			cpu.EFLAGS.PF=1;
		if(temp==0)
			cpu.EFLAGS.ZF=1;
		else 
			cpu.EFLAGS.ZF=0;
		 print_asm("sar" " %%%s,%s",REG_NAME(0x1),ModR_M_asm);
		 return 1  + len;
	} 
}


make_helper(concat(shr_rc2rm_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
	if (m.mod == 3) {
		DATA_TYPE temp = REG(m.R_M);
		int p=0;
		for (; p<REG(0x1);p++)
		{   cpu.EFLAGS.CF = temp & 0x1;
            temp = temp / 2;
		}
		switch (DATA_BYTE)
		{ case 1: REG(m.R_M) = temp & 0xff; break;
		  case 2: REG(m.R_M) = temp & 0xffff; break;
		  case 4: REG(m.R_M) = temp & 0xffffffff; break;
		  default : assert(0);
		}
		cpu.EFLAGS.SF = temp >> length;
		int i=0,sum=0,temp1=temp;
		for (; i<8; i++)
		{ DATA_TYPE tmp = temp1 & 0x1;
		  sum = sum + tmp;
		  temp1 = temp1 >> 1;
		}
		if (sum%2==0)
			cpu.EFLAGS.PF=0;
		else 
			cpu.EFLAGS.PF=1;
		if(temp==0)
			cpu.EFLAGS.ZF=1;
		else 
			cpu.EFLAGS.ZF=0;
                print_asm("shr" " %%%s,%%%s",REG_NAME(0x1),REG_NAME(m.R_M));
                return 1 + 1;
	} 
	else {
		swaddr_t addr;
		DATA_TYPE len = read_ModR_M(eip + 1,&addr);
        DATA_TYPE temp = MEM_R(addr);
		int p = 0;
		for(; p<REG(0x1);p++)
		{    cpu.EFLAGS.CF = temp & 0x1;
                     temp = temp / 2;
		}
		switch (DATA_BYTE)
		{  case 1: MEM_W(addr,temp&0xff); break;
		   case 2: MEM_W(addr,temp&0xffff); break;
		   case 4: MEM_W(addr,temp&0xffffffff); break;
		   default: assert(0);
		}
		cpu.EFLAGS.SF = temp >> length;
		int i=0,sum=0,temp1=temp;
		for (; i<8; i++)
		{ DATA_TYPE tmp = temp1 & 0x1;
		  sum = sum + tmp;
		  temp1 = temp1 >> 1;
		}
		if (sum%2==0)
			cpu.EFLAGS.PF=0;
		else 
			cpu.EFLAGS.PF=1;
		if(temp==0)
			cpu.EFLAGS.ZF=1;
		else 
			cpu.EFLAGS.ZF=0;
		 print_asm("shr" " %%%s,%s",REG_NAME(0x1),ModR_M_asm);
		 return 1  + len;
	} 
}

#include "exec/template-end.h"
