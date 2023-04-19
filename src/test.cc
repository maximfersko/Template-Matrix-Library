#include "gtest/gtest.h"
#include "matrix/matrix.h"


TEST(test, defAllocate) {
  Matrix<double> first;
  first(0, 0) = 2;
  first(0, 1) = 3;
  first(1, 0) = 7;
  first(1, 1) = 12;
  Matrix<double> second;
  second(0, 0) = 2;
  second(0, 1) = 3;
  second(1, 0) = 7;
  second(1, 1) = 12;
  bool result = first == second;
  ASSERT_EQ(result, true);
}

TEST(test, sumMatrix) {
  Matrix<double> first(3, 3);
  Matrix<double> second(3, 3);
  Matrix<double> result(3, 3);
  first.InitFromFile("data/3x3.txt");
  second.InitFromFile("data/3x3-1.txt");
  result.InitFromFile("data/result/add/3x3+3x3-1.txt");
  first = first + second;
  bool check = first == result;
  ASSERT_EQ(check, true);
}

TEST(test, sumMatrix2) {
  Matrix<double> first(5, 5);
  Matrix<double> second(5, 5);
  Matrix<double> result(5, 5);
  first.InitFromFile("data/5x5.txt");
  second.InitFromFile("data/5x5-1.txt");
  result.InitFromFile("data/result/add/5x5+5x5-1.txt");
  first += second;
  bool check = first == result;
  ASSERT_EQ(check, true);
}

TEST(test, sumMatrix3) {
  Matrix<double> first(10, 10);
  Matrix<double> second(10, 10);
  Matrix<double> result(10, 10);
  first.InitFromFile("data/10x10.txt");
  second.InitFromFile("data/10x10-1.txt");
  result.InitFromFile("data/result/add/10x10+10x10-1.txt");
  first += second;
  bool check = first == result;
  ASSERT_EQ(check, true);
}

TEST(test, sumMatrix4) {
  Matrix<double> first(10, 10);
  Matrix<double> second(10, 10);
  Matrix<double> result(10, 10);
  first.InitFromFile("data/10x10f.txt");
  second.InitFromFile("data/10x10-1f.txt");
  result.InitFromFile("data/result/add/10x10f+10x10-1f.txt");
  first += second;
  bool check = first == result;
  ASSERT_EQ(check, true);
}

TEST(test, sumMatrix5) {
  Matrix<double> first(7, 7);
  Matrix<double> second(7, 7);
  Matrix<double> result(7, 7);
  first.InitFromFile("data/7x7f.txt");
  second.InitFromFile("data/7x7-1f.txt");
  result.InitFromFile("data/result/add/7x7+7x7-1f.txt");
  first += second;
  bool check = first == result;
  ASSERT_EQ(check, true);
}

TEST(test, subMatrix1) {
  Matrix<double> first(7, 7);
  Matrix<double> second(7, 7);
  Matrix<double> result(7, 7);
  first.InitFromFile("data/7x7f.txt");
  second.InitFromFile("data/7x7-1f.txt");
  result.InitFromFile("data/result/sub/7x7-7x7-1f.txt");
  first = first - second;
  bool check = first == result;
  ASSERT_EQ(check, true);
}

TEST(test, subMatrix2) {
  Matrix<double> first(3, 3);
  Matrix<double> second(3, 3);
  Matrix<double> result(3, 3);
  first.InitFromFile("data/3x3.txt");
  second.InitFromFile("data/3x3-1.txt");
  result.InitFromFile("data/result/sub/3x3-3x3-1.txt");
  first -= second;
  bool check = first.IsEqualMatrix(result);
  ASSERT_EQ(check, true);
}

TEST(test, subMatrix3) {
  Matrix<double> first(10, 10);
  Matrix<double> second(10, 10);
  Matrix<double> result(10, 10);
  first.InitFromFile("data/10x10f.txt");
  second.InitFromFile("data/10x10-1f.txt");
  result.InitFromFile("data/result/sub/10x10-10x10-1f.txt");
  first -= second;
  bool check = first == result;
  ASSERT_EQ(check, true);
}

TEST(test, subMatrix4) {
  Matrix<double> first(10, 10);
  Matrix<double> second(10, 10);
  Matrix<double> result(10, 10);
  first.InitFromFile("data/10x10.txt");
  second.InitFromFile("data/10x10-1.txt");
  result.InitFromFile("data/result/sub/10x10-10x10-1.txt");
  first -= second;
  bool check = first == result;
  ASSERT_EQ(check, true);
}

