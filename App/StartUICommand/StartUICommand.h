// this class is used only for ui switching.
// that is, from startinterface to mainwindow.

#pragma once

#include <Common/etlbase.h>

class APP;
class StartUICommand : public ICommandBase
{
public:
    StartUICommand(APP* App_ptr);
    ~StartUICommand();
    virtual void SetParameter(const std::string &param,const double &param1);
    virtual void SetParameter(const std::string &param,const double &param1,const double &param2);
    virtual void Exec();
private:
    APP* App_ptr;
};


