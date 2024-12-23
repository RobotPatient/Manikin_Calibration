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

linearValue LinearRegression::calcAlphaBeta()
{
    // _dependantValue = b1 * _independentValue + b0
    double xy = 0.0f, x2 = 0.0f, xtussen;
    double dependantAverage = calcAverage(_dependantValue, _sampleAmount);
    double independentAverage = calcAverage(_independentValue, _sampleAmount);

    // _linearValue.b1 = -1.0f;
    // _linearValue.b0 = -1.0f;

    for (unsigned int i = 0; i < _sampleAmount; i++)
    {
        xtussen = _independentValue[i] - independentAverage;
        xy += xtussen * (_dependantValue[i] - dependantAverage);
        x2 += xtussen * xtussen;
    }

    _linearValue.b1 = xy / x2;
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
    double yl = 0.0f, yr = 0.0f, ytussenl, ytussenr;
    double dependantAverage = calcAverage(_dependantValue, _sampleAmount);

    for (unsigned int i = 0; i < _sampleAmount; i++)
    {
        ytussenl = calcPredictedValue(_independentValue[i]) - dependantAverage;
        ytussenr = _dependantValue[i] - dependantAverage;
        yl += ytussenl * ytussenl;
        yr += ytussenr * ytussenr;
    }

    return _r2 = yl / yr;
}

double LinearRegression::calcStandardError()
{
    double ytussen, ysom = 0.0f;
    for (unsigned int i = 0; i < _sampleAmount; i++)
    {
        ytussen = calcPredictedValue(_independentValue[i]) - _dependantValue[i];
        ysom += ytussen * ytussen;
    }

    return _standardError = sqrt(ysom / (_sampleAmountFloat - _order));
}