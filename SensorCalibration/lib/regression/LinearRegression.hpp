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
    unsigned int _sampleAmount;
    float _dependantMean = 0.0f, _r2, _standardError;
    float *_dependantValue, *_independentValue, _sampleAmountFloat;
    const unsigned int _order = 2;

public:
    LinearRegression(float *y, float *x, unsigned int n);
    ~LinearRegression();
    void setAlphaBeta(float alpha, float beta);
    linearValue calcAlphaBeta();
    float calcR2();
    float calcStandardError();

    float getYValue(int i);
    float getThing(int x);

protected:
    float calcAverage(float *numbers, unsigned int amount);
    float calcPredictedValue(float x);
};

#endif