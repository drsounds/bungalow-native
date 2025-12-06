#ifndef H_SPIDER_WINDOW_ELEMENT
#define H_SPIDER_WINDOW_ELEMENT
#include "SPVBoxElement.h"

#include <string>

using namespace std;

namespace spider {
	class Spider;
	struct sp_event;
	class SPGraphicsContext;
	class MainElement;
	class SPWindowElement : public SPVBoxElement {
	public:
		void draw(SPGraphicsContext *gc, int width, int height);
		explicit SPWindowElement(Spider *);
		virtual void invalidateRegion(sp_rectangle rect) {}

		string getType() override
		{
            return "window";
        }
		virtual void navigate(const string& uri);
		void pack() override;
	};
};

#endif
