#include "LinearRegression.hpp"
#include <cmath>
#include <string.h>

LinearRegression::LinearRegression(float *y, float *x, int n) : _n{n}
{
    _y = new float[n];
    _x = new float[n];
    _nf = (float)_n;
    memcpy(_y, y, _n);
    memcpy(_x, x, _n);
}

LinearRegression::~LinearRegression()
{
}

linearValue LinearRegression::calcAlphaBeta()
{
    // _y = alpha * _x + beta
    // also sets _yg
    float xg = 0.0f, xy = 0.0f, x2 = 0.0f, xtussen;

    _linearValue.alpha = -1.0f;
    _linearValue.beta = -1.0f;

    for (int i = 0; i < _n; i++)
    {
        xg += _x[i];
        _yg += _y[i];
    }

    for (int i = 0; i < _n; i++)
    {
        xtussen = _x[i] - xg;
        xy += xtussen * (_y[i] - _yg);
        x2 += xtussen * xtussen;
    }

    _linearValue.alpha = xy / x2;
    _linearValue.beta = _yg - _linearValue.alpha * xg;
    return _linearValue;
}

float LinearRegression::calcValue(float x)
{
    return _linearValue.alpha * x + _linearValue.beta;
}

float LinearRegression::calcR2()
{
    float  yl = 0.0f, yr = 0.0f, ytussenl, ytussenr;

    for (int i = 0; i < _n; i++)
    {
        ytussenl = (1 * i ) - _yg;
        ytussenr = _y[i] - _yg;
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
        ytussen = calcValue(i) - _y[i];
        ysom += ytussen * ytussen;
    }

    return _standardError = sqrt(ysom / (_nf - 2));
}