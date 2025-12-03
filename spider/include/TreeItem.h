#ifndef TREEITEM_H
#define TREEITEM_H
#include "Uri.h"
#include "SPType.h"
#include <string>
using namespace std;
namespace spider {
#ifdef URI_CLASS
#ifdef SPTYPE_CLASS
#ifndef TREEITEM_CLASS
    class TreeItem : SPType {
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
		TreeItem(Uri *uri);
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
#define TREEITEM_CLASS
#endif
#endif
#endif
}
#endif // TREEITEM_H
