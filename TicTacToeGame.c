//Tic-Tac-Toe game for single player mode and dual player mode 
//DONE BY: ABHISHEK KUMAR , 231210003, CSE(G1A)
//DONE BY: ABHINAV TRIPATHI, 231210002, CSE(G1A)

#include <stdio.h> // we used printf and scanf functions from this header file
#include <stdlib.h>// system function is used from this header file
#include <ctype.h>// toupper function is used from this header file
#include <time.h>// srand and time is used 

//functions for single player mode
void resetBoardai(); // this is to reset the board after moves are entered 
void printBoardai(int round); // this helps in displaying the board 
int checkFreeSpacesai();// this function checks if there is any space left or not 
void playerMoveai(); // this function is one of the key fuction as it is responsible for giving the user a chance to enter his/her move number
void computerMoveai(); // this is for computer move and need not to be entered by the user 
char checkWinnerai(); // it checks the winner after each move number is entered 
int printWinnerai(char); // this helps in displaying the winner after getting checked by the fuction 'checkWinnerai'

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

//Functions for dual player mode 

// to print the Tic Tac Toe board with round number
void printBoard(char board[3][3], int roundNumber);
// to check if a player has won
int checkwinner(char board[3][3]);
// to check if the board is full without any winner
int isBoardFull(char board[3][3]);
// to reset the board for a new game if players want to play further
void resetBoard(char board[3][3]);

