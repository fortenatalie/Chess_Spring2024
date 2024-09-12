#include "chess_pieces.h"
#include <iostream>

using namespace std;

#ifndef BOARD_H
#define BOARD_H

class Board {
private:
  string board[ROWS][COLS];

  // initialize all pieces
  ChessPieces *myPieces[AMTPIECES];

public:
  Board() {
    // Initialize array with empty spaces
    for (int r = 0; r < ROWS; r++) {
      for (int c = 0; c < COLS; c++) {
        board[r][c] = "[ ]";
      }
    }

    myPieces[0] = new KnightTour(7, 1, board);
    myPieces[1] = new KnightTour(7, 6, board);
    myPieces[2] = new PawnTour(6, 0, board);
    myPieces[3] = new PawnTour(6, 1, board);
    myPieces[4] = new PawnTour(6, 2, board);
    myPieces[5] = new PawnTour(6, 3, board);
    myPieces[6] = new PawnTour(6, 4, board);
    myPieces[7] = new PawnTour(6, 5, board);
    myPieces[8] = new PawnTour(6, 6, board);
    myPieces[9] = new PawnTour(6, 7, board);
    myPieces[10] = new KingTour(7, 4, board);
    myPieces[11] = new RookTour(7, 0, board);
    myPieces[12] = new RookTour(7, 7, board);
    myPieces[13] = new BishopTour(7, 2, board);
    myPieces[14] = new BishopTour(7, 5, board);
    myPieces[15] = new QueenTour(7, 3, board);
  }

  ~Board() {
    // Clean up dynamically allocated memory
    for (int i = 0; i < AMTPIECES; ++i) {
      delete myPieces[i];
    }
  }

  void resetBoard() {
    myPieces[0]->resetBoardClear();
    for (int i = 0; i < AMTPIECES; ++i) {
        myPieces[i]->resetPiece(board);
      }
  }

  void drawBoard() {
    cout << "  0  1  2  3  4  5  6  7\n";
    for (int r = 0; r < ROWS; r++) {
      cout << r;
      for (int c = 0; c < COLS; c++) {
        cout << board[r][c];
      }

      cout << endl;
    }
  }

  void choosePiece() {
    int row, col;
    do {
      cout << "\nEnter the position of a piece on the board to select it "
              "(input first row, then column): \n";
      cin >> row >> col;
      if (cin.fail() || row < 0 || row > 7 || col < 0 || col > 7) {
        cout << "Please enter two numbers in between 0 and 7.\n";
        cin.clear();
        cin.ignore(10000, '\n');
      }
    } while (cin.fail() || row < 0 || row > 7 || col < 0 || col > 7);

    for (int i = 0; i < AMTPIECES; ++i) {
      if (myPieces[i]->getRow() == row && myPieces[i]->getCol() == col) {
        myPieces[i]->legalMoves(board);
        myPieces[i]->movePiece(board);
      }
    }
  }
};

#endif