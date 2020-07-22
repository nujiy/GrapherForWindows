#ifndef MODEL_H
#define MODEL_H

#include "Common/etlbase.h"
#include "Algorithm/Lexer.h"
#include <memory>
#include <vector>
#include <QVector>
#include <string>

#define PointNumber 1000

class Model: public Proxy_PropertyNotification<Model>
{
public:
    Model();
    ~Model();
    std::shared_ptr<QVector<double>> getX();
    std::shared_ptr<QVector<double>> getY();
    std::string getString();
    void cal(double a,double b);
    bool buildtree(const std::string str);
private:
    std::shared_ptr<Lexer> lexer;
    std::shared_ptr<QVector<double>> x,y;
};

#endif 
