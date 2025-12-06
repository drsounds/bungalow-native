#ifndef LINKELEMENT_H
#define LINKELEMENT_H
#include "SPTextElement.h"

namespace spider {
class SPElement;
class SPLinkElement : public SPTextElement
{
    public:
        SPLinkElement(SPElement *parent);
        virtual ~SPLinkElement();
        virtual string getType() {
            return "link";
        }
    protected:
    private:
};
}

#endif // LINKELEMENT_H
