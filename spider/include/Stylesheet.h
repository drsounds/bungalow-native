#ifndef STYLESHEET_H
#define STYLESHEET_H
#include "Node.h"
#ifdef _MSC_VER
#include <boost/config/compiler/visualc.hpp>
#endif
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <cassert>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
namespace spider {
class Node;
class Stylesheet;

#ifdef NODE_CLASS
#ifndef SELECTOR_CLASS
class Selector : Node {
public:
    Selector();
    virtual ~Selector();
};
#define SELECTOR_CLASS
#endif

#ifndef STYLESHEET_CLASS
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
#define STYLESHEET_CLASS
#endif
#endif
}

#endif // STYLESHEET_H
