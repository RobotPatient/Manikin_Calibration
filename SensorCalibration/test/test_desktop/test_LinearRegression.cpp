#define DOCTEST_CONFIG_IMPLEMENT  // REQUIRED: Enable custom main()
#include <doctest.h>

#include "LinearRegression.hpp"

TEST_CASE("Testing linear regression functions")
{
    static const int n = 5;
    float x[n] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};//, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
    float y[n] = {2.0f, 4.0f, 5.0f, 4.0f, 5.0f};//, 6.02f, 6.5f, 8.1f, 8.2f, 9.9f};

    struct linearValue myValue;

    LinearRegression test(y, x, n);
    myValue = test.calcAlphaBeta();
    CHECK(myValue.alpha == 0.6f);
    CHECK(myValue.beta == 2.2f);
    CHECK(test.calcR2() == 0.6f);
    CHECK(test.calcStandardError() == 0.89f);
}
// TEST_SUITE ...

int main(int argc, char **argv)
{
  doctest::Context context;

  // BEGIN:: PLATFORMIO REQUIRED OPTIONS
  context.setOption("success", true);     // Report successful tests
  context.setOption("no-exitcode", true); // Do not return non-zero code on failed test case
  // END:: PLATFORMIO REQUIRED OPTIONS

  // YOUR CUSTOM DOCTEST OPTIONS

  context.applyCommandLine(argc, argv);
  return context.run();
}