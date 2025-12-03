#include "TitleElement.h"

#include "Color.h"

namespace spider {
TitleElement::TitleElement()
{
    //ctor
}

TitleElement::~TitleElement()
{

}
void TitleElement::setTitle(string title) {

    this->title->setInnerText((string)title.c_str());
}
string TitleElement::getTitle() {
}

void TitleElement::setEntity(string entity) {

    this->title->setInnerText((string)entity.c_str());
}
string TitleElement::getEntity() {
}
TitleElement::TitleElement(Element *parent)
 : VBoxElement(parent){
    entity = new TextElement(this);
    entity->setInnerText("Object");
    entity->setIntegerAttribute("height", 180);
    entity->setColorAttribute("fgcolor", Color(10, 10, 10, 1));
    entity->setIntegerAttribute("size", 15);
    entity->set("width", "100%");
    this->appendChild(entity);

    title = new TextElement(this);
    title->setInnerText("Title");
    title->setIntegerAttribute("height", 160);
    title->setColorAttribute("fgcolor", Color(255, 255, 255, 1));
    title->setIntegerAttribute("size", 25);
    title->set("width", "100%");
    this->appendChild(title);
}
}
