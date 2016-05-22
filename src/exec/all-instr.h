#include "prefix/prefix.h"

#include "data-mov/mov.h"
#include "data-mov/movzx.h"
#include "data-mov/movsx.h"
#include "data-mov/push.h"
#include "data-mov/pop.h"
#include "data-mov/xchg.h"
#include "data-mov/leave.h"

#include "misc/misc.h"
 
#include "logical/test.h"
#include "logical/not.h"
#include "logical/and.h"
#include "logical/or.h"
#include "logical/xor.h"
#include "logical/shift.h"
#include "logical/setcc.h"
 
#include "ctrl-transfer/jcc.h"
#include "ctrl-transfer/jmp.h"
#include "ctrl-transfer/call.h"
#include "ctrl-transfer/ret.h"


#include "binary-arith/cmp.h"
#include "binary-arith/sub.h"
#include "binary-arith/sbb.h"
#include "binary-arith/inc.h"
#include "binary-arith/dec.h"
#include "binary-arith/neg.h"
#include "binary-arith/add.h"
#include "binary-arith/adc.h"
#include "binary-arith/mul.h"
#include "binary-arith/imul.h"
#include "binary-arith/div.h"
#include "binary-arith/idiv.h"
#include "miscell-instr/lea.h"

#include "flag-ctrl/cwd.h"
#include "flag-ctrl/std.h"
#include "flag-ctrl/cld.h"

#include "str_char-transfer/movs.h"

#include "opdefine.h"
//#include "opdefine.c"
