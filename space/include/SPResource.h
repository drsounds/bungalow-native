#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>
#include <vector>

#include "SPObject.h"

using namespace std;
namespace space {
class SPResource : public SPObject
{
protected:
    string id;
    string uri;
    string name;
    vector<SPResource *> creators;
    SPResource *parent;
    SPResource *collection;
public:
    explicit SPResource(const string& uri);
    SPResource();
    virtual ~SPResource();
    virtual string getString(const string& key, const string& defaultValue);
    virtual void setString(const string& key, const string& value);
    string getName() const {
        return this->name;
    }
    virtual string getType() const {
        return "node";
    }
    SPResource *getParent() const {
        return this->parent;
    }
};
}
#endif // RESOURCE_H
