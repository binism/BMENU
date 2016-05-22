#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#define length (DATA_BYTE*8-1)

make_helper(concat(JCC_EorZ_,SUFFIX)) {
	DATA_TYPE rel;
        if(DATA_BYTE==1)
	  rel = instr_fetch(eip + 1,DATA_BYTE);
        else 
          rel = instr_fetch(eip + 1 + 1,DATA_BYTE);
	if(cpu.EFLAGS.ZF==1)
	{ if(rel>>length==1)
          { rel = ~rel + 1;
            cpu.eip -= rel;
          }
          else 
            cpu.eip += rel;
	  if(DATA_BYTE==2)
		  cpu.eip = cpu.eip & 0xffff;
	}
        if(DATA_BYTE==1)
	   { 
             print_asm("je" " 0x%x",cpu.eip + 1 + DATA_BYTE);
             return 1 + DATA_BYTE;   }
        else 
           {  
             print_asm("je" " 0x%x",cpu.eip + 1 + 1 + DATA_BYTE);
             return 1 + 1 + DATA_BYTE;     }   
}

make_helper(concat(JCC_A_,SUFFIX)) {
	DATA_TYPE rel;
	if(DATA_BYTE==1)
	  rel = instr_fetch(eip + 1,DATA_BYTE);
        else 
          rel = instr_fetch(eip + 1 + 1,DATA_BYTE);
	if(cpu.EFLAGS.ZF==0&&cpu.EFLAGS.CF==0)
	{ if(rel>>length==1)
          { rel = ~rel + 1;
            cpu.eip -= rel;
          }
          else 
            cpu.eip += rel;
	  if(DATA_BYTE==2)
		  cpu.eip = cpu.eip & 0xffff;
	}
        if(DATA_BYTE==1)
	   { 
             print_asm("ja" " 0x%x",cpu.eip + 1 + DATA_BYTE);
             return 1 + DATA_BYTE;   }
        else 
           {   
             print_asm("ja" " 0x%x",cpu.eip + 1 + 1 + DATA_BYTE);
             return 1 + 1 + DATA_BYTE;    }    
}


make_helper(concat(JCC_AorE_,SUFFIX)) {
	DATA_TYPE rel;
	if(DATA_BYTE==1)
	  rel = instr_fetch(eip + 1,DATA_BYTE);
        else 
          rel = instr_fetch(eip + 1 + 1,DATA_BYTE);
	if(cpu.EFLAGS.CF==0)
	{ if(rel>>length==1)
          { rel = ~rel + 1;
            cpu.eip -= rel;
          }
          else 
            cpu.eip += rel;
	  if(DATA_BYTE==2)
		  cpu.eip = cpu.eip & 0xffff;
	}
        if(DATA_BYTE==1)
	   { 
             print_asm("jae" " 0x%x",cpu.eip + 1 + DATA_BYTE);
             return 1 + DATA_BYTE;    }
        else 
           { 
             print_asm("jae" " 0x%x",cpu.eip + 1 + 1 + DATA_BYTE);
             return 1 + 1 + DATA_BYTE;   }   
}


make_helper(concat(JCC_B_,SUFFIX)) {
	DATA_TYPE rel;
	if(DATA_BYTE==1)
	  rel = instr_fetch(eip + 1,DATA_BYTE);
        else 
          rel = instr_fetch(eip + 1 + 1,DATA_BYTE);
	if(cpu.EFLAGS.CF==1)
	{ if(rel>>length==1)
          { rel = ~rel + 1;
            cpu.eip -= rel;
          }
          else 
            cpu.eip += rel;
	  if(DATA_BYTE==2)
		  cpu.eip = cpu.eip & 0xffff;
	}
        if(DATA_BYTE==1)
	   { 
             print_asm("je" " 0x%x",cpu.eip + 1 + DATA_BYTE);
             return 1 + DATA_BYTE;     }
        else 
           { 
             print_asm("je" " 0x%x",cpu.eip + 1 + 1 + DATA_BYTE);
             return 1 + 1 + DATA_BYTE;   }    
}


