#ifndef SP_WINDOW_H
#define SP_WINDOW_H

#include "libspace.h"

#include "SPObject.h"

namespace space {
  class Space;
  class SPSkin;
  class SPNode;
  class SPWindow {
  protected:
    SPNode *m_deepestElement = nullptr;
  public:
    virtual space::Space *getSpace() { return nullptr; }
	virtual void setSpace(space::Space *value) {}
    virtual void invalidateRegion(sp_rectangle region) {}
    SPNode *getDeepestElement() const {
      return this->m_deepestElement;
    }
    void setDeepestElement(SPNode *value) {
      this->m_deepestElement = value;
    }
    virtual SPSkin *getSkin() { return nullptr; }
    virtual void setSkin(SPSkin *) {}
  };
}
#endif