#include "DOMViewElement.h"
#include "VBoxElement.h"
#include "HBoxElement.h"
#include "ButtonElement.h"
#include "TextElement.h"
namespace spider {

    Element *p_parent;
    DOMViewElement::DOMViewElement(Element *parent) : Element(parent) {

    }
    static int offs;
    static char char_data_buffer[10024];
    static bool overflow;
    void reset_char_data_buffer (void) {
        offs = 0;
        overflow = false;
        memset(char_data_buffer, '\0', sizeof(char_data_buffer));
    }
    size_t offset = 0;
    void char_data(void *userData, const XML_strings, int len) {
        if (!overflow) {
            if (len + offs >= sizeof(char_data_buffer) ) {
                overflow = true;
            } else {
                memcpy(char_data_buffer + offs, s, len);
                offs += len;
            }
        }
    }
    void DOMViewElement::loadXML(string buffer) {

        this->getChildNodes()->clear();
        this->parseDepth = 0;
        XML_Parser parser = XML_ParserCreate(NULL);
        XML_SetUserData(parser, this);
        int len = buffer.size();
        bool done = false;
        p_parent = this;
        XML_SetCharacterDataHandler(parser, &char_data);
        XML_SetElementHandler(parser, &startElement, &endElement);
        do {


            if (!XML_Parse(parser, buffer, len, done)) {
                break;

            }
        } while (!done);
        XML_ParserFree(parser);
        this->pack();

    }

    string getAttribute(string attribute, vector<string> attributes, string defValue) {
        if (attributes.empty()) {
            return defValue;
        }

        for (size_t i = 0; i < attributes.size(); i += 2) {
            const string attr = attributes[i];
            const string val = attributes[i+1];
            if (attr.compare(attribute) == 0) {
                return val;
            }
        }
        return defValue;
    }

    void startElement(string data, const string el, const string*attr) {
        DOMViewElement *view = (DOMViewElement *)data;
        if (el.compare("document") == 0) {
            view->parseDepth++;
            return;
        }
        reset_char_data_buffer();
        Element *elm = NULL;
        if (el.compare("document") == 0) {
            VBoxElement *vbox = new VBoxElement(p_parent);

            elm = vbox;
        }
        if (el.compare("vbox") == 0) {
            VBoxElement *vbox = new VBoxElement(p_parent);

            elm = vbox;
        }
        if (el.compare("hbox") == 0) {
            HBoxElement *hbox = new HBoxElement(p_parent);


            elm = hbox;
        }
        if (el.compare("image") == 0) {

        }
        if (el.compare("text") == 0) {
            TextElement *textElement = new TextElement(p_parent);
            elm = textElement;

        }
        if (el.compare("button") == 0) {
            ButtonElement *button = new ButtonElement(p_parent);
            elm = button;
            button->set("height", "32");
            button->set("width", "120");
        }
        if (elm == NULL) {
            elm = new VBoxElement(p_parent);
        }

        // Get common attributes
        string flex = getAttribute("flex", attr, "");
        if (!flex.empty()) {
            if (elm != NULL) {
                elm->set("flex", new string(flex));
            }
        }

        string height = getAttribute("height", attr, "");
        if (!height.empty()) {
            if (elm != NULL) {
                elm->set(string("height"), new string(height));
            }
        }

        string width = getAttribute("width", attr, NULL);
        if (!width.empty()) {
            if (elm != NULL) {
                elm->set(string("width"), new string(width));
            }
        }

        if (p_parent != NULL && elm != NULL)
        p_parent->appendChild(elm);
        view->parseDepth++;
        p_parent = elm;
    }

    void endElement(void *data, const string el) {
        DOMViewElement *view = (DOMViewElement *)data;
        if (p_parent != NULL) {

            string text = string(char_data_buffer);
            p_parent->setInnerText(text);

            p_parent = (Element *)p_parent->getParent();

        }
        view->parseDepth--;

    }
}
