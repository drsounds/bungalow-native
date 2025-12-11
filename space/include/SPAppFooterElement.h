#ifndef APPFOOTERELEMENT_H
#define APPFOOTERELEMENT_H
#include "SPHBoxElement.h"

namespace space {
    class SPElement;
    class SPAppFooterElement : public SPHBoxElement
    {
    public:
        explicit SPAppFooterElement(SPElement *parent);
        SPAppFooterElement() = default;
        ~SPAppFooterElement() override;
        string getType() override
        {
            return "appfooter";
        }
    protected:
    private:
    };
}

#endif // APPHEADERELEMENT_H
