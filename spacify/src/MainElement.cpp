#include "MainElement.h"
#include "StartView.h"
#include "SPInputElement.h"
#include "SPInputEventArgs.h"
#include "SPWindowElement.h"
#include "SPSplitterElement.h"
#include "SPInfoElement.h"
#include "SPTreeItem.h"
#include "SPViewStackElement.h"
#include "SPSkin.h"
#include "PlayQueueView.h"
#include "SPAppHeaderElement.h"
#include "SPTreeViewElement.h"

namespace spider {
    MainElement::MainElement()
    {

    }

    void MainElement::hideMessage() {
        this->infoElement->hide();
    }
    int MainElement::treeview_itemselected(SPObject *sender, SPEventArgs *e) {
        auto *treeView = (SPTreeViewElement *)sender;
        auto *mainWindow = (MainElement *)treeView->getParent();
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

    MainElement::MainElement(SPElement *parent, SPWindow *window) : SPVBoxElement(parent, window)
    {
        this->viewStack = new SPViewStackElement(this);
        this->treeView = new SPTreeViewElement(this);
        this->infoElement = new SPInfoElement(this);
        this->layout();
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
        this->set("bgcolor", "#373737");
        auto *header = new SPAppHeaderElement(this);
        header->setColorAttribute("bgcolor", SPColor("#767676"));
        header->setHeight(55);
        header->getPadding()->top = 53;
        header->getPadding()->left = 13;
        header->getPadding()->bottom = 13;
        header->getPadding()->right =  13;
        header->setHeight(55);
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
        this->infoElement = new spider::SPInfoElement(this);
        this->infoElement->setHeight(28);
        this->appendChild((SPNode *)this->infoElement);
        this->infoElement->setId("Info");
        this->infoElement->hide();

        // Add header children

        auto *body = new SPHBoxElement(this);
        body->setColorAttribute("bgcolor", SPColor("#474747"));
        body->setIntegerAttribute("flex", 1);
        body->setId("body");
        this->appendChild(body);
        // Inside body
        auto *sidebar = new SPVBoxElement(body);
        sidebar->setId("sidebar");
        sidebar->setWidth(220);
        sidebar->setColorAttribute("bgcolor", SPColor(100, 100, 100, 1));
        body->appendChild(sidebar);

        body->appendChild(new SPSplitterElement(body));

        // Add TreeView
        this->treeView = new SPTreeViewElement(sidebar);
        treeView->setId("tree");
        treeView->set("bgcolor", "#575757");
        treeView->set("fgcolor", "#dddddd");
        treeView->setIntegerAttribute("flex", 1);
        treeView->setHeight(920);
        treeView->setWidth(220);
        sidebar->appendChild(treeView);
        treeView->setWindow(this->getWindow());
        // Add sample elements
        auto *item = new SPTreeItem(new SPUri("spacify:internal:start"));

        item->setSelected(false);
        auto *item2 = new SPTreeItem(new SPUri("spacify:internal:history"));

        item2->setSelected(false);
        treeView->addEventListener("itemselected", SPCallback(&MainElement::treeview_itemselected), this);
        treeView->addItem(item);
        treeView->addItem(item2);

        // Add viewstack

        this->viewStack = new spider::SPViewStackElement(body);
        this->viewStack->setId("viewstack");
        viewStack->set("bgcolor", "#373737");
        body->appendChild(viewStack);
        viewStack->setIntegerAttribute("flex",1);
        viewStack->setWindow(this->getWindow());
        viewStack->appendChild(new spider::views::StartView(this));
        viewStack->appendChild(new spider::views::PlayQueueView(this));

        auto *footer = new spider::SPHBoxElement(this);
        footer->set("bgcolor", "#444444");
        footer->set("height", "86");
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
