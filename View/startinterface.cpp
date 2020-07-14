#include "startinterface.h"
#include "ui_startinterface.h"

startinterface::startinterface(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::startinterface)
{
    ui->setupUi(this);
}

void startinterface::set_command(std::shared_ptr<ICommandBase>& command)
{
    this->commands = command;
}

void startinterface::on_ExitButton_clicked()
{
    qApp->exit(0);
}

void startinterface::on_EnterButtion_clicked()
{

}

startinterface::~startinterface()
{
    delete ui;
}

