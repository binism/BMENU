#include "common.h"
#include "cpu/reg.h"
#include "memory.h" 
/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

void load_table();
extern int val_SYMBOL(char *SYMBOL);

enum {
	NOTYPE = 256, plus='+', sub='-', mult='*', div='/',mod='%', l='(', r=')',EQ=0,NEQ,LESS,MORE,LESSEQ,MOREEQ, NUM, HNUM,REG,OR,AND,BOR,BXOR,BAND,LSFT,RSFT,NON,BANG,MENR,NEG,SYMBOL
	/* TODO: Add more token types */

}; 

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */
     {"0[Xx][[:xdigit:]]+", HNUM}, 
    {"[[:alpha:]][[:alpha:][:digit:]_]*",SYMBOL}, 	
	{"\\$[a-z]{2,3}", REG},			
	/*{,HNUM}*/
	{"[0-9]+", NUM},
	{" +", NOTYPE},			
	{">=",MOREEQ},					
	{"<=",LESSEQ},
    {"\\*", '*'},
	{"\\/", '/'},					
	{"\\+", '+'},					// plus
	{"\\-", '-'},
	{"\\(", '('},
	{"\\)", ')'},
	{"\\^",BXOR},					
	{"<",LESS},
    {"\\|{2}",OR},						
	{"\\&{2}",AND},					
	{"\\&",BAND},
	{"\\|",BOR},
	{"\\%",'%'},
	{"\\~",NON},
	{"\\!",BANG},	
	{">",MORE},  					
	{"<<",LSFT},					
	{">>",RSFT},
	{"==", EQ},						// equal
	{"!=",NEQ}
    
    //{"^[a-zA-Z_][a-zA-Z0-9_]*$",SYMBOL}
	/*{"\\^",BXOR},
	{"<<",LSFT},
	{">>",RSFT},
	{"!=",NEQ},
	{">=",MOREEQ},
	{"<=",LESSEQ},
	{">",MORE},
	{"<",LESS},
	{"\\|{2}",OR},
	{"\\&{2}",AND},
    {"\\&",BAND},
	{"\\|",BOR},
	{"\\%",PERC},
	{"\\~",NOT},
	{"\\!",BANG}
 */	 			
     
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for more mults.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			test(0, "regex compilation failed: %s\n%s\n", error_msg, rules[i].regex);
		}
	}
}

typedef struct token {
	int type;
        int order;
	char str[32];
} Token;

Token tokens[32];
int nr_token;

