#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H
#include "libspider.h"

#include "Color.h"
#include "FontStyle.h"

namespace spider {  
	class WindowElement;
	class Color;
	class FontStyle;
	class Element;
	class Image;
	class slice;
	class Skin;
    class GraphicsContext {
	protected:
		FontStyle *fontStyle;
		void *window;
	public:
		GraphicsContext(WindowElement *window);
		Skin *skin;
		virtual void drawImagePart(Image *image, int x, int y, int width, int height, int x1, int y1, int x2, int y2) {}
		virtual void drawSkinImage(const string& resourceId, int x, int y, int w, int h) {}
		virtual void restoreOrigo() {}
    	void drawImageSlices(map<string, slice *> *slices, string selector, int left, int top, int width, int height);
		virtual void setClip(const rectangle& rect) {}
		virtual void drawLine(int x, int y, int x2, int y2, Color color) {}
		virtual void drawRectangle(int x, int y, int w, int h, Color color) {}
		virtual void fillRectangle(int x, int y, int w, int h, Color color) {}
		virtual void drawImage(Image *image, int x, int y, int w, int h) {}
		virtual void drawControl(int x, int y, int w, int h, const string& name) { return;}
		virtual void drawString(const string& text, FontStyle fs, Color color, int x, int y, int w, int h) { return; }
		virtual void invalidateRegion(rectangle region) {}
		virtual void drawHTMLText(const string& html, FontStyle fs, Color color, int x, int y, int w, int h) { return; }
		virtual Image *loadImage(const string& bitmap) { return NULL; }
		virtual rectangle measureString(const string& text, FontStyle font) { return rectangle(); }
		virtual void declipRect() { return; }
		void setFontStyle(spider::FontStyle *fs) {
			this->fontStyle = fs;
		}
		FontStyle *getFontStyle() {
			return this->fontStyle;
		}
		virtual void drawControl(const string& control, Element *srcElement, int x, int y, int w, int h) { 	return; }
		virtual void drawInputElement(Element *srcElement, int x, int y, int w, int h) { return; }
		virtual void setOrigo(const int& x, const int& y);
	};

}
#endif // GRAPHICSCONTEXT_H
