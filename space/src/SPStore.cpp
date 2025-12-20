#include "SPStore.h"

namespace space {
    SPResource *SPStore::get(const string& key) {
      return this->values.at(key);
    }
    void SPStore::set(const string& key, SPResource *value) {
      (*this->values)[key] = value;
    }
    bool SPStore::contains(const string& key) {
      return this->values.count(key) > 0;
    }
    void SPStore::remove(const string&) {
      
    }
}