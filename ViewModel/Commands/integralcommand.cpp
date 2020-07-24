#include "integralcommand.h"
#include "ViewModel/ViewModel.h"

IntegralCommand::IntegralCommand(ViewModel* ptr_ViewModel)
{
    this->ptr_ViewModel = ptr_ViewModel;
}

void IntegralCommand::SetParameter(const std::string &param, const double &param1, const double &param2)
{
    this->Upper = param2;
    this->Lower = param1;
    str = param;
}

void IntegralCommand::Exec()
{
    ptr_ViewModel->CalcIntegral(str,Lower,Upper);
    ptr_ViewModel->Fire_OnCommandComplete("Integral",true);
}