int main() {
    char board[3][3];
    char player1Name[100], player2Name[100];
    int currentPlayer = 1;  // default : Player1 starts
    int playAgain = 1;  // option given to players if they want to play next round or quit game
    int roundNumber = 1;
    int player1Wins = 0, player2Wins = 0;
    int totalMatches = 0;
    int gamemode;

    printf("\nEnter game mode you want to play:\n");
    printf("1.play with computer\n");
    printf("2.play with friend\n");
    printf("\nEnter your choice (1 or 2) :- ");
    scanf("%d", &gamemode);

    if(gamemode!=1 && gamemode!=2)
    {
        printf("Invalid choice. pls try again " );
        return 1;
    }
    if (gamemode==1)
    {
        printf("Enter Your name :- ");
        scanf("%s", player1Name);
    }
    else{
        printf("Enter Player 1's name :- ");
        scanf("%s", player1Name);

        printf("Enter Player 2's name :- ");
        scanf("%s", player2Name);
    }
    //for single player mode
    while (gamemode==1)
    {
        char winner = ' ';
        int response = 1;
        int round=0;
        int match =0;
        int player1lose=0;
        int ties=0;
        do
        {
            match++;
            round++;
            winner = ' ';
            response = 1;
            resetBoardai();
            
        while(winner == ' ' && checkFreeSpacesai() != 0)
        {
            printBoardai(round);
            playerMoveai();
            winner = checkWinnerai();
            if(winner != ' ' || checkFreeSpacesai() == 0)
            {
                break;
            }
            computerMoveai();
            winner = checkWinnerai();
            if(winner != ' ' || checkFreeSpacesai() == 0)
            {
                break;
            }
        }
        int win = printWinnerai(winner);
        if (win==1)
        {  
            player1Wins++;
        }
        if(win==-1){ 
            player1lose++;
        }
        if(win==0){
            ties++;
        }
        printBoardai(round);
        printWinnerai(winner);
        
        printf("\nWould you like to play again? (1 for yes and 0 for no): ");
        scanf("%d", &response);
        } while (response == 1);

        //To print scorecard when exit the game for single player mode
        printf("\n---\e[1;36mSCORECARD\e[m---\n");
        printf("Total Matches Played :- %d\n", match);
        printf("you Wins :- %d\n", player1Wins);
        printf("you lose :- %d\n",player1lose);
        printf("Ties: %d\n",ties);
        if (player1Wins>player1lose){
            player1Name[100] = toupper(player1Name[100]);
            printf("\e[1;32myou win by %d-%d \e[m\n",player1Wins,player1lose);
            printf("\e[1;33mCONGRATULATION %s\e[m\n",player1Name);

        }

        printf("Thanks for playing! Exiting the game \n");
        return 0;
    }
    //for dual player mode 
    while (playAgain && gamemode==2) {
        resetBoard(board);

        // this line changes starting player in each consecutive rounds alternatively if players continues the game, starting with player1 in first match 
        currentPlayer = (roundNumber % 2 == 1) ? 1 : 2;

        while (1) {

            printBoard(board, roundNumber);

            // this code provide a player which has turn to enter move number and mark that number with his corresponding mark ( 'O' or 'X') in place of entered number
            int move;
            printf("%s, enter your move (1-9): ", (currentPlayer == 1) ? player1Name : player2Name);
            scanf("%d", &move);

            // to check that entered move must be any number between 1 to 9 including 1 and 9 also
            if (move < 1 || move > 9) {
                printf("Invalid move. Please enter a number between 1 and 9.\n");
                continue;
            }

            int row = (move - 1) / 3;
            int col = (move - 1) % 3;

            // to check that if the enter move number must not coincide with any previous move entered by both players
            if (board[row][col] != ' ') {
                printf("Cell is already occupied. Try again.\n");
                continue;
            }

            // this always player which has a turn can enter his desired move 
            if (currentPlayer == 1)
                board[row][col] = 'X';
            else
                board[row][col] = 'O';

            // to check who is the winner of current playing round and displaying the name of winner 
            int winner = checkwinner(board);
            if (winner) {
               
                printBoard(board, roundNumber);

                if (winner == 1)
                    printf("\033[1;31m%s is the winner!\033[0m\n", player1Name);  // Red colour mark for player 1
                else if (winner == 2)
                    printf("\033[1;34m%s is the winner!\033[0m\n", player2Name);  // Blue colour mark for player 2

                // to keep the record of number of rounds won by each player separetly
                if (winner == 1)
                    player1Wins++;
                else{
                    player2Wins++;
                }

                // to Display leading points
                printf("Leading Points:\n");
                printf("%s: %d\n", player1Name, player1Wins);
                printf("%s: %d\n", player2Name, player2Wins);

                // asking players if they want to play further or quit the game on the spot
                printf("Do you want to play more round? (non-zero for Yes, zero for No): ");
                scanf("%d", &playAgain);

                if (playAgain) 
                {
                    resetBoard(board);
                    roundNumber++;
                    printf("Let's start a new round!\n");
                    totalMatches++;
                } 
                else {
                    totalMatches++;
                    break;
                }
            }

            // checking that after the end of every round, whether that round is a tie/draw or not
            if (isBoardFull(board)) {
                void clearScreen();
                printBoard(board, roundNumber);
                printf("It's a tie!\n");

                // asking players if they want to play further or quit the game on the spot
                printf("Do you want to play another round? (non-zero for Yes, zero for No): ");
                scanf("%d", &playAgain);

                if (playAgain) {
                    resetBoard(board);
                    roundNumber++;
                    printf("Let's start a next round!\n");
                    totalMatches++;
                } else {
                    totalMatches++;
                    break;
                }
            }
            // to switch the starting player after every round if players continue the game
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        }
    }

    // to display the final scorecard/ report after quiting the game for final
    printf("\n---\e[1;36mSCORECARD\e[m---\n");
    printf("Total Matches Played :- %d\n", totalMatches);
    printf("%s Wins :- %d\n", player1Name, player1Wins);
    printf("%s Wins :- %d\n", player2Name, player2Wins);
    printf("Ties :- %d\n", totalMatches - player1Wins - player2Wins);
    
    if(player1Wins>player2Wins){
        printf("\e[1;32m%s wins by %d:%d\e[m\n",player1Name,player1Wins,player2Wins);
        printf("\e[1;33mCONGRATULATION %s\e[m\n",player1Name);
    }
    
    if(player2Wins>player1Wins){
        printf("\e[1;32%s wins by %d:%d\e[m\n",player2Name,player2Wins,player1Wins);
        printf("\e[1;33mCONGRATULATION %s\e[m\n",player2Name);
    }
    
    if(player1Wins==player2Wins){
        printf("both wins equal matches\n");
    }
    
    printf("Thanks for playing! Exiting the game.\n");
    return 0;
}
void clearScreen() {
    system("clear"); // Using "clear" for Linux to clear the previous board 
}
void printBoard(char board[3][3], int roundNumber) 
{
    printf("\e[1;33m---ROUND %d---\e[m\n\n",roundNumber);
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            char cell = board[i][j];

            if (cell == 'X')
                printf("\033[1;31m X \033[0m");  // Red color for 'X'
            else if (cell == 'O')
                printf("\033[1;34m O \033[0m");  // Blue color for 'O'
            else
                printf(" %c ", '1' + i * 3 + j);  // Use numbers for empty cells

            if (j < 2) printf("\e[0;33m|\e[m");
        }

        printf("\n");
        if (i < 2)
        {
        printf("\e[0;33m---+---+---\n\e[m");
        }
    }
    printf("\n");
}

