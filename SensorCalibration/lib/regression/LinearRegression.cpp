#include "LinearRegression.hpp"
#include <cmath> // used only for srqt()
// #include <string.h>

LinearRegression::LinearRegression(double *x, double *y, unsigned int n) : _sampleAmount{n}
{
    // change to ringbuffer with n size?
    _dependantValue = new double[_sampleAmount];
    _independentValue = new double[_sampleAmount];
    _sampleAmountFloat = (double)_sampleAmount;
    for (unsigned int i = 0; i < _sampleAmount; i++)
    {
        _dependantValue[i] = y[i];
        _independentValue[i] = x[i];
    }
}

LinearRegression::~LinearRegression()
{
    delete[] _dependantValue;
    delete[] _independentValue;
}

void LinearRegression::setAlphaBeta(double alpha, double beta)
{
    _linearValue.b1 = alpha;
    _linearValue.b0 = beta;
}

double LinearRegression::getThing(int x)
{
    return _dependantValue[x];
}

double LinearRegression::calcAverage(double *numbers, unsigned int amount)
{
    double sum = 0.0f;
    for (unsigned int i = 0; i < amount; i++)
    {
        sum += numbers[i];
    }
    return sum / (double)amount;
}

/*!
 * @brief Calculates \f$b_1\f$ and \f$b_0\f$ and uses the formulas:
 * \f[
 * b_1 = \frac{\sum_{i=0}^{n} (x_i - \bar{x})(y_i - \bar{y})}{\sum_{i=0}^{n} (x_i - \bar{x})^2}
 * \f]
 * \f[
 * b_0 = \bar{y} - b_1 \bar{x}
 * \f]
 *
 * @return struct with both \f$b_1\f$ and \f$b_0\f$
 */
linearValue LinearRegression::calcAlphaBeta()
{
    // _dependantValue = b1 * _independentValue + b0
    double numerator = 0.0f, denominator = 0.0f, deltaX;
    double dependantAverage = calcAverage(_dependantValue, _sampleAmount);
    double independentAverage = calcAverage(_independentValue, _sampleAmount);

    for (unsigned int i = 0; i < _sampleAmount; i++)
    {
        deltaX = _independentValue[i] - independentAverage;
        numerator += deltaX * (_dependantValue[i] - dependantAverage);
        denominator += deltaX * deltaX;
    }

    _linearValue.b1 = numerator / denominator;
    _linearValue.b0 = dependantAverage - _linearValue.b1 * independentAverage;
    return _linearValue;
}

double LinearRegression::calcPredictedValue(double x)
{
    return _linearValue.b1 * x + _linearValue.b0;
}

double LinearRegression::getYValue(int i)
{
    return _dependantValue[i];
}

double LinearRegression::calcR2()
{
    double sumSquaredResiduals = 0.0f;
    double sumSquaredTotal = 0.0f;
    double dependentAvg = calcAverage(_dependantValue, _sampleAmount);
    double predictedValue, residual, totalVariation;

    for (unsigned int i = 0; i < _sampleAmount; i++)
    {
        predictedValue = calcPredictedValue(_independentValue[i]);
        residual = predictedValue - dependentAvg;
        totalVariation = _dependantValue[i] - dependentAvg;

        sumSquaredResiduals += residual * residual;
        sumSquaredTotal += totalVariation * totalVariation;
    }

    return _r2 = sumSquaredResiduals / sumSquaredTotal;
}

double LinearRegression::calcStandardError()
{
    double sumSquaredErrors = 0.0f;
    double error;
    for (unsigned int i = 0; i < _sampleAmount; i++)
    {
        error = calcPredictedValue(_independentValue[i]) - _dependantValue[i];
        sumSquaredErrors += error * error;
    }

    return _standardError = sqrt(sumSquaredErrors / (_sampleAmountFloat - _order));
}
