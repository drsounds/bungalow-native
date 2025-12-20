#include "SPResource.h"
namespace space {
    SPResource::SPResource(const string& uri)
    {
        //ctor
        this->uri = uri;
    }

    SPResource::~SPResource()
    {
        //dtor
    }
    string SPResource::getString(const string& key, const string& defaultValue) {
        if (key == "uri") {
            return this->getUri();
        }
        if (key == "name") {
            return this->getName();
        }
        return "";
    }
    void SPResource::setString(const string& key, const string& value) {
        if (key == "name") {
            this->setName(value);
        }
    }
}