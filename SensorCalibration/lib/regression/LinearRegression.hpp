#ifndef LINEARREGRESSION_HPP
#define LINEARREGRESSION_HPP

struct linearValue
{
    float b0;
    float b1;
};

class LinearRegression
{
private:
    // PredictedDependentValue = linearValue.b1 * independentValue + linearValue.b0
    struct linearValue _linearValue;
    int _sampleAmount;
    float _dependantMean = 0.0f, _r2, _standardError;
    float *_dependantValue, *_independentValue, _sampleAmountFloat;

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