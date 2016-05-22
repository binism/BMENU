#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(set_o_b) {
	ModR_M m;
	m.val = instr_fetch(eip + 1 + 1, 1);
	if(m.mod == 3) {
		if(cpu.EFLAGS.OF==1)
			REG(m.R_M) = 1;
		else
			REG(m.R_M) = 0;
		print_asm("seto"" %%%s",REG_NAME(m.R_M));
		return 1 + 1 + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1 + 1,&addr);
		if(cpu.EFLAGS.OF==1)
			MEM_W(addr,1);
		else 
			MEM_W(addr,0);
		print_asm("seto" " %s",ModR_M_asm);
		return 1 + 1 + len;
	}
}


make_helper(set_no_b) {
	ModR_M m;
	m.val = instr_fetch(eip + 1 + 1, 1);
	if(m.mod == 3) {
		if(cpu.EFLAGS.OF==0)
			REG(m.R_M) = 1;
		else
			REG(m.R_M) = 0;
		print_asm("setno"" %%%s",REG_NAME(m.R_M));
		return 1 + 1 + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1 + 1,&addr);
		if(cpu.EFLAGS.OF==0)
			MEM_W(addr,1);
		else 
			MEM_W(addr,0);
		print_asm("setno" " %s",ModR_M_asm);
		return 1 + 1 + len;
	}
}


make_helper(set_b_b) {
	ModR_M m;
	m.val = instr_fetch(eip + 1 + 1, 1);
	if(m.mod == 3) {
		if(cpu.EFLAGS.CF==0)
			REG(m.R_M) = 1;
		else
			REG(m.R_M) = 0;
		print_asm("setb"" %%%s",REG_NAME(m.R_M));
		return 1 + 1 + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		if(cpu.EFLAGS.CF==0)
			MEM_W(addr,1);
		else 
			MEM_W(addr,0);
		print_asm("setb" " %s",ModR_M_asm);
		return 1 + 1 + len;
	}
}


make_helper(set_ae_b) {
	ModR_M m;
	m.val = instr_fetch(eip + 1 + 1, 1);
	if(m.mod == 3) {
		if(cpu.EFLAGS.CF==0&&cpu.EFLAGS.ZF==0)
			REG(m.R_M) = 1;
		else
			REG(m.R_M) = 0;
		print_asm("setae"" %%%s",REG_NAME(m.R_M));
		return 1 + 1 + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		if(cpu.EFLAGS.CF==0&&cpu.EFLAGS.ZF==0)
			MEM_W(addr,1);
		else 
			MEM_W(addr,0);
		print_asm("setae" " %s",ModR_M_asm);
		return 1 + 1 + len;
	}
}


make_helper(set_e_b) {
	ModR_M m;
	m.val = instr_fetch(eip + 1 + 1, 1);
	if(m.mod == 3) {
		if(cpu.EFLAGS.ZF==1)
			REG(m.R_M) = 1;
		else
			REG(m.R_M) = 0;
		print_asm("sete"" %%%s",REG_NAME(m.R_M));
		return 1 + 1 + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1 + 1,&addr);
		if(cpu.EFLAGS.ZF==1)
			MEM_W(addr,1);
		else 
			MEM_W(addr,0);
		print_asm("sete" " %s",ModR_M_asm);
		return 1 + 1 + len;
	}
}


make_helper(set_ne_b) {
	ModR_M m;
	m.val = instr_fetch(eip + 1 + 1, 1);
	if(m.mod == 3) {
		if(cpu.EFLAGS.ZF==0)
			REG(m.R_M) = 1;
		else
			REG(m.R_M) = 0;
		print_asm("setne"" %%%s",REG_NAME(m.R_M));
		return 1 + 1 + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1 + 1,&addr);
		if(cpu.EFLAGS.ZF==0)
			MEM_W(addr,1);
		else 
			MEM_W(addr,0);
		print_asm("setne" " %s",ModR_M_asm);
		return 1 + 1 + len;
	}
}


make_helper(set_na_b) {
	ModR_M m;
	m.val = instr_fetch(eip + 1 + 1, 1);
	if(m.mod == 3) {
		if(cpu.EFLAGS.CF==1||cpu.EFLAGS.ZF==1)
			REG(m.R_M) = 1;
		else
			REG(m.R_M) = 0;
		print_asm("setna"" %%%s",REG_NAME(m.R_M));
		return 1 + 1 + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		if(cpu.EFLAGS.CF==1||cpu.EFLAGS.ZF==1)
			MEM_W(addr,1);
		else 
			MEM_W(addr,0);
		print_asm("setna" " %s",ModR_M_asm);
		return 1 + 1 + len;
	}
}


make_helper(set_a_b) {
	ModR_M m;
	m.val = instr_fetch(eip + 1 + 1, 1);
	if(m.mod == 3) {
		if(cpu.EFLAGS.CF==0&&cpu.EFLAGS.ZF==0)
			REG(m.R_M) = 1;
		else
			REG(m.R_M) = 0;
		print_asm("seta"" %%%s",REG_NAME(m.R_M));
		return 1 + 1 + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1 + 1,&addr);
		if(cpu.EFLAGS.CF==0&&cpu.EFLAGS.ZF==0)
			MEM_W(addr,1);
		else 
			MEM_W(addr,0);
		print_asm("seta" " %s",ModR_M_asm);
		return 1 + 1 + len;
	}
}


