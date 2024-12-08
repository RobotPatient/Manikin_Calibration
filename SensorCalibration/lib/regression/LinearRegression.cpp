#include "LinearRegression.hpp"
#include <cmath>
#include <string.h>

LinearRegression::LinearRegression(float *y, float *x, int n) : _n{n}
{
    _dependantValue = new float[_n];
    _independentValue = new float[_n];
    _nf = (float)_n;
    for (int i = 0; i < _n; i++)
    {
        _dependantValue[i] = y[i];
        _independentValue[i] = x[i];
    }
}

LinearRegression::LinearRegression(float alpha, float beta)
{
    _linearValue.alpha = alpha;
    _linearValue.beta = beta;
}

LinearRegression::~LinearRegression()
{
    delete _dependantValue;
    delete _independentValue;
}

float LinearRegression::getThing(int x)
{
    return _dependantValue[x];
}

float LinearRegression::calcYMean()
{
    if (_yg != 0.0f) // _yg is already been calculated, no need to do it again
    {
        return _yg;
    }

    _yg = 0.0f;

    for (int i = 0; i < _n; i++)
    {
        _yg += _dependantValue[i];
    }
    return _yg /= _nf;
}

linearValue LinearRegression::calcAlphaBeta()
{
    // _dependantValue = alpha * _independentValue + betas
    float xg = 0.0f, xy = 0.0f, x2 = 0.0f, xtussen;
    float yg = calcYMean();

    _linearValue.alpha = -1.0f;
    _linearValue.beta = -1.0f;

    for (int i = 0; i < _n; i++)
    {
        xg += _independentValue[i];
    }

    xg /= _nf;

    for (int i = 0; i < _n; i++)
    {
        xtussen = _independentValue[i] - xg;
        xy += xtussen * (_dependantValue[i] - yg);
        x2 += xtussen * xtussen;
    }

    _linearValue.alpha = xy / x2;
    _linearValue.beta = yg - _linearValue.alpha * xg;
    return _linearValue;
}

float LinearRegression::calcPredictedValue(float x)
{
    return _linearValue.alpha * x + _linearValue.beta;
}

float LinearRegression::getYValue(int i)
{
    return _dependantValue[i];
}

float LinearRegression::calcR2()
{
    float j = 0.0f, yl = 0.0f, yr = 0.0f, ytussenl, ytussenr;
    float yg = calcYMean();

    for (int i = 0; i < _n; i++)
    {
        ytussenl = calcPredictedValue(_independentValue[i]) - yg;
        ytussenr = _dependantValue[i] - yg;
        yl += ytussenl * ytussenl;
        yr += ytussenr * ytussenr;
    }

    return _r2 = yl / yr;
}

float LinearRegression::calcStandardError()
{
    float ytussen, ysom = 0.0f;
    for (int i = 0; i < _n; i++)
    {
        ytussen = calcPredictedValue(_independentValue[i]) - _dependantValue[i];
        ysom += ytussen * ytussen;
    }

    return _standardError = sqrt(ysom / (_nf - 2));
}