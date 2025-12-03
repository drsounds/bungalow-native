#ifndef TREEVIEWELEMENT_H
#define TREEVIEWELEMENT_H
#include "Uri.h"
#include "Element.h"
#include "EventArgs.h"
#include <string>

using namespace std;

namespace spider {
    class Element;
    class TreeItem;
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
		explicit TreeViewElement(Element *parent);
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
}
#endif // TREEVIEWELEMENT_H