static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	
	nr_token = 0;

	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;
			//	Log("match regex[%d] at position %d with len %d: %.*s", i, position, substr_len, substr_len, substr_start);
				assert(substr_len);
				position += substr_len;
				int j;

				/* TODO: Now a new token is recognized with rules[i]. 
				 * Add codes to perform some actions with this token.
 				 */
 				switch(rules[i].token_type) {
					
							
					case NUM: 
							for(j=0;j<substr_len;j++){
								tokens[nr_token].str[j]=substr_start[j];
 							}
							tokens[nr_token].str[j]='\0';
							tokens[nr_token].type=NUM;
							nr_token++;
							break;
					case MENR: 
							tokens[nr_token].type=MENR;
							nr_token++;
							break; 
                                        case NEQ:
						tokens[nr_token].type=NEQ;
						nr_token++;
						break;
					case LESS:
						tokens[nr_token].type=LESS;
						nr_token++;
						break;
					case MORE:
						tokens[nr_token].type=MORE;
						nr_token++;
						break;
					case MOREEQ:
						tokens[nr_token].type=MOREEQ;
						nr_token++;
						break;
                    case REG:
 							for(j=1;j<substr_len;j++){
								tokens[nr_token].str[j-1]=substr_start[j];
							}
							tokens[nr_token].str[j-1]='\0';
							tokens[nr_token].type=REG;
							nr_token++;
							break;		
					
					case '+':
						tokens[nr_token].type='+';
						nr_token++;
						break;
					case '-':
						tokens[nr_token].type='-';
						nr_token++;
						break;
                    case HNUM:
					 		for(j=0;j<substr_len;j++){
								tokens[nr_token].str[j]=substr_start[j];
							}
							tokens[nr_token].str[j]='\0';
							tokens[nr_token].type=HNUM;
							nr_token++;
							break;
					case '*':
						tokens[nr_token].type='*';
						nr_token++;
						break;
                                        case LESSEQ:
						tokens[nr_token].type=LESSEQ;
						nr_token++;
						break;
					case '/':
						tokens[nr_token].type='/';
						nr_token++;
						break;
                                       
					case '(':
						tokens[nr_token].type='(';
						nr_token++;
						break;
					case ')':
						tokens[nr_token].type=')';
						nr_token++;
						break;
					case EQ:
						tokens[nr_token].type=EQ;
						nr_token++;
						break;
					case OR:
						tokens[nr_token].type=OR;
						nr_token++;
						break;
					case AND:
						tokens[nr_token].type=AND;
						nr_token++;
						break;
					case BOR:
						tokens[nr_token].type=BOR;
						nr_token++;
						break;
					case BXOR:
						tokens[nr_token].type=BXOR;
						nr_token++;
						break;
					case BAND:
						tokens[nr_token].type=BAND;
						nr_token++;
						break;
					case LSFT:
						tokens[nr_token].type=LSFT;
						nr_token++;
						break;
					case RSFT:
						tokens[nr_token].type=RSFT;
						nr_token++;
						break;
					case '%':
						tokens[nr_token].type='%';
						nr_token++;
						break;
					case NON:
						tokens[nr_token].type=NON;
						nr_token++;
						break;
					case BANG:
						tokens[nr_token].type=BANG;
						nr_token++;
						break;
				    case SYMBOL:
						for(j=0;j<substr_len;j++) {
							tokens[nr_token].str[j]=substr_start[j];
						}
						tokens[nr_token].str[j]='\0';
						tokens[nr_token].type=SYMBOL;
						nr_token++;
						break;
                    case NOTYPE: break;
					default: assert(0);
				}
				
				break;
 			}
 		}

		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
 	}
	return true; 
}
static bool check_parentheses(int p,int q){
	int l=0,r=0,i=p;
	while(i<=q){
		if(tokens[i].type=='(')
			l++;
		else if(tokens[i].type==')')
			r++;
		if(r>l){
			printf("Brackets do not match!\n");
			assert(0);
		}
		i++;
	}
	if(r<l){
		printf("Brackets do not match!\n");
		assert(0);
	}
	else if(r==l){
		if(tokens[p].type=='('&&tokens[q].type==')')
			return true;
	}
	return false;
}
static int getint(int p){
	int x=0;
	sscanf(tokens[p].str,"%d",&x);
	return x;
}
static int getint_x(int p){
	int x=0;
	sscanf(tokens[p].str,"%x",&x);
	return x;
}
static int getint_reg(int p){
	int i;
	for(i=1;i<=8;i++){
		if(strcmp(tokens[p].str,regsl[i])==0)
			return reg_l(i);
	}
	for(i=1;i<=8;i++){
		if(strcmp(tokens[p].str,regsw[i])==0)
			return reg_w(i);
	}
	for(i=1;i<=8;i++){
		if(strcmp(tokens[p].str,regsb[i])==0)
			return reg_b(i);
	} 
	printf("Wrong reg name!\n");
	assert(0);
        return 0;
	
}

const int top=10000;

