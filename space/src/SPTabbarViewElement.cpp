#include "SPTabbarViewElement.h"

#include "SPElement.h"
#include "SPViewElement.h"
#include "SPTabBarElement.h"
#include "SPViewStackElement.h"

namespace space {
    int SPTabbarViewElement::onTabSelected(SPObject *sender, SPEventArgs *e) {
        TabBarEventArgs *args = (TabBarEventArgs *)e;
        string uri = args->tab->getUri();
        SPTabbarViewElement *tabbarView = (SPTabbarViewElement *)sender;
        tabbarView->navigate(uri);
        return 0;
    }
    SPTabbarViewElement::SPTabbarViewElement()
     : SPViewElement() {

    }
    void SPTabbarViewElement::mouseDown(SPObject* sender, SPEventArgs* e) {
        SPElement::mouseDown(sender, e);
    }
    SPTabbarViewElement::SPTabbarViewElement(SPElement *parent)
     : SPViewElement::SPViewElement(parent)
    {
        //ctor
        this->tabBar = new SPTabBarElement(this);
        this->viewStack = new SPViewStackElement(this);
        this->viewStack->setIntegerAttribute("flex", 1);
        this->tabBar->setHeight(28);
        this->appendChild(this->tabBar);
        this->tabBar->addEventListener(string("tabselected"), static_cast<SPCallback>(&SPTabbarViewElement::onTabSelected), this);
        this->appendChild(this->viewStack);
    }
    bool SPTabbarViewElement::acceptsUri(string uri) {
        return false;
    }
    void SPTabbarViewElement::navigate(const string& uri) {
        this->viewStack->navigate(uri);
    }
    SPTabbarViewElement::~SPTabbarViewElement()
    {
        delete this->tabBar;
        delete this->viewStack;
    }
}
