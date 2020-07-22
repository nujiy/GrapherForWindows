#pragma once

#include "Common/etlbase.h"

class MainWindow;
class MainWindowSetSink : public ICommandNotification
{
private:
    MainWindow* ptr_MainWindow;
public:
    MainWindowSetSink(MainWindow* ptr);
    void OnCommandComplete(const std::string &str, bool bOK);
};
