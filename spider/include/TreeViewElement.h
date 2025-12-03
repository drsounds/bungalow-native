#ifndef TREEVIEWELEMENT_H
#define TREEVIEWELEMENT_H
#include "Uri.h"
#include "Element.h"
#include "EventArgs.h"
#include "TreeItem.h"
#include <string>

using namespace std;

namespace spider {
#ifdef GRAPHICSCONTEXT_CLASS
#ifdef ELEMENT_CLASS
#ifdef EVENTARGS_CLASS
#ifdef TREEITEM_CLASS
#ifndef TREEVIEWEVENTARGS_CLASS
    class TreeViewEventArgs : public EventArgs {
    protected:

        TreeItem *item;
    public:

        TreeItem *getItem() {
            return this->item;
        }
        void setItem(TreeItem *item) {
            this->item = item;
        }
    };
    class TreeViewElement : public Element {
	protected:
		vector<TreeItem *> *mItems;
		int itemHeight;
	public:
		TreeViewElement(Element *parent);
        virtual string getType() {
            return "tree";
        }
		void draw(int x, int y, GraphicsContext *g);
        vector<TreeItem *> *items() {
            return this->mItems;
        }
		void setItemHeight(int height);
		int getItemHeight();
        void addItem(TreeItem *item);
	};
#define TREEVIEWELEMENT_CLASS
#endif
#endif
#endif
#endif
#endif
}
#endif // TREEVIEWELEMENT_H