make_helper(concat(JCC_BorE_,SUFFIX)) {
	DATA_TYPE rel;
	if(DATA_BYTE==1)
	  rel = instr_fetch(eip + 1,DATA_BYTE);
        else 
          rel = instr_fetch(eip + 1 + 1,DATA_BYTE);
	if(cpu.EFLAGS.CF==1||cpu.EFLAGS.ZF==1)
	{ if(rel>>length==1)
          { rel = ~rel + 1;
            cpu.eip -= rel;
          }
          else 
            cpu.eip += rel;
	  if(DATA_BYTE==2)
		  cpu.eip = cpu.eip & 0xffff;
	}
        if(DATA_BYTE==1)
	   { 
             print_asm("jbe" " 0x%x",cpu.eip + 1 + DATA_BYTE);
             return 1 + DATA_BYTE;    }
        else 
           {
             print_asm("jbe" " 0x%x",cpu.eip + 1 + 1 + DATA_BYTE);
             return 1 + 1 + DATA_BYTE;   }     
}


make_helper(concat(JCC_G_,SUFFIX)) {
	DATA_TYPE rel;
	if(DATA_BYTE==1)
	  rel = instr_fetch(eip + 1,DATA_BYTE);
        else 
          rel = instr_fetch(eip + 1 + 1,DATA_BYTE); 
	if(cpu.EFLAGS.ZF==0&&cpu.EFLAGS.SF==cpu.EFLAGS.OF)
	{ if(rel>>length==1)
          { rel = ~rel + 1;
            cpu.eip -= rel;
          }
          else 
            cpu.eip += rel;
	  if(DATA_BYTE==2)
		  cpu.eip = cpu.eip & 0xffff;
	}
        if(DATA_BYTE==1)
	   { 
             print_asm("jg" " 0x%x",cpu.eip + 1 + DATA_BYTE);
             return 1 + DATA_BYTE;  }
        else 
           { 
             print_asm("jg" " 0x%x",cpu.eip + 1 + 1 + DATA_BYTE);
             return 1 + 1 + DATA_BYTE;   }     
}


make_helper(concat(JCC_GorE_,SUFFIX)) {
	DATA_TYPE rel;
	if(DATA_BYTE==1)
	  rel = instr_fetch(eip + 1,DATA_BYTE);
        else 
          rel = instr_fetch(eip + 1 + 1,DATA_BYTE);
	if(cpu.EFLAGS.SF==cpu.EFLAGS.OF)
	{ if(rel>>length==1)
          { rel = ~rel + 1;
            cpu.eip -= rel;
          }
          else 
            cpu.eip += rel;
	  if(DATA_BYTE==2)
		  cpu.eip = cpu.eip & 0xffff;
	}
        if(DATA_BYTE==1)
	   {
             print_asm("jge" " 0x%x",cpu.eip + 1 + DATA_BYTE);
             return 1 + DATA_BYTE;   }
        else 
           {
             print_asm("jge" " 0x%x",cpu.eip + 1 + 1 + DATA_BYTE);
             return 1 + 1 + DATA_BYTE;   }       
}


make_helper(concat(JCC_L_,SUFFIX)) {
	DATA_TYPE rel;
	if(DATA_BYTE==1)
	  rel = instr_fetch(eip + 1,DATA_BYTE);
        else 
          rel = instr_fetch(eip + 1 + 1,DATA_BYTE);
	if(cpu.EFLAGS.SF!=cpu.EFLAGS.OF)
	{ if(rel>>length==1)
          { rel = ~rel + 1;
            cpu.eip -= rel;
          }
          else 
            cpu.eip += rel;
	  if(DATA_BYTE==2)
		  cpu.eip = cpu.eip & 0xffff;
	}
        if(DATA_BYTE==1)
	   {
             print_asm("jl" " 0x%x",cpu.eip + 1 + DATA_BYTE);
            return 1 + DATA_BYTE;    }
        else 
           { 
             print_asm("jl" " 0x%x",cpu.eip + 1 + 1 + DATA_BYTE);
             return 1 + 1 + DATA_BYTE;      }    
} 


