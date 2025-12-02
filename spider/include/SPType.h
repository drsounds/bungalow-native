#ifndef SPTYPE_H
#define SPTYPE_H
#include <string>
using namespace std;
namespace spider {
    #ifndef SPTYPE_CLASS
    class SPType {
    public:
        virtual string getType() {
            return "Undefined";
        }
    };
    #define SPTYPE_CLASS
    #endif
}
#endif // SPTYPE_H
