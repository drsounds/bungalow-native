#ifndef TABBARELEMENT_H
#define TABBARELEMENT_H

#include <string>
#include <vector>

#include "SPEventArgs.h"
#include "SPElement.h"

using namespace std;
namespace spider {
class SPElement;
class SPGraphicsContext;
class SPImage;
class SPTabBarElement;
class Tab {
protected:
public:
    string id;
    string name;
    string uri;
    SPTabBarElement *tabBar;
    SPTabBarElement *getTabBar() {
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
    Tab(SPTabBarElement *tabBar, string name, string id, string uri);
    ~Tab();
};
class SPEventArgs;

class TabBarEventArgs : public SPEventArgs {
public:
    TabBarEventArgs(Tab *tab);
    Tab *tab;
};
class SPTabBarElement : public SPElement
{
    public:
        SPImage *tabBackgroundImage;
        SPImage *activeTabBackgroundImage;
        virtual string getType();
        SPTabBarElement();
        SPTabBarElement(SPElement *parent);
        void addTab(string id, string name, string uri);
        virtual ~SPTabBarElement();
        void mouseDown(int mouseButton, int x, int y);
        void draw(int x, int y, SPGraphicsContext *g);
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
