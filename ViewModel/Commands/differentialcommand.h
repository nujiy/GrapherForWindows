#ifndef DIFFERENTIALCOMMAND_H
#define DIFFERENTIALCOMMAND_H

#include "Common/etlbase.h"
#include <string>

using std::string;

class ViewModel;
class DifferentialCommand: public ICommandBase
{
public:
    DifferentialCommand(ViewModel* ptr_ViewModel);
    void SetParameter(const std::string &param, const double &param1);
    void SetParameter(const std::string &param, const double &param1, const double &param2){}
    void Exec();

private:
    ViewModel* ptr_ViewModel;
    double x;
    string str;
};

#endif // DIFFERENTIALCOMMAND_H
