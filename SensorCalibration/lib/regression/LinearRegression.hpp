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
    struct linearValue _linearValue;
    int _n;
    float _yg, _r2, _standardError;
    float *_y, *_x, _nf;

public:
    LinearRegression(float *y, float *x, int n);
    ~LinearRegression();
    linearValue calcAlphaBeta();
    float calcR2();
    float calcStandardError();

protected:
    float calcValue(float x);
};

#endif