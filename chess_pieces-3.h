#include "constants.h"
#include <vector>
#include <iostream>

using namespace std;

#ifndef CHESSPIECES_H
#define CHESSPIECES_H

class ChessPieces {
protected:
  int myRow, myCol;
  int initialRow, initialCol;
  char pieceLetter;
  string pieceName;
  vector<int> potentialRows;
  vector<int> potentialCols;
  static vector<int> takenRows;
  static vector<int> takenCols;

  void clearCin() {
    cin.clear();
    cin.ignore(10000, '\n'); // clears cin to avoid errors in the new loop ^^
  }

public:
  ChessPieces(int row, int col) {
    initialRow = row;
    initialCol = col;
    myRow = row;
    myCol = col;
    takenRows.push_back(myRow);
    takenCols.push_back(myCol);
  }

  virtual ~ChessPieces() = default;

  int getRow() { return myRow; }
  int getCol() { return myCol; }

  void resetBoardClear() {
    takenRows.clear();
    takenCols.clear();
  }

  void resetPiece(string arr[][8]) {
    arr[myRow][myCol] = "[ ]";
    myRow = initialRow;
    myCol = initialCol;
    takenRows.push_back(myRow);
    takenCols.push_back(myCol);
    arr[myRow][myCol] = "[" + string(1, pieceLetter) + "]";
  }

  bool locationSingleSpotTaken(int col, int row) {
    for (int i = 0; i < takenCols.size(); ++i) { // for each existing spot
        if ((takenCols[i] == col) && (takenRows[i] == row))
          return true;
    }
    return false;
  }

  void leaveTheTakenSpot(int col, int row) {
    for (int i = 0; i < takenCols.size(); ++i) { // for each existing spot
        if ((takenCols[i] == col) && (takenRows[i] == row)) {
          takenCols.erase(takenCols.begin() + i);
          takenRows.erase(takenRows.begin() + i);
        }
    }
  }

  virtual void legalMoves(string arr[][8]) = 0;

  void prepLegalMovesSmallStep() {
    potentialRows.clear();
    potentialCols.clear();

    cout << "\nYour current position on the board is [" << myRow << "]["
         << myCol << "] \n";
    cout << "\nFor this position legal moves are:\n";
  }

  void showLegalMovesSmallStep(string arrCopy[][8]) {
    // Show the board with all legal moves from the current position
    cout << "\n  0  1  2  3  4  5  6  7\n";
    for (int r = 0; r < ROWS; r++) {
      cout << r;
      for (int c = 0; c < COLS; c++) {
        cout << arrCopy[r][c];
      }

      cout << endl;
    }
  }

  void movePiece(string arr[][8]) {
    if (potentialCols.empty())
      cout << "\nThere are no possible spaces to move this " + pieceName + ". Please choose another piece.\n\n";
    else {
      arr[myRow][myCol] = "[ ]";
      leaveTheTakenSpot(myCol, myRow);
      bool placeFound = false;
      while (!placeFound) {
        int row, col;
        do {
          cout << "\nEnter the position of a place on the board to select it "
                  "(input first row, then column): \n";
          cin >> row >> col;
          if (cin.fail() || row < 0 || row > 7 || col < 0 || col > 7) {
            cout << "Please enter two numbers in between 0 and 7.\n";
            cin.clear();
            cin.ignore(10000, '\n');
          }
        } while (cin.fail() || row < 0 || row > 7 || col < 0 || col > 7);

        for (int i = 0; i < potentialRows.size(); i++) {
            if (row == potentialRows[i] && col == potentialCols[i]) {
              myRow = row; myCol = col;
              arr[myRow][myCol] = "[" + string(1, pieceLetter) + "]";
              placeFound = true;
              takenRows.push_back(myRow);
              takenCols.push_back(myCol);
            }
        }

        if (!placeFound)
          cout << "\nThis place is impossible to move to with the " + pieceName +". Please choose a coordinate with a '*'\n";
      }
    }
  }
};

class KnightTour : public ChessPieces {
public:
  KnightTour(int col, int row, string arr[][8]) : ChessPieces(col, row) {
    pieceLetter = 'K';
    pieceName = "Knight";
    arr[myRow][myCol] = "[" + string(1, pieceLetter) + "]";
  }
  ~KnightTour() override = default;

  void legalMoves(string arr[][8]) override {
    prepLegalMovesSmallStep();

    string arrCopy[ROWS][COLS]; // Create a copy of the array
    for (int r = 0; r < ROWS; r++) {
      for (int c = 0; c < COLS; c++) {
        arrCopy[r][c] = arr[r][c];
      }
    }

    int row, col;

    // to move up
    row = myRow - 2;
    col = myCol + 1;
    if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
      cout << "board[" << row << "][" << col << "] or \n";
      arrCopy[row][col] = "[*]";
      potentialRows.push_back(row);
      potentialCols.push_back(col);
    }