make_helper(set_s_b) {
	ModR_M m;
	m.val = instr_fetch(eip + 1 + 1, 1);
	if(m.mod == 3) {
		if(cpu.EFLAGS.SF==1)
			REG(m.R_M) = 1;
		else
			REG(m.R_M) = 0;
		print_asm("sets"" %%%s",REG_NAME(m.R_M));
		return 1 + 1 + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1 + 1,&addr);
		if(cpu.EFLAGS.SF==1)
			MEM_W(addr,1);
		else 
			MEM_W(addr,0);
		print_asm("sets" " %s",ModR_M_asm);
		return 1 + 1 + len;
	}
}


make_helper(set_ns_b) {
	ModR_M m;
	m.val = instr_fetch(eip + 1 + 1, 1);
	if(m.mod == 3) {
		if(cpu.EFLAGS.SF==0)
			REG(m.R_M) = 1;
		else
			REG(m.R_M) = 0;
		print_asm("setns"" %%%s",REG_NAME(m.R_M));
		return 1 + 1 + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1 + 1,&addr);
		if(cpu.EFLAGS.SF==0)
			MEM_W(addr,1);
		else 
			MEM_W(addr,0);
		print_asm("setns" " %s",ModR_M_asm);
		return 1 + 1 + len;
	}
}


make_helper(set_pe_b) {
	ModR_M m;
	m.val = instr_fetch(eip + 1 + 1, 1);
	if(m.mod == 3) {
		if(cpu.EFLAGS.PF==1)
			REG(m.R_M) = 1;
		else
			REG(m.R_M) = 0;
		print_asm("setpe"" %%%s",REG_NAME(m.R_M));
		return 1 + 1 + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1 + 1,&addr);
		if(cpu.EFLAGS.PF==1)
			MEM_W(addr,1);
		else 
			MEM_W(addr,0);
		print_asm("setpe" " %s",ModR_M_asm);
		return 1 + 1 + len;
	}
}


make_helper(set_po_b) {
	ModR_M m;
	m.val = instr_fetch(eip + 1 + 1, 1);
	if(m.mod == 3) {
		if(cpu.EFLAGS.PF==0)
			REG(m.R_M) = 1;
		else
			REG(m.R_M) = 0;
		print_asm("setpo"" %%%s",REG_NAME(m.R_M));
		return 1 + 1 + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		if(cpu.EFLAGS.PF==0)
			MEM_W(addr,1);
		else 
			MEM_W(addr,0);
		print_asm("setpo" " %s",ModR_M_asm);
		return 1 + 1 + len;
	}
}


make_helper(set_l_b) {
	ModR_M m;
	m.val = instr_fetch(eip + 1 + 1, 1);
	if(m.mod == 3) {
		if(cpu.EFLAGS.SF!=cpu.EFLAGS.OF)
			REG(m.R_M) = 1;
		else
			REG(m.R_M) = 0;
		print_asm("setl"" %%%s",REG_NAME(m.R_M));
		return 1 + 1 + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1 + 1,&addr);
		if(cpu.EFLAGS.SF!=cpu.EFLAGS.OF)
			MEM_W(addr,1);
		else 
			MEM_W(addr,0);
		print_asm("setl" " %s",ModR_M_asm);
		return 1 + 1 + len;
	}
}


make_helper(set_ge_b) {
	ModR_M m;
	m.val = instr_fetch(eip + 1 + 1, 1);
	if(m.mod == 3) {
		if(cpu.EFLAGS.SF==cpu.EFLAGS.OF)
			REG(m.R_M) = 1;
		else
			REG(m.R_M) = 0;
		print_asm("setge"" %%%s",REG_NAME(m.R_M));
		return 1 + 1 + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1 + 1,&addr);
		if(cpu.EFLAGS.SF==cpu.EFLAGS.OF)
			MEM_W(addr,1);
		else 
			MEM_W(addr,0);
		print_asm("setge" " %s",ModR_M_asm);
		return 1 + 1 + len;
	}
}


make_helper(set_le_b) {
	ModR_M m;
	m.val = instr_fetch(eip + 1 + 1, 1);
	if(m.mod == 3) {
		if(cpu.EFLAGS.ZF==1&&cpu.EFLAGS.SF!=cpu.EFLAGS.OF)
			REG(m.R_M) = 1;
		else
			REG(m.R_M) = 0;
		print_asm("setle"" %%%s",REG_NAME(m.R_M));
		return 1 + 1 + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1 + 1,&addr);
		if(cpu.EFLAGS.ZF==1&&cpu.EFLAGS.SF!=cpu.EFLAGS.OF)
			MEM_W(addr,1);
		else 
			MEM_W(addr,0);
		print_asm("setle" " %s",ModR_M_asm);
		return 1 + 1 + len;
	}
}


make_helper(set_g_b) {
	ModR_M m;
	m.val = instr_fetch(eip + 1 + 1, 1);
	if(m.mod == 3) {
		if(cpu.EFLAGS.ZF==0&&cpu.EFLAGS.SF==cpu.EFLAGS.OF)
			REG(m.R_M) = 1;
		else
			REG(m.R_M) = 0;
		print_asm("setg"" %%%s",REG_NAME(m.R_M));
		return 1 + 1 + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1 + 1,&addr);
		if(cpu.EFLAGS.ZF==0&&cpu.EFLAGS.SF==cpu.EFLAGS.OF)
			MEM_W(addr,1);
		else 
			MEM_W(addr,0);
		print_asm("setg" " %s",ModR_M_asm);
		return 1 + 1 + len;
	}
}



#include "exec/template-end.h"
