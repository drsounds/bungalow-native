#ifndef TEXTELEMENT_H
#define TEXTELEMENT_H
#include "Element.h"
#include "GraphicsContext.h"
namespace spider {
class Element;
class GraphicsContext;
#ifdef ELEMENT_CLASS
#ifdef GRAPHICSCONTEXT_CLASS
#ifndef TEXTELEMENT_CLASS
class TextElement : public Element
{
    public:
        TextElement(Element *parent);
        void draw(int x, int y, GraphicsContext *g);
        virtual ~TextElement();
        virtual string getType() {
            return "text";
        }
    protected:
    private:
};
#define TEXTELEMENT_CLASS
#endif
#endif
#endif
}
#endif // TEXTELEMENT_H
