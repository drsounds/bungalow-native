#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H
#include "FontStyle.h"
#include "libspider.h"
#include "Color.h"
#include "Element.h"
#include "Image.h"
#include "Skin.h"
namespace spider {
    class Element;
    class WindowElement;
    class GraphicsContext {
	protected:
		FontStyle *fontStyle;
        WindowElement *window;
	public:
        GraphicsContext(WindowElement *window);
        Skin *skin;
        virtual void drawImagePart(Image *image, int x, int y, int width, int height, int x1, int y1, int x2, int y2) {}
        virtual void drawSkinImage(string resourceId, int x, int y, int w, int h) {}
        virtual void restoreOrigo() {}
        virtual void setClip(rectangle rect) {}
		virtual void drawLine(int x, int y, int x2, int y2, Color *color) {}
		virtual void drawRectangle(int x, int y, int w, int h, Color *color) {}
		virtual void fillRectangle(int x, int y, int w, int h, Color *color) {}
		virtual void drawImage(Image *image, int x, int y, int w, int h) {}
		virtual void drawControl(int x, int y, int w, int h, string name) { return;}
		virtual void drawString(string text, FontStyle *fs, Color *color, int x, int y, int w, int h) { return; }
		virtual void invalidateRegion(rectangle region) {}
		virtual void drawHTMLText(string html, FontStyle *fs, Color *color, int x, int y, int w, int h) { return; }
		virtual Image *loadImage(const string& bitmap) {}
		virtual rectangle measureString(string text, spider::FontStyle *font) { return; }
		virtual void declipRect() { return; }
		void setFontStyle(spider::FontStyle *fs) {
			this->fontStyle = fs;
		}
		FontStyle *getFontStyle() {
			return this->fontStyle;
		}
        virtual void drawControl(string control, Element *srcElement, int x, int y, int w, int h) { 	return; }
        virtual void drawInputElement(Element *srcElement, int x, int y, int w, int h) { return; }
		virtual void setOrigo(const int& x, const int& y);
	};
}
#endif // GRAPHICSCONTEXT_H
