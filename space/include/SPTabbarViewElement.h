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
        string getType() override
        {
            return "tabbarview";
        }
		bool acceptsUri(const string &uri) override;
    	void onLoad(SPObject *sender, SPEventArgs *e);
        int onTabSelected(SPObject* sender, SPEventArgs* e);
        SPTabbarViewElement();
        SPTabbarViewElement(SPElement *parent);
        SPElement *getViewStackElement() override;
        void onClick(SPObject *sender, SPEventArgs *e);
        void clear() override;
        void onUnload(SPObject *sender, SPEventArgs *e);
        void onTreeChanged(SPObject *sender, SPEventArgs *e);
        virtual ~SPTabbarViewElement();
        virtual void navigate(const string& uri) override;
        void mouseDown(SPObject* sender, SPEventArgs* e) override;
    protected:
        SPViewStackElement *viewStack;
        SPTabBarElement *tabBar;

    private:
    };
}

#endif // TABBARVIEWELEMENT_H
