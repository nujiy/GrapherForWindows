#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // https://www.qcustomplot.com/index.php/demos/interactionexample(reference)
    srand(QDateTime::currentDateTime().toTime_t());
    ui->setupUi(this);

    // QCustomPlot::setInteractions() sets possible interactions of QCustomPlot
    // as an OR-combination of QCP::Interaction enums.
    ui->CustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                                    QCP::iSelectPlottables | QCP::iSelectAxes | QCP::iSelectLegend);

    // This part deals with settings of xAxis and yAxis.
    ui->CustomPlot->xAxis->setRange(-8,8);    // initial xAxis range.
    ui->CustomPlot->yAxis->setRange(-5,5);      // initial yAxis range.
    // grid setting.
    ui->CustomPlot->xAxis->grid()->setPen(QPen(QColor(180,180,180),1,Qt::PenStyle::DashLine));
    ui->CustomPlot->yAxis->grid()->setPen(QPen(QColor(180,180,180),1,Qt::PenStyle::DashLine));
    ui->CustomPlot->xAxis->grid()->setSubGridPen(QPen(QColor(50,50,50),1,Qt::DotLine));
    ui->CustomPlot->yAxis->grid()->setSubGridPen(QPen(QColor(50,50,50),1,Qt::DotLine));
    ui->CustomPlot->xAxis->grid()->setZeroLinePen(QPen(Qt::blue));
    ui->CustomPlot->yAxis->grid()->setZeroLinePen(QPen(Qt::blue));
    // xAxis and yAxis tick settings.
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    ui->CustomPlot->xAxis->setTickPen(pen);
    ui->CustomPlot->xAxis->setTickLengthIn(5);
    ui->CustomPlot->yAxis->setTickPen(pen);
    ui->CustomPlot->yAxis->setTickLengthIn(5);
    // xAxis and yAxis label settings.
    ui->CustomPlot->xAxis->setLabel("X Axis");
    ui->CustomPlot->yAxis->setLabel("y Axis");
    // xAxis and yAxis Ending settings.
    ui->CustomPlot->xAxis->setUpperEnding(QCPLineEnding::esLineArrow);
    ui->CustomPlot->yAxis->setUpperEnding(QCPLineEnding::esLineArrow);
    ui->CustomPlot->axisRect()->setupFullAxesBox();

    // add Title For Graph Plot
    ui->CustomPlot->plotLayout()->insertRow(0);
    QCPTextElement* title = new QCPTextElement(ui->CustomPlot,"Function Graphs",
                                               QFont("Courier New",15,QFont::Bold));
    ui->CustomPlot->plotLayout()->addElement(0,0,title);

    // Legend settings (Current not visible)
    ui->CustomPlot->legend->setVisible(false);
    ui->CustomPlot->legend->setFont(QFont("Helvetica",10));
    ui->CustomPlot->legend->setSelectedFont(QFont("Helvetica",10));
    ui->CustomPlot->legend->setBrush(QColor(255,255,255,0));
    ui->CustomPlot->legend->setSelectedParts(QCPLegend::spItems); // only legend items can ba selected.

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(ui->CustomPlot, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(ui->CustomPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->CustomPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // connect some interaction slots:
    connect(ui->CustomPlot, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
    connect(ui->CustomPlot, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));
    connect(title, SIGNAL(doubleClicked(QMouseEvent*)), this, SLOT(titleDoubleClick(QMouseEvent*)));

    // connect slot that shows a message in the status bar when a graph is clicked:
    connect(ui->CustomPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*,int)));

    // setup policy and connect slot for context menu popup:
    ui->CustomPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->CustomPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::titleDoubleClick(QMouseEvent* event)
{
    Q_UNUSED(event)
    if (QCPTextElement* title = qobject_cast<QCPTextElement*>(sender()))
    {
        // Set the plot title by double clicking on it
        bool ok;
        QString newTitle = QInputDialog::getText(this, "Grapher Title", "New plot title:", QLineEdit::Normal, title->text(), &ok);
        if(ok)
        {
            title->setText(newTitle);
            ui->CustomPlot->replot();
        }
    }
}

