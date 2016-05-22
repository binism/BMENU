#include "exec/helper.h"
#include "std.h"
#include "cpu/modrm.h"


make_helper(std) {
	cpu.EFLAGS.DF = 1;
	print_asm("std");
	return 1;
}
