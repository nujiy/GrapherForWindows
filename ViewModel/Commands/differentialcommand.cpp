#include "differentialcommand.h"
#include "ViewModel/ViewModel.h"

DifferentialCommand::DifferentialCommand(ViewModel* ptr_ViewModel)
{
    this->ptr_ViewModel = ptr_ViewModel;
}

void DifferentialCommand::SetParameter(const std::string &param, const double &param1)
{
    str = param;
    x = param1;
}

void DifferentialCommand::Exec()
{
    ptr_ViewModel->CalcDifferential(str,x);
    ptr_ViewModel->Fire_OnCommandComplete("DifferentialCommand", true);
}
