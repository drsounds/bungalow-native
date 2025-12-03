#ifndef EVENTARGS_H
#define EVENTARGS_H
#include "SPType.h"
namespace spider {
#ifdef SPTYPE_CLASS
#ifndef EVENTARGS_CLASS
class EventArgs : public SPType
{
    public:
        EventArgs();
        virtual ~EventArgs();
    protected:
    private:
};
#define EVENTARGS_CLASS
#endif
#endif
}

#endif // EVENTARGS_H
