#ifndef ELEMENT_H
#define ELEMENT_H
#include "Node.h"
#include "Observable.h"
#include "WindowElement.h"
#include "FontStyle.h"
#include <vector>

#include "Spider.h"

using namespace std;

namespace spider {
    class Spider;
    class SPMessage;
    class Skin;
    class GraphicsContext;
    class Stylesheet;
    class WindowElement;
    class Image;
    class FontStyle;
    class Element : public Node, public Observable {
    protected:
        Image *m_backgroundImage;
        vector<string> *m_classList;
        Skin *m_skin;
    public:
        Skin *getSkin() const
        {
            if (this->m_skin)
            {
                return this->m_skin;
            }
            if (this->getWindowElement() == nullptr)
            {
                return this->getWindowElement()->getSkin();
            }
        }

        void scroll(int x, int y);
        void scrollTo(int x, int y);
        virtual void scroll(int scrollX, int scrollY, int x, int y);
        void applyColorAttributeFromSkin (string attr, string skin);
        void applyImageAttributeFromSkin (string attr, string skin);
        bool hasClass(string _class);
        void addClass(string _class);
        void removeClass(string _class);
        rectangle *absoluteBounds;
        void applyStylesheet(Stylesheet *style);
        int width;
        int height;
        int x;
        int y;
        int z;
        int scrollX;
        int scrollY;
        bool clipView = false;
        string name;
        void setName(const string& value) {
            this->name = value;
         }
        string getName() const {
            return name;
        }

        bool scrollable;
        bool visible;
        margin *margins;
        margin *padding;
        std::vector<Observer *> *observers;
        FontStyle fontStyle = FontStyle("Tahoma", 13, 1, false, false);;
        string id;
        string data;
        WindowElement *windowElement;
        virtual void draw(int x, int y, GraphicsContext *c);
        string getType() override;
        rectangle *getAbsoluteBounds() const
        {
            return this->absoluteBounds;
        }
        void invalidate() const;
        void setAbsoluteBounds(rectangle *value) {
            this->absoluteBounds = value;
        }
        bool isVisible() const
        {
            return this->visible;
        }
        WindowElement *getWindowElement() const
        {
             return this->windowElement;
        }
        virtual GraphicsContext *createGraphics()
        {
            return this->getSpider()->getGraphicsContext();
        }
        void setWindowElement(WindowElement *value) {
            this->windowElement = value;
        }
        virtual void setVisible(bool value) {
            this->visible = value;
           // ((Element *)this->getParent())->pack();
        }
        bool isScrollable() const
        {
            return this->scrollable;
        }
        void setScrollable(bool value) {
            this->scrollable = value;
        }
        int getScrollX() const
        {
            return this->scrollX;
        }
        int getScrollY() const
        {
            return this->scrollY;
        }
        void setScrollX(int value) {
            this->scrollX = value;
        }
        void setScrollY(int value) {
            this->scrollY = value;
        }
        FontStyle getFontStyle();
        void setFontStyle(const FontStyle& value)  {
            this->fontStyle = value;
        }

        explicit Element(Element *parent) : Element(parent->getSpider(), parent->getWindowElement(), parent) {}

        explicit Element(Spider *spider, WindowElement *window, Element *parent);
        ~Element() override;
        int getX();
        void processEvent(const SPEvent& event);
        virtual void processMessage(const SPMessage&);
        margin *getMargins();
        margin *getPadding();
        string getInnerText();
        void setInnerText(string data);
        virtual void mouseMove(int, int) {}
        virtual void mouseClick(int, int, int);
        virtual void mouseDown(int, int, int);
        virtual void click(int, int, int);
        virtual void mouseUp(int, int, int);
        int getY();
        int getWidth();
        int getHeight();
        int getZ();
        void setX(int x);
        void setY(int y);
        void setWidth(int width);
        void setHeight(int height);
        void setZ(int z);
        void set(const std::string& title, const std::string& val) override;
        string getId();
        void setId(string id);
        virtual void pack() {}

    };
}

#endif // ELEMENT_H
