#include "exec/helper.h"

#define DATA_BYTE 1
#include "jcc-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jcc-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jcc-template.h"
#undef DATA_BYTE

extern char suffix;   


make_helper(JCC_CXZ_b) {
	int rel = instr_fetch(eip + 1,1);
	
    if(cpu.ecx==0||(cpu.ecx&0xffff)==0)
	{ cpu.eip += rel;
	}
	print_asm("jcxz(jecxz)" " 0x%x",cpu.eip + 2);
	return 2;
}



make_helper(JCC_EorZ_v) {
	return (suffix == 'l' ? JCC_EorZ_l(eip) : JCC_EorZ_w(eip));
}


make_helper(JCC_A_v)  {
	return (suffix == 'l' ? JCC_A_l(eip) : JCC_A_w(eip));
}


make_helper(JCC_AorE_v) {
	return (suffix == 'l' ? JCC_AorE_l(eip) : JCC_AorE_w(eip));
}


make_helper(JCC_B_v) {
	return (suffix == 'l' ? JCC_B_l(eip) : JCC_B_w(eip));
}


make_helper(JCC_BorE_v) {
	return (suffix == 'l' ? JCC_BorE_l(eip) : JCC_BorE_w(eip));
}


make_helper(JCC_G_v) {
	return (suffix == 'l' ? JCC_G_l(eip) : JCC_G_w(eip));
}


make_helper(JCC_GorE_v) {
	return (suffix == 'l' ? JCC_GorE_l(eip) : JCC_GorE_w(eip));
}


make_helper(JCC_L_v) {
	return (suffix == 'l' ? JCC_L_l(eip) : JCC_L_w(eip));
}


make_helper(JCC_LorE_v) {
	return (suffix == 'l' ? JCC_LorE_l(eip) : JCC_LorE_w(eip));
}


make_helper(JCC_NA_v) {
	return (suffix == 'l' ? JCC_NA_l(eip) : JCC_NA_w(eip));
}


make_helper(JCC_NE_v) {
	return (suffix == 'l' ? JCC_NE_l(eip) : JCC_NE_w(eip));
}


make_helper(JCC_NO_v) {
	return (suffix == 'l' ? JCC_NO_l(eip) : JCC_NO_w(eip));
}


make_helper(JCC_NP_v) {
	return (suffix == 'l' ? JCC_NP_l(eip) : JCC_NP_w(eip));
}


make_helper(JCC_NS_v) {
    return (suffix == 'l' ? JCC_NS_l(eip) : JCC_NS_w(eip));
}


make_helper(JCC_O_v) {
	return (suffix == 'l' ? JCC_O_l(eip) : JCC_O_w(eip));
}


make_helper(JCC_P_v) {
	return (suffix == 'l' ? JCC_P_l(eip) : JCC_P_w(eip));
}


make_helper(JCC_S_v) {
	return (suffix == 'l' ? JCC_S_l(eip) : JCC_S_w(eip));
}
