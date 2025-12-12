#ifndef ELEMENT_H
#define ELEMENT_H

#define SP_COLOR_SCHEME_DEFAULT 0
#define SP_COLOR_SCHEME_DARK 1
#define SP_COLOR_SCHEME_LIGHT 2

#include "SPNode.h"
#include "SPObservable.h"
#include "SPFontStyle.h"
#include "SPWindow.h"
#include <vector>

using namespace std;

namespace space {
    class Space;
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
        short m_colorScheme = 0;
        sp_margin *margins;
        sp_margin *padding;
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
        Space *m_space;
        SPGradient *m_gradient;
        bool m_hasDefaultGradient = false;
        SPColor* m_tintColor;
        SPColor* m_activeColor;
    public:
        SPElement *getParentElement()
        {
            return (SPElement *)this->getParent();
        }

        void setSpace(Space *space) {
            this->m_space = space;
        }
        short getColorScheme();
        void setColorScheme(short value);
        SPGradient *getGradient() const {
            return this->m_gradient;
        }
        void setGradient(SPGradient *value) {
            this->m_gradient = value;
        }
        SPColor* getActiveColor();
        void setActiveColor(SPColor* value);
        SPColor *getTintColor();
        void setTintColor(SPColor *value);
        SPColor getColorAttribute(const string& title, SPColor defaultValue) override;
        void notify(const string& event, SPObject* sender, SPEventArgs* data) override;
        bool hasDefaultGradient() const
        {
            return m_hasDefaultGradient;
        }
        void setHasDefaultGradient(bool value)
        {
            m_hasDefaultGradient = value;
        }
        space::Space *getSpace() {
            if (this->m_space == nullptr)
            {
                if (this->getWindow() != nullptr)
                {
                    if (this->getWindow()->getSpace() != nullptr)
                    {
                        return this->getWindow()->getSpace();
                    }
                }
                if (this->getParent() != nullptr) {
                    return this->getParent()->getSpace();
                }
            }
            return this->m_space;
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
    	SPColor getBackgroundColor();
    	void setBorderColor(const SPColor& value)
    	{
    		this->setColorAttribute("border-color", value);
    	}
    	SPColor getBorderColor() {
    		return this->getColorAttribute("border-color", SPColor(0, 0, 0, 0));
    	}
        void setBackgroundColor(const SPColor& value)
        {
            this->setColorAttribute("bgcolor", value);
        }
        SPColor getForegroundColor();
        void setForegroundColor(const SPColor& value)
        {
            this->setColorAttribute("fgcolor", value);
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
        virtual void mouseDown(SPObject sender, SPEventArgs* e);
        virtual void click(int, int, int);
        virtual void mouseUp(SPObject sender, SPEventArgs* e);
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
