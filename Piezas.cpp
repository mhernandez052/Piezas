#include "Piezas.h"
#include <iostream>
#include <vector>

using std::cout;
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
 **/

/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and
 * specifies it is X's turn first
 **/
Piezas::Piezas() {
  // turn = X;
  // std::vector<std::vector<Piece>> init_board(
  //     BOARD_ROWS, std::vector<Piece>(BOARD_COLS, Blank));
  // board = init_board;

  turn = X;
  board = std::vector<std::vector<Piece>>(
      BOARD_ROWS, std::vector<Piece>(BOARD_COLS, Blank));
  // board = init_board;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
 **/
void Piezas::reset() {
  turn = X;
  std::vector<std::vector<Piece>> init_board(
      BOARD_ROWS, std::vector<Piece>(BOARD_COLS, Blank));
  board = init_board;
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
 **/
Piece Piezas::dropPiece(int column) {
  if (column > BOARD_ROWS || column < 0) {
    (turn == X) ? turn = O : turn = X;
    return Invalid;
  }
  for (int i = 0; i < (int)BOARD_ROWS; i++) {
    if (board[i][column] == Blank) {
      board[i][column] = turn;
      (turn == X) ? turn = O : turn = X;
      return board[i][column];
    }
  }
  (turn == X) ? turn = O : turn = X;
  return Blank;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
 **/
Piece Piezas::pieceAt(int row, int column) {
  if (row < 0 || column < 0 || row >= BOARD_ROWS || column >= BOARD_COLS) {
    return Invalid;
  }
  return board[row][column];
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
 **/
Piece Piezas::gameState() {
  for (int i = 0; i < BOARD_ROWS; i++) {
    for (int j = 0; j < BOARD_COLS; j++) {
      if (board[i][j] == Blank) {
        return Invalid;
      }
    }
  }
  /* Checking for Horizontal Win */
  // cout << "BS: " <<   board.size() << " [i]: " << board[0].size() << "\n";
  int MaxX = 1;
  int MaxO = 1;
  for (int i = 0; i < BOARD_ROWS; i++) {
    int curX = 1;
    int curO = 1;
    for (int j = 0; j < BOARD_COLS - 1; j++) {
      if (board[i][j] == board[i][j+1]) {
        if (board[i][j] == X) {
          curX++;
          curO = 1;
        }
        else if (board[i][j] == O) {
          curO++;
          curX = 1;
        }
      }
      if (curX > MaxX) {
        // cout << "XMax Change I: " << i << " " << "J: " << j << "\n"; 
        MaxX = curX;
      }
      if (curO > MaxO) {
        // cout << "OMax change I: " << i << " " << "J: " << j << "\n"; 
        MaxO = curO;
      }
    }
  }
  cout << "HMaxX: " << MaxX << "\n";
  cout << "HMaxO: " << MaxO << "\n";
  /* Checking for Vertical Win */
  for (int i = 0; i < BOARD_COLS; i++) {
    int curX = 1;
    int curO = 1;
    for (int j = 0; j < BOARD_ROWS; j++) {
      if ((board[j][i] == board[j][i + 1]) && board[j][i] == X) {
        curX++;
      } else {
        curX = 1;
      }
      if (board[j][i] == board[j][i + 1] && board[j][i] == O) {
        curO++;
      } else {
        curO = 1;
      }
      if (curO > MaxO) {
        MaxO = curO;
      }
      if (curX > MaxX) {
        MaxX = curX;
      }
    }
  }
  cout << "VMaxX: " << MaxX << "\n";
  cout << "VMaxO: " << MaxO << "\n";
  if (MaxO == MaxX) {
    return Blank;
  } else if (MaxX > MaxO) {
    return X;
  } else {
    return O;
  }
  // return MaxX == MaxO ? Blank : (MaxX > MaxO ? X : O);
}