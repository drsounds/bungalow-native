#include "SPElement.h"

#include "SPButtonElement.h"

#include <iostream>
#include <cstdio>
#include <boost/lexical_cast/bad_lexical_cast.hpp>
#include <utility>

#include "Space.h"

#include "wx/xml/xml.h"

#include "SPWindow.h"
#include "SPObservable.h"
#include "SPMouseEventArgs.h"
#include "SPGraphicsContext.h"
#include "SPSkin.h"
#include "SPImage.h"
#include "SPStylesheet.h"
#include "SPFontStyle.h"
#include "SPImageElement.h"
#include "SPTextElement.h"

#include <boost/json.hpp>

namespace space {
	SPColor* SPElement::getActiveColor()
	{
		SPColor* ret = nullptr;

		if (SPColor* activeColor = this->m_tintColor; activeColor != nullptr)
		{
			ret = activeColor;
		}
		else
		{
			if (this->m_window != nullptr && this->getType() != "window")
			{
				ret = dynamic_cast<SPElement*>(this->getWindow())->getActiveColor();
			}
			if (activeColor == nullptr)
			{
				if (this->m_parent != nullptr && this->getType() != "window")
				{
					ret = this->getParentElement()->getActiveColor();
				}
			}
		}
		return ret;
	}

	void SPElement::setActiveColor(SPColor* value)
	{
		this->m_activeColor = value;
	}

	SPColor* SPElement::getTintColor()
	{
		SPColor* ret = nullptr;

		if (SPColor* tintColor = this->m_tintColor; tintColor != nullptr)
		{
			ret = tintColor;
		}
		else
		{
			if (this->m_window != nullptr && this->getType() != "window")
			{
				ret = dynamic_cast<SPElement*>(this->getWindow())->getTintColor();
			}
			if (tintColor == nullptr)
			{
				if (this->m_parent != nullptr && this->getType() != "window")
				{
					ret = this->getParentElement()->getTintColor();
				}
			}
		}
		return ret;
	}

	void SPElement::setTintColor(SPColor* value)
	{
		this->m_tintColor = value;
	}

	SPColor SPElement::getColorAttribute(const string& title, SPColor defaultValue)
	{
		SPColor color = this->SPNode::getColorAttribute(title, std::move(defaultValue));
		return color;
	}

	void SPElement::notify(const string &event, SPObject *sender, SPEventArgs *data) {
		SPNode::notify(event, sender, data);
		for (auto *child: *this->children) {
			if (data->getType() == "SPMouseEventArgs") {
				auto *mouseEventArgs = dynamic_cast<SPMouseEventArgs *>(data);
				auto element = dynamic_cast<SPElement *>(child);
				if (child != nullptr) {
					if (
						element->getAbsoluteBounds() != nullptr &&
						mouseEventArgs->getX() > element->getAbsoluteBounds()->x &&
						mouseEventArgs->getX() < element->getAbsoluteBounds()->x + element->getAbsoluteBounds()->width &&
						mouseEventArgs->getY() > element->getAbsoluteBounds()->y &&
						mouseEventArgs->getY() < element->getAbsoluteBounds()->y + element->getAbsoluteBounds()->height
					)
					{
						element->setState(SP_STATE_NORMAL);
						if (event == "mousemove") {
							element->setState(SP_STATE_HOVER);
						}
						if (event == "mousedown")
						{
							if (element->getType() == "tabbar")
							{
								cout << "Element: " << this->getType() << "#" << this->getId() << " notified child: " << element->getType() << "#" << element->getId() << " event: " << event << endl;
							}
							element->setState(SP_STATE_ACTIVE);
							element->mouseDown((SPNode *)element, data);
						}
						element->notify(event, sender, data);
						cout << "Element: " << this->getType() << "#" << this->getId() << " notified child: " << element->getType() << "#" << element->getId() << " event: " << event << endl;
					}
				}
			}
		}
	}

	SPSkin *SPElement::getSkin()
	{
		if (this->m_skin)
		{
			return this->m_skin;
		}
		if (this->getParentElement() != nullptr) {
			SPSkin *skin = this->getParentElement()->getSkin();
			if (skin != nullptr) {
				return skin;
			}
		}
		if (this->getWindow() != nullptr)
		{
			return this->getWindow()->getSkin();
		}
		return nullptr;
	}

