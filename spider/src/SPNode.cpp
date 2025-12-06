#include "SPNode.h"

#include <map>

#include "Spider.h"
#include "SPColor.h"

using namespace std;

namespace spider {



    SPNode::SPNode() {
        if(this->m_window == NULL)
            this->m_window = this;
            this->children = new vector<SPNode *>();
            this->properties = new map<string, void*>();
            this->stringAttributes = new map<string, string>();
            this->colorAttributes = new map<string, SPColor>();
            this->integerAttributes = new map<string, int>();
    }
    SPNode* SPNode::getParent() {
        return this->m_parent;
    }
    void SPNode::removeChild(SPNode *child) {
    }
    string SPNode::getStringAttribute(string title, string defaultValue) {
        return (*this->stringAttributes)[title];
    }
    void SPNode::setStringAttribute(string title, string value) {
        (*this->stringAttributes)[title] = value;
    }
    void SPNode::setColorAttribute(string title, SPColor value) {
        (*this->colorAttributes)[title] = value;
    }
    SPColor SPNode::getColorAttribute(string title, SPColor defaultValue) {
        return (*this->colorAttributes)[title];
    }
    int SPNode::getIntegerAttribute(string title, int defaultValue) {
        return (*this->integerAttributes)[title];
    }
    void SPNode::setIntegerAttribute(string title, int value) {
        (*this->integerAttributes)[title] = value;
    }
    std::vector<SPNode *> *SPNode::getChildNodes() {
        return (this->children);
    }
    bool SPNode::hasAttribute(string attr) {
        map<string, void *>::iterator it = this->properties->find(attr);
        return it != this->properties->end();
    }

    void SPNode::setParent(SPNode *elm) {
        this->m_parent = (elm);
    }
    std::string SPNode::get(const std::string& title) {
        std::string val = (*this->stringAttributes)[title];
        return val;
    }
    void* SPNode::getObject(const std::string& title) {
        return (*this->properties)[title];
    }

    string SPNode::getValue(const string& attrib)
    {
        return "";
    }


    SPNode* SPNode::getElementById(string id)
    {
        return nullptr;
    }

    void SPNode::set(const std::string& title, const std::string& val) {
        int n = 0;
        (*this->stringAttributes)[title] = val;
        try {
            n = atoi(val.c_str());



            (*this->integerAttributes)[title] = n;
        } catch (exception e) {
            
        }

        if(val.find("#") == 0) {
            SPColor c = SPColor(val);
            (*this->colorAttributes)[title] = c;
        }
    }

    void SPNode::appendChild(spider::SPNode *child) {
        vector<SPNode *> *nodes = this->children;
        if (nodes == NULL) {
            nodes = new vector<SPNode *>();
        }
        nodes->push_back(child);
        child->setParent(this);
        child->m_window = this->getWindowNode();
    }
    SPNode *getElementById(string *id) {
        return NULL;
    }
    SPNode *SPNode::getWindowNode() {
        return this->m_window;
    }








}
