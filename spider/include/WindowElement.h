#ifndef H_SPIDER_WINDOW_ELEMENT
#define H_SPIDER_WINDOW_ELEMENT
#include "VBoxElement.h"

#include <string>
using namespace std;

namespace spider {
	class GraphicsContext;
	class WindowElement : public VBoxElement {
public:
		void draw(spider::GraphicsContext *gs);
		WindowElement();
		virtual spider::GraphicsContext *createGraphics();
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
