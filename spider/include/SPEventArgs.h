#ifndef EVENTARGS_H
#define EVENTARGS_H
#include "SPObject.h"
namespace space {
class SPEventArgs : public SPObject
{
    public:
        SPEventArgs();
        ~SPEventArgs() override;
    protected:
    private:
};
}

#endif // EVENTARGS_H
