#ifndef NODE_H
#define NODE_H
#include "SPObject.h"
#include "SPColor.h"
#include "SPEventArgs.h"
#include "SPObservable.h"

#include <map>
#include <string>
#include <vector>
#include <wx/xml/xml.h>
using namespace std;
namespace space {
    class Space;
	class SPWindowElement;
    class SPColor;
    class SPNode : public SPObject, public SPObservable {
    protected:
        map<string, void *> *properties;
        map<string, string> *stringAttributes;
        map<string, SPColor> *colorAttributes;
        map<string, int> *integerAttributes;
        SPNode *m_parent;
        string tagName = "node";
    	string m_innerText;
    public:
    	string getTagName() const {
	        return this->tagName;
        }
    	void setTagName(const string& value) {
        	this->tagName = value;
        }
    	string getInnerText() {
	        return this->m_innerText;
        }
        void setInnerText(const string& value);
        SPNode *parseNode(wxXmlNode *xmlNode, SPNode *parent, SPNode *document);

    	space::Space *getSpace() {
    		if (this->m_space == nullptr) {
    			if (this->getParentNode() != nullptr) {
    				return this->getParentNode()->getSpace();
    			}
    		}
    		return this->m_space;
    	}
    	SPNode *getDeepestNode(const int level);

        std::vector<SPNode *> *children;
        SPNode();
        SPNode(Space *space, SPNode *parent) : SPNode() {
	        this->m_parent = parent;
        }
        SPNode(const string &tagName);
        explicit SPNode(SPNode *parent);
        void removeChild(SPNode *child);
        virtual void appendChild(SPNode *child);
        void setInnerXml(const string &value);
        SPNode *createNode(const string &tagName, SPNode *parent);

        void setChildren(std::vector<SPNode *> *value) {
            this->children = value;
        }

        SPNode *getNodeById(const string& id) const;
        void setAttribute(const std::string &attrName,
                          const std::string &value);
        virtual void set(const string& attrib, const string& val);
        string get(const string& attrib);
        void *getObject(const string& attrib);
        void setObject(const string& attrib, void *value);
        string getValue(const string& attrib);
        SPNode *getParentNode();

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

        void setParentNode(SPNode *parent);
        std::vector<SPNode *> *getChildNodes();
        bool hasAttribute(string attrib);
        virtual SPColor getColorAttribute(const string& title, SPColor defaultValue);
        void setColorAttribute(const string& attrName, SPColor value);
        void notify(const string &event, SPObject *sender, SPEventArgs *data);
        int getIntegerAttribute(const string& title, int defaultValue);
        void setIntegerAttribute(const string& title, int value);
        void setStringAttribute(const string& attribute, string value);
        string getStringAttribute(const string& attribute, string defaultValue);
    };
}
#endif // NODE_H
