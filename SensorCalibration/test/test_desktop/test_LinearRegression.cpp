#include <doctest.h>

#include "LinearRegression.hpp"
// 1.07	0.75
// 2.09	2.45
// 2.95	2.71
// 3.95	3.58
// 4.99	5.11
// 6.01	5.62
// 6.93	6.66
// 8.07	8.24
// b1	1.0056
// b0	-0.1429
// R2	0.9863
// SEE	0.3117

// 1,375,1705,1544,1820,2048,2137,2140,2305,2528

// 2560,2640,2864,2912,2944,2960,2976,2976,2992,3008

TEST_CASE("Testing linear regression functions")
{
  // TODO: fix this test. x = input = measured, y = output = reference
  static const int sampleAmount = 10;
  // double referenceValues[sampleAmount] = {1, 375, 1705, 1544, 1820, 2048, 2137, 2140, 2305, 2528};
  // double measuredValues[sampleAmount] = {2560, 2640, 2864, 2912, 2944, 2960, 2976, 2976, 2992, 3008};
  double measuredValues[sampleAmount] = {1, 375, 1705, 1544, 1820, 2048, 2137, 2140, 2305, 2528};
  double referenceValues[sampleAmount] = {2560, 2640, 2864, 2912, 2944, 2960, 2976, 2976, 2992, 3008};

  struct linearValue myValue;

  LinearRegression test(measuredValues, referenceValues, sampleAmount);
  myValue = test.calcAlphaBeta();
  REQUIRE(myValue.b1 == doctest::Approx(5.25643));
  REQUIRE(myValue.b0 == doctest::Approx(2576));
  CHECK(test.calcR2() == doctest::Approx(0.98628));
  CHECK(test.calcStandardError() == doctest::Approx(0.3117).epsilon(0.01));
}
