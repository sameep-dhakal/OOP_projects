#include <iostream>
using namespace std;
class check{
    public:
    int x = 1;
    check(int board[9][9], int row, int col, int num) 
    {
    // Check if 'num' is already in the same row
    for (int i = 0; i < 9; i++)
        if (board[row][i] == num) x = 0;

    // Check if 'num' is already in the same column
    for (int i = 0; i < 9; i++)
        if (board[i][col] == num) x = 0;

    // Check if 'num' is already in the same 3x3 box
    int boxRowStart = row - row % 3;
    int boxColStart = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i + boxRowStart][j + boxColStart] == num) x = 0;

    }
};

//function to print layout of sudoku board
void printBoard(int board[9][9]) {
    cout << endl;
    for (int row = 0; row < 9; row++){
      for (int col = 0; col < 9; col++){
         if(col == 3 || col == 6)
            cout << " | ";
         cout << board[row][col] <<" ";
      }
      if(row == 2 || row == 5){
         cout << endl;
         for(int i = 0; i<8; i++)
            cout << "-- ";
      }
      cout << endl;
   }
}

//function to start the game
void playGame(int board[9][9]){
    int row, col, num;
    while(true){
        printBoard(board);
        cout << endl << endl;
        cout << "Enter row: ";
        cin >> row;
        cout << "Enter column: ";
        cin >> col;
        cout << "Enter number: ";
        cin >> num;
        //value of row and col decreased beacause humans count from 1 and machine start from 0
        row--;
        col--;
        check c(board, row, col, num);
        if (c.x==0) {
            cout << "Invalid move. Try again." << endl;
            continue;
        }
        board[row][col] = num;
    }

    // Check if the user has solved it or not
    int solved = 0;
    for (int i = 0; i < 9; i++) 
    {
        for (int j = 0; j < 9; j++) 
        {
            if (board[i][j] == 0) break;
            else solved  = 1;
        }
    }
    if (solved =! 0) {
        cout << "Congratulations! You have solved the puzzle." << endl;
        printBoard(board);
    }
}

int main() {
    int board[9][9] = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };
    cout <<"Solve the Sudoku" << endl;
    playGame(board);
    return 0;
}
