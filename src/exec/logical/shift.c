#include "exec/helper.h"

#define DATA_BYTE 1
#include "shift-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "shift-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "shift-template.h"
#undef DATA_BYTE


extern char suffix;
make_helper(sal_ib2rm_v) {
	return (suffix == 'l' ? sal_ib2rm_l(eip) : sal_ib2rm_w(eip));
}



make_helper(sar_ib2rm_v) {
	return (suffix == 'l' ? sar_ib2rm_l(eip) : sar_ib2rm_w(eip));
}


make_helper(shr_ib2rm_v) {
	return (suffix == 'l' ? shr_ib2rm_l(eip) : shr_ib2rm_w(eip));
}


make_helper(sal_12rm_v) {
	return (suffix == 'l' ? sal_12rm_l(eip) : sal_12rm_w(eip));
}


make_helper(sar_12rm_v) {
	return (suffix == 'l' ? sar_12rm_l(eip) : sar_12rm_w(eip));
}


make_helper(shr_12rm_v) {
	return (suffix == 'l' ? shr_12rm_l(eip) : shr_12rm_w(eip));
}


make_helper(sal_rc2rm_v) {
	return (suffix == 'l' ? sal_rc2rm_l(eip) : sal_rc2rm_w(eip));
}


make_helper(sar_rc2rm_v) {
	return (suffix == 'l' ? sar_rc2rm_l(eip) : sar_rc2rm_w(eip));
}


make_helper(shr_rc2rm_v) {
	return (suffix == 'l' ? shr_rc2rm_l(eip) : shr_rc2rm_w(eip));
}

