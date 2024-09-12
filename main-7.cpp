// Natalie Forte

#include "board.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
  Board chessBoard;
  char continueGame;
  char resetGame;

  cout << "Welcome to the Chess Simulator. This is a one-sided board that allows the user to interact with chess pieces.\n\n";

  do {
    chessBoard.resetBoard();
    chessBoard.drawBoard();

    do {
      chessBoard.choosePiece();
      chessBoard.drawBoard();

      do {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\nMove again? (y/n): \n";
        cin >> continueGame;
        if (cin.fail() || (continueGame != 'y' && continueGame != 'n')) {
          cout << "Please enter either 'y' or 'n'.\n";
        }
      } while (cin.fail() || (continueGame != 'y' && continueGame != 'n'));

    } while (continueGame == 'y');

    do {
      cin.clear();
      cin.ignore(10000, '\n');
      cout << "\nReset board? (y/n): \n";
      cin >> resetGame;
      if (cin.fail() || (resetGame != 'y' && resetGame != 'n')) {
        cout << "Please enter either 'y' or 'n'.\n";
      }
    } while (cin.fail() || (resetGame != 'y' && resetGame != 'n'));

  } while (resetGame == 'y');

  cout << "\nThank you for playing!\n";

  return 0;
}

vector<int> ChessPieces::takenCols;
vector<int> ChessPieces::takenRows;