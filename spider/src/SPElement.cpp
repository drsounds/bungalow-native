#include "SPElement.h"
#include <iostream>
#include <cstdio>
#include <boost/lexical_cast/bad_lexical_cast.hpp>

#include "Spider.h"

#include "SPWindow.h"
#include "SPObservable.h"
#include "SPMouseEventArgs.h"
#include "SPGraphicsContext.h"
#include "SPSkin.h"
#include "SPImage.h"
#include "SPObserver.h"
#include "SPStylesheet.h"
#include "SPFontStyle.h"

namespace spider {
	SPSkin *SPElement::getSkin() const
	{
		if (this->m_skin)
		{
			return this->m_skin;
		}
		if (this->getWindow() != nullptr)
		{
			return this->getWindow()->getSkin();
		}
		return nullptr;
	}

	SPElement::SPElement() : SPNode(), fontStyle(SPFontStyle("Tahoma", 13, 1, false, false))
	{
	}

	SPGraphicsContext* SPElement::createGraphics()
	{
		return this->getSpider()->getGraphicsContext();
	}

	void SPElement::show() {
	    this->setVisible(true);
	}
	void SPElement::hide() {
	    this->setVisible(false);
	}
	void SPElement::mouseClick(int mouseButton, int x, int y) {

	}

	void SPElement::click(int mouseButton, int x, int y) {
		int xx = this->getAbsoluteBounds() != NULL ? x - this->getAbsoluteBounds()->y : x;
	    int yy = this->getAbsoluteBounds() != NULL ? y - this->getAbsoluteBounds()->y : y;
		SPMouseEventArgs *me = new SPMouseEventArgs(mouseButton, xx, yy);

		this->notify(string("click"), this, me);
		for(vector<SPNode *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
			SPElement *elm = static_cast<SPElement *>(*it);

			if (elm->getAbsoluteBounds() != NULL)
			if(x > elm->getAbsoluteBounds()->x && x < elm->getAbsoluteBounds()->x + elm->getAbsoluteBounds()->width &&
				y > elm->getAbsoluteBounds()->y && y < elm->getAbsoluteBounds()->y + elm->getAbsoluteBounds()->height) {

				elm->click(mouseButton, x , y);
			}
		}
	}


	void SPElement::mouseDown(int mouseButton, int x, int y) {
		int xx = this->getAbsoluteBounds() != NULL ? x - this->getAbsoluteBounds()->y : x;
	    int yy = this->getAbsoluteBounds() != NULL ? y - this->getAbsoluteBounds()->y : y;
		SPMouseEventArgs *me = new SPMouseEventArgs(mouseButton, xx, yy);

		this->notify(string("mousedown"), this, me);
		for(vector<SPNode *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
			SPElement *elm = static_cast<SPElement *>(*it);
	        if (elm->getAbsoluteBounds() != NULL)
			if(x > elm->getAbsoluteBounds()->x && x < elm->getAbsoluteBounds()->x + elm->getAbsoluteBounds()->width &&
				y > elm->getAbsoluteBounds()->y && y < elm->getAbsoluteBounds()->y + elm->getAbsoluteBounds()->height) {

				elm->mouseDown(mouseButton, x, y);
			}
		}
	}
	void SPElement::mouseUp(int mouseButton, int x, int y) {
		int xx = this->getAbsoluteBounds() != NULL ? x - this->getAbsoluteBounds()->y : x;
	    int yy = this->getAbsoluteBounds() != NULL ? y - this->getAbsoluteBounds()->y : y;
		SPMouseEventArgs *me = new SPMouseEventArgs(mouseButton, xx, yy);

		this->notify(string("mouseup"), this, me);
		for(vector<SPNode *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
			SPElement *elm = static_cast<SPElement *>(*it);
	        if (elm->getAbsoluteBounds() != NULL)
			if(x > elm->getAbsoluteBounds()->x && x < elm->getAbsoluteBounds()->x + elm->getAbsoluteBounds()->width &&
				y > elm->getAbsoluteBounds()->y && y < elm->getAbsoluteBounds()->y + elm->getAbsoluteBounds()->height) {

				elm->mouseUp(mouseButton, x, y);
			}
		}
	}
	void SPElement::addClass(string value) {
	    this->m_classList->push_back(value);
	}

	bool SPElement::hasClass(string value) {
	   return  std::find(this->m_classList->begin(), this->m_classList->end(), value) != this->m_classList->end();
	}

