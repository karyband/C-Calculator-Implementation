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

float expr();
float tmore(float x);
float term();
float umore(float x);
float unit();
int una();
void op2();
void op1();

#endif
