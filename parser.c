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
	}
}


void all(){
	printf("\nToken:%u",tok.tc);
}

void expr(){
}

void tmore(){
}

void term(){
}

void umore(){
}

static void unit(){
}

static void una(){
}

static void op2(){
}

static void op1(){
}

