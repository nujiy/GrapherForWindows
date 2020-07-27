#pragma once

#include "Common/etlbase.h"

class MainWindow;
class MainWindowProSink: public IPropertyNotification
{
private:
    MainWindow* ptr_MainWindow;
public:
    MainWindowProSink(MainWindow* ptr);
    void OnPropertyChanged(const std::string &str);
};
