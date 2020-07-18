#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <cstdlib>
#include <QString>
#include <QMainWindow>
#include <QInputDialog>
#include <Common/etlbase.h>
#include <Lib/qcustomplot.h>

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

protected slots:
    void Save_Plot_As_PNG();
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
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
