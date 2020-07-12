#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class startinterface; }
QT_END_NAMESPACE

class startinterface : public QWidget
{
    Q_OBJECT

public:
    startinterface(QWidget *parent = nullptr);
    ~startinterface();

private:
    Ui::startinterface *ui;
};
#endif // WIDGET_H
