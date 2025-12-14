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
    	this->setTagName("tabbarview");
        //ctor
        this->tabBar = new SPTabBarElement(this);
        this->viewStack = new SPViewStackElement(this);
        this->viewStack->setIntegerAttribute("flex", 1);
        this->tabBar->setHeight(28);
        this->appendChild(this->tabBar);
        this->tabBar->addEventListener(string("tabselected"), static_cast<SPCallback>(&SPTabbarViewElement::onTabSelected), this);
        this->appendChild(this->viewStack);
    	this->addEventListener("treechanged", SPCallback(&SPTabbarViewElement::onTreeChanged), this);
		this->addEventListener("unload", SPCallback(&SPTabbarViewElement::onUnload), this);
		this->addEventListener("mousedown", SPCallback(&SPTabbarViewElement::onClick), this);
    	this->addEventListener("load", SPCallback(&SPTabbarViewElement::onLoad), this);
    }
    void SPTabbarViewElement::onLoad(SPObject* sender, SPEventArgs* e) {
    	if (this->tabBar->getTabs()->size() > 0) {
    		this->navigate(this->tabBar->getTabs()->at(0)->getUri());
    	}
    }
	void SPTabbarViewElement::onClick(SPObject *sender, SPEventArgs *e) {
    }
	void SPTabbarViewElement::onUnload(SPObject *sender, SPEventArgs *e) {
	    this->tabBar->clear();
    }
	void SPTabbarViewElement::onTreeChanged(SPObject *sender, SPEventArgs *e) {
	    SPNodeTreeEventArgs *args = (SPNodeTreeEventArgs *)e;
    	if (args->getAction() == "remove") {
    		SPElement *elm = dynamic_cast<SPElement *>(args->getNode());
    		if (elm->getTagName() == "section") {
    			SPViewElement *view = dynamic_cast<SPViewElement *>(elm);
    			this->tabBar->remove(view->getUri());
    		}
    	} else if (args->getAction() == "append") {
		    SPElement *elm = dynamic_cast<SPElement *>(args->getNode());
	    	if (elm->getTagName() == "section") {
	    		SPViewElement *view = dynamic_cast<SPViewElement *>(elm);
	    		view->setUri(this->getUri() + ":" + view->getId());
	    		this->tabBar->addTab(elm->getId(), view->getStringAttribute("title", elm->getId()), elm->getUri());
	    		this->removeChild(elm);
 	    		this->viewStack->appendChild(view);
	    	}
	    }
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
