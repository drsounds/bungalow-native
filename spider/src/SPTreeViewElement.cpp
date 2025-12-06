#include "SPTreeViewElement.h"
#include "SPMouseEventArgs.h"
#include "SPWindowElement.h"

#include "SPTreeItem.h"
#include "SPSkin.h"

#include "SPGraphicsContext.h"

#include "SPColor.h"

namespace spider {

void SPTreeViewElement::treeview_mousedown(SPObject *sender, SPEventArgs *e) {
    SPMouseEventArgs *args = (SPMouseEventArgs *)e;
    SPTreeViewElement *treeView = (SPTreeViewElement *)sender;
    int top = 0;
    int y = args->getY() - treeView->getAbsoluteBounds()->y;
    sp_rectangle *bounds = treeView->getAbsoluteBounds();
	for (vector<SPTreeItem *>::iterator it = treeView->items()->begin(); it != treeView->items()->end(); ++it) {
		SPTreeItem *item = static_cast<SPTreeItem *>(*it);
		if (args->getY() > top + treeView->getY() && args->getY() < top + treeView->getY() + treeView->getItemHeight()) {
            item->setHighlighted(true);

            // Raise treeview itemselected event
            TreeViewEventArgs *eventArgs = new TreeViewEventArgs();
            eventArgs->setItem(item);
            treeView->notify(string("itemhighlighted"), treeView, eventArgs);

		} else {
            item->setHighlighted(false);
		}
		top += treeView->getItemHeight();
	}
	SPWindow * winElement = (SPWindowElement *)treeView->getWindow();
	sp_rectangle region;
	region.x = treeView->getAbsoluteBounds()->x;
	region.y = treeView->getAbsoluteBounds()->y;
	region.z = 0;
	region.width = treeView->getWidth();
	region.height = treeView->getHeight();
	winElement->invalidateRegion(region);
}

void SPTreeViewElement::treeview_mouseup(SPObject *sender, SPEventArgs *e) {
    SPMouseEventArgs *args = (SPMouseEventArgs *)e;
    SPTreeViewElement *treeView = (SPTreeViewElement *)sender;
    int top = 0;
    int y = args->getY() - treeView->getAbsoluteBounds()->y;
    sp_rectangle *bounds = treeView->getAbsoluteBounds();
	for (vector<SPTreeItem *>::iterator it = treeView->items()->begin(); it != treeView->items()->end(); ++it) {
		SPTreeItem *item = static_cast<SPTreeItem *>(*it);
		item->setHighlighted(false);
		if (args->getY() > top + treeView->getY() && args->getY() < top + treeView->getY() + treeView->getItemHeight()) {
            item->setSelected(true);

            // Raise treeview itemselected event
            TreeViewEventArgs *eventArgs = new TreeViewEventArgs();
            eventArgs->setItem(item);
            treeView->notify(string("itemselected"), treeView, eventArgs);

		} else {
            item->setSelected(false);
		}
		top += treeView->getItemHeight();
	}
	SPWindow * winElement = (SPWindow *)treeView->getWindow();
	sp_rectangle region;
	region.x = treeView->getX();
	region.y = treeView->getY();
	region.z = 0;
	region.width = treeView->getWidth();
	region.height = treeView->getHeight();
	winElement->invalidateRegion(region);
}
SPTreeViewElement::SPTreeViewElement(SPElement *parent)
: SPElement(parent) {
	this->setParent(parent);
	this->mItems = new vector<SPTreeItem *>;
	this->itemHeight = 18;
	this->addEventListener(string("mouseup"), SPCallback(&SPTreeViewElement::treeview_mouseup), this);
	this->setWindowElement(nullptr);
}

void SPTreeViewElement::addItem(SPTreeItem *item) {
    this->mItems->push_back(item);
}
void SPTreeViewElement::setItemHeight(int height) {
	this->itemHeight = height;

}

int SPTreeViewElement::getItemHeight() {
	return this->itemHeight;

}
#define spacify2009 true

void SPTreeViewElement::draw(int x, int y, SPGraphicsContext *g) {
    spider::SPElement::draw(x, y, g);
    g->fillRectangle(x, y, this->getWidth(), this->getHeight(), this->getWindow()->getSkin()->getColor("treeview.background.color", ""));

	int itemHeight = this->getItemHeight();

	int top = 0;
	for (vector<SPTreeItem *>::iterator it = this->mItems->begin(); it != this->mItems->end(); ++it) {
		SPTreeItem *item = static_cast<SPTreeItem *>(*it);
		if (item->isSelected()) {
            #if spacify2009
            g->fillRectangle(x, y + top , this->getWidth(), itemHeight, this->getWindow()->getSkin()->getColor("treeitem::selected.background.color", ""));
            #else
            g->fillRectangle(x, y + top, 5, itemHeight, (Color *)this->getAttributeObj("highlight"));
            #endif
		}
		if (item->isHighlighted()) {
            g->fillRectangle(x, y + top , this->getWidth(), itemHeight, this->getWindow()->getSkin()->getColor("treeitem::focus.background.color", ""));
		}
		SPColor color =  this->getWindow()->getSkin()->getColor("treeview.foreground.color", "");
		if(item->isSelected()) {
            if (false)
                color = this->getColorAttribute("highlight", SPColor(0, 0, 255, 1));
            else
                color = this->getWindow()->getSkin()->getColor("treeitem::selected.foreground.color", "");
		}

		sp_rectangle strB = g->measureString(item->getText(), fontStyle);
        int ttop = (top + (itemHeight / 2)) - (strB.height / 2);
		g->drawString(item->getText(), this->getFontStyle(), color, 20 + x, y + ttop, this->getWidth(), itemHeight);

		top += itemHeight;
	}
}

}

