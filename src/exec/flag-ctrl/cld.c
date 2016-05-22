#include "exec/helper.h"
#include "cld.h"
#include "cpu/modrm.h"


make_helper(cld) {
	cpu.EFLAGS.DF = 0;
	print_asm("cld");
	return 1;
}



