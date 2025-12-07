#ifndef APPHEADERELEMENT_H
#define APPHEADERELEMENT_H
#include "SPHBoxElement.h"

namespace spider {
class SPAppHeaderElement : public SPHBoxElement
{
    public:
        explicit SPAppHeaderElement(SPElement *parent);
        SPAppHeaderElement() = default;
        ~SPAppHeaderElement() override;
    protected:
    private:
};
}

#endif // APPHEADERELEMENT_H
