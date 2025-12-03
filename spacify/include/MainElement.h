#ifndef MAINWINDOWELEMENT_H
#define MAINWINDOWELEMENT_H
#include "VBoxElement.h"
#include "MessageType.h"
namespace spider {
    class HBoxElement;
    class ViewStackElement;
    class TreeViewElement;
    class InfoElement;
    class Stylesheet;
    class MainElement : public VBoxElement
    {
        protected:

            ViewStackElement *viewStack;
            TreeViewElement *treeView;
            InfoElement *infoElement;
            Stylesheet *stylesheet;
        public:
            GraphicsContext *graphicsContext;
            void navigate(string uri);
            void hideMessage();
            MainElement();
            MainElement(Element *parent, Skin *skin);
            virtual string getType() {
                return "window";
            }
            MainElement(Element *parent);
            void layout();
            virtual ~MainElement();
            ViewStackElement *getViewStack();

            void showMessage(MessageType msgType, string msg)
            {
            }
    };
}
#include "../../spider/include/libspider.h"

#endif // MAINWINDOWELEMENT_H
