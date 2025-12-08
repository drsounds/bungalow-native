#ifndef SPIDERBASE_H
#define SPIDERBASE_H

namespace space {
  class SpiderBase {
  protected:
    space::Spider *m_spider;
  public:
    void setSpider(space::Spider *spider) {
        this->m_spider = spider;
    }
    space::Spider *getSpider() {
        return this->m_spider;
    }
  };
}
#endif