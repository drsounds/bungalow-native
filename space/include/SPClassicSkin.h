//
// Created by Alexander Forselius on 2025-12-11.
//

#ifndef SPACIFYCLIENT_SPCLASSICSKIN_H
#define SPACIFYCLIENT_SPCLASSICSKIN_H
#include "SPSkin.h"


namespace space
{
    class SPClassicSkin : public SPSkin
    {
        virtual bool drawElement(SPGraphicsContext *gc, SPElement *, const string& state, const sp_rectangle& bounds, SPColor* tintColor, short mode) override;
        void drawTableRow(SPGraphicsContext* g, SPTableElement* table, int i, int x, int y, int width, int height,
                          int row, SPColor *tintColor) override;
        virtual void drawTableHeader(SPGraphicsContext* g, SPTableElement* table, int x, int y, int width, int height, SPColor *tintColor) override;
        virtual void drawTabBarTab(bool active, int x, int y, int width, int _height, const SPColor& sp_color,
                          const SPColor& bg_color, SPGraphicsContext* sp_graphics_context, int mode, SPColor *tintColor) override;
        virtual void drawTabBar(SPGraphicsContext* sp_graphics_context, SPTabBarElement* sp_tab_bar_element, int i, int y, int  , int get_height,
                       const SPColor&, SPGraphicsContext*, int mode, SPColor *tintColor) override
        ;
        virtual void drawTreeItem(SPGraphicsContext* g, int itemHeight, SPTreeViewElement* treeView, SPTreeItem* item, int x, int y, int width, int
                                  height, int mode, SPColor *tintColor) override;
    };
}

#endif //SPACIFYCLIENT_SPCLASSICSKIN_H