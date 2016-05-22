#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"



make_helper(concat(movs_,SUFFIX)) {
	swaddr_t addr1 = cpu.esi;
	swaddr_t addr2 = cpu.edi;
	DATA_TYPE tmp = MEM_R(addr1);
	MEM_W(addr2,tmp);
	print_asm("movs");
	return 1;
}







#include "exec/template-end.h"
