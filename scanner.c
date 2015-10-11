/**********************************************************************
    Tokenizer for Java source.

    Accepts all the tokens in the alphabet of my language: (,),;,+,-,*,/%,(++),(--),(-), any number (int or float)
    using the DFA that I have described in Writeup.pdf in detail. 
    
    It skips over blank space and new lines until it finds a token within my language's alphabet. 
    

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
	char *theres_num=malloc(1); //going to be concatenating, start by allocating space for one num
	int theres_num_size=0;
    enum {
            start,
            /*numbers*/
            got_int,
            got_dec, //decimals
            /* + and - */
            got_plus ,
            got_minus,
            /* increment or decrement */
            //left parenthesis
            got_paren,
            got_pos_una, //positive unary
            got_neg_una, //negative unary
            got_incre, //(++)
            got_decre,//(--)
            /*any other char thats not valid*/
            got_other,
            done
    } state = start;

/* Standard way to recognize a token: put back lookahead character that
    isn't part of current token: */
#define ACCEPT_REUSE(t) \
	if(t==T_NUM){ \
	tok->float_value= atof(theres_num);	\
    tok->int_value=(int)malloc(sizeof(int));  \
    tok->int_value=atoi(theres_num);} \
    if(t==T_DEC){ \
    tok->float_value= atof(theres_num);} \
    *loc = loc_save;    \
    tok->length--;      \
    tok->tc = t;        \
    state = done;

/* Shortcut to eliminate final states with no out transitions: go
    ahead and accept token in previous state, but don't put back the
    lookahead: it's actually part of the token: */
#define ACCEPT(t) \
    tok->tc = t;  \
    if(t==T_NUM){ \
    tok->int_value=(int)malloc(sizeof(int));  \
    tok->int_value=atoi(theres_num);} \
    state = done;


    tok->location = *loc;
    tok->length = -1;

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
                        printf("%c",c);
                        /*set first char of theres_num and increment the char array position count*/
                        theres_num[theres_num_size++]=c; 
                        //exit(1);
                        /*make theres_num bigger by 1 in case the next input will add on to the digit*/
                        theres_num=realloc(theres_num,theres_num_size+1); 
                        break;          
                        
                    case PLUS:
                    	printf("+");
                        ACCEPT(T_PLUS);
                        break;
                    case MINUS:
                    	printf("-");
                        ACCEPT(T_MINUS);
                        break;

                    case STAR:
                    	printf("*");
                        ACCEPT(T_MULT);
                        break;
                    case PCT:
                    	printf("%%");
                    	ACCEPT(T_MOD);
                    	break;
                    case LPAREN:
                        state=got_paren;
                        break;
                    case RPAREN:
                    	printf(")");
                        ACCEPT(T_RPAREN);
                        break;
                    case SEMIC:
                    	printf(";");
                        ACCEPT(T_SEMI);
                        break;
                    case SLASH:
                    	printf("/");
                        ACCEPT(T_DIV);
                        break;
                    case END:
                        ACCEPT_REUSE(T_EOF);
                        break;
                    default:
                        ACCEPT(T_THROWS);//for error
                        break;
			}
			
				break;
			
			case got_paren:
                switch (char_classes[c]) {
                	case PLUS:
                		//its a positive unary 
                        state = got_pos_una;                          
                        break;
                   case MINUS:
                   		//its a negative unary
                   		state = got_neg_una;
                        break;
                    default:
                    	//if ( is not followed by + or -, then its just a left parenthesis for order of operations
                    	printf("(");
                    	ACCEPT_REUSE(T_LPAREN);
                    	break;
                }
                break;
                
            
            case got_pos_una:
                switch (char_classes[c]) {
                	case PLUS:
                		//its a positive unary 
                        state = got_incre;                          
                        break;
                   case RPAREN:
                   		//(+), just eat it up since it doesnt have an effect
                   		ACCEPT(T_EOF);
                        break;
                    default:
                    	//anything else is invalid
                    	printf("\nInvalid unary combination.");
                    	ACCEPT(T_THROWS);
                    	break;
                }
                break;
                
            case got_incre:
                switch (char_classes[c]) {
                   case RPAREN:
                   		//end of positive unary, accept the increment token
                   		printf("(++)");
                   		ACCEPT(T_INCRE);
                        break;
                    default:
                    	//anything else is invalid
                    	printf("\nInvalid unary combination.");
                    	ACCEPT(T_THROWS);
                    	break;
                }
                break;
                
                
                
            case got_neg_una:
                switch (char_classes[c]) {
                	case RPAREN:
                		//its a negative
                		printf("(-)");
                        ACCEPT(T_NEG);                         
                        break;
                   case MINUS:
                   		//then its (--)
                   		state=got_decre;
                        break;
                    default:
                    	//anything else is invalid
                    	printf("Invalid unary combination.");
                    	ACCEPT(T_THROWS);
                    	break;
                }
                break;
                
            case got_decre:
                switch (char_classes[c]) {
                	case RPAREN:
                		//its a decrement
                		printf("(--)");
                        ACCEPT(T_DECRE);                         
                        break;
                    default:
                    	//anything else is invalid
                    	printf("Invalid unary combination");
                    	ACCEPT(T_THROWS);
                    	break;
                }
                break;
                
			case got_int:
                switch (char_classes[c]) {
                	case DOT:
                        state = got_dec;         
                        theres_num[theres_num_size++]=c;  
                        printf("%c",c);                  
                        break;
                    CASE_ANY_DIGIT: //concatenate to the digit(s) scanned prior      
                        theres_num[theres_num_size++]=c;                  
                        printf("%c",c);  
                    	theres_num=realloc(theres_num,theres_num_size+1);
                        break;
                    default:
                    	ACCEPT_REUSE(T_NUM);
                    	break;
                }
                break;
            
            case got_dec:
                switch (char_classes[c]) {
                	CASE_ANY_DIGIT: //add on to the decimal number
                		printf("%c",c);
                        theres_num[theres_num_size++]=c;       
                        printf("%c",c);             
                    	theres_num=realloc(theres_num,theres_num_size+1);
                        break;
                    default:
                    	ACCEPT_REUSE(T_DEC);  
                    	break;       	
                }
                break;
                
          /*  case got_plus:
                switch (char_classes[c]) {
                	case PLUS: //its an increment   
                		printf("+");   
						ACCEPT(T_INCRE);
                        break;
                    default: 
                    	ACCEPT_REUSE(T_PLUS);  //just a plus
                    	break;       	
                }
                break;
            
            case got_minus:
                switch (char_classes[c]) {
                	case MINUS: //its an increment      
						ACCEPT(T_DECRE);
                        break;
                    default: 
                    	ACCEPT_REUSE(T_MINUS);  //just a plus
                    	break;       	
                }
                break;*/
        	
		}
		
			
       
    }
}


