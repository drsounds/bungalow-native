#ifndef ELEMENT_H
#define ELEMENT_H
#include "SPNode.h"
#include "SPObservable.h"
#include "SPFontStyle.h"
#include <vector>

using namespace std;

namespace spider {
    class Spider;
    class SPMessage;
    class Skin;
    class SPGraphicsContext;
    class SPStylesheet;
    class SPWindowElement;
    class SPImage;
    class SPFontStyle;
    class SPElement : public SPNode, public SPObservable {
    protected:
        SPImage *m_backgroundImage;
        vector<string> *m_classList;
        Skin *m_skin;
        bool scrollable;
        bool visible;
        sp_margin *margins;
        sp_margin *padding;
        std::vector<SPObserver *> *observers;
        SPFontStyle fontStyle;
        string id;
        string data;
        SPWindowElement *m_windowElement;
        int width;
        int height;
        int x;
        int y;
        int z;
        int scrollX;
        int scrollY;
        bool clipView = false;
        string name;
    public:
        Skin *getSkin() const;
        SPElement();
        void scroll(int x, int y);
        void scrollTo(int x, int y);
        virtual void scroll(int scrollX, int scrollY, int x, int y);
        void applyColorAttributeFromSkin (string attr, string skin);
        void applyImageAttributeFromSkin (string attr, string skin);
        bool hasClass(string _class);
        void addClass(string _class);
        void removeClass(string _class);
        sp_rectangle *absoluteBounds;
        SPWindowElement *geWindowElement() const
        {
            return this->m_windowElement;
        }
        void applyStylesheet(SPStylesheet *style);
        void setName(const string& value) {
            this->name = value;
         }
        string getName() const {
            return name;
        }

        virtual void draw(int x, int y, SPGraphicsContext *c);
        string getType() override;
        sp_rectangle *getAbsoluteBounds() const
        {
            return this->absoluteBounds;
        }
        void setBackgroundImage(SPImage *value);
        void invalidate() const;
        void setAbsoluteBounds(sp_rectangle *value) {
            this->absoluteBounds = value;
        }
        bool isVisible() const
        {
            return this->visible;
        }
        SPWindowElement *getWindowElement() const
        {
             return this->m_windowElement;
        }
        virtual SPGraphicsContext *createGraphics();
        virtual void show();
        virtual void hide();

        void setWindowElement(SPWindowElement *value) {
            this->m_windowElement = value;
        }
        virtual void setVisible(bool value) {
            this->visible = value;
           // ((Element *)this->getParent())->pack();
        }
        bool isScrollable() const
        {
            return this->scrollable;
        }
        void setScrollable(const bool value) {
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
        SPFontStyle getFontStyle();
        void setFontStyle(const SPFontStyle& value)  {
            this->fontStyle = value;
        }

        explicit SPElement(SPElement *parent) : SPElement(parent->getSpider(), parent->getWindowElement(), parent) {}

        explicit SPElement(Spider *spider, SPWindowElement *window, SPElement *parent);
        ~SPElement() override;
        int getX();
        void processEvent(const SPEvent& event);
        virtual void processMessage(const SPMessage&);
        sp_margin *getMargins();
        sp_margin *getPadding();
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
