#include "SPTreeViewElement.h"
#include "SPMouseEventArgs.h"
#include "SPWindowElement.h"

#include "SPTreeItem.h"
#include "SPSkin.h"

#include "SPGraphicsContext.h"

#include <iostream>

#include "SPColor.h"

using namespace std;

namespace space {

void SPTreeViewElement::treeview_mousedown(SPObject *sender, SPEventArgs *e) {
    SPMouseEventArgs *args = (SPMouseEventArgs *)e;
    SPTreeViewElement *treeView = (SPTreeViewElement *)sender;
    int top = 0;
    int y = args->getY() - treeView->getAbsoluteBounds().y;
		for (vector<SPTreeItem *>::iterator it = treeView->m_items->begin(); it != treeView->m_items->end(); ++it) {
		SPTreeItem *item = static_cast<SPTreeItem *>(*it);
		if (y > top && y < top + treeView->getItemHeight()) {
				item->setHighlighted(true);
				TreeViewEventArgs *eventArgs = new TreeViewEventArgs();
				eventArgs->setItem(item);
				treeView->notify(string("itemhighlighted"), treeView, eventArgs);
		} else {
				item->setHighlighted(false);
		}
		top += treeView->getItemHeight();
	}
	SPWindowElement * winElement = treeView->getWindowElement();
	sp_rectangle region;
	region.x = treeView->getAbsoluteBounds().x;
	region.y = treeView->getAbsoluteBounds().y;
	region.z = 0;
	region.width = treeView->getWidth();
	region.height = treeView->getHeight();
	winElement->invalidateRegion(region);
}

void SPTreeViewElement::treeview_mouseup(SPObject *sender, SPEventArgs *e) {
	SPMouseEventArgs *args = (SPMouseEventArgs *)e;
	SPTreeViewElement *treeView = this;
	int top = 0;
	int y = args->getY() - treeView->getAbsoluteBounds().y;
	for (vector<SPTreeItem *>::iterator it = treeView->getItems()->begin(); it != treeView->getItems()->end(); ++it) {
		SPTreeItem *item = static_cast<SPTreeItem *>(*it);
		item->setHighlighted(false);
		if (y > top && y < top + treeView->getItemHeight()) {
			item->setSelected(true);
			// Raise treeview itemselected event
			TreeViewEventArgs *eventArgs = new TreeViewEventArgs();
			eventArgs->setItem(item);
			treeView->notify(string("itemselected"), treeView, eventArgs);
		}
		top += treeView->getItemHeight();
	}
	SPWindowElement * winElement = treeView->getWindowElement();
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
	this->setTagName("treeview");
	this->setParentNode(parent);
	this->m_items = new vector<SPTreeItem *>;
	this->itemHeight = 18;
	this->addEventListener(string("mouseup"), SPCallback(&SPTreeViewElement::treeview_mouseup), this, this);
}

void SPTreeViewElement::addItem(SPTreeItem *item) {
    this->m_items->push_back(item);
}
void SPTreeViewElement::setItemHeight(int height) {
	this->itemHeight = height;

}

int SPTreeViewElement::getItemHeight() {
	return this->itemHeight;

}
#define spacify2009 true

void SPTreeViewElement::paint(int x, int y, int width, int height, SPGraphicsContext *g)
{
	SPColor bgColor = this->getBackgroundColor();
	if (this->getTintColor() != nullptr)
	{
		bgColor = bgColor.tint(*this->getTintColor());
	}
 	if (!this->getSkin()->drawElement(g, this, "", sp_rectangle { x, y, width, height, 0 })) {
		g->fillRectangle(x, y, width, height, bgColor);
	}
	SPColor color = this->getForegroundColor();
	int itemHeight = this->getItemHeight();

	int top = 0;
	for (vector<SPTreeItem *>::iterator it = this->m_items->begin(); it != this->m_items->end(); ++it) {
		SPTreeItem *item = static_cast<SPTreeItem *>(*it);
		this->getSkin()->drawTreeItem(
			g,
			this,
			item,
			itemHeight,
			x,
			y + top,
			this->getWidth(),
			itemHeight
		);
		sp_rectangle strB = g->measureString(item->getText(), fontStyle);
        int ttop = (top + (itemHeight / 2)) - (strB.height / 2);
		g->drawString(item->getText(), this->getFontStyle(), color, 20 + x, y + ttop, this->getWidth(), itemHeight);
		top += itemHeight;
	}

}

}

