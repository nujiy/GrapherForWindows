#include <App/StartUICommand/StartUICommand.h>
#include <App/APP.h>

StartUICommand::StartUICommand(APP* App_ptr)
{
    this->App_ptr = App_ptr;
}

StartUICommand::~StartUICommand()
{
}

void StartUICommand::SetParameter(const std::string &param,const double &param1)
{
}

void StartUICommand::SetParameter(const std::string &param,const double &param1,const double &param2)
{
}

 void StartUICommand::Exec()
 {
    App_ptr->startwindow.close();
    App_ptr->mainwindow.show();
 }