	void SPElement::removeClass(string value) {
	    this->m_classList->erase(std::find(this->m_classList->begin(), this->m_classList->end(), value), this->m_classList->end());
	}

	SPFontStyle SPElement::getFontStyle() {
	    return this->fontStyle;
	}
	void SPElement::applyStylesheet(SPStylesheet *style) {

	}

	void SPElement::applyColorAttributeFromSkin (string attr, string prop) {
	    cout << prop << "\r\n";
	    cout << this->m_skin->colors << "\r\n";
	    cout << attr << "\r\n";
	    if (this->m_skin->colors->find(prop) != this->m_skin->colors->end()) {
	        pixel *color = (*this->m_skin->colors)[prop];

	        this->set(attr, spider_pixel_to_hex(color));
	    }
	}

	void SPElement::applyImageAttributeFromSkin (string attr, string prop) {
	    cout << attr << "\r\n";
	    cout << m_skin << "\r\n";
	    cout << this->m_skin->colors << "\r\n";
	    cout << attr << "\r\n";
	    if (this->m_skin->images->find(prop) != this->m_skin->images->end()) {
	        SPImage *img = (*this->m_skin->images)[prop];

	        this->setObject(attr, (void *)img);
	    }
	}

	SPElement::SPElement(Spider *spider, SPWindow *window, SPElement *parent) : SPNode(static_cast<SPNode*>(parent)), fontStyle("Tahoma", 13, 1, false, false) {
	    this->m_classList = new vector<string>;
	    this->absoluteBounds = NULL;
		this->setScrollable(false);
		this->m_spider = spider;
		if (window == nullptr) {
			this->setWindow(parent->getWindow());	
		}
		if (window != nullptr) {
			this->m_skin = window->getSkin();
		}
		if (parent != nullptr) {
			this->m_skin = parent->getSkin();
		}
		this->visible = true;
		this->scrollX = 0;
		this->scrollY = 0;
	    this->data = "";
		this->observers = new vector<SPObserver *>();
		this->m_window = window;
		this->setParent(parent);

	    #if false
	    this->set("fgcolor", new string("#ffffff"));
	    this->set("bgcolor", new string("#000000"));
	    this->set("font", new string("MS Sans Serif"));
	    this->set("highlight", "#a9d9fe");
	    this->set("size", new string("11"));
	    #endif

	    this->applyColorAttributeFromSkin(string("bgcolor"), string("body.background.color"));
	    this->applyColorAttributeFromSkin(string("fgcolor"), string("body.foreground.color"));

	    string type = string(this->getType());

	    this->applyColorAttributeFromSkin(string("bgcolor"), string(this->getType()) + "body.background.color");
	    this->applyColorAttributeFromSkin(string("fgcolor"), string(this->getType()) + "body.foreground.color");
	    if (this->m_skin->hasImage(this->SPElement::getType() + ".background.image")) {
	        this->m_backgroundImage = this->m_skin->getImage(string(this->getType()) + ".background.image", "");
	    }
		if (this->getParent() != NULL) {
	        #if false
	        this->set("bgcolor", new string(this->getParent()->get("bgcolor")));
	        this->set("fgcolor", new string(this->getParent()->get("fgcolor")));
	        this->set("font", new string(this->getParent()->get("font")));
	        this->set("highlight", new string(this->getParent()->get("highlight")));
	        this->set("size", new string(this->getParent()->get("size")));
	        #endif
	        this->fontStyle = parent->fontStyle;
	        this->m_window = parent->getWindow();
		}
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->m_width = 0;
		this->m_height = 0;
		this->margins = new sp_margin();
		this->margins->left = 0;
		this->margins->top = 0;
		this->margins->right = 0;
		this->margins->bottom = 0;
		this->padding = new sp_margin();
		this->padding->left = 0;
		this->padding->top = 0;
		this->padding->right = 0;
		this->padding->bottom = 0;

	}

	void SPElement::setBackgroundImage(SPImage* value)
	{
		this->m_backgroundImage = value;
	}

	void SPElement::invalidate() const
	{
	    auto *rect = this->getAbsoluteBounds();
	    if (rect == nullptr)
	        return;
	    auto *we = this->getWindow();
	    we->invalidateRegion(*rect);
	}
	sp_margin *SPElement::getMargins() {
		return this->margins;
	}
	sp_margin *SPElement::getPadding() {
		return this->padding;
	}
	SPElement::~SPElement() {

	}
	int SPElement::getHeight() {
		return this->m_height;
	};
	int SPElement::getWidth() {
		return this->m_width;
	}
	int SPElement::getX() {
		return this->x;
	}

