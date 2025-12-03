#ifndef ARTISTOVERVIEW_H
#define ARTISTOVERVIEW_H

#include "ViewElement.h"
namespace spider {
class Element;
class ViewElement;
class ImageElement;
class TextElement;
class HBoxElement;
class ArtistOverView : public ViewElement
{
    public:
        ArtistOverView(Element *parent);
        virtual ~ArtistOverView();
    protected:
    private:
}; 
}
#endif // ARTISTOVERVIEW_H
