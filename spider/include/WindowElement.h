#ifndef H_SPIDER_WINDOW_ELEMENT
#define H_SPIDER_WINDOW_ELEMENT
#include "VBoxElement.h"

#include <string>
using namespace std;

namespace spider {
	class GraphicsContext;
	class WindowElement : public VBoxElement {
public:
		void draw(spider::GraphicsContext *gc);
		WindowElement(GraphicsContext *gc);
		GraphicsContext *gc;
		virtual void invalidateRegion(rectangle rect) {}
        virtual string getType() {
            return "window";
        }
        virtual void scrollTo(int x, int y) {}
        virtual void scroll(int x, int y) {}
        spider::Element *deepestView;

	};
};

#endif
