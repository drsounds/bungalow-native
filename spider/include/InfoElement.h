#ifndef INFOELEMENT_H
#define INFOELEMENT_H
#include "HBoxElement.h"
namespace spider {
enum MessageType {
    Info, Warning, Error, Message
};
class TextElement;
class ButtonElement;
class InfoElement : public HBoxElement
{
    protected:
        MessageType type;
        HBoxElement *hbox;
        TextElement *textElement;
        ButtonElement *btnElement;

    public:
        virtual string getType() {
            return "info";
        }
        MessageType getMessageType() {
            return this->type;
        }
        void hide();
        void show(MessageType type, string text);
        void setMessageType(MessageType type);
        InfoElement(Element *parent);
        virtual ~InfoElement();
        void show();
    private:
};
}
#endif // INFOELEMENT_H
