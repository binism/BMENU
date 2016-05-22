#include "exec/helper.h"

#define DATA_BYTE 1
#include "imul-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "imul-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "imul-template.h"
#undef DATA_BYTE

extern char suffix;   




make_helper(imul_rm2ra_v) {
	return (suffix == 'l' ? imul_rm2ra_l(eip) : imul_rm2ra_w(eip));
}


make_helper(imul_rm2r_v) {
	return (suffix == 'l' ? imul_rm2r_l(eip) : imul_rm2r_w(eip));
}


make_helper(imul_ib2rm2r_v) {
	return (suffix == 'l' ? imul_ib2rm2r_l(eip) : imul_ib2rm2r_w(eip));
}


make_helper(imul_i2rm2r_v) {
	return (suffix == 'l' ? imul_i2rm2r_l(eip) : imul_i2rm2r_w(eip));
}
