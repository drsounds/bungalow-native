#include "SPTabBarElement.h"

#include <iostream>

#include "SPMouseEventArgs.h"
#include "SPColor.h"
#include "SPSkin.h"
#include "SPGraphicsContext.h"

namespace space {

SPTab::SPTab(SPTabBarElement *tabBar, string name, string id, string uri) {
    this->tabBar = tabBar;
    this->name = name;
    this->id = id;
    this->uri = uri;
}

int SPTabBarElement::tabbar_mousedown(SPObject *sender, SPEventArgs *e) {
    SPTabBarElement *tabBar = (SPTabBarElement *)sender;
    SPMouseEventArgs *me = (SPMouseEventArgs *)e;
    int x = tabBar->getAbsoluteBounds() != NULL ? me->getX() - tabBar->getAbsoluteBounds()->y : me->getX();
    int y = tabBar->getAbsoluteBounds() != NULL ? me->getY() - tabBar->getAbsoluteBounds()->y : me->getY();
    int left = 0;
    ;
    for(std::vector<SPTab *>::iterator it = tabBar->tabs->begin(); it != tabBar->tabs->end(); ++it) {
        SPTab *tab = (SPTab *)dynamic_cast<SPTab *>(*it);
        string title = tab->getName();
        string id = tab->getId();
        string uri = tab->getUri();
        SPFontStyle fontStyle = tabBar->getFontStyle();
        SPGraphicsContext *g = tabBar->createGraphics();
        sp_rectangle strSize = g->measureString(title.c_str(), fontStyle);
        int width = 20 + strSize.width + 20;
        if (x > left && x < left + width) {
            tabBar->activeTab = tab;
            TabBarEventArgs *args = new TabBarEventArgs(tab);
            tabBar->notify(string("tabselected"), (SPObject *)tabBar, (SPEventArgs *)args);
        }

        left += width;
    }
    tabBar->invalidate();
    return 0;
}
string SPTabBarElement::getType() {
     return "tabbar";
}
void SPTabBarElement::addTab(string id, string name, string uri) {
    SPTab *tab = new SPTab(this, id, name, uri);
    this->tabs->push_back(tab);
    if (this->tabs->size() == 1) {
        this->activeTab = tab;
    }
}

TabBarEventArgs::TabBarEventArgs(SPTab *tab) {
    this->tab = tab;
}

SPTabBarElement::SPTabBarElement()
 : SPElement()
{
    this->clipView = false;
    //ctor
    this->tabs = new std::vector<SPTab *>;
    this->addEventListener(string("mousedown"), SPCallback(&SPTabBarElement::tabbar_mousedown), this);

}
SPTabBarElement::SPTabBarElement(SPElement *parent)
 : SPElement(parent)
{
    this->m_backgroundImage = (SPImage *)this->m_skin->getImage("tabbar.background.image", "");
    //ctor
    this->tabs = new std::vector<SPTab *>;
    this->addEventListener(string("mousedown"), SPCallback(&SPTabBarElement::mouseDown), this);
    std::vector<SPObserver *> *observers = this->observers;
}
void SPTabBarElement::mouseDown(SPObject* sender, SPEventArgs *e) {
    SPMouseEventArgs *me = (SPMouseEventArgs *)e;
    SPTabBarElement *tabBar = this;
    int x = me->getX();
    SPFontStyle font = tabBar->getFontStyle();
    int left = tabBar->getAbsoluteBounds() != NULL ? tabBar->getAbsoluteBounds()->x : 0;
    for(std::vector<SPTab *>::iterator it = tabBar->getTabs()->begin(); it != tabBar->getTabs()->end(); ++it) {
        SPTab *tab = (SPTab *)static_cast<SPTab *>(*it);
        string title = tab->getName();
        string id = tab->getId();
        string uri = tab->getUri();
        SPGraphicsContext *g = tabBar->createGraphics();
        sp_rectangle strSize = g->measureString((string)title.c_str(), font);
        int width = 100;//20 + strSize.width + 20;
        if (x > left  && x < left + width) {
            tabBar->activeTab = tab;
            TabBarEventArgs *args = new TabBarEventArgs(tab);
            tabBar->notify(string("tabselected"), (SPObject *)tabBar, (SPEventArgs *)args);
            cout << title.c_str();
            break;
        }

        left += width;
    }
    tabBar->invalidate();
}
#define spacify2009 true
void SPTabBarElement::paint(int x, int y, int width, int height, SPGraphicsContext *g) {
    
    this->getSkin()->drawTabBar(g, this, x, y, width, height);

    int left = 0;
    int index = 0;
    for (std::vector<SPTab *>::iterator it = this->getTabs()->begin(); it != this->getTabs()->end(); ++it) {
        SPColor fgColor = this->getForegroundColor();

        SPTab *tab = (SPTab *)static_cast<SPTab *>(*it);

        string title = tab->getName();
        string id = tab->getId();
        sp_rectangle strSize = g->measureString(title, this->getFontStyle());
        int tabWidth = 20 + strSize.width + 20;
        this->getSkin()->drawTabBarTab(g, this, tab, index, this->activeTab == tab, x + left, y, tabWidth, height);

        g->drawString(title, this->getFontStyle(), fgColor, left + x + (tabWidth / 2) - (strSize.width / 2), y + (height / 2) - (strSize.height / 2), strSize.width, strSize.height);
        left += tabWidth;
        index++;
    }
}


SPTabBarElement::~SPTabBarElement()
{
    //dtor
}
}
