#ifndef SKIN_H
#define SKIN_H
#include <map>
#include <string>

#include "SPTabBarElement.h"
#include "SPTableElement.h"
#include "SPTreeItem.h"
#include "SPTreeViewElement.h"

#define SP_MODE_DEFAULT 0
#define SP_MODE_DARK 1
#define SP_MODE_LIGHT 2

namespace space
{
    class SPElement;
    class SPGraphicsContext;
}

using namespace std;
namespace space {
    struct sp_rectangle;
    class SPImage;
class SPColor;
class pixel;
class slice {
public:
    SPImage *image;
    int x1;
    int y1;
    int x2;
    int y2;
    int leftBorder;
    int topBorder;
    int rightBorder;
    int bottomBorder;
    slice(SPImage *image, int x1, int x2, int y1, int y2, int leftBorder, int topBorder, int rightBorder, int bottomBorder);
};
class SPSkin
{
    public:
        map<string, SPImage *> *images;
        map<string, pixel *> *colors;
        map<string, slice *> *slices;
        SPImage *image;
        SPSkin();
        SPSkin(const string& bitmap);
        virtual ~SPSkin();
        bool hasColor(string selector);
        bool hasImage(string selector);
        SPColor getColor(string selector, string def);
        SPImage *getImage(string selector, string def);
        virtual bool drawElement(SPGraphicsContext *gc, SPElement *, const string& state, const sp_rectangle& bounds) {}
        virtual void drawTableRow(SPGraphicsContext* g, SPTableElement* table, int i, int x, int y, int width, int height, int row) {}
        virtual void drawTableHeader(SPGraphicsContext* g, SPTableElement* table, int x, int y, int width, int height) {}
        virtual void drawTabBarTab(SPGraphicsContext* g, SPTabBarElement *tabBar, SPTab *tab, int index, bool active, int x, int y, int width, int height) {}
        virtual void drawTabBar(SPGraphicsContext* g, SPTabBarElement* tabBar, int x, int y, int width, int height) {}
        virtual void drawTreeItem(SPGraphicsContext* g, SPTreeViewElement *treeView, SPTreeItem* item, int itemHeight, int x, int y, int width, int height) {}
};
}
#endif // SKIN_H
