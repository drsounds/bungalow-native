#ifndef EVENTARGS_H
#define EVENTARGS_H
#include "SPObject.h"
namespace spider {
class SPEventArgs : virtual public SPObject
{
    public:
        SPEventArgs();
        ~SPEventArgs() override;
    protected:
    private:
};
}

#endif // EVENTARGS_H
