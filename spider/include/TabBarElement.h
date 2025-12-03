#ifndef TABBARELEMENT_H
#define TABBARELEMENT_H

#include <string>
#include <vector>

#include "EventArgs.h"
#include "Element.h"

using namespace std;
namespace spider {
class Element;
class GraphicsContext;
class Image;
class TabBarElement;
class Tab {
protected:
public:
    string id;
    string name;
    string uri;
    TabBarElement *tabBar;
    TabBarElement *getTabBar() {
        return this->tabBar;
    }
    string getId() {
        return this->id;
    }
    string getName() {
        return this->name;
    }
    string getUri() {
        return this->uri;
    }
    Tab(TabBarElement *tabBar, string name, string id, string uri);
    ~Tab();
};
class EventArgs;

class TabBarEventArgs : public EventArgs {
public:
    TabBarEventArgs(Tab *tab);
    Tab *tab;
};
class TabBarElement : public Element
{
    public:
        Image *tabBackgroundImage;
        Image *activeTabBackgroundImage;
        virtual string getType();
        TabBarElement();
        TabBarElement(Element *parent);
        void addTab(string id, string name, string uri);
        virtual ~TabBarElement();
        void mouseDown(int mouseButton, int x, int y);
        void draw(int x, int y, GraphicsContext *g);
        vector<Tab *> *getTabs() {
            return this->tabs;
        }
        Tab *activeTab;
        vector<Tab *> *tabs;
    protected:
    private:
};
}


#endif // TABBARELEMENT_H
