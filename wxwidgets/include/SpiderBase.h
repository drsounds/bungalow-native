#ifndef SPIDERBASE_H
#define SPIDERBASE_H

namespace spider {
  class SpiderBase {
  protected:
    spider::Spider *m_spider;
  public:
    void setSpider(spider::Spider *spider) {
        this->m_spider = spider;
    }
    spider::Spider *getSpider() {
        return this->m_spider;
    }
  };
}
#endif