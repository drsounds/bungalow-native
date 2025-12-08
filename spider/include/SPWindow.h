#ifndef SP_WINDOW_H
#define SP_WINDOW_H

#include "libspider.h"

#include "SPObject.h"

namespace space {
  class Spider;
  class SPSkin;
  class SPElement;
  class SPWindow {
  protected:
    space::Spider *m_spider;
    SPSkin *m_skin;
    SPElement *m_deepestElement;
  public:
    space::Spider *getSpider() {
      return this->m_spider;
    }
    void setSpider(space::Spider *value) {
      this->m_spider = value;
    }
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