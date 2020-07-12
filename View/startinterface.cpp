#include "startinterface.h"
#include "ui_startinterface.h"

startinterface::startinterface(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::startinterface)
{
    ui->setupUi(this);
}

startinterface::~startinterface()
{
    delete ui;
}

