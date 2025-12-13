#ifndef TEXTELEMENT_H
#define TEXTELEMENT_H
#include "SPElement.h"
namespace space {
class SPGraphicsContext;
class SPTextElement : public SPElement
{
    public:
        SPTextElement(SPElement *parent);
        void pack() override;
        void paint(int x, int y, SPGraphicsContext *g) override;
        virtual ~SPTextElement();
        virtual string getType() override {
            return "text";
        }
};
}
#endif // TEXTELEMENT_H
