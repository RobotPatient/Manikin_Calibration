#include "LinearRegression.hpp"
#include <cmath> // used only for srqt()
// #include <string.h>

LinearRegression::LinearRegression(float *y, float *x, unsigned int n) : _sampleAmount{n}
{
    // change to ringbuffer with n size?
    _dependantValue = new float[_sampleAmount];
    _independentValue = new float[_sampleAmount];
    _sampleAmountFloat = (float)_sampleAmount;
    for (unsigned int i = 0; i < _sampleAmount; i++)
    {
        _dependantValue[i] = y[i];
        _independentValue[i] = x[i];
    }
}

LinearRegression::~LinearRegression()
{
    delete _dependantValue;
    delete _independentValue;
}

void LinearRegression::setAlphaBeta(float alpha, float beta)
{
    _linearValue.b1 = alpha;
    _linearValue.b0 = beta;
}

float LinearRegression::getThing(int x)
{
    return _dependantValue[x];
}

float LinearRegression::calcAverage(float *numbers, unsigned int amount)
{
    float sum = 0.0f;
    for (unsigned int i = 0; i < amount; i++)
    {
        sum += numbers[i];
    }
    return sum / (float)amount;
}

linearValue LinearRegression::calcAlphaBeta()
{
    // _dependantValue = b1 * _independentValue + b0
    float xy = 0.0f, x2 = 0.0f, xtussen;
    float dependantAverage = calcAverage(_dependantValue, _sampleAmount);
    float independentAverage = calcAverage(_independentValue, _sampleAmount);

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

float LinearRegression::calcPredictedValue(float x)
{
    return _linearValue.b1 * x + _linearValue.b0;
}

float LinearRegression::getYValue(int i)
{
    return _dependantValue[i];
}

float LinearRegression::calcR2()
{
    float yl = 0.0f, yr = 0.0f, ytussenl, ytussenr;
    float dependantAverage = calcAverage(_dependantValue, _sampleAmount);

    for (unsigned int i = 0; i < _sampleAmount; i++)
    {
        ytussenl = calcPredictedValue(_independentValue[i]) - dependantAverage;
        ytussenr = _dependantValue[i] - dependantAverage;
        yl += ytussenl * ytussenl;
        yr += ytussenr * ytussenr;
    }

    return _r2 = yl / yr;
}

float LinearRegression::calcStandardError()
{
    float ytussen, ysom = 0.0f;
    for (unsigned int i = 0; i < _sampleAmount; i++)
    {
        ytussen = calcPredictedValue(_independentValue[i]) - _dependantValue[i];
        ysom += ytussen * ytussen;
    }

    return _standardError = sqrt(ysom / (_sampleAmountFloat - _order));
}