#ifndef IMAGEELEMENT_H
#define IMAGEELEMENT_H
#include "Element.h"
namespace spider {
#ifdef ELEMENT_CLASS
#ifndef IMAGEELEMENT_CLASS
class ImageElement : public Element
{
    public:
        ImageElement(Element *parent);
        virtual ~ImageElement();
        void draw(int x, int y, GraphicsContext *g);
        virtual string getType() {
            return "img";
        }
    protected:
    private:
};
#define IMAGEELEMENT_CLASS
#endif
#endif
}

#endif // IMAGEELEMENT_H
