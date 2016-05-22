#include "exec/helper.h"


#define DATA_BYTE 2
#include "movsx-template.h"
#undef DATA_BYTE


#define DATA_BYTE 4
#include "movsx-template.h"
#undef DATA_BYTE


extern char suffix;
make_helper(movsx_rmb2r_v) {
	return (suffix == 'l' ? movsx_rmb2r_l(eip) : movsx_rmb2r_w(eip));
}


