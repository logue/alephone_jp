#ifndef _PES_LIST_MODEL_FROM_ARRAY_
#define _PES_LIST_MODEL_FROM_ARRAY_

#include <guichan.hpp>
#include <guichan/sdl.hpp>
#include "SDL.h"
#include <vector>

namespace hpl{
namespace pes{
    class ListModelFromArray: public gcn::ListModel{
    private:
        ListModelFromArray():gcn::ListModel(){}
        std::vector<std::string> data;
    public:
        ListModelFromArray(std::vector<std::string>& lst);
        virtual ~ListModelFromArray();

        virtual int getNumberOfElements();
        virtual std::string getElementAt(int i);
    };
};
};
#endif
