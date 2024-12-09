#include <doctest.h>

#include "LinearRegression.hpp"

TEST_CASE("Testing linear regression functions")
{
  static const int sampleAmount = 5;
  float referenceValues[sampleAmount] = {1.0f, 2.0f, 3.0f, 4.0f,
                                         5.0f};
  float measuredValues[sampleAmount] = {2.0f, 4.0f, 5.0f, 4.0f,
                                        5.0f};

  struct linearValue myValue;

  LinearRegression test(measuredValues, referenceValues, sampleAmount);
  myValue = test.calcAlphaBeta();
  REQUIRE(myValue.b1 == 0.6f);
  REQUIRE(myValue.b0 == doctest::Approx(2.2f));
  CHECK(test.calcR2() == doctest::Approx(0.6f));
  CHECK(test.calcStandardError() == doctest::Approx(0.89f).epsilon(0.01));
}
