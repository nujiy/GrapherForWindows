#include "View/MainWindowProSink/mainwindowprosink.h"
#include "View/mainwindow.h"

MainWindowProSink::MainWindowProSink(MainWindow* ptr)
{
    this->ptr_MainWindow = ptr;
}

// depending on different results, execute different tasks.
void MainWindowProSink::OnPropertyChanged(const std::string &str)
{
    if (str == "Lexer")
    {
        ptr_MainWindow->GraphPlot();
    }
}
