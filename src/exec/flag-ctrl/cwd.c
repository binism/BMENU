#include "exec/helper.h"


#define DATA_BYTE 2
#include "cwd-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "cwd-template.h"
#undef DATA_BYTE


/* for instruction encoding overloading */

extern char suffix;

make_helper(cwd_v) {
	return (suffix == 'l' ? cwd_l(eip) : cwd_w(eip));
}