TEST(test, subMatrix5) {
  Matrix<double> first(5, 5);
  Matrix<double> second(5, 5);
  Matrix<double> result(5, 5);
  first.InitFromFile("data/5x5.txt");
  second.InitFromFile("data/5x5-1.txt");
  result.InitFromFile("data/result/sub/5x5-5x5-1.txt");
  first -= second;
  bool check = first == result;
  ASSERT_EQ(check, true);
}

TEST(test, subMatrix6) {
  Matrix<double> first(5, 5);
  Matrix<double> second(5, 5);
  Matrix<double> result(5, 5);
  first.InitFromFile("data/5x5.txt");
  second.InitFromFile("data/5x5-0.txt");
  result.InitFromFile("data/result/sub/5x5-zero.txt");
  first -= second;
  bool check = first == result;
  ASSERT_EQ(check, true);
}

TEST(test, mulNumber) {
  Matrix<double> first(5, 5);
  Matrix<double> result(5, 5);
  first.InitFromFile("data/30x30f.txt");
  result.InitFromFile("data/result/multNumber/30x30f*33f.txt");
  first *= 33;
  bool check = first == result;
  ASSERT_EQ(check, true);
}

TEST(test, Determinant2) {
  Matrix<double> first(2, 2);
  double res = 0, cmpRes = -681;
  first.InitFromFile("data/2x2.txt");
  res = first.Determinant();
  ASSERT_EQ(res, cmpRes);
}

TEST(test, Determinant3) {
  Matrix<double> first(1, 1);
  double res = 0, cmpRes = 89;
  first.InitFromFile("data/1.txt");
  res = first.Determinant();
  ASSERT_EQ(res, cmpRes);
}

TEST(test, mulMatrix1) {
  Matrix<double> first(7, 7);
  Matrix<double> second(7, 7);
  Matrix<double> result(7, 7);
  first.InitFromFile("data/7x7f.txt");
  second.InitFromFile("data/7x7-1f.txt");
  result.InitFromFile("data/result/multMatrix/7x7f*7x7-1f.txt");
  first = first * second;
  bool check = first == result;
  ASSERT_EQ(check, true);
}

TEST(test, mulMatrix2) {
  Matrix<double> first(5, 5);
  Matrix<double> second(5, 5);
  Matrix<double> result(5, 5);
  first.InitFromFile("data/5x5.txt");
  second.InitFromFile("data/5x5-1.txt");
  result.InitFromFile("data/result/multMatrix/5x5*5x5-1.txt");
  first *= second;
  bool check = first == result;
  ASSERT_EQ(check, true);
}

TEST(test, Transpose1) {
  Matrix<double> first(30, 30);
  Matrix<double> result(30, 30);
  Matrix<double> tmp(30, 30);
  first.InitFromFile("data/30x30f.txt");
  result.InitFromFile("data/result/transponse/30x30f.txt");
  tmp = first.Transpose();
  bool check = tmp == result;
  ASSERT_EQ(check, true);
}

TEST(test, Transpose2) {
  Matrix<double> first(7, 7);
  Matrix<double> result(7, 7);
  Matrix<double> tmp(7, 7);
  first.InitFromFile("data/7x7f.txt");
  result.InitFromFile("data/result/transponse/7x7f.txt");
  tmp = first.Transpose();
  bool check = tmp == result;
  ASSERT_EQ(check, true);
}

TEST(test, Transpose3) {
  Matrix<double> first(2, 22);
  Matrix<double> result(22, 2);
  Matrix<double> tmp(22, 2);
  first.InitFromFile("data/2x22f.txt");
  result.InitFromFile("data/result/transponse/2x22f.txt");
  tmp = first.Transpose();
  bool check = tmp == result;
  ASSERT_EQ(check, true);
}

TEST(test, Determinant1) {
  Matrix<double> first(5, 5);
  double res = 0, cmpRes = -96;
  first.InitFromFile("data/5x5.txt");
  res = first.Determinant();
  ASSERT_EQ(res, cmpRes);
}

TEST(test, Determinant4) {
  Matrix<double> A(2, 2);
  A.InitFromFile("data/2x2.txt");
  ASSERT_EQ(A.Determinant(), -681);
}

TEST(test, Determinant5) {
  Matrix<double> A(1, 1);
  A.InitFromFile("data/1.txt");
  ASSERT_EQ(A.Determinant(), 89);
}

