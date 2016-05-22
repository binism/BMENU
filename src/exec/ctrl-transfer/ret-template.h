#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(ret_ss_,SUFFIX)) {
	DATA_TYPE temp = MEM_R(cpu.esp);
	if(DATA_BYTE==2)
	{   cpu.eip = temp ;
		cpu.eip = cpu.eip & 0xffff;
		cpu.esp = cpu.esp + 2;
	}
	else if(DATA_BYTE==4)
	{	cpu.eip = temp;
		cpu.esp = cpu.esp + 4;
	}
	print_asm("ret");
	return 1;
}

#include "exec/template-end.h"
