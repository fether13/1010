/////////////////////////////////////////////////
/////////////////////////////////////////////////
#include <time.h>
#include "piece.h"
/////////////////////////////////////////////////
/////////////////////////////////////////////////
void available(piece*, int board[LEN][LEN]);
int checkLines(int board[LEN][LEN], piece*, coords);
/////////////////////////////////////////////////
/////////////////////////////////////////////////
static int score=0;

int main() {
    srand(time(NULL));
    int playing=1;
    int i; //i is a general purpose counter
    int board[LEN][LEN] = {0}; //game board
    int chosen_one=0; //piece chosen to be placed by the user
    coords pos; //input coordinates

    piece p1 = generate();
    piece p2 = generate();
    piece p3 = generate();
    piece* pp1=&p1;
    piece* pp2=&p2; 
    piece* pp3=&p3; //pointers to the pieces
    piece* arr[] = {pp1, pp2, pp3}; //array with pointers to all the pieces


    while (playing) {

        ///////////////////////////////////////////////// PIECE GENERATION
        if(p1.placed && p2.placed && p3.placed) { //generate the pieces if they've all been placed
            p1 = generate();
            p2 = generate();
            p3 = generate();
        }
        print_board(board, p1, p2, p3, score);

        for(i=0; i<3; i++) //determine the available moves
            if (arr[i]->placed==0)
                available(arr[i], board);
        /////////////////////////////////////////////////


        ///////////////////////////////////////////////// GAME OVER CHECK
        for(i=0; i<3 && (arr[i]->count==0 || arr[i]->placed==1); i++);
        printf("\ni:%d", i);
        if(i==3) {
            playing=0;
            print_board(board, p1, p2, p3, score);
            printf("\nGAME OVER\n");
        }
        /////////////////////////////////////////////////


        ///////////////////////////////////////////////// GAME LOOP
        if(playing) {

            ///////////////////////////////////////////////// PIECE INPUT
            do { //ask which piece to place
                printf("\nPIECE: ");
                scanf("%d", &chosen_one);
                fflush(stdin);
                if((chosen_one<1 && chosen_one!=-1) || chosen_one>3 || arr[chosen_one-1]->placed==1) {
                    print_board(board, p1, p2, p3, score);
                    printf("\npiece is invalid.");
                }

                if (chosen_one==-1)
                    playing=0;

            } while((chosen_one<1 && chosen_one!=-1) || chosen_one>3 || arr[chosen_one-1]->placed==1);

            chosen_one--;
            /////////////////////////////////////////////////


            ///////////////////////////////////////////////// POSITION INPUT
            while(arr[chosen_one]->placed==0 && playing!=0) { //ask where to place it

                printf("\n\n[format: X, Y]\nPOSITION: ");
                scanf("%d, %d", &pos.X, &pos.Y);
                printf("(%d %d) ", pos.X, pos.Y);
                fflush(stdin);
                arr[chosen_one]->placed = place(board, arr[chosen_one], pos);

                if (arr[chosen_one]->placed==0) {
                    print_board(board, p1, p2, p3, score);
                    if(pos.X>=0 && pos.Y>=0 && pos.X<=9 && pos.Y<=9)
                        printf("\nposition (%d, %d) is unavailable.", pos.X, pos.Y);
                    else
                        printf("\ninvalid position.");
                }
            }
            /////////////////////////////////////////////////


            if(arr[chosen_one]->placed) //if piece was placed once increase score 
                score = score + arr[chosen_one]->points + checkLines(board, arr[chosen_one], pos);
        }
        /////////////////////////////////////////////////
    }
    return 0;
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
void available(piece* p, int board[LEN][LEN]) {
    int i=0, j=0, k, l=0, count=0, temp=0; //"l" needs to be init at 0 

    for(i=0; i<=LEN-(p->dim.Y); i++) { //loops the board matrix
        for(j=0; j<=LEN-(p->dim.X); j++) {
            temp=0;
            for(k=0; k<(p->dim.Y); k++) { //loops the piece itself
                for(l=0; l<(p->dim.X); l++) {

                    if(p->mat[k][l]*board[i+k][j+l]==0)
                        temp++;
                    else {
                        l=p->dim.X;
                        k=p->dim.Y;
                    }
                }
            }

            if(temp == (p->dim.X * p->dim.Y)) { //the current position is available
                count++;
                p->av = (coords*)realloc(p->av, sizeof(coords)*count);
                p->av[count-1].Y = i;
                p->av[count-1].X = j;
            }
        }
    }
    p->count=count;
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
int checkLines(int board[LEN][LEN], piece* p, coords pos) {
    int i, j, lines=0, temp=0;
    int rows[LEN];
    int cols[LEN];

    for(i=pos.Y; i < p->dim.Y + pos.Y; i++) //see if any row is complete
        for(j=0; j<LEN && board[i][j]==1; j++)
            if(j==LEN-1) {
                rows[lines] = i;
                lines++;
            }

    for(i=pos.X; i < p->dim.X + pos.X; i++) //see if any column is complete
        for(j=0; j<LEN && board[j][i]==1; j++)
            if(j==LEN-1) {
                cols[temp] = i;
                temp++;
            }
    
    for(i=0; i<lines; i++) //delete the complete rows
        for(j=0; j<LEN; j++)
            board[rows[i]][j] = 0;

    for(i=0; i<temp; i++) //delete the complete columns
        for(j=0; j<LEN; j++)
            board[j][cols[i]] = 0;

    return (lines+temp)*10;
}
/////////////////////////////////////////////////
/////////////////////////////////////////////////