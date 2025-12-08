#ifndef ELEMENT_H
#define ELEMENT_H
#include "SPNode.h"
#include "SPObservable.h"
#include "SPFontStyle.h"
#include "SPWindow.h"
#include <vector>

using namespace std;

namespace space {
    class Spider;
    class SPMessage;
    class SPSkin;
    class SPGraphicsContext;
    class SPStylesheet;
    class SPWindowElement;
    class SPImage;
    class SPFontStyle;
    class SPElement : public SPNode, public SPObservable {
    protected:
        SPImage *m_backgroundImage;
        vector<string> *m_classList;
        SPSkin *m_skin;
        bool scrollable;
        bool visible;
        sp_margin *margins;
        sp_margin *padding;
        std::vector<SPObserver *> *observers;
        SPFontStyle fontStyle;
        string id;
        string data;
        SPElement *deepestView;
        int m_width;
        int m_height;
        int x;
        int y;
        int z;
        int scrollX;
        int scrollY;
        bool clipView = false;
        string name;
        space::Spider *m_spider;
        SPGradient *m_gradient;
        bool m_hasDefaultGradient = false;
    public:
        void setSpider(space::Spider *spider) {
            this->m_spider = spider;
        }
        SPGradient *getGradient() const {
            return this->m_gradient;
        }
        void setGradient(SPGradient *value) {
            this->m_gradient = value;
        }
        bool hasDefaultGradient() const
        {
            return m_hasDefaultGradient;
        }
        void setHasDefaultGradient(bool value)
        {
            m_hasDefaultGradient = value;
        }
        space::Spider *getSpider() {
            return this->m_spider;
        }
        SPSkin *getSkin() const;
        SPElement();
        void setSkin(SPSkin *value);
        SPElement *getDeepestView()
        {
            return this->deepestView;
        }
        virtual void resize(int width, int height);
        void scroll(int x, int y);
        void scrollTo(int x, int y);
        void applySkin();
        virtual void scroll(int scrollX, int scrollY, int x, int y);
        void applyColorAttributeFromSkin (string attr, string skin);
        void applyImageAttributeFromSkin (string attr, string skin);
        void generateAndSetDefaultGradient();
        SPGradient* generateDefaultGradient();
        bool hasClass(string _class);
        void addClass(string _class);
        void removeClass(string _class);
        sp_rectangle *absoluteBounds;
        void applyStylesheet(SPStylesheet *style);
        SPColor getBackgroundColor()
        {
            return this->getColorAttribute("bgcolor", SPColor(0, 0, 0, 1));
        }
        SPColor getForegroundColor()
        {
            return this->getColorAttribute("fgcolor", SPColor(255, 255, 255, 1));
        }
        void setName(const string& value) {
            this->name = value;
         }
        string getName() const {
            return name;
        }

        virtual void draw(int x, int y, SPGraphicsContext *c);
        string getType() override;
        virtual void paint(int x, int y, int width, int height, SPGraphicsContext* c);

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
        virtual SPGraphicsContext *createGraphics();
        virtual void show();
        virtual void hide();

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

        explicit SPElement(SPElement *parent);

        explicit SPElement(SPElement *parent, SPWindow *window);

        explicit SPElement(SPWindow *window, SPElement *parent);
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
        virtual void pack();

    };
}

#endif // ELEMENT_H