int checkwinner(char board[3][3]) 
{
    
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            if (board[i][0] == 'X')
                return 1;  // Player1 wins
            else if (board[i][0] == 'O')
                return 2;  // Player2 wins
        }

        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            if (board[0][i] == 'X')
                return 1;  // Player1 wins
            else if (board[0][i] == 'O')
                return 2;  // Player2 wins
        }
    }
    
    // Check diagonally three similar mark
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        if (board[0][0] == 'X')
            return 1;  // Player1 wins
        else if (board[0][0] == 'O')
            return 2;  // Player2 wins
    }
    
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        if (board[0][2] == 'X')
            return 1;  // Player1 wins
        else if (board[0][2] == 'O')
            return 2;  // Player2 wins
    }
    return 0;  // winner is not decided yet 
}

int isBoardFull(char board[3][3]) 
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ')
                return 0; // to check that any number/cell is left to enter any move further
        }
    }
    return 1;  // if board is full
}

void resetBoard(char board[3][3]) 
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}
void resetBoardai() 
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoardai(int round) 
{
    int boxNumbers[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    printf("\n");
    printf("\e[1;33m---ROUND %d---\e[m\n\n",round);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                printf(" %d ", boxNumbers[i][j]);
            } 

            else {
                printf(" %c ", board[i][j]);
            }

            if (j < 2) {
                printf("\e[33m|\e[m");
            }
        }
        printf("\n");

        if (i < 2) {
            printf("\e[33m---|---|---\e[m\n");
        }
    }
    printf("\n");
}

int checkFreeSpacesai() {
    int freeSpaces = 9;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != ' ') {
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
}

void playerMoveai() {
    int boxNo;
    do {
        printf("enter your move (1-9): ");
        scanf("%d", &boxNo);
        if (boxNo < 1 || boxNo > 9) {
            printf("Invalid input! Please enter a number between 1 and 9.\n");
        } else {
            int row = (boxNo - 1) / 3;
            int col = (boxNo - 1) % 3;
            if (board[row][col] != ' ') {
                printf("Invalid move! The cell is already occupied.\n");
            } else {
                board[row][col] = PLAYER;
                break;
            }
        }
    } while (1);
}

void computerMoveai() {
    // srand(time(0));
    int x, y;

    // Check if the computer can win in the next move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = COMPUTER;
                
                if (checkWinnerai() == COMPUTER) {
                    return; // Computer can win, so make this move
                }

                board[i][j] = ' '; // Undo the move
            }
        }
    }

    // Check if the player can win in the next move and block them
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = PLAYER;
                
                if (checkWinnerai() == PLAYER) {
                    board[i][j] = COMPUTER; // Block the player
                    return;
                }

                board[i][j] = ' '; // Undo the move
            }
        }
    }

    // If no immediate winning move for computer or blocking move for the player, make a random move
    do {
        x = rand() % 3;
        y = rand() % 3;
    }while (board[x][y] != ' ');

    board[x][y] = COMPUTER;
}

char checkWinnerai() {
    
    //check rows
    for(int i = 0; i < 3; i++)
    {
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
            return board[i][0];
        }
    }

    //check columns
    for(int i = 0; i < 3; i++)
    {
        if(board[0][i] == board[1][i] && board[0][i] == board[2][i])
        {
            return board[0][i];
        }
    }

    //check diagonals
    if(board[0][0] == board[1][1] && board[0][0] == board[2][2])
    {
        return board[0][0];
    }
    if(board[0][2] == board[1][1] && board[0][2] == board[2][0])
    {
        return board[0][2];
    }
    return ' ';
}

int printWinnerai(char winner) {
    if (winner == PLAYER) {
        printf("YOU WIN!\n");
        return 1;
    } 
    else if (winner == COMPUTER) {
        printf("YOU LOSE!\n");
        return -1;
    } 
    else {
        printf("IT'S A TIE!\n");
        return 0;
    }
}