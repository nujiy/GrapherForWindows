#include "View/MainWindowSetSink/mainwindowsetsink.h"
#include "View/mainwindow.h"

MainWindowSetSink::MainWindowSetSink(MainWindow* ptr)
{
    this->ptr_MainWindow = ptr;
}

void MainWindowSetSink::OnCommandComplete(const std::string &str, bool bOK)
{
    // depending on whether the PaintCommand is succeed,
    // show different messages.
    if(str == "PaintCommand")
    {
        if(bOK)
            ptr_MainWindow->PaintSucceed();
        else
            ptr_MainWindow->PaintFailed();
    }
}
