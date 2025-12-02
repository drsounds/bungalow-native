#include "Node.h"
namespace spider {



    Node::Node() {
        if(this->window == NULL)
            this->window = this;
            this->children = new vector<Node *>();
            this->properties = new map<string, void*>();
            this->stringAttributes = new map<string, string>();
            this->colorAttributes = new map<string, Color>();
            this->integerAttributes = new map<string, int>();
    }
    Node* Node::getParent() {
        return this->parent;
    }
    void Node::removeChild(Node *child) {
    }
    string Node::getStringAttribute(string title, string defaultValue) {
        return (*this->stringAttributes)[title];
    }
    void Node::setStringAttribute(string title, string value) {
        (*this->stringAttributes)[title] = value;
    }
    void Node::setColorAttribute(string title, Color value) {
        (*this->colorAttributes)[title] = value;
    }
    Color Node::getColorAttribute(string title, Color defaultValue) {
        return (*this->colorAttributes)[title];
    }
    int Node::getIntegerAttribute(string title, int defaultValue) {
        return (*this->integerAttributes)[title];
    }
    void Node::setIntegerAttribute(string title, int value) {
        (*this->integerAttributes)[title] = value;
    }
    std::vector<Node *> *Node::getChildNodes() {
        return (this->children);
    }
    bool Node::hasAttribute(string attr) {
        map<string, void *>::iterator it = this->properties->find(attr);
        return it != this->properties->end();
    }

    void Node::setParent(Node *elm) {
        this->parent = (elm);
    }
    std::string Node::get(const std::string& title) {
        std::string val = (*this->stringAttributes)[title];
        return val;
    }
    void* Node::getObject(const std::string& title) {
        return (*this->properties)[title];
    }


    void Node::set(const std::string& title, const std::string& val) {
        int n = 0;
        (*this->stringAttributes)[title] = val;
        try {
            n = atoi(val.c_str());



            (*this->integerAttributes)[title] = n;
        } catch (exception e) {
            
        }

        if(val.find("#") == 0) {
            Color c = Color(val);
            (*this->colorAttributes)[title] = c;
        }
    }

    void Node::appendChild(spider::Node *child) {
        vector<Node *> *nodes = this->children;
        if (nodes == NULL) {
            nodes = new vector<Node *>();
        }
        nodes->push_back(child);
        child->setParent(this);
        child->window = this->getWindowNode();
    }
    Node *getElementById(string *id) {
        return NULL;
    }
    Node *Node::getWindowNode() {
        return this->window;
    }








}