void MainWindow::axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)
{
    // Set an axis label by double clicking on it
    if (part == QCPAxis::spAxisLabel)
    {
        bool ok;
        QString newLabel = QInputDialog::getText(this, "Axis Name", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
        if(ok)
        {
            axis->setLabel(newLabel);
            ui->CustomPlot->replot();
        }
    }
}

void MainWindow::legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item)
{
    // Rename a graph by double clicking on its legend item
    Q_UNUSED(legend)
    if (item)
    {
        QCPPlottableLegendItem* plItem = qobject_cast<QCPPlottableLegendItem*>(item);
        bool ok;
        QString newName = QInputDialog::getText(this, "Function Name", "New function name:",QLineEdit::Normal,plItem->plottable()->name(),&ok);
        if (ok)
        {
            plItem->plottable()->setName(newName);
            ui->CustomPlot->replot();
        }
    }
}

void MainWindow::selectionChanged()
{
    /*
     we tie the selected states of the tick label and the axis base line together.
     the axis label shall be selectable individually.(MainWindow::axisLabelDoubleClick)
     we synchronize the selection of the graphs with the selection state of the respective
     legend item belonging to that graph.
    */

    // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (ui->CustomPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->CustomPlot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
        ui->CustomPlot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->CustomPlot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        ui->CustomPlot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        ui->CustomPlot->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }

    // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (ui->CustomPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->CustomPlot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
          ui->CustomPlot->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->CustomPlot->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
      {
        ui->CustomPlot->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        ui->CustomPlot->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
      }

    // synchronize selection of graphs with selection of corresponding legend items:
    for (int i=0; i < ui->CustomPlot->graphCount();i++)
    {
        QCPGraph *graph = ui->CustomPlot->graph(i);
        QCPPlottableLegendItem *item = ui->CustomPlot->legend->itemWithPlottable(graph);
        if (item->selected() || graph->selected())
        {
            item->setSelected(true);
            graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
        }
    }
}

