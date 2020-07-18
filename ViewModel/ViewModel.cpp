#ifndef VIEWMODEL_H
#define VIEWMODEL_H

class ViewModel:public Proxy_PropertyNotification<ViewModel>,public Proxy_CommandNotification<ViewModel>
{
public:
    ViewModel();
    ~ViewModel();
    void setModel(std::shared_ptr<Model> ptr_Model);
    
    std::shared_ptr<ICommandBase> getPaintCmd();
    std::shared_ptr<ICommandBase> getDifferentialCmd();
    std::shared_ptr<ICommandBase> getIntegralCmd();
    
    void CalcDifferential(const std::string &str,const double &x);
    void CalcIntegral(const std::string &str,const double &left,const double &right);
    
    std::shared_ptr<QVector<double>> getX();
    std::shared_ptr<QVector<double>> getY();
    std::shared_ptr<double> getIntegral();
    std::shared_ptr<double> getDifferential();
    
private:
    std::shared_ptr<Model> ptr_Model;   
};

#endif
