#include "exec/helper.h"

#define DATA_BYTE 1
#include "sub-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "sub-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "sub-template.h"
#undef DATA_BYTE


extern char suffix;


make_helper(sub_i2ra_v) {
   return (suffix == 'l'?sub_i2ra_l(eip):sub_i2ra_w(eip));
}


make_helper(sub_i2rm_v) {
   return (suffix == 'l'?sub_i2rm_l(eip):sub_i2rm_w(eip));
}

make_helper(sub_ib2rm_v) {
   return (suffix == 'l'?sub_ib2rm_l(eip):sub_ib2rm_w(eip));
}

make_helper(sub_r2rm_v) {
   return (suffix == 'l'?sub_r2rm_l(eip):sub_r2rm_w(eip));
}

make_helper(sub_rm2r_v) {
   return (suffix == 'l'?sub_rm2r_l(eip):sub_rm2r_w(eip));
}
