#include "exec/helper.h"

#define DATA_BYTE 1
#include "leave-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "leave-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "leave-template.h"
#undef DATA_BYTE


/* for instruction encoding overloading */

extern char suffix;

make_helper(leave_r_v) {
    return (suffix == 'l' ? leave_r_l(eip) : leave_r_w(eip));
}
