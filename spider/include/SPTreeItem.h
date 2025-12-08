#ifndef TREEITEM_H
#define TREEITEM_H
#include "SPObject.h"
#include <string>
using namespace std;
namespace space {
	class SPUri;
    class SPTreeItem : SPObject {
    protected:
        bool highlighted;
		string title;
		string subtitle;
		SPUri *uri;
		bool selected;
	public:
	    [[nodiscard]] bool isHighlighted() const
	    {
            return this->highlighted;
	    }
	    void setHighlighted(bool value) {
            this->highlighted = value;
	    }
	    [[nodiscard]] bool isSelected() const
	    {
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
		[[nodiscard]] SPUri *getUri() const
		{
            return this->uri;
		}
		~SPTreeItem() override = default;

	};
}
#endif // TREEITEM_H
