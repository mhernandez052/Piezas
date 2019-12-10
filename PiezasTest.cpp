/**
 * Unit Tests for Piezas
 **/

#include "Piezas.h"
#include <gtest/gtest.h>

class PiezasTest : public ::testing::Test {
protected:
  PiezasTest() {}            // constructor runs before each test
  virtual ~PiezasTest() {}   // destructor cleans up after tests
  virtual void SetUp() {}    // sets up before each test (after constructor)
  virtual void TearDown() {} // clean up after each test, (before destructor)
};

TEST(PiezasTest, sanityCheck) {

  /* Initial Test */
  ASSERT_TRUE(true);
}
/***********************************
 *  reset() Testing
 **********************************/

TEST(PiezasTest, resetTestingStart) {
  Piezas Board;
  Board.reset();
  ASSERT_EQ(Board.dropPiece(0), X);
}

TEST(PiezasTest, resetTestingSimple) {
  Piezas Board;
  Board.dropPiece(0);
  Board.dropPiece(0);
  Board.dropPiece(0);
  Board.dropPiece(1);
  Board.dropPiece(2);
  Board.dropPiece(3);
  Board.reset();
  ASSERT_EQ(Board.dropPiece(0), X);
}

TEST(PiezasTest, resetTestingFull) {
  Piezas Board;
  Board.dropPiece(0);
  Board.dropPiece(0);
  Board.dropPiece(0);
  Board.dropPiece(1);
  Board.dropPiece(1);
  Board.dropPiece(1);
  Board.dropPiece(2);
  Board.dropPiece(2);
  Board.dropPiece(2);
  Board.dropPiece(3);
  Board.dropPiece(3);
  Board.dropPiece(3);
  Board.reset();
  ASSERT_EQ(Board.dropPiece(3), X);
}

TEST(PiezasTest, resetOnWinner) {
  Piezas Board;
  Board.dropPiece(0);
  Board.dropPiece(1);
  Board.dropPiece(0);
  Board.dropPiece(1);
  Board.dropPiece(1);
  Board.dropPiece(0);
  Board.dropPiece(2);
  Board.dropPiece(2);
  Board.dropPiece(3);
  Board.dropPiece(3);
  Board.dropPiece(2);
  Board.dropPiece(3);
  Board.reset();
  ASSERT_EQ(Board.pieceAt(0,0), Blank);
}
/***********************************
 *  dropPiece() Testing
 **********************************/
TEST(PiezasTest, dropPieceX) {
  Piezas Board;
  ASSERT_EQ(Board.dropPiece(0), X);
}

TEST(PiezasTest, dropPieceO) {
  Piezas Board;
  Board.dropPiece(0);
  ASSERT_EQ(Board.dropPiece(0), O);
}

TEST(PiezasTest, dropPieceOverflow) {
  Piezas Board;
  Board.dropPiece(0);
  Board.dropPiece(0);
  Board.dropPiece(0);
  ASSERT_EQ(Board.dropPiece(0), Blank);
}

TEST(PiezasTest, dropPieceOverflowSkipTurn) {
  Piezas Board;
  Board.dropPiece(0);
  Board.dropPiece(0);
  Board.dropPiece(0);
  Board.dropPiece(0);
  ASSERT_EQ(Board.dropPiece(1), X);
}

TEST(PiezasTest, dropPieceOutOfBoundsCol) {
  Piezas Board;
  ASSERT_EQ(Board.dropPiece(4), Invalid);
}

TEST(PiezasTest, checkOutOfBoundsTurnSkip) {
  Piezas Board;
  Board.dropPiece(3);
  ASSERT_EQ(Board.dropPiece(2), O);
}

/***********************************
 * pieceAt() Testing
 **********************************/

TEST(PiezasTest, getPieceStart) {
  Piezas Board;
  ASSERT_EQ(Board.pieceAt(0, 2), Blank);
}

TEST(PiezasTest, getPieceStartReset) {
  Piezas Board;
  Board.dropPiece(3);
  Board.reset();
  ASSERT_EQ(Board.pieceAt(0, 3), Blank);
}

TEST(PiezasTest, getPieceX) {
  Piezas Board;
  Board.dropPiece(3);
  ASSERT_EQ(Board.pieceAt(0, 3), X);
}

TEST(PiezasTest, getPieceO) {
  Piezas Board;
  Board.dropPiece(3);
  Board.dropPiece(3);
  ASSERT_EQ(Board.pieceAt(1, 3), O);
}

