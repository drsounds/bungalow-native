#include "MainElement.h"
#include "StartView.h"
#include "SPInputElement.h"
#include "SPInputEventArgs.h"
#include "SPWindowElement.h"
#include "SPSplitterElement.h"
#include "SPNavigateEventArgs.h"
#include "SPInfoElement.h"
#include "SPTreeItem.h"
#include "SPViewStackElement.h"
#include "SPSkin.h"
#include "PlayQueueView.h"
#include "SpaceView.h"
#include "SPAppFooterElement.h"
#include "SPAppHeaderElement.h"
#include "SPTreeViewElement.h"
#include "SPButtonElement.h"

namespace space {
    MainElement::MainElement()
    {

    }

    void MainElement::hideMessage() {
        this->infoElement->hide();
    }
    int MainElement::treeview_itemselected(SPObject *sender, SPEventArgs *e) {
        auto *treeView = (SPTreeViewElement *)sender;
        auto *mainWindow = (MainElement *)treeView->getParentNode();
        auto *args = (TreeViewEventArgs *)e;
        SPTreeItem *selectedItem = args->getItem();
        SPUri *uri = selectedItem->getUri();
        string uri2 = uri->getUri();
        string uri3 (uri2);
        mainWindow->navigate(uri3);
        return 0;
    }
    void MainElement::navigate(const string& uri) const
    {
        this->viewStack->navigate(uri);
        this->searchElement->setValue(uri);
    }

    SPElement* MainElement::createElement(const string& name, SPElement *parent) {
        SPElement *elm = nullptr;
        if (name == "appheader") {
            elm = new SPAppHeaderElement(parent);
            assert(elm->getParentElement() != nullptr);
        } else if (name == "viewstack") {
            elm = new SPViewStackElement(parent);
            assert(elm->getParentElement() != nullptr);
        } else if (name == "treeview") {
            elm = new SPTreeViewElement(parent);
            assert(elm->getParentElement() != nullptr);
        } else if (name == "appfooter") {
            elm = new SPAppFooterElement(parent);
            assert(elm->getParentElement() != nullptr);
        } else if (name == "tabbar") {
            elm = new SPTabBarElement(parent);
            assert(elm->getParentElement() != nullptr);
        } else {
            elm = SPElement::createElement(name, parent);
            assert(elm->getParentElement() != nullptr);
        }
        return elm;
    }

    void MainElement::onLoad(SPNode *sender, SPEventArgs *args) {
    }

    void MainElement::layout() {
        this->clipView = false;

        header = (SPAppHeaderElement *)this->getElementById("header");
        header->setHeight(38);
		header->setPadding({ 5, 5, 5, 5 });
        header->setGap(5);

        backButton = (SPButtonElement *)this->getElementById("backButton");
        backButton->setInnerText("<");
        backButton->setWidth(28);
    	backButton->setHeight(28);

        forwardButton = (SPButtonElement *)this->getElementById("forwardButton");
        forwardButton->setInnerText("<");
        forwardButton->setWidth(28);
    	forwardButton->setHeight(28);

        searchElement = (SPInputElement *)this->getElementById("searchInput");
        searchElement->setWidth(120);
    	searchElement->setHeight(28);
        searchElement->setFlex(1);
        searchElement->setColorAttribute("bgcolor", SPColor("#777777"));
        searchElement->addEventListener("enter", reinterpret_cast<SPCallback>(&MainElement::onSearchEntered), this, this);

        accountButton = (SPButtonElement *)this->getElementById("accountButton");
        accountButton->setInnerText("A");
        accountButton->setWidth(28);
    	accountButton->setHeight(28);

        infoElement = new space::SPInfoElement(this);
        infoElement->setHeight(28);
        infoElement->setId("Info");
        infoElement->hide();

        body = (SPHBoxElement *)this->getElementById("body");
        body->setFlex(1);
        leftSidebar = (SPVBoxElement *)this->getElementById("leftSidebar");

    	SPElement *leftTabBar = leftSidebar->getElementById("leftTabBar");
        tabBar = (SPTabBarElement *)leftTabBar;
    	treeView = (SPTreeViewElement *)this->getElementById("treeview");
        // Add sample elements
        auto *item = new SPTreeItem(new SPUri("spacify:internal:start"));
        item->setSelected(false);
        auto *item2 = new SPTreeItem(new SPUri("spacify:internal:history"));
        item2->setSelected(false);
        treeView->addEventListener("itemselected", SPCallback(&MainElement::treeview_itemselected), this, treeView);
        treeView->addItem(item);
        treeView->addItem(item2);
        treeView->setFlex(1);

        // Add viewstack
        viewStack = (SPViewStackElement *)this->getElementById("viewstack");
        viewStack->setFlex(1);
        viewStack->appendChild(new views::SpaceView(viewStack));
        viewStack->appendChild(new views::StartView(viewStack));
        viewStack->appendChild(new views::PlayQueueView(viewStack));

    	/*
        body->appendChild(new SPSplitterElement(body));
        auto *rightSidebar = new SPVBoxElement(body);
        rightSidebar->setId("sidebar");
        rightSidebar->setWidth(220);
        body->appendChild(rightSidebar);
        body->pack();
		*/

        footer = (SPAppFooterElement *)this->getElementById("footer");
        footer->setHeight(32);
        footer->setId("footer");
        // Add header buttons
        this->navigate("spacify:start:overview");
    }

    MainElement::MainElement(SPElement *parent) : SPVBoxElement(parent)
    { 
        this->loadXUL("../resources/app/views/app.xml");
        this->layout();
        this->addEventListener("load", SPCallback(&MainElement::onLoad), this, this);
        this->getWindowElement()->addEventListener("navigate", static_cast<SPCallback>(&MainElement::onNavigate), this, this);
    }

    int MainElement::onNavigate(SPObject* sender, SPEventArgs* args)
    {
        auto *eventArgs = dynamic_cast<SPNavigateEventArgs *>(args);
        this->navigate(eventArgs->getUrl());
        return 0;
    }
    int MainElement::onSearchEntered(SPObject *, SPEventArgs *eventArgs) const
    {
        auto *ie = dynamic_cast<SPInputEventArgs*>(eventArgs);
        string query = ie->getText();
        if (query.find("spacify:") < 0) {
            query = "spacify:search:" + query;
        }
        this->viewStack->navigate(query);
        return 0;
    }
    MainElement::~MainElement()
    {
        //dtor
    }
    SPViewStackElement *MainElement::getViewStack() {
        return this->viewStack;
    }
}
