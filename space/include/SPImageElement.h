#ifndef IMAGEELEMENT_H
#define IMAGEELEMENT_H
#include "SPElement.h"
namespace space {
class SPGraphicsContext;
class SPImageElement : public SPElement
{
    public:
        SPImageElement(SPElement *parent);
        virtual ~SPImageElement();
        void paint(int x, int y, SPGraphicsContext *g);
        virtual string getType() override {
            return "img";
        }
    protected:
    private:
};
}

#endif // IMAGEELEMENT_H