make_helper(concat(JCC_LorE_,SUFFIX)) {
	DATA_TYPE rel;
	if(DATA_BYTE==1)
	  rel = instr_fetch(eip + 1,DATA_BYTE);
        else 
          rel = instr_fetch(eip + 1 + 1,DATA_BYTE); 
	if(cpu.EFLAGS.ZF==1||cpu.EFLAGS.SF!=cpu.EFLAGS.OF)
	{ if(rel>>length==1)
          { rel = ~rel + 1;
            cpu.eip -= rel;
          }
          else 
            cpu.eip += rel;
	  if(DATA_BYTE==2)
		  cpu.eip = cpu.eip & 0xffff;
	}
        if(DATA_BYTE==1)
	   { 
             print_asm("jle" " 0x%x",cpu.eip + 1 + DATA_BYTE);
             return 1 + DATA_BYTE;    }
        else 
           { 
             print_asm("jle" " 0x%x",cpu.eip + 1 + 1 + DATA_BYTE);
             return 1 + 1 + DATA_BYTE;     }    
} 


make_helper(concat(JCC_NA_,SUFFIX)) {
	DATA_TYPE rel;
	if(DATA_BYTE==1)
	  rel = instr_fetch(eip + 1,DATA_BYTE);
        else 
          rel = instr_fetch(eip + 1 + 1,DATA_BYTE); 
	if(cpu.EFLAGS.CF==1||cpu.EFLAGS.ZF==1)
	{ if(rel>>length==1)
          { rel = ~rel + 1;
            cpu.eip -= rel;
           }
          else 
            cpu.eip += rel;
	  if(DATA_BYTE==2)
		  cpu.eip = cpu.eip & 0xffff;
	 }
        if(DATA_BYTE==1)
	   {
             print_asm("jna" " 0x%x",cpu.eip + 1 + DATA_BYTE);
             return 1 + DATA_BYTE;   }
        else 
           {
             print_asm("jna" " 0x%x",cpu.eip + 1 + 1 + DATA_BYTE);
             return 1 + 1 + DATA_BYTE;    }   
}


make_helper(concat(JCC_NE_,SUFFIX)) {
	DATA_TYPE rel;
 	if(DATA_BYTE==1)
	  rel = instr_fetch(eip + 1,DATA_BYTE);
        else 
          rel = instr_fetch(eip + 1 + 1,DATA_BYTE);
    if(cpu.EFLAGS.ZF==0)
	{ if(rel>>length==1)
		{ rel = ~rel + 1;
		  cpu.eip -= rel;
		}
	  else 
		  cpu.eip += rel;
	  if(DATA_BYTE==2)
		  cpu.eip = cpu.eip & 0xffff;
	}
        if(DATA_BYTE==1)
	   { 
             print_asm("jne" " 0x%x",cpu.eip + 1 + DATA_BYTE);
             return 1 + DATA_BYTE;    }
        else 
           {  
             print_asm("jne" " 0x%x",cpu.eip + 1 + 1 + DATA_BYTE);
             return 1 + 1 + DATA_BYTE;   }      
}


make_helper(concat(JCC_NO_,SUFFIX)) {
	DATA_TYPE rel;
 	if(DATA_BYTE==1)
	  rel = instr_fetch(eip + 1,DATA_BYTE);
        else 
          rel = instr_fetch(eip + 1 + 1,DATA_BYTE);
    if(cpu.EFLAGS.OF==0)
	{ if(rel>>length==1)
		{ rel = ~rel + 1;
		  cpu.eip -= rel;
		}
	  else 
		  cpu.eip += rel;
	  if(DATA_BYTE==2)
		  cpu.eip = cpu.eip & 0xffff;
	}
        if(DATA_BYTE==1)
	   { 
             print_asm("jno" " 0x%x",cpu.eip + 1 + DATA_BYTE);
             return 1 + DATA_BYTE;    }
        else 
           {  
             print_asm("jno" " 0x%x",cpu.eip + 1 + 1 + DATA_BYTE);
             return 1 + 1 + DATA_BYTE;   }   
}


make_helper(concat(JCC_NP_,SUFFIX)) {
	DATA_TYPE rel;
 	if(DATA_BYTE==1)
	  rel = instr_fetch(eip + 1,DATA_BYTE);
        else 
          rel = instr_fetch(eip + 1 + 1,DATA_BYTE);
    if(cpu.EFLAGS.PF==0)
	{ if(rel>>length==1)
		{ rel = ~rel + 1;
		  cpu.eip -= rel;
		}
	  else 
		  cpu.eip += rel;
	  if(DATA_BYTE==2)
		  cpu.eip = cpu.eip & 0xffff;
	}
        if(DATA_BYTE==1)
	   { 
             print_asm("jnp" " 0x%x",cpu.eip + 1 + DATA_BYTE);
             return 1 + DATA_BYTE;    }
        else 
           {  
             print_asm("jnp" " 0x%x",cpu.eip + 1 + 1 + DATA_BYTE);
             return 1 + 1 + DATA_BYTE;    }   
}


