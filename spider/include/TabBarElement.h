#ifndef TABBARELEMENT_H
#define TABBARELEMENT_H
#include <string>
#include "Element.h"
#include "MouseEventArgs.h"
#include <vector>
using namespace std;
namespace spider {
class Element;
class Image;
class TabBarElement;
#ifndef TAB_CLASS
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
#define TAB_CLASS
#endif
class EventArgs;
#ifndef TABBAREVENTARGS_CLASS

class TabBarEventArgs : public EventArgs {
public:
    TabBarEventArgs(Tab *tab);
    Tab *tab;
};
#define TABBAREVENTARGS_CLASS
#endif
#ifndef TABBARELEMENT_CLASS
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
        void mousedown(int mouseButton, int x, int y);
        void draw(int x, int y, GraphicsContext *g);
        vector<Tab *> *getTabs() {
            return this->tabs;
        }
        Tab *activeTab;
        vector<Tab *> *tabs;
    protected:
    private:
};
#define TABBARELEMENT_CLASS
#endif
}


#endif // TABBARELEMENT_H
