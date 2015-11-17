Karina Banda
CSC 173
C Week 3/4
10/11/2015

char_classes.c // gives the ASCII key for a given element
char_classes.h //interface for char_classes.c
main.c //runs program
input.txt //example of what my calculator accepts
parser.c //parses, contains my CFG and evaluates within an implicit parse tree
reader.c //reads the input file
scanner.c// contains my DFA for the tokenizer


My program only accepts unary operators if they are enclosed within parenthesis. 
For extra credit I have used GitHub and have error handling for elements that are invalid
such as (---) or (+-+) in the tokenizer and also in the parse tree if it does follow the 
grammar. 

to run:
make
 ./calculator input.txt > output.txt
 or
  ./calculator input.tx