#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include "Model/Model.h"
#include "../Common/etlbase.h"
#include "ViewModel/Sinks/ViewModelSink.h"
#include "ViewModel/Commands/PaintCommand.h"
#include "ViewModel/Commands/integralcommand.h"
#include "ViewModel/Commands/differentialcommand.h"

class ViewModel:public Proxy_PropertyNotification<ViewModel>,
        public Proxy_CommandNotification<ViewModel>
{
public:
    ViewModel();
    ~ViewModel();
    void setModel(std::shared_ptr<Model> ptr_Model);
    std::shared_ptr<ICommandBase> getPaintCmd();
    std::shared_ptr<ICommandBase> getIntegralCmd();
    std::shared_ptr<ICommandBase> getDifferentialCmd();
    bool CalcCoordinate(const std::string &str,const double &left,const double &right);
    void CalcIntegral(const std::string &str,const double &left,const double &right);
    void CalcDifferential(const std::string &str, const double &x);
    std::shared_ptr<QVector<double>> getX();
    std::shared_ptr<QVector<double>> getY();
    std::shared_ptr<double> getIntegral();
    std::shared_ptr<double> getDifferential();
private:
    std::shared_ptr<Model> ptr_Model;
    std::shared_ptr<ViewModelSink> ptr_ViewModelSink;
    std::shared_ptr<PaintCommand> ptr_PaintCmd;
    std::shared_ptr<IntegralCommand> ptr_IntegralCmd;
    std::shared_ptr<DifferentialCommand> ptr_DifferentialCmd;
};

#endif // VIEWMODEL_H
