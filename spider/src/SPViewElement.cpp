#include "SPViewElement.h"
#include <string>
#include <iostream>

using namespace std;

namespace spider {
SPViewElement::SPViewElement()
 : SPVBoxElement::SPVBoxElement()
{

    //ctor
}
void SPViewElement::scroll(int scrollX, int scrollY, int mouseX, int mouseY) {
    if (this->clipView) {
        this->scrollX += x;
        this->scrollY += y;
        this->invalidate();
    }
}
void SPViewElement::request(std::string uri) {

}

std::string SPViewElement::loadView(std::string view) {
    std::string path = "C:\\Users\\Alecca\\Documents\\Spoyler\\resources\\views\\" + view;
    string fileName = (string)path.c_str();
    FILE *fil = fopen(fileName.c_str(), "rb");
    fseek(fil, 0, SEEK_END);
    size_t fsize = ftell(fil);
    rewind(fil);
    char *buffer = (char *)malloc(sizeof(char) * fsize);
    fread(buffer, sizeof(char), fsize, fil);
    fclose(fil);
    std::string output (buffer);
    delete buffer;
    return output;
}

void SPViewElement::pack() {
    SPVBoxElement::pack();
    /*for(std::vector<Node *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
        Element *child = (Element *)*it;
        child->setWidth(this->getWidth());

        child->setHeight(this->getHeight());
    }*/
}

SPViewElement::SPViewElement(SPElement *parent)
 : SPVBoxElement::SPVBoxElement(parent)
{
    this->clipView = true;
    //ctor
}
void SPViewElement::navigate(string uri) {

}
SPViewElement::~SPViewElement()
{
    //dtor
}
}
