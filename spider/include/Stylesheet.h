#ifndef STYLESHEET_H
#define STYLESHEET_H
#include "Node.h"
#ifdef _MSC_VER
#include <boost/config/compiler/visualc.hpp>
#endif
#include <boost/property_tree/ptree.hpp>
#include <string>
namespace spider {
class Stylesheet;

class Selector : Node {
public:
    Selector();
    virtual ~Selector();
};

class Stylesheet
{

    public:
        Stylesheet();
        virtual ~Stylesheet();
        string get(string entity, string prop);
    protected:
         boost::property_tree::ptree *pt;
        map<string, string> *selectors;
    private:
};
}

#endif // STYLESHEET_H
