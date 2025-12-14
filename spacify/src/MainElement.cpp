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
#include "SPAppFooterElement.h"
#include "SPAppHeaderElement.h"
#include "SPTreeViewElement.h"

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
    }

    MainElement::MainElement(SPElement *parent) : SPVBoxElement(parent)
    {
        this->viewStack = new SPViewStackElement(this);
        this->treeView = new SPTreeViewElement(this);
        this->infoElement = new SPInfoElement(this);
        this->layout();
        this->addEventListener("navigate", static_cast<SPCallback>(&MainElement::onNavigate), this, this);
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
    void MainElement::layout() {
        this->clipView = false;
        auto *header = new SPAppHeaderElement(this);
        header->setHeight(55);
        header->getPadding()->top = 53;
        header->getPadding()->left = 13;
        header->getPadding()->bottom = 13;
        header->getPadding()->right =  13;
        this->appendChild(header);
        header->setId("header");
        // add search element
        /*
        auto *searchElement = new SPInputElement(header);

        header->appendChild(searchElement);
        searchElement->setIntegerAttribute("width", 120);
        searchElement->setName("searchBox");
        searchElement->setColorAttribute("bgcolor", SPColor("#777777"));
        searchElement->addEventListener("enter", reinterpret_cast<SPCallback>(&MainElement::onSearchEntered), this);
        */
        // Add the info element
        this->infoElement = new space::SPInfoElement(this);
        this->infoElement->setHeight(28);
        this->appendChild((SPNode *)this->infoElement);
        this->infoElement->setId("Info");
        this->infoElement->hide();

        // Add header children

        auto *body = new SPHBoxElement(this);
        body->setIntegerAttribute("flex", 1);
        body->setId("body");
        this->appendChild(body);
        // Inside body
        auto *leftSidebar = new SPVBoxElement(body);
        leftSidebar->setId("sidebar");
    	leftSidebar->setWidth(220);
    	auto *tabBar = new SPTabBarElement(leftSidebar);
    	tabBar->setId("tabbar");
    	tabBar->setHeight(28);
    	leftSidebar->appendChild(tabBar);
    	this->treeView = new SPTreeViewElement(leftSidebar);
    	treeView->setId("tree");
    	treeView->setIntegerAttribute("flex", 1);
    	treeView->setHeight(920);
    	treeView->setWidth(220);
    	leftSidebar->appendChild(treeView);
        body->appendChild(leftSidebar);

        body->appendChild(new SPSplitterElement(body));

        // Add sample elements
        auto *item = new SPTreeItem(new SPUri("spacify:internal:start"));

        item->setSelected(false);
        auto *item2 = new SPTreeItem(new SPUri("spacify:internal:history"));

        item2->setSelected(false);
        treeView->addEventListener("itemselected", SPCallback(&MainElement::treeview_itemselected), this, treeView);
        treeView->addItem(item);
        treeView->addItem(item2);

        // Add viewstack
        this->viewStack = new space::SPViewStackElement(body);
        this->viewStack->setId("viewstack");
        viewStack->setIntegerAttribute("flex",1);
        viewStack->appendChild(new views::StartView(viewStack));
        viewStack->appendChild(new views::PlayQueueView(viewStack));
        body->appendChild(viewStack);

        body->appendChild(new SPSplitterElement(body));

        auto *rightSidebar = new SPVBoxElement(body);
        rightSidebar->setId("sidebar");
        rightSidebar->setWidth(220);
        body->appendChild(rightSidebar);
        body->pack();
        auto *footer = new space::SPAppFooterElement(this);
        footer->setHeight(32);
        footer->setId("footer");
        this->appendChild(footer);

        // Add header buttons
        this->pack();
        this->navigate("spacify:internal:start");
    }
    MainElement::~MainElement()
    {
        //dtor
    }
    SPViewStackElement *MainElement::getViewStack() {
        return this->viewStack;
    }
}
