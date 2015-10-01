/**********************************************************************
    Tokenizer for Java source.

    Allows unicode escapes only within strings and comments.  Otherwise,
    accepts all and only those tokens defined by the Java language
    specification.  (Note that this is significantly more than you were
    required to do for assignment 3; this solution would have received a
    lot of extra credit.)

    Tokens are classified as listed in scanner.h.

 **********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "reader.h"
#include "char_classes.h"
#include "scanner.h"

static void print_location (token_t *tok)
{
    fprintf(stderr, " at line %d, column %d\n",
        tok->location.line->line_num, tok->location.column);
}

/********
    Modify tok to describe next token of input.
    Update loc to refer to location immediately after tok.
 ********/
void scan(location_t * loc, token_t * tok)
{        
	str theres_num; //going to be concatenating

    enum {
            start,
            /*numbers*/
            got_int,
            got_dec, //decimals
            /* + and - */
            got_plus ,
            got_minus,
            /* increment or decrement */
            got_incre,
            got_decre,
            /* all other chars that are valid:*,/,.,(,),tab,and new line*/
            got_mult,
            got_div,
            got_mod,
            got_rparen,
            got_lparen,
            got_space,
            got_semi,
            got_tab,
            got_nl,
            /*any other char thats not valid*/
            got_other,
            done
    } state = start;

/* Standard way to recognize a token: put back lookahead character that
    isn't part of current token: */
#define ACCEPT_REUSE(t) \
    *loc = loc_save;    \
    tok->length--;      \
    tok->tc = t;        \
    state = done;

/* Shortcut to eliminate final states with no out transitions: go
    ahead and accept token in previous state, but don't put back the
    lookahead: it's actually part of the token: */
#define ACCEPT(t) \
    tok->tc = t;  \
    state = done;


    tok->location = *loc;
    tok->length = 0;

    while (state != done) {
        location_t loc_save = *loc;

        int c = get_character(loc);
        tok->length++;


                               
        switch (state) {
            case start:
                switch (char_classes[c]) {
                    case WHITE:
                        break; //just eat it up
                    case EOLN:
                        break; //just eat it up
                    case DOT:
                        state = got_dec;
                        break;
                    CASE_ANY_DIGIT:
                        state = got_int;
                        printf("got 0");
                        exit(1);
                        break;
                        
                        
                        /*
                    case PLUS:
                        state = got_plus;
                        break;
                    case MINUS:
                        state = got_minus;
                        break;
                    case EQUALS:
                        state = got_equals;
                        break;
                    case STAR:
                        state = got_star;
                        break;
                    case PCT:
                    	state = got_mod;
                    	break;
                    case LPAREN:
                        ACCEPT(T_LPAREN);
                        break;
                    case RPAREN:
                        ACCEPT(T_RPAREN);
                        break;
                    case SEMIC:
                        ACCEPT(T_SEMIC);
                        break;
                    case SLASH:
                        state = got_slash;
                        break;
                    case END:
                        ACCEPT_REUSE(T_EOF);
                        break;
                    case OTHER:
                        /* This will be an error.  Eat as many bogus
                            characters as possible. */
			}
		}
        
    }
}
