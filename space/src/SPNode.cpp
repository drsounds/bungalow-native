#include "SPNode.h"

#include <map>

#include "SPColor.h"

using namespace std;

namespace space {
    SPNode::SPNode() {
        this->children = new vector<SPNode *>();
        this->properties = new map<string, void*>();
        this->stringAttributes = new map<string, string>();
        this->colorAttributes = new map<string, SPColor>();
        this->integerAttributes = new map<string, int>();
    }
    SPNode::SPNode(SPNode *parent) : SPNode() {
        if (parent == nullptr) {
            return;
        }
        SPWindow *window = parent->getWindow();
        if (window != nullptr) {
            this->setWindow(window);
        } 
    }
    SPNode* SPNode::getParent() {
        return this->m_parent;
    }
    void SPNode::removeChild(SPNode *child) {
    }
    string SPNode::getStringAttribute(const string& title, string defaultValue) {
        return (*this->stringAttributes)[title];
    }
    void SPNode::setStringAttribute(const string& title, string value) {
        (*this->stringAttributes)[title] = value;
    }
    void SPNode::setColorAttribute(const string& title, SPColor value) {
        (*this->colorAttributes)[title] = value;
    }
    SPColor SPNode::getColorAttribute(const string& title, SPColor defaultValue) {
    	SPColor color = SPColor(0, 0, 0, 0);

        if ((this->colorAttributes)->count(title)) {
	        color = (*this->colorAttributes)[title];
        }
		if (color.empty()) {
    		if (this->getParent() != nullptr) {
		        color = this->getParent()->getColorAttribute(title, defaultValue);
	        }
        }
    	if (color.empty()) {
    		return defaultValue;
    	}
        return color;
    }
    int SPNode::getIntegerAttribute(const string& title, int defaultValue) {
        if (!(this->integerAttributes)->count(title))
        {
            return defaultValue;
        }
        return (*this->integerAttributes)[title];
    }
    void SPNode::setIntegerAttribute(const string& title, int value) {
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

    void SPNode::setObject(const string& attrib, void* value)
    {
        (*this->properties)[attrib] = value;
    }

    string SPNode::getValue(const string& attrib)
    {
        return "";
    }


    SPNode* SPNode::getNodeById(const string& id) const {
        for (const auto child : *this->children) {
	        if (child->getStringAttribute("id", "") == id) {
		        return child;
	        }
        	for (const auto grandChild : *child->getChildNodes()) {
        		return grandChild->getNodeById(id);
        	}
        }
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

    void SPNode::appendChild(space::SPNode *child) {
        vector<SPNode *> *nodes = this->children;
        if (nodes == nullptr) {
            nodes = new vector<SPNode *>();
        }
        nodes->push_back(child);
        child->setParent(this);
    }
    SPNode *getElementById(string *id) {
        return NULL;
    }
}
