/**********************************************************************
    Java parser and pretty-printer.
 **********************************************************************/

#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "reader.h"


void parse();
    /* Scan source, identify structure, and print appropriately. */

void s();

void all();

void expr();
void tmore();
void term();
void umore();
void unit();
void una();
void op2();
void op1();

#endif
