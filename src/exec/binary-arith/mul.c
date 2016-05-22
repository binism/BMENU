#include "exec/helper.h"

#define DATA_BYTE 1
#include "mul-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "mul-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "mul-template.h"
#undef DATA_BYTE

extern char suffix;   

make_helper(mul_rm2ra_v) {
	return (suffix == 'l'?mul_rm2ra_l(eip):mul_rm2ra_w(eip));
}
