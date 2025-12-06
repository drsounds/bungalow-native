#ifndef NODE_H
#define NODE_H
#include "SPObject.h"
#include <map>
#include <string>
#include <vector>
using namespace std;
namespace spider {
    class Spider;
    class SPColor;
    class SPNode : public SPObject {
    protected:
        map<string, void *> *properties;
        map<string, string> *stringAttributes;
        map<string, SPColor *> *colorAttributes;
        map<string, int> *integerAttributes;
        SPNode *m_parent;
        SPNode *m_window;
        Spider *m_spider;
    public:
        Spider *getSpider() const {
            return this->m_spider;
        }
        std::vector<SPNode *> *children;
        SPNode()
        {
            this->children = new vector<SPNode *>();
            this->integerAttributes = new map<string, int>();
            this->stringAttributes = new map<string, string>();
            this->colorAttributes = new map<string, SPColor *>();
            this->properties = new map<string, void *>();
            this->m_parent = nullptr;
            this->m_window = nullptr;
            this->m_spider = nullptr;
        }
        SPNode(Spider *spider, SPNode *parent) : SPNode()
        {
            this->m_parent = parent;
            this->m_spider = spider;
            this->m_window = parent->getWindowNode();
        }

        explicit SPNode(SPNode *parent) : SPNode(parent->getSpider(), parent) {

        }
        void removeChild(SPNode *child);
        virtual void appendChild(SPNode *child);
        void setChildren(std::vector<SPNode *> *value) {
            this->children = value;
        }

        SPNode *getElementById(string id);
        virtual void set(const string& attrib, const string& val);
        string get(const string& attrib);
        void *getObject(const string& attrib);
        string getValue(const string& attrib);
        SPNode *getParent();

        map<string, string> *getStringAttributes() {
            return this->stringAttributes;
        }
        map<string, SPColor *> *getColorAttributes() const
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