    row = myRow - 1;
    col = myCol + 2;
    if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
      cout << "board[" << row << "][" << col << "] or \n";
      arrCopy[row][col] = "[*]";
      potentialRows.push_back(row);
      potentialCols.push_back(col);
    }

    // to move right
    row = myRow + 1;
    col = myCol + 2;
    if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
      cout << "board[" << row << "][" << col << "] or \n";
      arrCopy[row][col] = "[*]";
      potentialRows.push_back(row);
      potentialCols.push_back(col);
    }
    row = myRow + 2;
    col = myCol + 1;
    if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
      cout << "board[" << row << "][" << col << "] or \n";
      arrCopy[row][col] = "[*]";
      potentialRows.push_back(row);
      potentialCols.push_back(col);
    }

    // to move down
    row = myRow + 2;
    col = myCol - 1;
    if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
      cout << "board[" << row << "][" << col << "] or \n";
      arrCopy[row][col] = "[*]";
      potentialRows.push_back(row);
      potentialCols.push_back(col);
    }
    row = myRow + 1;
    col = myCol - 2;
    if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
      cout << "board[" << row << "][" << col << "] or \n";
      arrCopy[row][col] = "[*]";
      potentialRows.push_back(row);
      potentialCols.push_back(col);
    }

    // to move left
    row = myRow - 1;
    col = myCol - 2;
    if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
      cout << "board[" << row << "][" << col << "] or \n";
      arrCopy[row][col] = "[*]";
      potentialRows.push_back(row);
      potentialCols.push_back(col);
    }
    row = myRow - 2;
    col = myCol - 1;
    if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
      cout << "board[" << row << "][" << col << "] or \n";
      arrCopy[row][col] = "[*]";
      potentialRows.push_back(row);
      potentialCols.push_back(col);
    }

    showLegalMovesSmallStep(arrCopy);
  }
};

class PawnTour : public ChessPieces {
private:
  bool firstTurn;

public:
  PawnTour(int col, int row, string arr[][8]) : ChessPieces(col, row) {
    pieceLetter = 'P';
    pieceName = "Pawn";
    arr[myRow][myCol] = "[" + string(1, pieceLetter) + "]";
    firstTurn = true;
  }
  ~PawnTour() override = default;

  void legalMoves(string arr[][8]) override {
    prepLegalMovesSmallStep();

    string arrCopy[ROWS][COLS]; // Create a copy of the array
    for (int r = 0; r < ROWS; ++r) {
      for (int c = 0; c < COLS; ++c) {
        arrCopy[r][c] = arr[r][c];
      }
    }

    int row, col = myCol;

    bool canMoveOne = false;
    // to move up
    row = myRow - 1;
    if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
      cout << "board[" << row << "][" << col << "] or \n";
      arrCopy[row][col] = "[*]";
      potentialRows.push_back(row);
      potentialCols.push_back(col);
      canMoveOne = true;
    }

    // if it is the first turn, then it can move up 2 spaces
    if (firstTurn) {
      row = myRow - 2;
      if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row) && canMoveOne) {
        cout << "board[" << row << "][" << col << "] or \n";
        arrCopy[row][col] = "[*]";
        potentialRows.push_back(row);
        potentialCols.push_back(col);
        firstTurn = false;
      }
    }

    showLegalMovesSmallStep(arrCopy);
  }
};

class KingTour : public ChessPieces {
public:
  KingTour(int col, int row, string arr[][8]) : ChessPieces(col, row) {
    pieceLetter = 'G';
    pieceName = "King";
    arr[myRow][myCol] = "[" + string(1, pieceLetter) + "]";
  }
  ~KingTour() override = default;

  void legalMoves(string arr[][8]) override {
    prepLegalMovesSmallStep();

    string arrCopy[ROWS][COLS]; // Create a copy of the array
    for (int r = 0; r < ROWS; ++r) {
      for (int c = 0; c < COLS; ++c) {
        arrCopy[r][c] = arr[r][c];
      }
    }

    int row, col;

    // to move up
    row = myRow - 1;
    col = myCol;
    if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
        cout << "board[" << row << "][" << col << "] or \n";
        arrCopy[row][col] = "[*]";
        potentialRows.push_back(row);
        potentialCols.push_back(col);
    }

