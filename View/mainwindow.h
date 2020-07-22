#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <cstdlib>
#include <QString>
#include <QMainWindow>
#include <QInputDialog>
#include <Common/etlbase.h>
#include <Lib/qcustomplot.h>
#include <View/MainWindowProSink/mainwindowprosink.h>
#include <View/MainWindowSetSink/mainwindowsetsink.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void GraphPlot();
    void PaintFailed();
    void PaintSucceed();
    void set_x(std::shared_ptr<QVector<double>> x);
    void set_y(std::shared_ptr<QVector<double>> y);
    void Set_Paint_Command(std::shared_ptr<ICommandBase> ptrCmd);
    std::shared_ptr<IPropertyNotification> getProSink(void);
    std::shared_ptr<ICommandNotification> getSetSink(void);

protected slots:
    void Save_Plot_As_PNG();
    void on_AddButton_clicked();
    void on_ClearButton_clicked();
    void on_RemoveButton_clicked();
    void selectionChanged();
    void mousePress();
    void mouseWheel();
    void axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part);
    void legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item);
    void titleDoubleClick(QMouseEvent* event);
    void addRandomGraph();
    void removeSelectedGraph();
    void removeAllGraphs();
    void contextMenuRequest(QPoint pos);
    void moveLegend();
    void graphClicked(QCPAbstractPlottable *plottable, int dataIndex);

private:
    QLabel* message;
    Ui::MainWindow *ui;
    std::shared_ptr<QVector<double>> x,y;
    std::shared_ptr<ICommandBase> PaintCommand;
    std::shared_ptr<MainWindowProSink> ptr_ProSink;
    std::shared_ptr<MainWindowSetSink> ptr_SetSink;
};

#endif // MAINWINDOW_H
