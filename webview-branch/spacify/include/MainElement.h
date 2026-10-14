#ifndef MAINWINDOWELEMENT_H
#define MAINWINDOWELEMENT_H
#include "SPVBoxElement.h"

#include "SPMessageType.h"

#include "libspace.h"


namespace space {
    class SPViewStackElement;
    class SPTreeViewElement;
    class SPInfoElement;
    class SPStylesheet;
    class SPEventArgs;
    class SPAppFooterElement;
    class SPAppHeaderElement;
    class SPButtonElement;
    class SPHBoxElement;
    class SPTabBarElement;
    class SPInputElement;
    class SPNowPlayingBarElement;
    class MainElement : public SPVBoxElement
    {
        protected:
            SPInputElement *searchElement;
            SPViewStackElement *viewStack;
            SPTreeViewElement *treeView;
            SPInfoElement *infoElement;
            SPAppFooterElement *footer;
            SPAppHeaderElement *header;
            SPHBoxElement *body;
            SPVBoxElement *leftSidebar;
            SPTabBarElement *tabBar;
            SPButtonElement *backButton;
            SPButtonElement *forwardButton;
            SPButtonElement *accountButton;
            SPNowPlayingBarElement* m_nowPlayingBar = nullptr;

        public:
            void navigate(const string& uri) const;
            void hideMessage();
            int treeview_itemselected(SPObject* sender, SPEventArgs* e);
            MainElement();
            void onLoad(SPNode *sender, SPEventArgs *args);
            virtual SPElement* createElement(const string&, SPElement*) override;

            string getType() override
            {
                return "main";
            }
            int onNavigate(SPObject* sender, SPEventArgs* args);
            int onBackClicked(SPObject* sender, SPEventArgs* args);
            int onForwardClicked(SPObject* sender, SPEventArgs* args);
            explicit MainElement(SPElement *parent);
            int onSearchEntered(SPObject* sender, SPEventArgs* eventArgs) const;
            void layout();
            ~MainElement() override;
            SPViewStackElement *getViewStack();

            void showMessage(SPMessageType msgType, string msg);
    };
}
#include "libspace.h"

#endif // MAINWINDOWELEMENT_H
