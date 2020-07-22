#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include "Model/Model.h"
#include "../Common/etlbase.h"
#include "ViewModel/Sinks/ViewModelSink.h"
#include "ViewModel/Commands/PaintCommand.h"

class ViewModel:public Proxy_PropertyNotification<ViewModel>,
        public Proxy_CommandNotification<ViewModel>
{
public:
    ViewModel();
    ~ViewModel();
    void setModel(std::shared_ptr<Model> ptr_Model);
    std::shared_ptr<ICommandBase> getPaintCmd();
    bool CalcCoordinate(const std::string &str,const double &left,const double &right);
    std::shared_ptr<QVector<double>> getX();
    std::shared_ptr<QVector<double>> getY();
private:
    std::shared_ptr<Model> ptr_Model;
    std::shared_ptr<ViewModelSink> ptr_ViewModelSink;
    std::shared_ptr<PaintCommand> ptr_PaintCmd;
};

#endif // VIEWMODEL_H
