#ifndef TABBARVIEWELEMENT_H
#define TABBARVIEWELEMENT_H

#include "ViewElement.h"

namespace spider
{
    class ViewElement;
    class ViewStackElement;
    class TabBarElement;
    class TabbarViewElement : public ViewElement
    {
    public:
        virtual string getType() {
            return "table";
        }
        TabbarViewElement();
        TabbarViewElement(Element *parent);
        virtual ~TabbarViewElement();
        virtual void navigate(string uri);
        virtual bool acceptsUri(string uri);
        void mousedown(int mouseButton, int x, int y);
    protected:
        ViewStackElement *viewStack;
        TabBarElement *tabBar;

    private:
    }
}

#endif // TABBARVIEWELEMENT_H
