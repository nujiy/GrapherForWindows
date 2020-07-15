#pragma once

#include <View/mainwindow.h>
#include <View/startinterface.h>
#include <App/StartUICommand/StartUICommand.h>

class APP
{
public:
    startinterface startwindow;
    MainWindow mainwindow;
    std::shared_ptr<StartUICommand> start_ui_command;

public:
    APP();
    ~APP();
    void run();
};
