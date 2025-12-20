#ifndef SP_STORE_H
#define SP_STORE_H

#include <map>

#include "SPResource.h"
#include "SPObject.h"
#include "SPObservable.h"

namespace space {
  class SPStore : public SPObject, SPObservable {
    std::map<string, SPResource *> values;
  public:
    SPResource *get(const string&);
    void set(const string&, SPResource *);
    bool contains(const string&);
    void remove(const string&);
  }
}