TEST(test, calcComplements) {
  Matrix<double> A(3, 3);
  Matrix<double> B(3, 3);
  Matrix<double> C(3, 3);
  A.InitFromFile("data/calc.txt");
  B.InitFromFile("data/result/calc/1.txt");
  C = A.CalcComplements();
  bool result = C == B;
  ASSERT_EQ(result, true);
}

TEST(test, inverseMatrix) {
  Matrix<double> A(3, 3);
  Matrix<double> B(3, 3);
  Matrix<double> C(3, 3);
  A.InitFromFile("data/inverse.txt");
  B.InitFromFile("data/result/inverse/1.txt");
  C = A.InverseMatrix();
  bool result = C == B;
  ASSERT_EQ(result, true);
}

TEST(test, expectEq) {
  Matrix<double> A(2, 3);
    A.InitFromFile("data/2x3.txt");
  Matrix<double> B(3, 2);
  B.InitFromFile("data/3x2.txt");
  ASSERT_EQ(A == B, false);
}

TEST(test, expectSum) {
  Matrix<double> A(2, 3);
  A.InitFromFile("data/2x3.txt");
  Matrix<double> B(3, 2);
  B.InitFromFile("data/3x2.txt");
  EXPECT_THROW(A.SumMatrix(B), std::exception);
}

TEST(test, expectSub) {
  Matrix<double> A(2, 3);
  A.InitFromFile("data/2x3.txt");
  Matrix<double> B(3, 2);
  B.InitFromFile("data/3x2.txt");
  EXPECT_THROW(A.SubMatrix(B), std::exception);
}

TEST(test, expectMulNum) {
  Matrix<double> A(2, 3);
  A.InitFromFile("data/2x3.txt");
  Matrix<double> B(3, 2);
  B.InitFromFile("data/3x2.txt");
  EXPECT_THROW(A.MulNumber(NAN), std::exception);
}

TEST(test, expectMul) {
  Matrix<double> A(2, 3);
  A.InitFromFile("data/2x3.txt");
  Matrix<double> B(3, 3);
  B.InitFromFile("data/3x3.txt");
  EXPECT_THROW(A.MulMatrix(B), std::exception);
}

TEST(test, expectInit) {
  Matrix<double> A(2, 3);
  A.InitFromFile("data/2x3.txt");
  Matrix<double> B(3, 2);
  B.InitFromFile("data/3x2.txt");
  EXPECT_THROW(A.InitFromFile("blabla"), std::exception);
}

TEST(test, expectOperatorBrackets) {
  Matrix<double> A(2, 2);
  A.InitFromFile("data/2x2.txt");
  EXPECT_THROW(A(2, 3), std::exception);
}

TEST(test, expectDeterm) {
  Matrix<double> A(2, 3);
  A.InitFromFile("data/2x3.txt");
  EXPECT_THROW(A.Determinant(), std::exception);
}

TEST(test, expectCalcComplements) {
  Matrix<double> A(2, 3);
  A.InitFromFile("data/2x3.txt");
  EXPECT_THROW(A.CalcComplements(), std::exception);
}

TEST(test, expectConstructor) {
  EXPECT_THROW(Matrix<double> A(2, 0), std::exception);
}

TEST(test, setElm) {
  Matrix<double> A(2, 2);
  Matrix<double> B(3, 3);
  A.InitFromFile("data/2x2.txt");
  A.SetRows(3);
  A.SetColumns(3);
  B.InitFromFile("data/upto3.txt");
  bool result = B == A;
  ASSERT_EQ(true, result);
}

TEST(test, expectSetRows) {
  Matrix<double> A;
  EXPECT_THROW(A.SetRows(0), std::exception);
}

TEST(test, expectSetColumns) {
  Matrix<double> A;
  EXPECT_THROW(A.SetColumns(0), std::exception);
}

TEST(test, expectinverse) {
  Matrix<double> A(2, 3);
  EXPECT_THROW(A.InverseMatrix(), std::exception);
}

TEST(test, copyMatrix) {
  Matrix<double> A(2, 2);
  A.InitFromFile("data/2x2.txt");
  Matrix<double> B(A);
  bool result = A == B;
  ASSERT_EQ(result, true);
}

TEST(test, transferMatrix) {
  Matrix<double> A(2, 2);
  A.InitFromFile("data/2x2.txt");
  Matrix<double> B = std::move(A);
  Matrix<double> C(2, 2);
  C.InitFromFile("data/2x2.txt");
  bool result = C == B;
  ASSERT_EQ(result, true);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
