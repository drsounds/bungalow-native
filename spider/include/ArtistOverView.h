#ifndef ARTISTOVERVIEW_H
#define ARTISTOVERVIEW_H

#include "ViewElement.h"
#include "ImageElement.h"
#include "TextElement.h"
#include "HBoxElement.h"
#include "Element.h"
namespace spider {
class Element;
class ViewElement;
class ImageElement;
class TextElement;
class HBoxElement;
#ifdef HBOX_ELEMENT
#ifdef VIEWELEMENT_CLASS
#ifdef IMAGEELEMENT_CLASS
#ifdef TEXTELEMENT_CLASS
#ifndef ARTISTOVERVIEW_CLASS
class ArtistOverView : public ViewElement
{
    public:
        ArtistOverView(Element *parent);
        virtual ~ArtistOverView();
    protected:
    private:
}; 
#define ARTISTOVERVIEW_CLASS
#endif
#endif
#endif
#endif
#endif
}
#endif // ARTISTOVERVIEW_H