	void SPElement::processEvent(const SPEvent& event)
	{
		if (event.type == "mousedown")
		{
			auto *mouseEventArgs = dynamic_cast<SPMouseEventArgs *>(event.args);
			if (mouseEventArgs != nullptr)
			{
				if (mouseEventArgs->getX() > this->getAbsoluteBounds()->x && mouseEventArgs->getX() < this->getAbsoluteBounds()->y + this->getWidth() &&
					mouseEventArgs->getY() >this->getAbsoluteBounds()->y && mouseEventArgs->getY() < this->getAbsoluteBounds()->y + this->getHeight())
				{
					this->dispatchEvent("mousedown", mouseEventArgs, this);
				}

			}
		}
		if (event.type == "mouseup")
		{
			auto *mouseEventArgs = dynamic_cast<SPMouseEventArgs *>(event.args);
			if (mouseEventArgs != nullptr)
			{
				if (mouseEventArgs->getX() > this->getAbsoluteBounds()->x && mouseEventArgs->getX() < this->getAbsoluteBounds()->y + this->getWidth() &&
					mouseEventArgs->getY() >this->getAbsoluteBounds()->y && mouseEventArgs->getY() < this->getAbsoluteBounds()->y + this->getHeight())
				{
					this->dispatchEvent("mouseup", mouseEventArgs, this);
				}

			}
		}
		if (event.type == "mousemove")
		{
			auto *mouseEventArgs = dynamic_cast<SPMouseEventArgs *>(event.args);
			if (mouseEventArgs != nullptr)
			{
				if (mouseEventArgs->getX() > this->getX() && mouseEventArgs->getX() < this->getX() + this->getWidth() &&
					mouseEventArgs->getY() > this->getY() && mouseEventArgs->getY() < this->getY() + this->getHeight())
				{
					this->dispatchEvent("mousemove", mouseEventArgs, this);
				}
			}
		}
		for (auto & it : *this->children)
		{
			auto *elm = dynamic_cast<SPElement *>(it);
			elm->processEvent(event);
		}
	}

	void SPElement::processMessage(const SPMessage& message)
	{
		for (auto & it : *this->children)
		{
			auto *elm = dynamic_cast<SPElement *>(it);

			elm->processMessage(message);
		}
	}

	int SPElement::getY() {
		return this->y;
	}
	int SPElement::getZ() {
		return this->z;
	}
	void SPElement::setWidth(int w) {
		this->m_width = w;
	}
	void SPElement::setHeight(int h) {
		this->m_height = h;

	}
	void SPElement::setX(int x) {
		this->x = x;
	}
	void SPElement::setY(int y) {
		this->y = y;
	}
	void SPElement::setZ(int z) {
		this->z = z;
	}

	void SPElement::set(const std::string& title, const std::string& val) {
	    int n = 0;
	        (*this->getStringAttributes())[title] = val;
	    try {
	        n = stoi(val);
	        this->setIntegerAttribute(title, n);
	    } catch (const boost::bad_lexical_cast e) {
	    } catch (const std::invalid_argument e)
	    {

	    }

	    if(val.find("#") == 0) {
	        SPColor c = SPColor(val);
	        this->setColorAttribute(title, c);
	    }
	}

	void SPElement::setId(std::string id) {
		this->id = id;
	}
	std::string SPElement::getId() {
		return this->id;
	}


	std::string SPElement::getType() {
	    return "element";
	}

