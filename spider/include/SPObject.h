#ifndef SPTYPE_H
#define SPTYPE_H
#include <string>
using namespace std;
namespace spider {
    class Spider;
    class SPObject {
    protected:
        Spider *m_spider;
    public:
        virtual Spider *getSpider() const {
            return this->m_spider;
        }
        virtual void setSpider(Spider *value) {
            this->m_spider = value;
        }
        virtual ~SPObject() = default;

        virtual string getType() {
            return "Undefined";
        }
    };
}
#endif // SPTYPE_H
