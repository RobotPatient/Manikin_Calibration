#ifndef LINEARREGRESSION_HPP
#define LINEARREGRESSION_HPP

struct linearValue
{
    float alpha;
    float beta;
};

class LinearRegression
{
private:
    // PredictedDependentValue = alpha * independentValue + beta
    struct linearValue _linearValue;
    int _n;
    float _yg = 0.0f, _r2, _standardError;
    float *_dependantValue, *_independentValue, _nf;

public:
    LinearRegression(float *y, float *x, int n);
    LinearRegression(float alpha, float beta);
    ~LinearRegression();
    linearValue calcAlphaBeta();
    float calcR2();
    float calcStandardError();

    float getYValue(int i);
    float getThing(int x);

protected:
    float calcYMean();
    float calcPredictedValue(float x);
};

#endif