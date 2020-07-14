#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <Common/etlbase.h>

QT_BEGIN_NAMESPACE
namespace Ui { class startinterface; }
QT_END_NAMESPACE

class startinterface : public QWidget
{
    Q_OBJECT

public:
    startinterface(QWidget *parent = nullptr);
    ~startinterface();
    void set_command(std::shared_ptr<ICommandBase>& command);

public slots:
    void on_EnterButtion_clicked();
    void on_ExitButton_clicked();

private:
    Ui::startinterface *ui;
    std::shared_ptr<ICommandBase> commands;
};
#endif // WIDGET_H