static int domin_op(int p,int q){
	int basic=0,i=p,j=0;
	for(;j<32;j++)
		tokens[j].order=top;
	while(i<=q){
		if(tokens[i].type == '+'||tokens[i].type == '-')
			tokens[i].order=basic+9;
		else if(tokens[i].type =='*'||tokens[i].type =='/'||tokens[i].type =='%')
			tokens[i].order=basic+10;
		else if(tokens[i].type ==NEG||tokens[i].type ==NON||tokens[i].type ==BANG||tokens[i].type ==MENR)
			tokens[i].order=basic+11;
		else if(tokens[i].type == LSFT||tokens[i].type == RSFT)
			tokens[i].order=basic+8;
		else if(tokens[i].type ==LESS||tokens[i].type ==MORE||tokens[i].type ==LESSEQ||tokens[i].type ==MOREEQ)
			tokens[i].order=basic+7;
		else if(tokens[i].type ==EQ||tokens[i].type ==NEQ)
			tokens[i].order=basic+6;
		else if(tokens[i].type ==BAND)
			tokens[i].order=basic+5;
		else if(tokens[i].type ==BXOR)
			tokens[i].order=basic+4;
		else if(tokens[i].type ==BOR)
			tokens[i].order=basic+3;
		else if(tokens[i].type ==AND)
			tokens[i].order=basic+2;
		else if(tokens[i].type ==OR)
			tokens[i].order=basic+1;
		else if(tokens[i].type =='('){
			basic+=12;
		}
		else if(tokens[i].type ==')')
			basic-=12;
		i++;
	}
	i=p;
	int min=p;
	while(i<=q){
		if(tokens[min].order%12==11){
			if(tokens[i].order<=tokens[min].order)
				min=i;
		}
		else{
			if(tokens[i].order<tokens[min].order)
				min=i;
		}
		i++;
	}
	return min;
}
static int eval(int p,int q){
	fflush(stdout);
	if(p>q){
		if((q==p-1)&&(tokens[p].type==BANG||tokens[p].type==NEG||tokens[p].type==NON||tokens[p].type==MENR)){
			return 0;
		}
		else
			printf("Bad expression!\n");
			assert(0);
	}
	else if(p==q){
	/*	if(tokens[p].type==NUM)
			return getint(p);
		else if(tokens[p].type==HNUM)
			return getint_x(p);
		else if(tokens[p].type==REG) 
			return getint_reg(p);
		else if(tokens[p].type==SYMBOL)
			return val_SYMBOL(tokens[p].str);
		else 
			assert(0);*/
		switch (tokens[p].type) {
			case NUM: return getint(p);
			case HNUM: return getint_x(p);
		    case REG: return getint_reg(p);
		    case SYMBOL: return val_SYMBOL(tokens[p].str);
			default: assert(0);
		}
	}
	
	else if(check_parentheses(p,q)==true) {
		return eval(p+1,q-1);
	}
	else{
		int op=domin_op(p,q);
		int val1=eval(p,op-1);
		int val2=eval(op+1,q);
	 	switch(tokens[op].type){
			case '+':return val1+val2;
			case '-':return val1-val2;
			case '*':return val1*val2;
			case '/':return val1/val2;
			case '%':return val1%val2;	
			case LSFT:return val1<<val2;
			case MORE:return val1>val2;
			case LESSEQ:return val1<=val2;
                        case EQ:return val1==val2;
                        case BOR:return val1|val2;
			case BAND:return val1&val2;
			case BXOR:return val1^val2;
                        case RSFT:return val1>>val2;
			case NEQ:return val1!=val2;
			case LESS:return val1<val2;
			case MOREEQ:return val1>=val2;
			case OR:return val1||val2;
			case AND:return val1&&val2;
			case NEG:return -val2;
			case BANG:return !val2;
			case NON:return ~val2;
			case MENR:return swaddr_read(val2,4);
		    case SYMBOL: return val_SYMBOL(tokens[op-1].str);
			default:assert(0);
		}
	}
}

uint32_t expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	} 
	int i;
	for(i=0;i<nr_token;i++){
		if(tokens[i].type=='-'&&(i==0||tokens[i-1].type==NEG||tokens[i-1].type=='+'||tokens[i-1].type=='-'||tokens[i-1].type=='*'||tokens[i-1].type=='/'||tokens[i-1].type=='(')){
			tokens[i].type=NEG;
	 	}
	} 
	for(i=0;i<nr_token;i++){
		if(tokens[i].type=='*'&&(i==0||tokens[i-1].type=='*'||tokens[i-1].type=='+'||tokens[i-1].type=='-'||tokens[i-1].type=='('||tokens[i-1].type=='/')){
			tokens[i].type=MENR;
		}
	}
	uint32_t p=0,q=nr_token-1;
	uint32_t val=eval(p,q);

	/* TODO: Implement code to evaluate the expression. */
	return val;
}

