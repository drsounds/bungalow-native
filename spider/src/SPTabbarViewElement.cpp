#include "SPTabbarViewElement.h"

#include "SPElement.h"
#include "SPViewElement.h"
#include "SPTabBarElement.h"
#include "SPViewStackElement.h"

namespace spider {
    int SPTabbarViewElement::onTabSelected(SPObject *sender, SPEventArgs *e) {
        TabBarEventArgs *args = (TabBarEventArgs *)e;
        string uri = args->tab->getUri();
        SPTabBarElement *tabView = (SPTabBarElement *)sender;
        SPTabbarViewElement *tabbarView = (SPTabbarViewElement *)tabView->getParent();
        tabbarView->navigate(uri);
        return 0;
    }
    SPTabbarViewElement::SPTabbarViewElement()
     : SPViewElement() {

    }
    void SPTabbarViewElement::mouseDown(int mouseButton, int x, int y) {
        SPElement::mouseDown(mouseButton, x, y);
    }
    SPTabbarViewElement::SPTabbarViewElement(SPElement *parent)
     : SPViewElement::SPViewElement(parent)
    {
        //ctor
        this->tabBar = new SPTabBarElement(parent);
        this->viewStack = new SPViewStackElement(parent);
        this->viewStack->setIntegerAttribute("flex", 1);
        this->tabBar->setHeight(28);
        this->appendChild(this->tabBar);
        this->tabBar->addEventListener(string("tabselected"), SPCallback(&SPTabbarViewElement::onTabSelected), this);
        this->appendChild(this->viewStack);
    }
    bool SPTabbarViewElement::acceptsUri(string uri) {
        return false;
    }
    void SPTabbarViewElement::navigate(string uri) {
        this->viewStack->navigate(uri);
    }
    SPTabbarViewElement::~SPTabbarViewElement()
    {
        delete this->tabBar;
        delete this->viewStack;
    }
}
