#include <App/APP.h>

APP::APP()
{
}

APP::~APP()
{
}

void APP::run()
{
    // this part is necessary otherwise we can't access mainwindow
    // simply by class <StartUICommand>.
    startwindow.setWindowTitle("Grapher");
    mainwindow.setWindowTitle("Grapher");
    start_ui_command = std::make_shared<StartUICommand>(this);
    startwindow.set_command(std::static_pointer_cast<ICommandBase>(this->start_ui_command));
    startwindow.show();
}
