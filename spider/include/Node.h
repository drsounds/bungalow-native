#ifndef NODE_H
#define NODE_H
#include "SPType.h"
#include <map>
#include <boost/lexical_cast.hpp>
#include <string>
#include <vector>
using namespace std;
namespace spider {
class Color;
class Node : public SPType {
protected:
    map<string, void *> *properties;
    map<string, string> *stringAttributes;
    map<string, Color> *colorAttributes;
    map<string, int> *integerAttributes;
    Node *pparent;
    Node *window;
public:
    Node *parent;
    std::vector<Node *> *children;
    Node();
    void removeChild(Node *child);
    virtual void appendChild(Node *child);
    void setChildren(std::vector<Node *> *children) {
        this->children = children;
    }

    Node *getElementById(string id);
    virtual void set(const string& attrib, const string& val);
    string get(const string& attrib);
    void *getObject(const string& attrib);
    string getValue(const string& attrib);
    Node *getParent();

    map<string, string> *getStringAttributes() {
        return this->stringAttributes;
    }
    map<string, Color> *getColorAttributes() {
        return this->colorAttributes;
    }
    map<string, int> *getIntegerAttributes() {
        return this->integerAttributes;
    }
    map<string, void *> *getProperties() {
        return this->properties;
    }

    Node *getWindowNode();

    void setParent(Node *parent);
    std::vector<Node *> *getChildNodes();
    bool hasAttribute(string attrib);
    Color getColorAttribute(string title, Color defaultValue);
    void setColorAttribute(string title, Color value);
    int getIntegerAttribute(string title, int defaultValue);
    void setIntegerAttribute(string title, int value);
    void setStringAttribute(string attribute, string value);
    string getStringAttribute(string attribute, string defaultValue);
};
}
#endif // NODE_H
