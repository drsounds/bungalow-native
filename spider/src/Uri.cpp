#include "Uri.h"

namespace spider {
   Uri::Uri(stringuri) {
        this->uri = uri;
   }
   Uri::~Uri() {
        free(this->uri);
   }
}
