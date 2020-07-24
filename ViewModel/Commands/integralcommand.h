#ifndef INTEGRALCOMMAND_H
#define INTEGRALCOMMAND_H

#include "Common/etlbase.h"
#include <string>

using std::string;

class ViewModel;
class IntegralCommand : public ICommandBase
{
public:
    IntegralCommand(ViewModel* ptr_ViewModel);
    void SetParameter(const std::string &param, const double &param1){}
    void SetParameter(const std::string &param, const double &param1, const double &param2);
    void Exec();

private:
    ViewModel* ptr_ViewModel;
    double Upper,Lower;
    string str;
};

#endif // INTEGRALCOMMAND_H
