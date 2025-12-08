#ifndef INFOELEMENT_H
#define INFOELEMENT_H
#include "SPHBoxElement.h"
#include "SPMessageType.h"

namespace space {
class SPTextElement;
class SPButtonElement;
class SPInfoElement : public SPHBoxElement
{
    protected:
        SPMessageType type;
        SPHBoxElement *hbox;
        SPTextElement *textElement;
        SPButtonElement *btnElement;

    public:
        virtual string getType() {
            return "info";
        }
        SPMessageType getMessageType() {
            return this->type;
        }
        void hide();
        void show(SPMessageType type, string text);
        void setMessageType(SPMessageType type);
        SPInfoElement(SPElement *parent);
        virtual ~SPInfoElement();
    private:
};
}
#endif // INFOELEMENT_H
