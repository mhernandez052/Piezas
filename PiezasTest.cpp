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

TEST(PiezasTest, sanityCheck) { ASSERT_TRUE(true); }
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

TEST(PiezasTest, resetTestingSimple) {
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
  ASSERT_EQ(Board.dropPiece(3), Invalid);
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
  ASSERT_EQ(Board.pieceAt(0,2), Blank);
}

