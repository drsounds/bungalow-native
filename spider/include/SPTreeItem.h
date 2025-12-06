#ifndef TREEITEM_H
#define TREEITEM_H
#include "SPUri.h"
#include "SPObject.h"
#include <string>
using namespace std;
namespace spider {
    class SPTreeItem : SPObject {
    protected:
        bool highlighted;
		string title;
		string subtitle;
		SPUri *uri;
		bool selected;
	public:
	    bool isHighlighted() {
            return this->highlighted;
	    }
	    void setHighlighted(bool value) {
            this->highlighted = value;
	    }
	    bool isSelected() {
            return this->selected;
	    }
	    void setSelected(bool selected) {
            this->selected = selected;
	    }
		explicit SPTreeItem(SPUri *uri);
		string getText() {
			return this->title;
		}
		void setText(string value) {
            this->title = value;
		}
		SPUri *getUri() {
            return this->uri;
		}
		~SPTreeItem();

	};
}
#endif // TREEITEM_H
