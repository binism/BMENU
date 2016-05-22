#include "ui/breakpoint.h"

#include "nemu.h"

#define NR_BP 32

static BP bp_pool[NR_BP];
static BP *head, *free_;

void init_bp_pool() {
	int i;
	for(i = 0; i < NR_BP  - 1; i ++) {
		bp_pool[i].NO = i;
		bp_pool[i].next = &bp_pool[i + 1];

	}
	bp_pool[i].NO=i;
	bp_pool[i].next = NULL;

	head = NULL;
	free_ = bp_pool;
}

void new_bp(uint32_t bp_addr,uint8_t firstbyte)
{  if (free_->next==NULL)
	{
     printf("Max number of breakpoints!.\n");
	 assert(0);
   }
 else
 {
	 BP *q=free_;
	 free_=free_->next;
	 q->next=NULL;
	 if (head==NULL)
	 {  head=q;
		 head->NO=0;
	 }
	 else
	 {   BP *p=head;
		 if (p->address==bp_addr)
		 {printf("The breakpoint you set has existed!\n");assert(0);} 
	 	 while (p->next!=NULL)
     	{ if (p->address==bp_addr)
			{printf("The breakpoint you set has existed!\n");assert(0);}
		  p=p->next;
     	}
		 int n=p->NO;
		 p->next=q;
		
		 q->NO=n+1;
     }
	 q->address=bp_addr;
	 q->firstbyte=firstbyte;
	 printf("Breakpoint %d at 0x%x;\n",q->NO,q->address);
  }
}
void free_all_bp()
{
	if (head==NULL)
	{ printf("No breakpoint up to now!\n"); assert(0);}
	while (head!=NULL)
	{  BP *p=head;
	   head=p->next;
       swaddr_write(p->address,1,p->firstbyte);
	   p->address=0;
	   p->firstbyte=0;
	   int n=p->NO;
	   p->next=free_;
	   free_=p;
	   int m=free_->NO;
	   p->NO=m+1;
	   free_->next=p;
	   free_=free_->next;
       printf("Delete breakpoint %d.\n",n);
	}
}
void free_bp(uint32_t bp_NO)
{
   if (head==NULL)
   {printf("No breakpoint up to now!\n"); assert(0);}
   else 
   { BP *p=head;
     int tmp=0;
	 if (bp_NO==0&&bp_NO==p->NO)
	 {    swaddr_write(p->address,1,p->firstbyte);
	      p->address=0;
	      p->firstbyte=0;
	      printf("Delete breakpoint %d.\n",bp_NO);
		  BP *q=free_;
	      BP *qq=q;
	      BP *ppp=p;
	      q=ppp;
	      head=p->next;
		   q->next=qq;
	 }
	 else
	 {
	 while (p->NO!=bp_NO)
	 {if (p->next==NULL) {printf("No breakpoint%u!\n",bp_NO);assert(0);}
		 p=p->next;
		 tmp++;
	 }
	 BP *pp=head;
	 int i=1;
	 while (i<tmp)
	 { pp=pp->next;
		 i++;
	 }
	 BP *ppp=pp->next;
	 swaddr_write(ppp->address,1,ppp->firstbyte);
	 ppp->address=0;
	 ppp->firstbyte=0;
	 printf("Delete breakpoint %d.\n",bp_NO);
	 pp->next=ppp->next;
	 BP *q=free_;
	 int tep=0;
	 while ((ppp->NO)+1!=(q->NO)&&q->next!=NULL  )
	 {q=q->next;
      tep++;
	 }
	 BP *qq=head;
	 int j=1;
	 while (j<tmp)
	 { qq=qq->next;
	   j++;
	 }
	 BP *qqq=qq->next;
	 qq->next=ppp;
     ppp->next=qqq;
   }
}
}
void print_info_b()
{
	BP *pp=head;
	if(pp==NULL)
	{printf("No breakpoint to print!\n"); return;	}
	while(pp!=NULL)
	{
	 printf("Breakpoint%d at 0x%x.\n",pp->NO,pp->address);
	pp=pp->next;
}
}
uint32_t find_bpaddr(uint32_t addr)
{  BP *pp=head;
	if(pp==NULL)
	{printf("No breakpoint up to new!\n"); assert(0);}
	while (addr!=pp->address)
	{if (pp==NULL)
	  { printf("There is no breakpoint at 0x%x!\n",addr); assert(0);}
		  pp=pp->next;
	}
    return pp->firstbyte;
}



/* TODO: Implement the function of breakpoint */
