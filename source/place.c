/////////////////////////////////////////////////
/////////////////////////////////////////////////
#include "piece.h"
/////////////////////////////////////////////////
/////////////////////////////////////////////////
int search(coords*, coords, int);
/////////////////////////////////////////////////
/////////////////////////////////////////////////
int place(int board[LEN][LEN], piece* p, coords pos) {

    if (pos.X<0 || pos.X>=LEN || pos.Y<0 || pos.Y>=LEN) //define some base cases
        return 0;

    int esito = search(p->av, pos, p->count);
    int i, j;

    if(esito==-1) //the coordinates are invalid, return 0
        return 0;

    else //the coordinates are valid, copy the piece onto the board
        for(i=0; i<p->dim.Y; i++)
            for(j=0; j<p->dim.X; j++)
                board[i+pos.Y][j+pos.X] = p->mat[i][j] + board[i+pos.Y][j+pos.X];
    p->placed=1;
    return 1;
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
int search(coords* coord, coords pos, int dim) {
    int i;
    for(i=0; i<dim; i++)
        if(coord[i].Y==pos.Y && coord[i].X==pos.X)
            return i;
    return -1;
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////