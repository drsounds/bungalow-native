#ifndef MAINWINDOWELEMENT_H
#define MAINWINDOWELEMENT_H
#include "MessageType.h"
#include "VBoxElement.h"
namespace spider {
    class HBoxElement;
    class ViewStackElement;
    class TreeViewElement;
    class InfoElement;
    class Stylesheet;
class MainWindowElement : public VBoxElement
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
        MainWindowElement();
        MainWindowElement(Element *parent, Skin *skin);
        virtual string getType() {
            return "window";
        }
        MainWindowElement(Element *parent);
        void layout();
        virtual ~MainWindowElement();
        ViewStackElement *getViewStack();

        void showMessage(MessageType msgType, string msg)
        {
        }
};
}
#include "libspider.h"

#endif // MAINWINDOWELEMENT_H
