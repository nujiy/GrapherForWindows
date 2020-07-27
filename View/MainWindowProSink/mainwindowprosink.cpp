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
    else if (str == "Integral")
    {
        ptr_MainWindow->showIntegral();
        ptr_MainWindow->repaint();
    }
    else if (str == "Differential")
    {
        ptr_MainWindow->showDifferential();
        ptr_MainWindow->repaint();
    }
}
