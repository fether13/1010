/////////////////////////////////////////////////
/////////////////////////////////////////////////
#include "piece.h"
/////////////////////////////////////////////////
/////////////////////////////////////////////////
void printp(piece, piece, piece);
/////////////////////////////////////////////////
/////////////////////////////////////////////////
void print_board(int board[LEN][LEN], piece p1, piece p2, piece p3, int score) {
    system("cls || clear");
    printf("\n________________________________\n\n");
    printf("Score: %d\n", score);
    printf("\n ");
    for(int i=0;  i<LEN; printf("  %d", i), i++);
    printf("\n");
    for(int i=0; i<LEN; i++, printf("\n")) {
        printf("%d ", i);
        for(int j=0; j<LEN; j++)
            if(board[i][j]==0)
                printf("[ ]");
            else
                printf("[#]");
    }
    printp(p1, p2, p3);
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
void printp(piece p1, piece p2, piece p3) { 
    //print the available pieces by merging them into a matrix
    int table[5][19] = {0};
    int i, j;
    int a, offset=0;
    int max_y;
    piece* pp1=&p1;
    piece* pp2=&p2; 
    piece* pp3=&p3;
    piece* arr[] = {pp1, pp2, pp3};
    
    //merge the matrices into table[][]
    for(a=0; a<3; a++) {
        if(a>0)
            offset = offset + arr[a-1]->dim.X + 2;
        if (arr[a]->placed==0) {
            if (arr[a]->type == 0) { //if it's a line fill a line
                if (arr[a]->rot==0)
                    for(i=0; i<arr[a]->size; i++)
                        table[0][offset+i]=1; //we use an offset for the second and third pieces
                else
                    for(i=0; i<arr[a]->size; i++)
                        table[i][offset]=1;
            }
            else { //if it's a square or an L shape just copy it onto the table
                for(i=0; i<arr[a]->size; i++)
                    for(j=0; j<arr[a]->size; j++)
                        table[i][j+offset]=arr[a]->mat[i][j];
            }
        }
    }

    //determine the max height to be printed
    for(i=0, max_y=0; i<3; i++)
        if (max_y<arr[i]->dim.Y && arr[i]->placed==0)
            max_y=arr[i]->dim.Y;

    //actually print the table
    printf("\n");
    for(i=0; i<max_y; i++) {
        for(j=0; j<19; j++) {
            if(table[i][j]==0)
                printf("   ");
            else
                printf("[#]");;
            if(j==18)
                printf("\n");
        }
    }
    printf("\n");
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