void MainWindow::mousePress()
{
    // if an axis is selected, only allow the direction of that axis to be dragged
    // if no axis is selected, both directions may be dragged
    if (ui->CustomPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->CustomPlot->axisRect()->setRangeDrag(ui->CustomPlot->xAxis->orientation());
    else if (ui->CustomPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->CustomPlot->axisRect()->setRangeDrag(ui->CustomPlot->yAxis->orientation());
    else
        ui->CustomPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void MainWindow::mouseWheel()
{
    // if an axis is selected, only allow the direction of that axis to be zoomed
    // if no axis is selected, both directions may be zoomed
    if (ui->CustomPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->CustomPlot->axisRect()->setRangeZoom(ui->CustomPlot->xAxis->orientation());
    else if (ui->CustomPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->CustomPlot->axisRect()->setRangeZoom(ui->CustomPlot->yAxis->orientation());
    else
        ui->CustomPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void MainWindow::removeSelectedGraph()
{
    if (ui->CustomPlot->selectedGraphs().size() > 0)
    {
        ui->CustomPlot->removeGraph(ui->CustomPlot->selectedGraphs().first());

        if (ui->CustomPlot->graphCount() <=0)
            ui->CustomPlot->legend->setVisible(false);
        ui->CustomPlot->replot();
    }
}

void MainWindow::removeAllGraphs()
{
    ui->CustomPlot->clearGraphs();
    if (ui->CustomPlot->graphCount() <= 0)
            ui->CustomPlot->legend->setVisible(false);
    ui->CustomPlot->replot();
}

void MainWindow::addRandomGraph()
{
    int n = 100; // number og points in graph
    double xScale = (rand()/(double)RAND_MAX + 0.5)*2;
    double yScale = (rand()/(double)RAND_MAX + 0.5)*2;
    double xOffset = (rand()/(double)RAND_MAX - 0.5)*4;
    double yOffset = (rand()/(double)RAND_MAX - 0.5)*10;
    double r1 = (rand()/(double)RAND_MAX - 0.5)*2;
    double r2 = (rand()/(double)RAND_MAX - 0.5)*2;
    double r3 = (rand()/(double)RAND_MAX - 0.5)*2;
    double r4 = (rand()/(double)RAND_MAX - 0.5)*2;
    QVector<double> x(n),y(n);
    for (int i=0; i<n; i++)
    {
        x[i] = (i/(double)n-0.5)*10.0*xScale + xOffset;
        y[i] = (qSin(x[i]*r1*5)*qSin(qCos(x[i]*r2)*r4*3)+r3*qCos(qSin(x[i])*r4*2))*yScale + yOffset;
    }
    ui->CustomPlot->addGraph();
    ui->CustomPlot->graph()->setName(QString("Random Graph %1").arg(ui->CustomPlot->graphCount()-1));
    ui->CustomPlot->graph()->setData(x,y);
    ui->CustomPlot->graph()->setLineStyle((QCPGraph::LineStyle)(rand()%5+1));
    if (rand()%100 > 50)
        ui->CustomPlot->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%14+1)));
    QPen graphPen;
    graphPen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
    graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);
    ui->CustomPlot->graph()->setPen(graphPen);

    if (ui->CustomPlot->graphCount() > 0)
        ui->CustomPlot->legend->setVisible(true);
    ui->CustomPlot->replot();
}

void MainWindow::Save_Plot_As_PNG()
{
    // Save Plot Image (PNG) in sub-folder "SavedPNG";
    QString FolderName = QDir::currentPath() + "\\SavedPNG";
    QDir dir(FolderName);
    if (!dir.exists())
        dir.mkdir(FolderName);

    // Support more than one Images Saved (plot1.png plot2.png ...)
    int i = 1;
    QString FileBase = FolderName + "\\plot";
    QFileInfo fileInfo(FileBase + "0" + QString::number(i) + ".png");
    while(fileInfo.isFile())
    {
        i++;
        if (i >= 10)
            fileInfo = FileBase + QString::number(i) + ".png";
        else
            fileInfo = FileBase + "0" + QString::number(i) + ".png";
    }

    // High Quality PNG
    if (i >= 10)
        ui->CustomPlot->savePng(FileBase + QString::number(i) + ".png",0,0,1.0,90);
    else
        ui->CustomPlot->savePng(FileBase + "0" + QString::number(i) + ".png",0,0,1.0,90);
}

void MainWindow::contextMenuRequest(QPoint pos)
{
    QMenu* menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);

    // context menu on legend requested
    if (ui->CustomPlot->legend->selectTest(pos, false) >= 0)
    {
        menu->addAction("Move to top left",this,SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignLeft));
        menu->addAction("Move to top center",this,SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignHCenter));
        menu->addAction("Move to top right",this,SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignRight));
        menu->addAction("Move to bottom left",this,SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
        menu->addAction("Move to bottom center",this,SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignHCenter));
        menu->addAction("Move to bottom right",this,SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignRight));

    }
    else // general context menu on graphs requested
    {
        menu->addAction("Add Random Graph", this, SLOT(addRandomGraph()));
        if(ui->CustomPlot->selectedGraphs().size() > 0)
            menu->addAction("Remove Selected Graph", this, SLOT(removeSelectedGraph()));
        if (ui->CustomPlot->graphCount() > 0)
            menu->addAction("Remove All Graphs", this, SLOT(removeAllGraphs()));
        if (ui->CustomPlot->graphCount() > 0)
            menu->addAction("Save Plot (PNG)",this, SLOT(Save_Plot_As_PNG()));
    }

    menu->popup(ui->CustomPlot->mapToGlobal(pos));
}

void MainWindow::moveLegend()
{
    if (QAction* contextAction = qobject_cast<QAction*>(sender()))
    {
        bool ok;
        int dataInt = contextAction->data().toInt(&ok);
        if (ok)
        {
            ui->CustomPlot->axisRect()->insetLayout()->setInsetAlignment(0,(Qt::Alignment)dataInt);
            ui->CustomPlot->replot();
        }
    }
}

void MainWindow::graphClicked(QCPAbstractPlottable *plottable, int dataIndex)
{
    double dataValue = plottable->interface1D()->dataMainValue(dataIndex);
    QString message = QString("Graph: '%1' data point: %2 Value: %3.").arg(plottable->name()).arg(dataIndex).arg(dataValue);
    ui->statusbar->showMessage(message);
}

void MainWindow::on_ClearButton_clicked()
{
    removeAllGraphs();
}

void MainWindow::on_RemoveButton_clicked()
{
    removeSelectedGraph();
}
