#include "exec/helper.h"

#define DATA_BYTE 1
#include "ret-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "ret-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "ret-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(ret_ss_v) {
	return (suffix == 'l' ? ret_ss_l(eip) : ret_ss_w(eip));
}

make_helper(ret_iw_l) {
    uint16_t imm = instr_fetch(eip + 1 ,2);
	cpu.eip = cpu.eip + imm;
	print_asm("ret" " $0x%x",imm);
	return 3;
}
