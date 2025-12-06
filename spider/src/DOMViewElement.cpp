#include "SPDOMViewElement.h"
#include "SPVBoxElement.h"
#include "SPHBoxElement.h"
#include "SPButtonElement.h"
#include "SPTextElement.h"
namespace spider {

    SPElement *p_parent;
    SPDOMViewElement::DOMViewElement(SPElement *parent) : SPElement(parent) {

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
    void SPDOMViewElement::loadXML(string buffer) {

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


            if (!XML_Parse(parser, buffer.c_str(), len, done)) {
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

    void startElement(void *data, const string el, const string*attr) {
        SPDOMViewElement *view = (SPDOMViewElement *)data;
        if (el.compare("document") == 0) {
            view->parseDepth++;
            return;
        }
        reset_char_data_buffer();
        SPElement *elm = nullptr;
        if (el.compare("document") == 0) {
            SPVBoxElement *vbox = new SPVBoxElement(p_parent);

            elm = vbox;
        }
        if (el.compare("vbox") == 0) {
            SPVBoxElement *vbox = new SPVBoxElement(p_parent);

            elm = vbox;
        }
        if (el.compare("hbox") == 0) {
            SPHBoxElement *hbox = new SPHBoxElement(p_parent);


            elm = hbox;
        }
        if (el.compare("image") == 0) {

        }
        if (el.compare("text") == 0) {
            SPTextElement *textElement = new SPTextElement(p_parent);
            elm = textElement;

        }
        if (el.compare("button") == 0) {
            SPButtonElement *button = new SPButtonElement(p_parent);
            elm = button;
            button->set("height", "32");
            button->set("width", "120");
        }
        if (elm == nullptr) {
            elm = new SPVBoxElement(p_parent);
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
        SPDOMViewElement *view = (SPDOMViewElement *)data;
        if (p_parent != NULL) {

            string text = string(char_data_buffer);
            p_parent->setInnerText(text);

            p_parent = (SPElement *)p_parent->getParent();

        }
        view->parseDepth--;

    }
}
