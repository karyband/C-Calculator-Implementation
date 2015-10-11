/**********************************************************************
    Java parser and pretty-printer.

    Uses a recursive-descent parser that accepts a superset of the
    language.

    At the moment it's an unreasonably large superset: basically any
    string of tokens with balanced curvy braces is accepted inside a
    class definition.  You have to fix that by fleshing out the routines
    that parse a compound_stmt.  You also have to
        - find all declared identifiers, so you can print them red
        - indent things appropriately
        - fix inter-token spaces

 **********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "reader.h"
#include "scanner.h"
#include "parser.h"
#include <math.h>

static token_t     tok;
static location_t  loc;
//need to keep track if all the values are ints, if they are then I need to convert the final answer to int
static int only_ints=1; //1 for true, 0 for false

/* forward declarations: */





/********
    Print current token.  Precede with appropriate space.
 ********/
static void put_token()
{
    
}

/********
    Get next token from the scanner.  Filter out white space, comments,
    and newlines.

 ********/
 
 
static void get_token()
{
	scan(&loc,&tok);
//	printf("\nToken:%u",tok.tc);
//	printf("\n");
}

/********
    A parse error has occurred.  Print error message and halt.
 ********/
static void parse_error()
{
    fprintf(stderr, "Syntax error");
    fprintf(stderr, " at line %d, column %d\n",
        tok.location.line->line_num, tok.location.column);
    exit(1);
}

/********
    A token of class tc is expected from the scanner.  Verify and print.
 ********/
static void match(token_class tc)
{

}

/********
    Scan source, identify structure, and print appropriately.
 ********/
void parse()
{
    set_to_beginning(&loc);
    get_token();
    s();


}

void s(){
	//if the token is any of the tokens in the predict set of S->ALL; send to S
	switch(tok.tc){
		case T_LPAREN:
		case T_NUM:
		case T_DEC:
		case T_PLUS:
		case T_MINUS:
			printf("\nToken:%u",tok.tc);
			printf("S\n");
			all();
			break;
		//if end of equation
		case T_SEMI:
			break;
			
		 //if it gets here then it is an invalid token for the calculator 
		default:
    		parse_error();
    		exit(1);
    		break;
	}
	
	
}


void all(){
	switch(tok.tc){
		//end of equation, ALL->E (E for epsilon)
		case T_SEMI:
			break;
		//valid chars All->EXPR ALL
		case T_LPAREN:
		case T_NUM:
		case T_DEC:
		case T_PLUS:
		case T_MINUS:
		printf("\nToken:%u",tok.tc);
			printf("All\n");
			expr();
			all();
			break;
		//if it gets here then it is an invalid token for the calculator 
		default:
    		parse_error();
    		exit(1);
    		break;
	}
}

void expr(){
	switch(tok.tc){
		//end of equation,
		case T_SEMI:
			break;
		//valid chars
		case T_LPAREN:
		case T_NUM:
		case T_DEC:
		case T_PLUS:
		case T_MINUS:
		printf("\nToken:%u",tok.tc);
		printf("expr\n");
			//get the value
			float term_float=term();
			//sent it into tmore so that it can get evaluated with what comes next
			float expr=tmore(term_float);
			printf("EXPRE NUM: %f",expr);
			break;
		//if it gets here then it is an invalid token for the calculator 
		default:
    		parse_error();
    		exit(1);
    		break;
	}


}

float term(){
	float temp=0;

	switch(tok.tc){
		//Term->E 
		case T_PLUS:
		case T_MINUS:
		case T_SEMI:
			break;
		//valid chars, TERM->UNIT UMORE
		case T_LPAREN:
		case T_NUM:
		case T_DEC:
			temp=unit();			
			temp=umore(temp);
			break;
		//if it gets here then it is an invalid token for the calculator 
		default:
    		parse_error();
    		exit(1);
	}
	
	
	return temp;

}

