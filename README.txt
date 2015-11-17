Karina Banda
CSC 173
C Week 3/4 project
10/11/2015

C Calculator with Parser and Scanner Implementation - details on the implementation can be read in WRITEUP.PDF

FILES INCLUDED ARE:

char_classes.c // gives the ASCII key for a given element, supplied in the assignment’s given start files
char_classes.h //interface for char_classes.c, supplied in the assignment’s given start files but edited for this assignment
main.c //runs program,  supplied in the assignment’s given start files
input.txt //example of what my calculator accepts
parser.c //parses, contains my CFG and evaluates within an implicit parse tree
reader.c //reads the input file
scanner.c// contains my DFA for the tokenizer
MISSION.txt //prompt for this assignment
WRITEUP.pdf //details on how the program works
README.txt //This current file, includes an overview of files included in this repository


NOTE:
 
The way my program handles unary operators is it will accept them only if they are enclosed 
within parenthesis. For extra credit I have used GitHub and have error handling for elements 
that are invalid such as (---) or (+-+) in the tokenizer and also in the parse tree if it does 
follow the grammar. 

TO RUN:
make
 ./calculator input.txt > output.txt
 or
  ./calculator input.tx