	void SPElement::draw(int x, int y, SPGraphicsContext *c) {
	    if (!this->isVisible()) {
	        return;
	    }

		sp_position pos;
		std::vector<SPNode *> *children = this->getChildNodes();
		x += this->getX() ;
		y += this->getY();
		if (this->absoluteBounds == NULL)
	    this->absoluteBounds = new sp_rectangle;

	    this->absoluteBounds->x = x + this->getMargins()->left;
	    this->absoluteBounds->y = y + this->getMargins()->bottom;
	    this->absoluteBounds->width = this->getWidth() - this->getMargins()->left + this->getMargins()->right;
	    this->absoluteBounds->height = this->getHeight() - this->getMargins()->top + this->getMargins()->bottom;

		int width =  this->getWidth();
		int height = this->getHeight();

		sp_rectangle rect2;
		rect2.x = 0;
		rect2.y = 0;
		rect2.width = width;
		rect2.height = height;
		if (this->clipView) {
	        c->setClip(*absoluteBounds);
		}
	    SPColor bgColor = this->getColorAttribute("bgcolor", SPColor(0, 0, 0, 1));
	    SPColor fgColor = this->getColorAttribute("fgcolor", SPColor(255, 255, 255, 1));
	    int fontSize = this->getIntegerAttribute("size", 12);
	    string fontFamily = this->getStringAttribute("font", "MS Sans Serif");
	    c->fillRectangle(x, y, width, height, bgColor);
	    string sel = "";
	    sel.append(this->getType());
	    sel.append(".background.image");
	    c->drawImageSlices(this->m_skin->slices, sel, x, y, width, height);

	    // Draw background image
	    if (this->getId() != "" && this->getId().length() > 0) {
	        string sel2 = "#";
	        sel2.append(this->getId());
	        sel2.append(".background.image");
	        c->drawImageSlices(this->m_skin->slices, sel2, x, y, width, height);
	       // c->drawImage(this->backgroundImage,  x - scrollX, y - scrollY, width, height);
	    }
		//c->drawRectangle(x, y, this->getWidth(), this->getHeight(), (Color *)this->getAttributeObj("bgcolor"));
		SPColor color(255, 0, 0, 255);
	    //c->drawRectangle(0, 0, this->getWidth(), this->getHeight() , &color);
	    string text = this->getInnerText();
	    // draw text
	    if (!text.empty())
	        c->drawString(this->getInnerText(), SPFontStyle(fontFamily, fontSize, fontSize / 2, false, false), fgColor, x - scrollX, y - scrollY, this->getWidth(), this->getHeight());

		// adjust for scroll
	    x -= this->scrollX;
	    y -= this->scrollY;
		for(std::vector<SPNode *>::iterator it = children->begin(); it != children->end(); ++it) {
			SPElement *elm = static_cast<SPElement *>(*it);
			if(elm != NULL) {
				elm->draw(x + this->getPadding()->left - scrollX, y  + this->getPadding()->top - scrollY, c);
			}
		}
		sp_rectangle rect;
		rect.x = x;
		rect.y = y;
		rect.width = width;
		rect.height = height;

		x += this->scrollX;
	    y += this->scrollY;
		x -= this->getX();
		y -= this->getY();
		//c->setOrigo(-x - getX(), -y - getY());
		if (clipView) {
	        c->declipRect();
		}
	}

	void SPElement::resize(int width, int height)
	{
		this->m_width = width;
		this->m_height = height;
		this->invalidate();
		this->pack();
	}

	void SPElement::scroll(int scrollX, int scrollY, int x, int y) {
	    int xx = this->getAbsoluteBounds() != NULL ? x - this->getAbsoluteBounds()->y : x;
	    int yy = this->getAbsoluteBounds() != NULL ? y - this->getAbsoluteBounds()->y : y;
	    cout << "Current scrolling element is " << this->getType() << endl;
	    bool foundElement = false;
	    if (this->clipView) {
	        this->getWindow()->setDeepestElement(this);
	    }
	    if (string(this->getType()) == string("toplistview")) {
	        cout << "Test" << endl;
	    }
		for(vector<SPNode *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
	        if ((this->getWindow())->getDeepestElement() == NULL) {
	            break;
	        }
			SPElement *elm = static_cast<SPElement *>(*it);
			string type = elm->getType();
			cout << type << endl;
	        if (elm->isVisible()) {
	            if (elm->getAbsoluteBounds() != NULL) {

	                if(x > elm->getAbsoluteBounds()->x && x < elm->getAbsoluteBounds()->x + elm->getAbsoluteBounds()->width &&
	                    y > elm->getAbsoluteBounds()->y && y < elm->getAbsoluteBounds()->y + elm->getAbsoluteBounds()->height) {
	                    foundElement = true;
	                    cout << elm->getType() << endl;
	                    elm->scroll(scrollX, scrollY, x, y);

	                }
	                else {

	                }
	            } else {
	            }
	        }

		}


	}

	void SPElement::scroll(int x, int y) {
	    if (this->clipView) {
	        this->scrollX += x;
	        this->scrollY += y;
	        if (scrollY < 0) {
	            scrollY = 0;
	        }
	        this->invalidate();
	    }
	}

	void SPElement::scrollTo(int x, int y) {
	    if (this->clipView) {
	        this->scrollX = x;
	        this->scrollY = y;

	        if (scrollY < 0) {
	            scrollY = 0;
	        }
	        this->invalidate();

	    }

	}

	string SPElement::getInnerText() {
	    return this->data;
	}
	void SPElement::setInnerText(string value) {
		 this->data = value;
	}
}