float tmore(float x){
	float tmore_float;
	float term_right;

	switch(tok.tc){
		//TMORE->E
		case T_LPAREN:
		case T_NUM:
		case T_DEC:
		case T_SEMI:
			return x;
			break;
		//TMORE_>OP2 TERM TMORE
		case T_PLUS:
			op2();
			//get value that comes after the plus
			term_right=term();
			//evaluate with what came before the operator 
			tmore_float=x+term_right;
			tmore_float=tmore(tmore_float);
			break;
		case T_MINUS:
			op2();
			//get value that comes after the minus
			term_right=term();
			//evaluate with what came before the operator 
			tmore_float=x-term_right;
			tmore_float=tmore(tmore_float);
			break;
		default:
			printf("tmore");
    		parse_error();
    		exit(1);
    		break;
	}
	
	return tmore_float;
}

float unit(){
float temp;

	switch(tok.tc){
		//UNIT->NUM
		case T_DEC:
			//to keep track if it contains a decimal and no need to convert the final answer to an int
			only_ints=0;
		case T_NUM:
			temp=tok.float_value;
			/*************************************************************** return number */
			get_token(); //move it to the next token
			return(temp);
			break;
		//UNIT->(UNA EXPR UNA) 
		case T_LPAREN:
			get_token(); //get the next token
			una();
			expr();
			una();
			//if theres no closing parenthesis
			if(tok.tc!=T_RPAREN){
			parse_error();
    		exit(1);
    		}
    		break;
		default:
			printf("unit");
    		parse_error();
    		exit(1);
	}
}

float umore(float x){
float tempmore;
float new;
	switch(tok.tc){
		//UMORE->E
		case T_PLUS:
		case T_MINUS:
		case T_SEMI:
			return x;
			break;
		//UMORE->OP1 UNIT UMORE
		case T_MULT:
			op1();
			tempmore=unit();
			//multiply the right side of the * with what was on the left and brought over from within term (for order of operations)
			new=x*tempmore;
			printf("ANSWER %f",new);
			printf("\nToken:%u",tok.tc);
			new=umore(new);
			break;
		case T_DIV:
			op1();
			tempmore=unit();
			//divid the right side of the / with what was on the left and brought over from within term
			new=x/tempmore;
			printf("ANSWER %f",new);
			printf("\nToken:%u",tok.tc);
			new=umore(new);
			break;
		case T_MOD:
			op1();
			
			//need to convert the floats into ints for %
			int tempmore_int=(int)malloc(sizeof(int));
			int x_to_int=(int)malloc(sizeof(int));
			int new_int=(int)malloc(sizeof(int));
			
			tempmore_int=(int)unit();
			x_to_int=(int) x;
			
			//mod the right side of the % with what is on the left and brought over from within term
			new_int=x_to_int%tempmore_int;
			new=(float)new_int;
			printf("ANSWER %d",new_int);
			printf("\nToken:%u",tok.tc);
			new=umore(new_int);
			break;
		default:
			printf("umore");
    		parse_error();
    		exit(1);
    		
	}
	
	return new;
	
}


void una(){
	switch(tok.tc){
		//UNA->E
		case T_LPAREN:
		case T_RPAREN:
		case T_NUM:
		case T_PLUS:
		case T_MINUS:
			break;
		//UNA->--
		case T_DECRE:
		/*************************************************** decrement */
			break;
		//UNA->++
		case T_INCRE:
		/*************************************************** increment */
			break;
		default:
    		parse_error();
    		exit(1);
	}
	
}

void op2(){
	switch(tok.tc){
		//OP2->-
		case T_MINUS:
			printf("minus");
			get_token();
			break;
		//OP2->++
		case T_PLUS:
			printf("add");
			get_token();
			break;
		default:
    		parse_error();
    		exit(1);
	}
}

void op1(){
	switch(tok.tc){
		//OP1->*
		case T_MULT:
			printf("mult");
			get_token();
			break;
		//OP2->/
		case T_DIV:
			printf("div");
			get_token();
			break;
		case T_MOD:
			printf("mod");
			get_token();
			break;
		default:
    		parse_error();
    		exit(1);
	}
}

