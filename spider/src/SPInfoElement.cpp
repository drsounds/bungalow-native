#include "SPInfoElement.h"
#include "SPButtonElement.h"
#include "SPTextElement.h"
#include <list>
namespace spider {
    SPInfoElement::SPInfoElement(SPElement *parent)
     : SPHBoxElement(parent)
    {
        //ctor
        this->set("height", "32");
        this->getPadding()->top = 5;
        this->getPadding()->left = 5;
        this->getPadding()->right = 5;
        this->getPadding()->bottom = 5;

        SPTextElement *icon = new SPTextElement(this);
        icon->set("width", "128");
        this->appendChild(icon);
        this->textElement = new SPTextElement(this);
        this->textElement->set("flex", "1");
        this->appendChild(this->textElement);

        this->btnElement = new SPButtonElement(this);
        this->btnElement->set("width", "64");
        this->btnElement->setInnerText("X");
        this->appendChild(this->btnElement);

    }
    void SPInfoElement::show(SPMessageType type, string text) {
        this->setMessageType(type);
        this->textElement->setInnerText(text);
        SPElement::show();
        this->mainWindowElement->pack();

    }
    void SPInfoElement::hide() {
        SPElement::hide();
        this->mainWindowElement->pack();
    }
    void SPInfoElement::setMessageType(SPMessageType type) {
        this->type = type;
        string bgcolor = "#ffffaa";
        switch(type) {
        case Warning:
            bgcolor = "#ffffaa";
            break;
        case Info:
            bgcolor = "#00ffff";
            break;
        case Error:
            bgcolor = "#ffeeee";
            break;
        case Message:
            bgcolor = "#eeffee";
            break;
        }
        this->set("bgcolor", bgcolor);

        for (std::vector<SPNode *>::iterator it = this->children->begin(); it != this->children->end(); ++it) {
            SPNode *node = dynamic_cast<SPNode *>(*it);
            node->set("bgcolor", bgcolor);

        }

    }
    SPInfoElement::~SPInfoElement()
    {
        //dtor
    }
}
