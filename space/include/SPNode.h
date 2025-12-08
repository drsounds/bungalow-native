#ifndef NODE_H
#define NODE_H
#include "SPObject.h"
#include "SPColor.h"
#include "SPWindow.h"

#include <map>
#include <string>
#include <vector>
using namespace std;
namespace space {
    class Space;
    class SPColor;
    class SPNode : public SPObject {
    protected:
        map<string, void *> *properties;
        map<string, string> *stringAttributes;
        map<string, SPColor> *colorAttributes;
        map<string, int> *integerAttributes;
        SPNode *m_parent;
        SPWindow *m_window;
        space::Space *m_space;
    public:
        void setSpace(space::Space *space) {
            this->m_space = space;
        }
        space::Space *getSpace() {
            return this->m_space;
        }
        std::vector<SPNode *> *children;
        SPNode();
        SPWindow *getWindow() const
        {
             return this->m_window;
        }
        void setWindow(SPWindow *value) {
            this->m_window = value;
        }
        SPNode(Space *space, SPNode *parent) : SPNode()
        {
            this->m_parent = parent;
            if (parent != nullptr) {
                this->m_window = parent->getWindow();
            }
        }

        explicit SPNode(SPNode *parent);
        void removeChild(SPNode *child);
        virtual void appendChild(SPNode *child);
        void setChildren(std::vector<SPNode *> *value) {
            this->children = value;
        }

        SPNode *getElementById(string id);
        virtual void set(const string& attrib, const string& val);
        string get(const string& attrib);
        void *getObject(const string& attrib);
        void setObject(const string& attrib, void *value);
        string getValue(const string& attrib);
        SPNode *getParent();

        map<string, string> *getStringAttributes() {
            return this->stringAttributes;
        }
        map<string, SPColor> *getColorAttributes() const
        {
            return this->colorAttributes;
        }
        map<string, int> *getIntegerAttributes() {
            return this->integerAttributes;
        }
        map<string, void *> *getProperties() {
            return this->properties;
        }

        SPNode *getWindowNode();

        void setParent(SPNode *parent);
        std::vector<SPNode *> *getChildNodes();
        bool hasAttribute(string attrib);
        SPColor getColorAttribute(string title, SPColor defaultValue);
        void setColorAttribute(string title, SPColor value);
        int getIntegerAttribute(string title, int defaultValue);
        void setIntegerAttribute(string title, int value);
        void setStringAttribute(string attribute, string value);
        string getStringAttribute(string attribute, string defaultValue);
    };
}
#endif // NODE_H
