#ifndef TABBARVIEWELEMENT_H
#define TABBARVIEWELEMENT_H

#include "SPViewElement.h"

namespace space
{
    class SPViewElement;
    class SPViewStackElement;
    class SPTabBarElement;
    class SPTabbarViewElement : public SPViewElement
    {
    public:
        virtual string getType() {
            return "table";
        }

        int onTabSelected(SPObject* sender, SPEventArgs* e);
        SPTabbarViewElement();
        SPTabbarViewElement(SPElement *parent);
        virtual ~SPTabbarViewElement();
        virtual void navigate(string uri);
        virtual bool acceptsUri(string uri);
        void mouseDown(int mouseButton, int x, int y);
    protected:
        SPViewStackElement *viewStack;
        SPTabBarElement *tabBar;

    private:
    };
}

#endif // TABBARVIEWELEMENT_H
