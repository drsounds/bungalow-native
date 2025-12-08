#ifndef SPLITTERELEMENT_H
#define SPLITTERELEMENT_H
#include "SPElement.h"
namespace space {
class SPSplitterElement : public SPElement
{
    public:
        SPSplitterElement(SPElement *parent);
        virtual ~SPSplitterElement();
    protected:
    private:
};
}

#endif // SPLITTERELEMENT_H
