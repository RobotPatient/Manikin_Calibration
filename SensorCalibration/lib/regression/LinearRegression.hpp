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
    double _dependantMean = 0.0f, _r2, _standardError;
    double *_dependantValue, *_independentValue, _sampleAmountFloat;
    const unsigned int _order = 2;

public:
    LinearRegression(double *x, double *y, unsigned int n);
    ~LinearRegression();
    void setAlphaBeta(double alpha, double beta);
    linearValue calcAlphaBeta();
    double calcR2();
    double calcStandardError();

    double getYValue(int i);
    double getThing(int x);

protected:
    double calcAverage(double *numbers, unsigned int amount);
    double calcPredictedValue(double x);
};

#endif