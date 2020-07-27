#include "Model/Model.h"


Model::Model()
{
    lexer = std::make_shared<class Lexer>();
    x = std::make_shared<QVector<double>>();
    y = std::make_shared<QVector<double>>();
    IntegralAnswer = std::make_shared<double>();
    DifferentialAnswer = std::make_shared<double>();
}

Model::~Model()
{
}

// Model::cal(double a, double b) is used to
// generate graph point, a is the lower bound
// and b is the upper bound.
void Model::cal(double a,double b)
{
    // clear x and y.
    while(!x->empty())x->pop_back();
    while(!y->empty())y->pop_back();

    // generate y depending on x
    // number of point is decided by PointNumber which is specified in header.
    for(int i=0;i<PointNumber;i++)
    {
        x->push_back(a+(b-a)*i*1.0/PointNumber);
        y->push_back(lexer->calculate((*x)[i]));
    }
    Fire_OnPropertyChanged("Lexer");
}

std::shared_ptr<QVector<double>> Model::getX()
{
    return x;
}

std::shared_ptr<QVector<double>> Model::getY()
{
    return y;
}

// To generate point (x,y), we need to first build
// the expression tree.
bool Model::buildtree(const string str)
{
    lexer->setstring(str);
    if(lexer->string_to_tree())return true;
    else return false;
}

std::string Model::getString()
{
    return lexer->getstring();
}

std::shared_ptr<double> Model::getDifferential()
{
    return DifferentialAnswer;
}

std::shared_ptr<double> Model::getIntegral()
{
    return IntegralAnswer;
}

void Model::integral(double a, double b)
{
    *IntegralAnswer = lexer->integralcal(a,b);
    Fire_OnPropertyChanged("Integral");
}

void Model::differential(double x)
{
    *DifferentialAnswer = lexer->differentialCal(x);
    Fire_OnPropertyChanged("Differential");
}
