#include "exec/helper.h"


#define DATA_BYTE 2
#include "movzx-template.h"
#undef DATA_BYTE


#define DATA_BYTE 4
#include "movzx-template.h"
#undef DATA_BYTE


extern char suffix;
make_helper(movzx_rmb2r_v) {
	return (suffix == 'l' ? movzx_rmb2r_l(eip) : movzx_rmb2r_w(eip));
}




