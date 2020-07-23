#include <App/APP.h>

APP::APP()
{
}

APP::~APP()
{
}

void APP::run()
{
    startwindow.setWindowTitle("Grapher");
    mainwindow.setWindowTitle("Grapher");

    // binding model with viewmodel
    model = std::make_shared<Model>();
    viewmodel = std::make_shared<ViewModel>();
    viewmodel->setModel(model);

    // binding viewmodel with view
    mainwindow.Set_Paint_Command(viewmodel->getPaintCmd());
    mainwindow.Set_Integral_Command(viewmodel->getIntegralCmd());
    mainwindow.Set_Differential_Command(viewmodel->getDifferentialCmd());
    mainwindow.setIntegral(viewmodel->getIntegral());
    mainwindow.SetDifferential(viewmodel->getDifferential());
    mainwindow.set_x(viewmodel->getX());
    mainwindow.set_y(viewmodel->getY());

    viewmodel->AddPropertyNotification(mainwindow.getProSink());
    viewmodel->AddCommandNotification(mainwindow.getSetSink());

    // this part is necessary otherwise we can't access mainwindow
    // simply by class <StartUICommand>.
    start_ui_command = std::make_shared<StartUICommand>(this);
    startwindow.set_command(std::static_pointer_cast<ICommandBase>(this->start_ui_command));
    startwindow.show();
}
