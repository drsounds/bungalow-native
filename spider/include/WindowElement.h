#ifndef H_SPIDER_WINDOW_ELEMENT
#define H_SPIDER_WINDOW_ELEMENT
#include "VBoxElement.h"

#include <string>

#include "../../spacify/include/MainElement.h"

using namespace std;

namespace spider {
	class Spider;
	struct sp_event;
	class GraphicsContext;
	class WindowElement : public VBoxElement {
	public:
		void draw(GraphicsContext *gc, int width, int height);
		void processEvent(const sp_event& event);
		WindowElement(Spider *);
		GraphicsContext *getGraphicsContext()
		{
			return this->m_spider->getGraphicsContext();
		}
		virtual void invalidateRegion(rectangle rect) {}
        virtual string getType() {
            return "window";
        }
        virtual void scrollTo(int, int);
        virtual void scroll(int, int);
		virtual void resize(int, int);
		virtual void navigate(string uri);
		virtual void mouseDown(int x, int y);
		virtual void mouseMove(int x, int y);
        Element *deepestView;
		MainElement *mainWindow;
	};
};

#endif
