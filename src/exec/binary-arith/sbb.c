#include "exec/helper.h"

#define DATA_BYTE 1
#include "sbb-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "sbb-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "sbb-template.h"
#undef DATA_BYTE


extern char suffix;


make_helper(sbb_i2ra_v) {
   return (suffix == 'l'?sbb_i2ra_l(eip):sbb_i2ra_w(eip));
}


make_helper(sbb_i2rm_v) {
   return (suffix == 'l'?sbb_i2rm_l(eip):sbb_i2rm_w(eip));
}

make_helper(sbb_ib2rm_v) {
   return (suffix == 'l'?sbb_ib2rm_l(eip):sbb_ib2rm_w(eip));
}

make_helper(sbb_r2rm_v) {
   return (suffix == 'l'?sbb_r2rm_l(eip):sbb_r2rm_w(eip));
}

make_helper(sbb_rm2r_v) {
   return (suffix == 'l'?sbb_rm2r_l(eip):sbb_rm2r_w(eip));
}
