#include "SPTabBarElement.h"

#include <iostream>

#include "SPMouseEventArgs.h"
#include "SPColor.h"
#include "SPSkin.h"
#include "SPGraphicsContext.h"

namespace spider {

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
    this->set("active_tab_fgcolor", "#ffffff");
    this->set("active_tab_bgcolor", "#474747");
    this->addEventListener(string("mousedown"), SPCallback(&SPTabBarElement::tabbar_mousedown), this);

}
SPTabBarElement::SPTabBarElement(SPElement *parent)
 : SPElement(parent)
{
    this->m_backgroundImage = (SPImage *)this->m_skin->getImage("tabbar.background.image", "");
    //ctor
    this->tabs = new std::vector<SPTab *>;
    this->set("active_tab_fgcolor", "#ffffff");
    this->set("active_tab_bgcolor", "#474747");
    this->set("bgcolor", "#666666");
    this->addEventListener(string("mousedown"), SPCallback(&SPTabBarElement::tabbar_mousedown), this);
    std::vector<SPObserver *> *observers = this->observers;
    int count = observers->size();
    if (count < 1)
        {
        int f = 0;
    }


}
void SPTabBarElement::mouseDown(int mouseButton, int x, int y) {
    SPTabBarElement *tabBar = this;
    x = tabBar->getAbsoluteBounds() != NULL ? x - tabBar->getAbsoluteBounds()->x : x;
    y = tabBar->getAbsoluteBounds() != NULL ? y - tabBar->getAbsoluteBounds()->y : y;
    SPFontStyle font = tabBar->getFontStyle();
    int left = 0;
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
void SPTabBarElement::draw(int x, int y, SPGraphicsContext *g) {
    SPElement::draw(x, y, g);
    if (this->absoluteBounds == NULL)
        this->absoluteBounds = new sp_rectangle;

    this->absoluteBounds->x = x;
    this->absoluteBounds->y = y;
    this->absoluteBounds->width = this->getWidth();
    this->absoluteBounds->height = this->getHeight();
    //g->fillRectangle(x, y, this->getWidth(), this->getHeight(), (Color *)this->getAttributeObj("bgcolor"));
    // Draw background image

    map<string, slice *> *slices = this->m_skin->slices;

    g->drawImageSlices(slices, "tabbar.background.image", x, y-1, this->getWidth(), this->getHeight());

    int left = 0;
    std::vector<SPTab *>::iterator it = this->getTabs()->begin();
    do {
        SPColor fgColor = this->getColorAttribute("fgcolor", SPColor(255, 255, 255, 1));

        SPTab *tab = (SPTab *)static_cast<SPTab *>(*it);

        string title = tab->getName();
        string id = tab->getId();
        sp_rectangle strSize = g->measureString((string)title.c_str(), this->getFontStyle());
        int width = 100;// 20 + strSize.width + 20;
        if (this->activeTab == tab) {
            #if spacify2009
            fgColor = this->getColorAttribute("active_tab_fgcolor", SPColor(255, 255, 255, 1));
            SPColor bgColor = this->getColorAttribute("active_tab_bgcolor", SPColor(0, 0, 0, 1));
            g->fillRectangle(x + left, y, width, this->getHeight(), bgColor);



            #else
            SPColor bgColor = this->getColorAttribute("highlight", SPColor(0, 0, 0, 1));
            g->fillRectangle(x + left, y + this->getHeight() - 5, width, 5, bgColor);
            #endif
        } else {
            #if spacify2009
            // Draw line
            g->drawLine(left + width, y, left + width, this->getHeight() + y, SPColor(0, 0, 0, 1));
            #endif
        }
        g->drawString(title.c_str(), this->getFontStyle(), fgColor, left + x + 20, y + (this->getHeight() / 2) - (strSize.height / 2), strSize.width, strSize.height);
        left += width;
        ++it;
    } while (it != this->getTabs()->end());
}


SPTabBarElement::~SPTabBarElement()
{
    //dtor
}
}
