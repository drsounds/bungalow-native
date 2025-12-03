#ifndef TEXTELEMENT_H
#define TEXTELEMENT_H
#include "Element.h"
namespace spider {
class GraphicsContext;
class TextElement : public Element
{
    public:
        TextElement(Element *parent);
        void draw(int x, int y, GraphicsContext *g);
        virtual ~TextElement();
        virtual string getType() {
            return "text";
        }
};
}
#endif // TEXTELEMENT_H
