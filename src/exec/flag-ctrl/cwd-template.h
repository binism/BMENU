#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"






make_helper(concat(cwd_,SUFFIX)) {
  if(DATA_BYTE==2) {
      if((REG(0x0)&0xffff)<0)
         REG(0x2)=-1;
	  else 
		 REG(0x2)=0;
   }
   else if(DATA_BYTE==4) {
	   if(REG(0x0)<0)
		   REG(0x2)=-1;
	   else
		   REG(0x2)=0;
   }
   print_asm("cwd");
   return 1;
}














#include "exec/template-end.h"
