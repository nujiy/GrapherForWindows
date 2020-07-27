#pragma once

#include <Model/Model.h>
#include <View/mainwindow.h>
#include <View/startinterface.h>
#include <ViewModel/ViewModel.h>
#include <App/StartUICommand/StartUICommand.h>

class APP
{
public:
    startinterface startwindow;
    MainWindow mainwindow;
    std::shared_ptr<Model> model;
    std::shared_ptr<ViewModel> viewmodel;
    std::shared_ptr<StartUICommand> start_ui_command;

public:
    APP();
    ~APP();
    void run();
};
