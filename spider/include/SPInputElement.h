#ifndef INPUTELEMENT_H
#define INPUTELEMENT_H
#include "SPElement.h"
#include "SPGraphicsContext.h"
namespace spider {
class SPInputElement : public SPElement
{
private:
    public:
        SPInputElement();
        SPInputElement(SPElement *parent);
        virtual ~SPInputElement();
        virtual void draw(int x, int y, SPGraphicsContext *g);
        virtual string getType() {
            return "input";
        }
    protected:
    private:
};
}
#endif // INPUTELEMENT_H
