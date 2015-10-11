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

static token_t     tok;
static location_t  loc;


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
			all();
			break;
		//if end of equation
		case T_EOF:
			break;
			
		 //if it gets here then it is an invalid token for the calculator 
		default:
    		parse_error();
    		exit(1);
	}
}


void all(){
	switch(tok.tc){
		//end of equation, ALL->E (E for epsilon)
		case T_EOF:
			break;
		//valid chars All->EXPR ALL
		case T_LPAREN:
		case T_NUM:
		case T_DEC:
		case T_PLUS:
		case T_MINUS:
			expr();
			all();
			break;
		//if it gets here then it is an invalid token for the calculator 
		default:
    		parse_error();
    		exit(1);
	}
}

void expr(){
	switch(tok.tc){
		//end of equation,
		case T_EOF:
			break;
		//valid chars
		case T_LPAREN:
		case T_NUM:
		case T_DEC:
		case T_PLUS:
		case T_MINUS:
			term();
			tmore();
			break;
		//if it gets here then it is an invalid token for the calculator 
		default:
    		parse_error();
    		exit(1);
	}


}

void term(){

	switch(tok.tc){
		//Term->E 
		case T_PLUS:
		case T_MINUS:
		case T_EOF:
			break;
		//valid chars, TERM->UNIT UMORE
		case T_LPAREN:
		case T_NUM:
		case T_DEC:
			unit();
			umore();
			break;
		//if it gets here then it is an invalid token for the calculator 
		default:
    		parse_error();
    		exit(1);
	}

}

void tmore(){
	switch(tok.tc){
		//TMORE->E
		case T_LPAREN:
		case T_NUM:
		case T_EOF:
			break;
		//TMORE_>OP2 TERM TMORE
		case T_PLUS:
		case T_MINUS:
			op2();
			term();
			tmore();
		default:
    		parse_error();
    		exit(1);
	}
}

void unit(){
	switch(tok.tc){
		//UNIT->NUM
		case T_NUM:
		case T_DEC:
			/*************************************************************** return number */
			get_token; //move it to the next token
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
    		parse_error();
    		exit(1);
	}
}

void umore(){
	switch(tok.tc){
		//UMORE->E
		case T_PLUS:
		case T_MINUS:
		case T_EOF:
			break;
		//UMORE->OP1 UNIT UMORE
		case T_MULT:
		case T_DIV:
		case T_MOD:
			op1();
			unit();
			umore();
		default:
    		parse_error();
    		exit(1);
	}
	
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
		/*************************************************** minus */
			break;
		//OP2->++
		case T_PLUS:
		/*************************************************** plus */
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
		/*************************************************** multiply */
			break;
		//OP2->/
		case T_DIV:
		/*************************************************** divide */
			break;
		case T_MOD:
		/*************************************************** modolus */
			break;
		default:
    		parse_error();
    		exit(1);
	}
}