    // to move top right
    row = myRow - 1;
    col = myCol + 1;
    if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
        cout << "board[" << row << "][" << col << "] or \n";
        arrCopy[row][col] = "[*]";
        potentialRows.push_back(row);
        potentialCols.push_back(col);
    }

    // to move right
    row = myRow;
    col = myCol + 1;
    if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
        cout << "board[" << row << "][" << col << "] or \n";
        arrCopy[row][col] = "[*]";
        potentialRows.push_back(row);
        potentialCols.push_back(col);
    }

    // to move top left
    row = myRow - 1;
    col = myCol - 1;
    if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
        cout << "board[" << row << "][" << col << "] or \n";
        arrCopy[row][col] = "[*]";
        potentialRows.push_back(row);
        potentialCols.push_back(col);
    }

    // to move down
    row = myRow + 1;
    col = myCol;
    if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
      cout << "board[" << row << "][" << col << "] or \n";
      arrCopy[row][col] = "[5]";
    }

    // to move bottom left
    row = myRow + 1;
    col = myCol - 1;
    if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
        cout << "board[" << row << "][" << col << "] or \n";
        arrCopy[row][col] = "[*]";
        potentialRows.push_back(row);
        potentialCols.push_back(col);
    }

    // to move left
    row = myRow;
    col = myCol - 1;
    if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
        cout << "board[" << row << "][" << col << "] or \n";
        arrCopy[row][col] = "[*]";
        potentialRows.push_back(row);
        potentialCols.push_back(col);
    }

    // to move bottom right
    row = myRow + 1;
    col = myCol + 1;
    if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
        cout << "board[" << row << "][" << col << "] or \n";
        arrCopy[row][col] = "[*]";
        potentialRows.push_back(row);
        potentialCols.push_back(col);
    }

    showLegalMovesSmallStep(arrCopy);
  }
};

class RookTour : public ChessPieces {
public:
  RookTour(int col, int row, string arr[][8]) : ChessPieces(col, row) {
    pieceLetter = 'R';
    pieceName = "Rook";
    arr[myRow][myCol] = "[" + string(1, pieceLetter) + "]";
  }
  ~RookTour() override = default;

  void legalMoves(string arr[][8]) override {
    prepLegalMovesSmallStep();

    string arrCopy[ROWS][COLS]; // Create a copy of the array
    for (int r = 0; r < ROWS; ++r) {
      for (int c = 0; c < COLS; ++c) {
        arrCopy[r][c] = arr[r][c];
      }
    }

    int row, col;

    // to move up
    col = myCol;
    for (int i = 1; i <= ROWS; i++) {
      row = myRow - i;
      if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
        cout << "board[" << row << "][" << col << "] or \n";
        arrCopy[row][col] = "[*]";
        potentialRows.push_back(row);
        potentialCols.push_back(col);
      }
      else
        break;
    }

    // to move down
    col = myCol;
    for (int i = 1; i <= ROWS; i++) {
      row = myRow + i;
      if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
        cout << "board[" << row << "][" << col << "] or \n";
        arrCopy[row][col] = "[*]";
        potentialRows.push_back(row);
        potentialCols.push_back(col);
      }
      else
        break;
    }

    // to move right
    row = myRow;
    for (int i = 1; i <= COLS; i++) {
      col = myCol + i;
      if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
        cout << "board[" << row << "][" << col << "] or \n";
        arrCopy[row][col] = "[*]";
        potentialRows.push_back(row);
        potentialCols.push_back(col);
      }
      else
        break;
    }

    // to move left
    row = myRow;
    for (int i = 1; i <= COLS; i++) {
      col = myCol - i;
      if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
        cout << "board[" << row << "][" << col << "] or \n";
        arrCopy[row][col] = "[*]";
        potentialRows.push_back(row);
        potentialCols.push_back(col);
      }
      else
        break;
    }

    showLegalMovesSmallStep(arrCopy);
  }
};

class BishopTour : public ChessPieces {
public:
  BishopTour(int col, int row, string arr[][8]) : ChessPieces(col, row) {
    pieceLetter = 'B';
    pieceName = "Bishop";
    arr[myRow][myCol] = "[" + string(1, pieceLetter) + "]";
  }
  ~BishopTour() override = default;

  void legalMoves(string arr[][8]) override {
    prepLegalMovesSmallStep();

    string arrCopy[ROWS][COLS]; // Create a copy of the array
    for (int r = 0; r < ROWS; ++r) {
      for (int c = 0; c < COLS; ++c) {
        arrCopy[r][c] = arr[r][c];
      }
    }

    int row, col;

    // to move top right
    for (int i = 1; i <= ROWS; i++) {
      row = myRow - i;
      col = myCol + i;
      if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
        cout << "board[" << row << "][" << col << "] or \n";
        arrCopy[row][col] = "[*]";
        potentialRows.push_back(row);
        potentialCols.push_back(col);
      }
      else
        break;
    }

