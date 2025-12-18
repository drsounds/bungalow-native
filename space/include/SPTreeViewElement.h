#ifndef TREEVIEWELEMENT_H
#define TREEVIEWELEMENT_H
#include "SPUri.h"
#include "SPElement.h"
#include "SPEventArgs.h"
#include <string>

using namespace std;

namespace space {
    class SPElement;
    class SPTreeItem;
    class TreeViewEventArgs : public SPEventArgs {
    protected:

        SPTreeItem *item;
    public:

        SPTreeItem *getItem() {
            return this->item;
        }
        void setItem(SPTreeItem *item) {
            this->item = item;
        }
    };
    class SPTreeViewElement : public SPElement {
	protected:
		vector<SPTreeItem *> *m_items;
		int itemHeight;
	public:
        void treeview_mousedown(SPObject* sender, SPEventArgs* e);
        void treeview_mouseup(SPObject* sender, SPEventArgs* e);
        explicit SPTreeViewElement(SPElement *parent);
        virtual string getType() override {
            return "treeview";
        }
    	vector<SPTreeItem *> *getItems() const {
	        return m_items;
        }
		void paint(int x, int y, int width, int height, SPGraphicsContext *g) override;
		void setItemHeight(int height);
		int getItemHeight();
        void addItem(SPTreeItem *item);
	};
}
#endif // TREEVIEWELEMENT_H
