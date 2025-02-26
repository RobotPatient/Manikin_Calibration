#include <doctest.h>

#include "matrix.hpp"

TEST_CASE("Matrix addition")
{
    matrix<double, 2, 3> A;
    matrix<double, 2, 3> B;
    matrix<double, 2, 3> C;
    A.setElement(0, 0, 1);
    A.setElement(0, 1, 3);
    A.setElement(0, 2, 4);
    A.setElement(1, 0, 1);
    A.setElement(1, 1, 0);
    A.setElement(1, 2, 0);

    CHECK(A.getElement(0, 0) == 1);

    B.setElement(0, 0, 0);
    B.setElement(0, 1, 0);
    B.setElement(0, 2, 2);
    B.setElement(1, 0, 7);
    B.setElement(1, 1, 5);
    B.setElement(1, 2, 0);

    CHECK(B.getElement(0, 0) == 0);

    C = A + B;
    CHECK(C.getElement(0, 0) == 1);
    CHECK(C.getElement(0, 1) == 3);
    CHECK(C.getElement(0, 2) == 6);
    CHECK(C.getElement(1, 0) == 8);
    CHECK(C.getElement(1, 1) == 5);
    CHECK(C.getElement(1, 2) == 0);
}

TEST_CASE("Matrix Scaler muliplication")
{
    matrix<double, 2, 3> A;
    matrix<double, 2, 3> B;
    double Scalar = 2;

    A.setElement(0, 0, 1);
    A.setElement(0, 1, 3);
    A.setElement(0, 2, 4);
    A.setElement(1, 0, 1);
    A.setElement(1, 1, 0);
    A.setElement(1, 2, 0);

    B = A * Scalar;

    CHECK(B.getElement(0, 0) == 2);
    CHECK(B.getElement(0, 1) == 6);
    CHECK(B.getElement(0, 2) == 8);
    CHECK(B.getElement(1, 0) == 2);
    CHECK(B.getElement(1, 1) == 0);
    CHECK(B.getElement(1, 2) == 0);
}

TEST_CASE("Matrix Multipilcation")
{
    matrix<int, 2, 3> A;
    matrix<int, 3, 2> B;
    matrix<int, 2, 2> C;

    A.setElement(0, 0, 1);
    A.setElement(0, 1, 0);
    A.setElement(0, 2, 2);
    A.setElement(1, 0, -1);
    A.setElement(1, 1, 3);
    A.setElement(1, 2, 1);

    B.setElement(0, 0, 3);
    B.setElement(0, 1, 1);
    B.setElement(1, 0, 2);
    B.setElement(1, 1, 1);
    B.setElement(2, 0, 1);
    B.setElement(2, 1, 0);

    C = A * B;

    CHECK(C.getElement(0, 0) == 5);
    CHECK(C.getElement(0, 1) == 1);
    CHECK(C.getElement(1, 0) == 4);
    CHECK(C.getElement(1, 1) == 2);
}

TEST_CASE("Matrix Determinant")
{
    matrix<int, 2, 2> A;
    A.setElement(0, 0, 3);
    A.setElement(0, 1, 7);
    A.setElement(1, 0, 1);
    A.setElement(1, 1, -4);

    matrix<int, 3, 3> B;
    B.setElement(0, 0, -2);
    B.setElement(0, 1, -1);
    B.setElement(0, 2, 2);
    B.setElement(1, 0, 2);
    B.setElement(1, 1, 1);
    B.setElement(1, 2, 4);
    B.setElement(2, 0, -3);
    B.setElement(2, 1, 3);
    B.setElement(2, 2, -1);

    matrix<int, 4, 4> C;
    C.setElement(0, 0, 2);
    C.setElement(0, 1, 1);
    C.setElement(0, 2, 0);
    C.setElement(0, 3, 3);

    C.setElement(1, 0, 4);
    C.setElement(1, 1, -1);
    C.setElement(1, 2, 2);
    C.setElement(1, 3, 0);

    C.setElement(2, 0, -3);
    C.setElement(2, 1, 2);
    C.setElement(2, 2, 1);
    C.setElement(2, 3, 5);

    C.setElement(3, 0, 1);
    C.setElement(3, 1, 0);
    C.setElement(3, 2, -2);
    C.setElement(3, 3, 3);

    CHECK(A.determinant() == -19);
    CHECK(B.determinant() == 54);
    CHECK(C.determinant() == -85);
}

TEST_CASE("Matrix inverse")
{
    matrix<double, 2, 2> A;
    A.setElement(0, 0, 1);
    A.setElement(0, 1, 1);
    A.setElement(1, 0, 1);
    A.setElement(1, 1, 1);

    matrix<double, 3, 3> B;
    B.setElement(0, 0, 1);
    B.setElement(0, 1, 2);
    B.setElement(0, 2, 0);
    B.setElement(1, 0, 2);
    B.setElement(1, 1, 4);
    B.setElement(1, 2, 1);
    B.setElement(2, 0, 2);
    B.setElement(2, 1, 1);
    B.setElement(2, 2, 0);

    matrix<double, 4, 4> C;
    C.setElement(0, 0, 2);
    C.setElement(0, 1, 1);
    C.setElement(0, 2, 0);
    C.setElement(0, 3, 3);

    C.setElement(1, 0, 4);
    C.setElement(1, 1, -1);
    C.setElement(1, 2, 2);
    C.setElement(1, 3, 0);

    C.setElement(2, 0, -3);
    C.setElement(2, 1, 2);
    C.setElement(2, 2, 1);
    C.setElement(2, 3, 5);

    C.setElement(3, 0, 1);
    C.setElement(3, 1, 0);
    C.setElement(3, 2, -2);
    C.setElement(3, 3, 3);

    REQUIRE(A.determinant() != 0);
    A.inverse();
    CHECK(A.getElement(0, 0) == 1);
    CHECK(A.getElement(0, 1) == 1);
    CHECK(A.getElement(1, 0) == 1);
    CHECK(A.getElement(1, 1) == 1);

    B.inverse();
    // CHECK(B.getElement(0, 0) == -1 / 3);
    // CHECK(B.getElement(0, 1) == 0);
    // CHECK(B.getElement(0, 2) == 2 / 3);
    // CHECK(B.getElement(1, 0) == 2 / 3);
    // CHECK(B.getElement(1, 1) == 0);
    // CHECK(B.getElement(1, 2) == -1 / 3);
    // CHECK(B.getElement(2, 0) == -2);
    // CHECK(B.getElement(2, 1) == 1);
    // CHECK(B.getElement(2, 2) == 0);
    // C.inverse();
}