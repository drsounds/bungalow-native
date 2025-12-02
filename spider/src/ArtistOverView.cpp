#include "ArtistOverView.h"
#include "HBoxElement.h"
namespace spider {
ArtistOverView::ArtistOverView(Element *parent)
 : ViewElement(parent)
{
    //ctor
    HBoxElement *header = new HBoxElement(this);
    header->set("height", "128");



}

ArtistOverView::~ArtistOverView()
{
    //dtor
}
}