	void SPElement::decreaseParsingDepth() {
		this->m_parsingDepth--;
	}


	void SPElement::increaseParsingDepth() {
		this->m_parsingDepth++;
	}

	SPElement::SPElement() : SPNode(), fontStyle(SPFontStyle("Tahoma", 13, 1, false, false)) {

		this->padding = new sp_margin();
		this->margins = new sp_margin();

	}

	SPGraphicsContext* SPElement::createGraphics()
	{
		return this->getSpace()->getGraphicsContext();
	}

	void SPElement::show() {
	    this->setVisible(true);
	}
	void SPElement::hide() {
	    this->setVisible(false);
	}
	void SPElement::mouseClick(int mouseButton, int x, int y) {

	}

	void SPElement::setSkin(SPSkin *value) {
		this->m_skin = value;
		this->applySkin();
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


	void SPElement::mouseDown(SPObject* sender, SPEventArgs* e) {
		SPMouseEventArgs *me = dynamic_cast<SPMouseEventArgs *>(e);
		int x = me->getX();
		int y = me->getY();
		int xx = this->getAbsoluteBounds() != NULL ? x - this->getAbsoluteBounds()->y : x;
	    int yy = this->getAbsoluteBounds() != NULL ? y - this->getAbsoluteBounds()->y : y;


		this->setState(SP_STATE_ACTIVE);
		this->notify(string("mousedown"), this, me);
		for(vector<SPNode *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
			SPElement *elm = static_cast<SPElement *>(*it);
	        if (elm->getAbsoluteBounds() != NULL)
			if(x > elm->getAbsoluteBounds()->x && x < elm->getAbsoluteBounds()->x + elm->getAbsoluteBounds()->width &&
				y > elm->getAbsoluteBounds()->y && y < elm->getAbsoluteBounds()->y + elm->getAbsoluteBounds()->height) {
				elm->mouseDown(sender, me);
			}
		}
	}
	void SPElement::mouseUp(SPObject* sender, SPEventArgs* e) {
		SPMouseEventArgs *me = dynamic_cast<SPMouseEventArgs *>(e);
		int x = me->getX();
		int y = me->getY();

		this->notify(string("mouseup"), this, me);
		this->setState(SP_STATE_NORMAL);
		for(vector<SPNode *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
			SPElement *elm = static_cast<SPElement *>(*it);
	        if (elm->getAbsoluteBounds() != NULL)
			if(x > elm->getAbsoluteBounds()->x && x < elm->getAbsoluteBounds()->x + elm->getAbsoluteBounds()->width &&
				y > elm->getAbsoluteBounds()->y && y < elm->getAbsoluteBounds()->y + elm->getAbsoluteBounds()->height) {
				elm->mouseUp(sender, e);
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

	SPColor SPElement::getBackgroundColor()
	{
		SPColor def = SPColor(220, 220, 220, 255);
		if (this->getTintColor() != nullptr)
		{
			if (this->getColorScheme() == SP_COLOR_SCHEME_DARK) {
				def = *this->getTintColor();
			} else {
				def = def.tint(*this->getTintColor());
			}
			def = def.alpha(1);
		}
		switch (this->getColorScheme())
		{
		case SP_COLOR_SCHEME_LIGHT:
			break;
		case SP_COLOR_SCHEME_DARK:
			def = def.lighten(-0.8);
		default:
		}
		return this->getColorAttribute("bgcolor",def);
	}

	SPColor SPElement::getForegroundColor()
	{
		SPColor def = SPColor(28, 28, 28, 255);
		if (this->getColorScheme() == SP_COLOR_SCHEME_DARK)
		{
			def = SPColor(200, 200, 200, 255);
		}
		if (this->getTintColor() != nullptr)
		{
			def = def.tint(*this->getTintColor());
		}
		return this->getColorAttribute("fgcolor",def);

	}

	void SPElement::applyColorAttributeFromSkin (string attr, string prop) {
	    cout << prop << "\r\n";
	    cout << this->m_skin->colors << "\r\n";
	    cout << attr << "\r\n";
	    if (this->m_skin->colors->find(prop) != this->m_skin->colors->end()) {
	        pixel *color = (*this->m_skin->colors)[prop];

	        this->set(attr, space_pixel_to_hex(color));
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

	void SPElement::generateAndSetDefaultGradient()
	{
		SPGradient* gradient = this->generateDefaultGradient();
		this->setGradient(gradient);
	}

	SPGradient* SPElement::generateDefaultGradient()
	{
		SPColor bgColor = this->getColorAttribute("bgcolor", SPColor(28, 28, 28, 255));
		SPColor fgColor = this->getColorAttribute("fgcolor", SPColor(255, 255, 255, 255));

		SPColor startColor = bgColor.lighten(0.1);
		SPColor endColor = bgColor.lighten(-0.1);
		return new SPGradient(startColor, endColor, 0);
	}

	SPElement::SPElement(SPElement *parent) : SPNode(static_cast<SPNode*>(parent)), fontStyle("Tahoma", 13, 1, false, false) {
		this->setTintColor(new SPColor(0, 127, 255, 56));
		this->m_classList = new vector<string>;
		this->absoluteBounds = new sp_rectangle;
		this->setScrollable(false);
		if (parent != nullptr) {
			this->m_skin = parent->getSkin();
			this->fontStyle = parent->fontStyle;
			this->absoluteBounds = new sp_rectangle { parent->getX(), parent->getY(), parent->getWidth(), parent->getHeight() };
		}
		this->visible = true;
		this->scrollX = 0;
		this->scrollY = 0;
	    this->data = "";
		this->setParentNode(parent);
		if (this->m_skin != nullptr) {
			this->applySkin();	   
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

		if (parent != nullptr) {
			if (parent->getType() == "window") {
				this->m_window = (SPWindow *)parent;
			} else {
				SPWindow *window = parent->getWindow();
				if (window != nullptr) {
					this->m_window = window;
					if (window->getSkin() != nullptr) {
						this->m_skin = window->getSkin();
					}
				}
			}
			SPSkin *skin = parent->getSkin();
			if (skin != nullptr) {
				this->m_skin = skin;
			}
		}
	}

	void SPElement::applySkin() {
		this->applyColorAttributeFromSkin(string("bgcolor"), string("body.background.color"));
		this->applyColorAttributeFromSkin(string("fgcolor"), string("body.foreground.color"));

		string type = string(this->getType());

		this->applyColorAttributeFromSkin(string("bgcolor"), string(this->getType()) + "body.background.color");
		this->applyColorAttributeFromSkin(string("fgcolor"), string(this->getType()) + "body.foreground.color");
		if (this->m_skin->hasImage(this->SPElement::getType() + ".background.image")) {
			this->m_backgroundImage = this->m_skin->getImage(string(this->getType()) + ".background.image", "");
		}
	}

	SPElement::SPElement(SPElement *parent, SPWindow *window, SPSkin *skin) : SPElement(parent) {
		if (window == nullptr) {
			throw "Window is null";
		}
		if (skin == nullptr) {
			throw "Skin is null";
		}
		if (window->getSkin() == nullptr) {
			window->setSkin(skin);
		}
		this->m_window = window;
		this->m_skin = skin;
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
	void SPElement::setColorScheme(short value)
	{
		this->m_colorScheme	= value;
	}

	short SPElement::getColorScheme() {
		short colorScheme = this->m_colorScheme;
		if (colorScheme == SP_COLOR_SCHEME_DEFAULT)
		{
			if (this->m_window != nullptr)
			{
				colorScheme = dynamic_cast<SPElement*>(this->getWindow())->getColorScheme();
			}
			if (colorScheme == SP_COLOR_SCHEME_DEFAULT)
			{
				if (this->m_parent != nullptr)
				{
					colorScheme = this->getParentElement()->getColorScheme();
				}
			}
		}
		if (colorScheme < 1 || colorScheme > 2)
		{
			throw "Invalid color scheme";
		}
		return colorScheme;
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

			if (message.type == "event") {
				if (message.predicate == "mousedown" || message.predicate == "mouseup" || message.predicate == "mousemove") {
					//SPMouseEventArgs *args = new SPMouseEventArgs(0, message.data.at("x").as_double(), message.data.at("y").as_double(), this);
					//this->dispatchEvent(message.predicate, args, this);
				}
			}

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
		if (w < 1)
		{
			w = 1;
		}
		this->m_width = w;
	}
	void SPElement::setHeight(int h) {
		if (h < 1)
		{
			h = 1;
		}
		this->m_height = h;

	}
	void SPElement::setX(int x) {
		if (x < 0)
		{
			x = 0;
		}
		this->x = x;
	}
	void SPElement::setY(int y) {
		if (y < 0)
		{
			y = 0;
		}
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

	void SPElement::paint(int x, int y, int width, int height, SPGraphicsContext *c)
	{
		SPColor fgColor = this->getForegroundColor();
		SPColor bgColor = this->getBackgroundColor();
		int fontSize = this->getIntegerAttribute("size", 12);
		string fontFamily = this->getStringAttribute("font", "MS Sans Serif");

		string stateClass;
		switch (this->getState()) {
		case SP_STATE_ACTIVE:
			stateClass = "active";
			break;
		case SP_STATE_HOVER:
			stateClass = "hover";
		default:
			stateClass = "";
		}

		if (!this->getSkin()->drawElement(c, this, stateClass, sp_rectangle { x, y, width, height, 0 }))
		{
			c->fillRectangle(x + 1, y, width, height, bgColor);
		}
		SPColor color(255, 0, 0, 255);
		string text = this->getInnerText();
		// draw text
		if (!text.empty())
			c->drawString(this->getInnerText(), SPFontStyle(fontFamily, fontSize, fontSize / 2, false, false), fgColor, x - scrollX, y - scrollY, this->getWidth(), this->getHeight());
		// adjust for scroll
	}

    void SPElement::resizeToText(bool width, bool height) {
		sp_rectangle bounds = this->getTextBounds();
		if (width) {
			this->setWidth(bounds.width);
		}
		if (height) {
			this->setHeight(bounds.height * 2);
		}
	}

	sp_rectangle SPElement::getTextBounds() {
		SPGraphicsContext *c = this->createGraphics();
		string text = this->getInnerText();
		if (text.empty()) {
			return sp_rectangle { 0, 0, 0, 0 };
		}
	    sp_rectangle tSize = c->measureString(text, fontStyle);
		return tSize;
	}

	string SPElement::getSrc() {
		return this->getStringAttribute("src", "");
	}


	void SPElement::setSrc(const string &value) {
		this->setStringAttribute("src", value);
	}


	void SPElement::draw(int x, int y, SPGraphicsContext *c) {
	    if (!this->isVisible()) {
	        return;
	    }
		sp_position pos;
		std::vector<SPNode *> *children = this->getChildNodes();
		x += this->getX();
		y += this->getY();
		if (this->absoluteBounds == nullptr)
	    this->absoluteBounds = new sp_rectangle;

	    this->absoluteBounds->x = x;
	    this->absoluteBounds->y = y;
	    this->absoluteBounds->width = this->getWidth();
	    this->absoluteBounds->height = this->getHeight();

		int width =  this->getWidth();
		int height = this->getHeight();

		sp_rectangle rect2;
		rect2.x = this->absoluteBounds->x;
		rect2.y = this->absoluteBounds->y;
		rect2.width = width;
		rect2.height = height;
		if (this->clipView) {
	        c->setClip(*absoluteBounds);
		}
		x -= this->scrollX;
		y -= this->scrollY;
		this->paint(rect2.x, rect2.y, rect2.width, rect2.height, c);
		SPColor borderColor = this->getBorderColor();
		if (!borderColor.empty() && this->drawBorder) {
			c->drawRectangle(x, y, width, height, borderColor);
		}
		for(std::vector<SPNode *>::iterator it = children->begin(); it != children->end(); ++it) {
			SPElement *elm = static_cast<SPElement *>(*it);
			if(elm != nullptr) {
				elm->draw(rect2.x, rect2.y, c);
			}
		}
		SPColor bgColor = this->getColorAttribute("bgcolor", SPColor(28, 28, 28, 255));
		SPColor fgColor = this->getColorAttribute("fgcolor", SPColor(255, 255, 255, 255));
		int fontSize = this->getIntegerAttribute("size", 12);
		string fontFamily = this->getStringAttribute("font", "MS Sans Serif");
		c->drawRectangle(rect2.x, rect2.y, width, height, SPColor(255, 0, 0,255));
		c->drawString(this->getType(), SPFontStyle(fontFamily, fontSize, fontSize / 2, false, false), fgColor, rect2.x, rect2.y, this->getWidth(), this->getHeight());
		const string strLoc = "type=" + this->getType() + "&x=" + std::to_string(x) + "&y=" + std::to_string(y) + "&width=" + std::to_string(width) + "&height=" + std::to_string(height) + "&flex=" + std::to_string(this->getIntegerAttribute("flex", 0));
		c->drawString(strLoc, SPFontStyle(fontFamily, fontSize, fontSize / 2, false, false), SPColor(0, 0, 255, 255), rect2.x + (rect2.width / 2), rect2.y + (rect2.height / 2), this->getWidth(), this->getHeight());

		if (clipView) {
	        c->declipRect();
		}
	}

	void SPElement::pack()
	{
		//cout << "Element: " << this->getType() << "#" << this->getId() << " packed to width: " << this->getWidth() << " height: " << this->getHeight() << " flex: " << this->getIntegerAttribute("flex", 0) << endl;
	}

	void SPElement::resize(int width, int height)
	{
		this->m_width = width;
		this->m_height = height;
		this->invalidate();
		this->pack();

		//cout << "Element: " << this->getType() << "#" << this->getId() << " resized to width: " << width << " height: " << height << " flex: " << this->getIntegerAttribute("flex", 0) << endl;
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
	        if ((this->getWindow())->getDeepestElement() == nullptr) {
	            break;
	        }
			SPElement *elm = dynamic_cast<SPElement *>(*it);
			string type = elm->getType();
			cout << type << endl;
	        if (elm->isVisible()) {
	            if (elm->getAbsoluteBounds() != nullptr) {

	                if(x > elm->getAbsoluteBounds()->x && x < elm->getAbsoluteBounds()->x + elm->getAbsoluteBounds()->width &&
	                    y > elm->getAbsoluteBounds()->y && y < elm->getAbsoluteBounds()->y + elm->getAbsoluteBounds()->height) {
	                    foundElement = true;
	                    cout << elm->getType() << endl;
	                    elm->scroll(scrollX, scrollY, x, y);
	                }
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

	SPElement *SPElement::parseElement(wxXmlNode *xmlNode, SPElement *parent,
							   SPElement *document) {
		SPElement *elm = nullptr;
		elm = document->getElementById(string(xmlNode->GetAttribute("id")));
		if (elm == nullptr) {
			elm = createElement(xmlNode->GetName().ToStdString(), parent);
		}
		for (int i = 0; i < sizeof(xmlNode->GetAttributes()); i++) {
			auto attribute = xmlNode->GetAttributes()[i];
			elm->set(attribute.GetName().ToStdString(), attribute.GetValue().ToStdString());
		}
		elm->setInnerText(this->getInnerText());
		for (wxXmlNode *child = xmlNode->GetChildren(); child; child = child->GetNext()) {
			parseElement(child, elm, document);
		}
		return elm;
	}

	SPElement * SPElement::createElement(const string& tagName, SPElement *parent) {
		if (parent == nullptr) {
			parent = this;
		}
		SPElement *elm = nullptr;
		if (tagName == "text") {
			elm = new SPTextElement(parent);
		} else if (tagName == "img") {
			elm = new SPImageElement(parent);
		} else if (tagName == "button") {
			elm = new SPButtonElement(parent);
		} else {
			elm = new SPElement(parent);
		}
		return elm;
	}

	SPElement* SPElement::getElementById(const string& id) const {
		for (const auto child : *this->children) {
			if (child->getStringAttribute("id", "") == id) {
				return (SPElement *)child;
			}
			for (const auto grandChild : *child->getChildNodes()) {
				return (SPElement *)grandChild->getNodeById(id);
			}
		}
		return nullptr;
	}

}


