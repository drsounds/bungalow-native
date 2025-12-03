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
		explicit WindowElement(Spider *);
		GraphicsContext *getGraphicsContext() const
		{
			return this->m_spider->getGraphicsContext();
		}
		virtual void invalidateRegion(rectangle rect) {}

		string getType() override
		{
            return "window";
        }
		virtual void navigate(const string& uri);
		void pack() override;
	};
};

#endif