make_helper(concat(JCC_NS_,SUFFIX)) {
	DATA_TYPE rel;
 	if(DATA_BYTE==1)
	  rel = instr_fetch(eip + 1,DATA_BYTE);
        else 
          rel = instr_fetch(eip + 1 + 1,DATA_BYTE);
    if(cpu.EFLAGS.SF==0)
	{ if(rel>>length==1)
		{ rel = ~rel + 1;
		  cpu.eip -= rel;
		}
	  else 
		  cpu.eip += rel;
	  if(DATA_BYTE==2)
		  cpu.eip = cpu.eip & 0xffff;
	}
        if(DATA_BYTE==1)
	   { 
             print_asm("jns" " 0x%x",cpu.eip + 1 + DATA_BYTE);
             return 1 + DATA_BYTE;   }
        else 
           { 
             print_asm("jns" " 0x%x",cpu.eip + 1 + 1 + DATA_BYTE);
             return 1 + 1 + DATA_BYTE;    }   
}


make_helper(concat(JCC_O_,SUFFIX)) {
	DATA_TYPE rel;
 	if(DATA_BYTE==1)
	  rel = instr_fetch(eip + 1,DATA_BYTE);
        else 
          rel = instr_fetch(eip + 1 + 1,DATA_BYTE);
    if(cpu.EFLAGS.OF==1)
	{ if(rel>>length==1)
		{ rel = ~rel + 1;
		  cpu.eip -= rel;
		}
	  else 
		  cpu.eip += rel;
	  if(DATA_BYTE==2)
		  cpu.eip = cpu.eip & 0xffff;
	}
        if(DATA_BYTE==1)
	   { 
             print_asm("jo" " 0x%x",cpu.eip + 1 + DATA_BYTE);
             return 1 + DATA_BYTE;   }
        else 
           {  
             print_asm("jo" " 0x%x",cpu.eip + 1 + 1 + DATA_BYTE);
             return 1 + 1 + DATA_BYTE;  }   
}


make_helper(concat(JCC_P_,SUFFIX)) {
	DATA_TYPE rel;
 	if(DATA_BYTE==1)
	  rel = instr_fetch(eip + 1,DATA_BYTE);
        else 
          rel = instr_fetch(eip + 1 + 1,DATA_BYTE);
    if(cpu.EFLAGS.PF==1)
	{ if(rel>>length==1)
		{ rel = ~rel + 1;
		  cpu.eip -= rel;
		}
	  else 
		  cpu.eip += rel;
	  if(DATA_BYTE==2)
		  cpu.eip = cpu.eip & 0xffff;
	}
        if(DATA_BYTE==1)
	   { 
             print_asm("jp" " 0x%x",cpu.eip + 1 + DATA_BYTE);
             return 1 + DATA_BYTE;  }
        else 
           {  
             print_asm("jp" " 0x%x",cpu.eip + 1 + 1 + DATA_BYTE);
             return 1 + 1 + DATA_BYTE;  }   
}


make_helper(concat(JCC_S_,SUFFIX)) {
	DATA_TYPE rel;
 	if(DATA_BYTE==1)
	  rel = instr_fetch(eip + 1,DATA_BYTE);
        else 
          rel = instr_fetch(eip + 1 + 1,DATA_BYTE);
    if(cpu.EFLAGS.SF==1)
	{ if(rel>>length==1)
		{ rel = ~rel + 1;
		  cpu.eip -= rel;
		}
	  else 
		  cpu.eip += rel;
	  if(DATA_BYTE==2)
		  cpu.eip = cpu.eip & 0xffff;
	}
        if(DATA_BYTE==1)
	   { 
             print_asm("js" " 0x%x",cpu.eip + 1 + DATA_BYTE);
              return 1 + DATA_BYTE;  }
        else 
           { print_asm("js" " 0x%x",cpu.eip + 1 + 1 + DATA_BYTE);
             return 1 + 1 + DATA_BYTE;   }   
}
#include "exec/template-end.h"
