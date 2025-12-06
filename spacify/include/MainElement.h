#ifndef MAINWINDOWELEMENT_H
#define MAINWINDOWELEMENT_H
#include "SPVBoxElement.h"
#include "SPMessageType.h"
namespace spider {
    class SPViewStackElement;
    class SPTreeViewElement;
    class SPInfoElement;
    class SPStylesheet;
    class MainElement : public SPVBoxElement
    {
        protected:

            SPViewStackElement *viewStack;
            SPTreeViewElement *treeView;
            SPInfoElement *infoElement;
        public:
            void navigate(const string& uri) const;
            void hideMessage();
            MainElement();

            string getType() override
            {
                return "window";
            }
            explicit MainElement(SPElement *parent);
            int onSearchEntered(SPObject* sender, SPEventArgs* eventArgs) const;
            void layout();
            ~MainElement() override;
            SPViewStackElement *getViewStack();

            void showMessage(SPMessageType msgType, string msg)
            {
            }
    };
}
#include "../../spider/include/libspider.h"

#endif // MAINWINDOWELEMENT_H