TEST(PiezasTest, getPieceOutOfBounds) {
  Piezas Board;
  Board.dropPiece(3);
  Board.dropPiece(3);
  ASSERT_EQ(Board.pieceAt(5, 0), Invalid);
}

TEST(PiezasTest, getPieceOverFlow) {
  Piezas Board;
  Board.dropPiece(3);
  Board.dropPiece(3);
  Board.dropPiece(3);
  Board.dropPiece(3);
  ASSERT_EQ(Board.pieceAt(2, 3), X);
}

/***********************************
 * gameState() Testing
 **********************************/
TEST(PiezasTest, gameRunningBlank) {
  Piezas Board;
  ASSERT_EQ(Board.gameState(), Invalid);
}

TEST(PiezasTest, gameRunningNormal) {
  Piezas Board;
  Board.dropPiece(0);
  Board.dropPiece(1);
  Board.dropPiece(2);
  Board.dropPiece(3);
  ASSERT_EQ(Board.gameState(), Invalid);
}

TEST(PiezasTest, gameStateWinThenReset) {
  Piezas Board;
  Board.dropPiece(0);
  Board.dropPiece(1);
  Board.dropPiece(0);
  Board.dropPiece(1);
  Board.dropPiece(1);
  Board.dropPiece(0);
  Board.dropPiece(2);
  Board.dropPiece(2);
  Board.dropPiece(3);
  Board.dropPiece(3);
  Board.dropPiece(2);
  Board.dropPiece(3);
  Board.reset();
  ASSERT_EQ(Board.gameState(), Invalid);
}

TEST(PiezasTest, gameTieLength1) {
  Piezas Board;
  // Multiple Ties of Length 1
  Board.dropPiece(0);
  Board.dropPiece(0);
  Board.dropPiece(0);
  Board.dropPiece(1);
  Board.dropPiece(1);
  Board.dropPiece(1);
  Board.dropPiece(2);
  Board.dropPiece(2);
  Board.dropPiece(2);
  Board.dropPiece(3);
  Board.dropPiece(3);
  Board.dropPiece(3);
  ASSERT_EQ(Board.gameState(), Blank);
}

TEST(PiezasTest, gameTieLength2) {
  // Multiple Ties of Length 2
  Piezas Board;
  Board.dropPiece(2);
  Board.dropPiece(0);
  Board.dropPiece(3);
  Board.dropPiece(1);
  Board.dropPiece(0);
  Board.dropPiece(1);
  Board.dropPiece(2);
  Board.dropPiece(3);
  Board.dropPiece(0);
  Board.dropPiece(2);
  Board.dropPiece(1);
  Board.dropPiece(3);
  ASSERT_EQ(Board.gameState(), Blank);
}


TEST(PiezasTest, verticalWinXLength3) {
  Piezas Board;
  Board.dropPiece(0);
  Board.dropPiece(1);
  Board.dropPiece(0);
  Board.dropPiece(2);
  Board.dropPiece(0);
  Board.dropPiece(1);
  Board.dropPiece(1);
  Board.dropPiece(2);
  Board.dropPiece(3);
  Board.dropPiece(3);
  Board.dropPiece(2);
  Board.dropPiece(3);
  ASSERT_EQ(Board.gameState(), X);
}

TEST(PiezasTest, horizontalWinOLength4) {
  Piezas Board;
  Board.dropPiece(0);
  Board.dropPiece(0);
  Board.dropPiece(0);
  Board.dropPiece(1);
  Board.dropPiece(2);
  Board.dropPiece(1);
  Board.dropPiece(1);
  Board.dropPiece(2);
  Board.dropPiece(3);
  Board.dropPiece(3);
  Board.dropPiece(2);
  Board.dropPiece(3);
  ASSERT_EQ(Board.gameState(), O);
}

TEST(PiezasTest, horizontalWinOLength3) {
  Piezas Board;
  Board.dropPiece(0);
  Board.dropPiece(1);
  Board.dropPiece(0);
  Board.dropPiece(1);
  Board.dropPiece(1);
  Board.dropPiece(0);
  Board.dropPiece(2);
  Board.dropPiece(2);
  Board.dropPiece(3);
  Board.dropPiece(3);
  Board.dropPiece(2);
  Board.dropPiece(3);
  ASSERT_EQ(Board.gameState(), O);
}
