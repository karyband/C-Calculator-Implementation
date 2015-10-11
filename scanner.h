/**********************************************************************
    Tokenizer for Java source.
 **********************************************************************/

#ifndef SCANNER_H
#define SCANNER_H

#include "reader.h"



typedef enum {
	T_NUM,
	T_DEC,
	T_INCRE,
	T_DECRE,
	T_NEG,
	T_PLUS,
	T_MINUS,
	T_MULT,
	T_DIV,
	T_MOD,
	T_DOT,
	T_SEMI,
	T_LPAREN, 
	T_RPAREN,
    T_THROWS,
    T_EOF
    
} token_class;


typedef struct {
    token_class tc;
    location_t location;
    int int_value; //if its an int
    float float_value; //if its a decimal
    int length;     /* length of token in characters (may span lines) */
} token_t;

void scan(location_t * loc, token_t * tok);
    /* Modify tok to describe next token of input.
        Update loc to refer to location immediately after tok. */

#endif