    // to move bottom right
    for (int i = 1; i <= ROWS; i++) {
      row = myRow + i;
      col = myCol + i;
      if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
        cout << "board[" << row << "][" << col << "] or \n";
        arrCopy[row][col] = "[*]";
        potentialRows.push_back(row);
        potentialCols.push_back(col);
      }
      else
        break;
    }

    // to move top left
    for (int i = 1; i <= COLS; i++) {
      row = myRow - i;
      col = myCol - i;
      if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
        cout << "board[" << row << "][" << col << "] or \n";
        arrCopy[row][col] = "[*]";
        potentialRows.push_back(row);
        potentialCols.push_back(col);
      }
      else
        break;
    }

    // to move bottom left
    for (int i = 1; i <= COLS; i++) {
      row = myRow + i;
      col = myCol - i;
      if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
        cout << "board[" << row << "][" << col << "] or \n";
        arrCopy[row][col] = "[*]";
        potentialRows.push_back(row);
        potentialCols.push_back(col);
      }
      else
        break;
    }

    showLegalMovesSmallStep(arrCopy);
  }
};

class QueenTour : public ChessPieces {
public:
  QueenTour(int col, int row, string arr[][8]) : ChessPieces(col, row) {
    pieceLetter = 'Q';
    pieceName = "Queen";
    arr[myRow][myCol] = "[" + string(1, pieceLetter) + "]";
  }
  ~QueenTour() override = default;

  void legalMoves(string arr[][8]) override {
    prepLegalMovesSmallStep();

    string arrCopy[ROWS][COLS]; // Create a copy of the array
    for (int r = 0; r < ROWS; ++r) {
      for (int c = 0; c < COLS; ++c) {
        arrCopy[r][c] = arr[r][c];
      }
    }

    int row, col;

        // to move up
    col = myCol;
    for (int i = 1; i <= ROWS; i++) {
      row = myRow - i;
      if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
        cout << "board[" << row << "][" << col << "] or \n";
        arrCopy[row][col] = "[*]";
        potentialRows.push_back(row);
        potentialCols.push_back(col);
      }
      else
        break;
    }

    // to move down
    col = myCol;
    for (int i = 1; i <= ROWS; i++) {
      row = myRow + i;
      if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
        cout << "board[" << row << "][" << col << "] or \n";
        arrCopy[row][col] = "[*]";
        potentialRows.push_back(row);
        potentialCols.push_back(col);
      }
      else
        break;
    }

    // to move right
    row = myRow;
    for (int i = 1; i <= COLS; i++) {
      col = myCol + i;
      if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
        cout << "board[" << row << "][" << col << "] or \n";
        arrCopy[row][col] = "[*]";
        potentialRows.push_back(row);
        potentialCols.push_back(col);
      }
      else
        break;
    }

    // to move left
    row = myRow;
    for (int i = 1; i <= COLS; i++) {
      col = myCol - i;
      if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
        cout << "board[" << row << "][" << col << "] or \n";
        arrCopy[row][col] = "[*]";
        potentialRows.push_back(row);
        potentialCols.push_back(col);
      }
      else
        break;
    }

    // to move top right
    for (int i = 1; i <= ROWS; i++) {
      row = myRow - i;
      col = myCol + i;
      if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
        cout << "board[" << row << "][" << col << "] or \n";
        arrCopy[row][col] = "[*]";
        potentialRows.push_back(row);
        potentialCols.push_back(col);
      }
      else
        break;
    }

    // to move bottom right
    for (int i = 1; i <= ROWS; i++) {
      row = myRow + i;
      col = myCol + i;
      if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
        cout << "board[" << row << "][" << col << "] or \n";
        arrCopy[row][col] = "[*]";
        potentialRows.push_back(row);
        potentialCols.push_back(col);
      }
      else
        break;
    }

    // to move top left
    for (int i = 1; i <= COLS; i++) {
      row = myRow - i;
      col = myCol - i;
      if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
        cout << "board[" << row << "][" << col << "] or \n";
        arrCopy[row][col] = "[*]";
        potentialRows.push_back(row);
        potentialCols.push_back(col);
      }
      else
        break;
    }

    // to move bottom left
    for (int i = 1; i <= COLS; i++) {
      row = myRow + i;
      col = myCol - i;
      if (row >= 0 && row < 8 && col >= 0 && col < 8 && !locationSingleSpotTaken(col, row)) {
        cout << "board[" << row << "][" << col << "] or \n";
        arrCopy[row][col] = "[*]";
        potentialRows.push_back(row);
        potentialCols.push_back(col);
      }
      else
        break;
    }

    showLegalMovesSmallStep(arrCopy);
  }
};

#endif