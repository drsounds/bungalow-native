#ifndef H_SPIDER_WINDOW_ELEMENT
#define H_SPIDER_WINDOW_ELEMENT
#include "SPVBoxElement.h"

#include "SPWindow.h"

#include <string>

using namespace std;

namespace space {
	class Spider;
	class SPSkin;
	struct sp_event;
	class SPGraphicsContext;
	class MainElement;
	class SPWindowElement : public SPVBoxElement, public SPWindow {
	public:
		void draw(SPGraphicsContext *gc, int width, int height);
		explicit SPWindowElement(Spider *, SPSkin *);
		void invalidateRegion(sp_rectangle rect) override {}

		string getType() override
		{
			return "window";
		}
		virtual void navigate(const string& uri);
		void pack() override;
	};
};

#endif
