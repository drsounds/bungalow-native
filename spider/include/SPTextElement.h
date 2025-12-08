#ifndef TEXTELEMENT_H
#define TEXTELEMENT_H
#include "SPElement.h"
namespace space {
class SPGraphicsContext;
class SPTextElement : public SPElement
{
    public:
        SPTextElement(SPElement *parent);
        void draw(int x, int y, SPGraphicsContext *g);
        virtual ~SPTextElement();
        virtual string getType() {
            return "text";
        }
};
}
#endif // TEXTELEMENT_H
