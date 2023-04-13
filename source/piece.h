#include <stdio.h>
#include <stdlib.h>
#define LEN 10

struct coords_ {
    int X;
    int Y;
};
typedef struct coords_ coords;

struct piece_ {
    int type; //the shape of the piece (square, L, line)
    int size; //its size
    int rot; //its rotation
    int **mat; //pointer to the piece's matrix
    int placed; //tells if the piece has been placed
    int count; //size of av
    int points; //tells how many points the piece is worth
    coords dim; //the width and heigth of its matrix
    coords *av; //array with the available places
};
typedef struct piece_ piece;


//////////////////////////////
////////// FUNZIONI //////////
piece generate();
void print_board();
int place();