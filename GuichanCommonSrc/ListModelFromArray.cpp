#include "ListModelFromArray.h"

hpl::pes::ListModelFromArray::ListModelFromArray(std::vector<std::string>& lst):gcn::ListModel()
{
    //ÉRÉsÅ[
    for(int i = 0; i < (int)lst.size(); i ++){
        this->data.push_back(lst[i]);
    }
}
hpl::pes::ListModelFromArray::~ListModelFromArray()
{
    this->data.clear();
}

int hpl::pes::ListModelFromArray::getNumberOfElements()
{
    return (int)this->data.size();
}
std::string hpl::pes::ListModelFromArray::getElementAt(int i)
{
    if(i < 0 || i >= this->getNumberOfElements()){
        return std::string("");
    }else{
        return this->data[i];
    }
}
