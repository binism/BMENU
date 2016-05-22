#ifndef __OPDEFINE_H__
#define __OPDEFINE_H__
#include "exec/helper.h"

#include "cpu/modrm.h"
//make_helper(dbopcode) {} 
make_helper(concat(opdefine,0f));
make_helper(concat(opdefine,80));
make_helper(concat(opdefine,81));
make_helper(concat(opdefine,83));
make_helper(concat(opdefine,8f));
make_helper(concat(opdefine,c0));
make_helper(concat(opdefine,c1));
make_helper(concat(opdefine,d0));
make_helper(concat(opdefine,d1));
make_helper(concat(opdefine,d2));
make_helper(concat(opdefine,d3));
make_helper(concat(opdefine,f6));
make_helper(concat(opdefine,f7));
make_helper(concat(opdefine,fe));
make_helper(concat(opdefine,ff));
make_helper(concat(dbopcode,));
#endif
