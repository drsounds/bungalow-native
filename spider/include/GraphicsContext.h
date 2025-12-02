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
        virtual void drawSkinImage(const string& resourceId, int x, int y, int w, int h) {}
        virtual void restoreOrigo() {}
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
	#define GRAPHICSCONTEXT_CLASS
}
#endif // GRAPHICSCONTEXT_H
