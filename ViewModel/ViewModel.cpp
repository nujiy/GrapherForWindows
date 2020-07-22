#include "ViewModel/ViewModel.h"
#include "ViewModel/Sinks/ViewModelSink.h"
#include "ViewModel/Commands/PaintCommand.h"

ViewModel::ViewModel()
{
    ptr_ViewModelSink = std::make_shared<ViewModelSink>(this);
    ptr_PaintCmd = std::make_shared<PaintCommand>(this);
}

ViewModel::~ViewModel()
{
}

void ViewModel::setModel(std::shared_ptr<Model> ptr_Model)
{
    this->ptr_Model = ptr_Model;
    this->ptr_Model->AddPropertyNotification(std::static_pointer_cast<IPropertyNotification>(ptr_ViewModelSink));
}

std::shared_ptr<ICommandBase> ViewModel::getPaintCmd()
{
    return std::static_pointer_cast<ICommandBase>(ptr_PaintCmd);
}

// str is the user-input string which is sent to ViewModel by View.
// left is the lower bound, right is the upper bound.
bool ViewModel::CalcCoordinate(const std::string &str, const double &left, const double &right)
{
    if(ptr_Model->buildtree(str))
    {
        ptr_Model->cal(left,right);
        return true;
    }
    else
    {
        return false;
    }
}

// get the result X coordinates.
std::shared_ptr<QVector<double> > ViewModel::getX()
{
    return ptr_Model->getX();
}

// get the result Y coordinates.
std::shared_ptr<QVector<double> > ViewModel::getY()
{
    return ptr_Model->getY();
}
