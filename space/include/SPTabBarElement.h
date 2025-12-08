#ifndef TABBARELEMENT_H
#define TABBARELEMENT_H

#include <string>
#include <vector>

#include "SPEventArgs.h"
#include "SPElement.h"

using namespace std;
namespace space {
class SPElement;
class SPGraphicsContext;
class SPImage;
class SPTabBarElement;
class SPTab {
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
    SPTab(SPTabBarElement *tabBar, string name, string id, string uri);
    ~SPTab();
};
class SPEventArgs;

class TabBarEventArgs : public SPEventArgs {
public:
    explicit TabBarEventArgs(SPTab *tab);
    SPTab *tab;
};
class SPTabBarElement : public SPElement
{
    public:
        SPImage *tabBackgroundImage;
        SPImage *activeTabBackgroundImage;
        int tabbar_mousedown(SPObject* sender, SPEventArgs* e);
        virtual string getType();
        SPTabBarElement();
        SPTabBarElement(SPElement *parent);
        void addTab(string id, string name, string uri);
        void paint(int x, int y, int width, int height, SPGraphicsContext* c) override;
        virtual ~SPTabBarElement();
        void mouseDown(int mouseButton, int x, int y);
        vector<SPTab *> *getTabs() {
            return this->tabs;
        }
        SPTab *activeTab;
        vector<SPTab *> *tabs;
    protected:
    private:
};
}


#endif // TABBARELEMENT_H
