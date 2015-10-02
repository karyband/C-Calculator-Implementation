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

    Print comments appropriately:
      - If comment is preceded by a newline in input, precede it with
        newline in output.  If an old-style comment is followed by a
        newline, add a newline to the output.  These are the ONLY places
        where the formatter pays attention to white space in the input.
      - if the comment is new style (// to eoln), follow with newline
        (scanner does not include newline in comment).
      - with both of the previous rules, if the parser also decides to
        generate a newline (e.g. for a semicolon), combine them so we
        don't generate an *extra* one.
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

}

