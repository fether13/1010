/////////////////////////////////////////////////
/////////////////////////////////////////////////
#include "piece.h"
/////////////////////////////////////////////////
/////////////////////////////////////////////////
piece generatePiece();
int** generateMat(piece);
void rotateLShape(int**, int);
void printPiece(piece);
/////////////////////////////////////////////////
/////////////////////////////////////////////////
piece generate() {

    piece piece_1;
    piece_1 = generatePiece();
    return piece_1;
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
/*
TYPE:
    0 = line
    1 = square
    2 = L shape
ROTATION:
    90° counterclockwise * ROT (0 for squares, max 1 for lines, max 3 for L shapes)
SIZE:
    SIZE x SIZE (max 3) for squares and L shapes
    1 x SIZE oppure SIZE x 1 (max 5) for lines
*/
/////////////////////////////////////////////////
/////////////////////////////////////////////////
piece generatePiece() {

    piece out;
    out.type = rand()%3; //generate the type

    out.av = (coords*)malloc(sizeof(coords)); //available moves aren't determined yet
    out.placed = 0; //piece isn't placed when generated
    out.count = 0;

    switch (out.type) 
    {
    case 0: //line
        out.rot = rand()%2;
        out.size = (rand()%4)+2;
        switch (out.rot) 
        {
        case 0:
            out.dim.X = out.size;
            out.dim.Y = 1;
            break;
        
        case 1:
            out.dim.Y = out.size;
            out.dim.X = 1;
            break;
        }
        out.points = out.dim.X*out.dim.Y;
        break;
    
    case 1: //square
        out.rot = 0;
        out.size = (rand()%3)+1;
        out.dim.X = out.dim.Y = out.size;
        out.points = out.size*out.size;
        break;
    
    case 2: //L shape
        out.rot = rand()%4;
        out.size = (rand()%2)+2;
        out.dim.X = out.dim.Y = out.size;
        out.points = out.size + out.size-1;
        break;
    }
    out.mat = generateMat(out);
    return out;
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
int **generateMat(piece in) {
    int **arr = NULL;
    in.mat=arr;

    int rows=in.dim.Y;
    int cols=in.dim.X;

    //allocating the matrix
    arr = (int**)malloc(rows*sizeof(int*));
    for(int i=0; i<rows; i++)
        arr[i] = malloc(cols*sizeof(int));
    
    switch (in.type) {

    case 2: //if the piece is L shaped
        for(int i=0; i<in.size; i++) //create the L shape with 1's and the set rest to 0
            for (int j=0; j<in.size; j++)
                if (i==0 || j==0)
                    arr[i][j]=1;
                else
                    arr[i][j]=0;
        for(int i=0; i<in.rot; i++) //rotate according to the rot value
            rotateLShape(arr, in.dim.X);
        break;

    default: //if the piece is a line or a square
        for(int i=0; i<in.dim.Y; i++) //fill the entire matrix with 1's
            for (int j=0; j<in.dim.X; j++)
                arr[i][j]=1;
    }
    return arr;
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
void rotateLShape(int **arr, int len) {
    int m=len,n=len;
    int temp;

    for (int i = 0; i<m; i++)
        for (int j=i+1; j<n; j++) {
            temp = arr[i][j];
            arr[i][j] = arr[j][i];
            arr[j][i] = temp;
        }

    for (int i=0; i<m; i++)
        for (int j=0; j<n/2; j++) {
            temp = arr[i][j];
            arr[i][j] = arr[i][n-1-j];
            arr[i][n-1-j] = temp;
        }
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
void printPiece(piece in) {
    int **arr = in.mat;

    for(int i=0; i<in.dim.Y; i++, printf("\n")) {
        for(int j=0; j<in.dim.X; j++)
            printf("%d ", arr[i][j]);
    }
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////