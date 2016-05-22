#include "exec/helper.h"

#define DATA_BYTE 1
#include "push-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "push-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "push-template.h"
#undef DATA_BYTE


/* for instruction encoding overloading */

extern char suffix;


make_helper(PUSH_r_v) {  //binism added 10.26
	return (suffix== 'l' ? PUSH_r_l(eip) : PUSH_r_w(eip));
}
