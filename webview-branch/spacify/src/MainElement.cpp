#include "MainElement.h"
#include "SpacifyApp.h"
#include "LibraryView.h"
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
#include "SPNowPlayingBarElement.h"
#include "SPAppHeaderElement.h"
#include "SPTreeViewElement.h"
#include "SPButtonElement.h"
#include "ConfigView.h"
#include "LocalFilesView.h"

namespace space {
    MainElement::MainElement()
    {

    }

    void MainElement::hideMessage() {
        this->infoElement->hide();
        this->infoElement->invalidate();
    }

    void MainElement::showMessage(SPMessageType msgType, string msg) {
        this->infoElement->show(msgType, msg);
    }
    int MainElement::treeview_itemselected(SPObject *sender, SPEventArgs *e) {
        auto *treeView = (SPTreeViewElement *)sender;
        auto *mainWindow = (MainElement *)treeView->getParentNode();
        auto *args = (TreeViewEventArgs *)e;
        SPTreeItem *selectedItem = args->getItem();
        SPUri *uri = selectedItem->getUri();
        string uri2 = uri->getUri();
        string uri3 (uri2);
        this->navigate(uri3);
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
        } else if (name == "nowplayingbar") {
            elm = new SPNowPlayingBarElement(parent);
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
        header->setHeight(60);
		header->setPadding({ 5, 25, 5, 5 });
        header->setGap(5);

        backButton = (SPButtonElement *)this->getElementById("backButton");
        backButton->setInnerText("<");
        backButton->setWidth(28);
    	backButton->setHeight(28);
        backButton->addEventListener("click", SPCallback(&MainElement::onBackClicked), this, backButton);

        forwardButton = (SPButtonElement *)this->getElementById("forwardButton");
        forwardButton->setInnerText(">");
        forwardButton->setWidth(28);
    	forwardButton->setHeight(28);
        forwardButton->addEventListener("click", SPCallback(&MainElement::onForwardClicked), this, forwardButton);

        searchElement = (SPInputElement *)this->getElementById("searchInput");
        searchElement->setWidth(120);
    	searchElement->setHeight(28);
        searchElement->setColorAttribute("bgcolor", SPColor("#777777"));
        searchElement->addEventListener("enter", reinterpret_cast<SPCallback>(&MainElement::onSearchEntered), this, this);

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
        auto *item = new SPTreeItem(new SPUri("spacify:start"));
        item->setSelected(false);
        auto *itemLibrary = new SPTreeItem(new SPUri("spacify:library"));
        itemLibrary->setText("Library");
        itemLibrary->setSelected(false);
        auto *itemLocalFiles = new SPTreeItem(new SPUri("spacify:localfiles"));
        itemLocalFiles->setText("Local Files");
        itemLocalFiles->setSelected(false);
        treeView->addEventListener("itemselected", SPCallback(&MainElement::treeview_itemselected), this, treeView);
        treeView->addItem(item);
        treeView->addItem(itemLibrary);
        treeView->addItem(itemLocalFiles);
        treeView->setFlex(1);

        // Now-playing widget pinned to the bottom of the sidebar (below the flex treeview)
        m_nowPlayingBar = new SPNowPlayingBarElement(leftSidebar);
        leftSidebar->appendChild(m_nowPlayingBar);

        // Add viewstack
        viewStack = (SPViewStackElement *)this->getElementById("viewstack");
        viewStack->setFlex(1);
        sqlite3* db = nullptr;
        if (auto* app = dynamic_cast<SpacifyApp*>(wxTheApp))
            db = app->getDatabase() ? app->getDatabase()->handle() : nullptr;

        viewStack->appendChild(new views::SpaceView(viewStack));
        viewStack->appendChild(new views::StartView(viewStack));
        viewStack->appendChild(new views::ConfigView(viewStack));
        viewStack->appendChild(new views::LibraryView(viewStack, db));
        viewStack->appendChild(new views::LocalFilesView(viewStack, db));

        body->appendChild(new SPSplitterElement(body));
        auto *playQueuePanel = new views::PlayQueueView(body);
        body->appendChild(playQueuePanel);
        body->pack();

        footer = (SPAppFooterElement *)this->getElementById("footer");
        footer->setHeight(32);
        footer->setId("footer");
        // Add header buttons
        this->navigate("spacify:start");
    }

    MainElement::MainElement(SPElement *parent) : SPVBoxElement(parent)
    { 
        this->loadXUL("resources/app/views/app.xml"); // CWD set to resources parent by SpacifyApp::OnInit
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
    int MainElement::onBackClicked(SPObject *, SPEventArgs *) {
        if (!viewStack->canGoBack()) return 0;
        viewStack->goBack();
        searchElement->setValue(viewStack->getCurrentUri());
        return 0;
    }

    int MainElement::onForwardClicked(SPObject *, SPEventArgs *) {
        if (!viewStack->canGoForward()) return 0;
        viewStack->goForward();
        searchElement->setValue(viewStack->getCurrentUri());
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
