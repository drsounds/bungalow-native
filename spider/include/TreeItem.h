#ifndef TREEITEM_H
#define TREEITEM_H
#include "Uri.h"
#include "SPObject.h"
#include <string>
using namespace std;
namespace spider {
    class TreeItem : SPObject {
    protected:
        bool highlighted;
		string title;
		string subtitle;
		Uri *uri;
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
		explicit TreeItem(Uri *uri);
		string getText() {
			return this->title;
		}
		void setText(string value) {
            this->title = value;
		}
		Uri *getUri() {
            return this->uri;
		}
		~TreeItem();

	};
}
#endif // TREEITEM_H
