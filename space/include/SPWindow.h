#ifndef SP_WINDOW_H
#define SP_WINDOW_H

#include "libspace.h"

#include "SPObject.h"

namespace space {
  class Space;
  class SPSkin;
  class SPElement;
  class SPWindow {
  protected:
    space::Space *m_space;
    SPSkin *m_skin;
    SPElement *m_deepestElement;
  public:
    space::Space *getSpace() {
      return this->m_space;
    }
    void setSpace(space::Space *value) {
      this->m_space = value;
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