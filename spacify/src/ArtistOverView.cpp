#include "ArtistOverView.h"

#include "HBoxElement.h"
#include "Element.h"
#include "ViewElement.h"

namespace spider {
ArtistOverView::ArtistOverView(Element *parent)
 : ViewElement(parent)
{
    //ctor
    auto *header = new HBoxElement(this);
    header->setIntegerAttribute("height", 128);



}

ArtistOverView::~ArtistOverView()
{
    //dtor
}
}
