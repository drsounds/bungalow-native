#include "MainElement.h"
#include "StartView.h"
#include "SPInputElement.h"
#include "SPInputEventArgs.h"
#include "SPWindowElement.h"
#include "SPSplitterElement.h"
#include "SPInfoElement.h"
#include "SPTreeItem.h"
#include "SPViewStackElement.h"
#include "Skin.h"
#include "PlayQueueView.h"
#include "SPTreeViewElement.h"

namespace spider {
    MainElement::MainElement()
    {

    }

    void MainElement::hideMessage() {
        this->infoElement->hide();
    }
    int treeview_itemselected(SPObject *sender, SPEventArgs *e) {
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

    MainElement::MainElement(SPElement *parent) : SPVBoxElement(parent)
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
        auto *header = new SPHBoxElement(this);
        header->setColorAttribute("bgcolor", SPColor("#767676"));
        header->setIntegerAttribute("height", 55);
        header->getPadding()->top = 53;
        header->getPadding()->left = 13;
        header->getPadding()->bottom = 13;
        header->getPadding()->right =  13;
        header->setBackgroundImage(this->getSkin()->getImage("header.background.image", ""));
        this->appendChild(header);
        header->setId("header");
        // add search element
        auto *searchElement = new SPInputElement(header);
        header->appendChild(searchElement);
        searchElement->setIntegerAttribute("width", 120);
        searchElement->setName("searchBox");
        searchElement->setColorAttribute("bgcolor", SPColor("#777777"));
        searchElement->addEventListener("enter", reinterpret_cast<SPCallback>(&MainElement::onSearchEntered));
        // Add the info element
        this->infoElement = new spider::SPInfoElement(this);
        this->infoElement->setIntegerAttribute("height", 28);
        this->appendChild((SPNode *)this->infoElement);
        this->infoElement->hide();

        // Add header children

        auto *body = new SPHBoxElement(this);
        body->setColorAttribute("bgcolor", SPColor("#474747"));
        body->set("flex", "1");
        body->set("height", "100");

        this->appendChild(body);

        // Inside body
        auto *sidebar = new SPVBoxElement(body);
        sidebar->set("width", "220");
        sidebar->set("bgcolor", "#474747");
        body->appendChild(sidebar);

        body->appendChild(new SPSplitterElement(body));

        // Add TreeView
        this->treeView = new SPTreeViewElement(sidebar);
        treeView->set("bgcolor", "#575757");
        treeView->set("fgcolor", "#dddddd");
        treeView->set("flex", "1");
        treeView->set("height", "920");
        treeView->set("width", "220");
        sidebar->appendChild(treeView);
        treeView->setWindowElement(this->getWindowElement());
        // Add sample elements
        auto *item = new SPTreeItem(new SPUri("spacify:internal:start"));

        item->setSelected(false);
        auto *item2 = new SPTreeItem(new SPUri("spacify:internal:history"));

        item2->setSelected(false);
        treeView->addEventListener("itemselected", &treeview_itemselected);
        treeView->addItem(item);
        treeView->addItem(item2);

        // Add viewstack

        this->viewStack = new spider::SPViewStackElement(body);
        viewStack->set("bgcolor", "#373737");
        body->appendChild(viewStack);
        viewStack->set("flex", "1");
        viewStack->setWindowElement(this->getWindowElement());
        viewStack->appendChild(new spider::views::StartView(this));
        viewStack->appendChild(new spider::views::PlayQueueView(this));
        auto *footer = new spider::SPHBoxElement(this);
        footer->set("bgcolor", "#444444");
        footer->set("height", "86");
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
