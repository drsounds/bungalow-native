#ifndef SP_WINDOW_H
#define SP_WINDOW_H

#include "libspider.h"

#include "SPObject.h"

namespace spider {
  class Spider;
  class SPSkin;
  class SPElement;
  class SPWindow : virtual public SPObject {
  protected:
    SPSkin *m_skin;
    SPElement *m_deepestElement;
  public:
    virtual void invalidateRegion(sp_rectangle region) {}
    SPElement *getDeepestElement() {
      return this->m_deepestElement;
    }
    void setDeepestElement(SPElement *value) {
      this->m_deepestElement = value;
    }
    SPSkin *getSkin() {
      return this->m_skin;
    }
    void setSkin(SPSkin *skin) {
      this->m_skin = skin;
    }
  };
}
#endif