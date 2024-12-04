#define DOCTEST_CONFIG_IMPLEMENT  // REQUIRED: Enable custom main()
#include <doctest.h>

#include "LinearRegression.hpp"

TEST_CASE("Testing linear regression functions")
{
    static const int n = 10;
    float y[n] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
    float x[n] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};

    struct linearValue myValue;

    LinearRegression test(y, x, n);
    myValue = test.calcAlphaBeta();
    CHECK(myValue.alpha == 1.0f);
    CHECK(myValue.beta == 0.0f);
    CHECK(test.calcR2() == 1.0f);
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