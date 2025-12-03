#include "Element.h"
#include <iostream>
#include <cstdio>

#include "../include/Spider.h"
#include "WindowElement.h"
#include "Observable.h"
#include "MouseEventArgs.h"
#include "GraphicsContext.h"
#include "Skin.h"
#include "Image.h"
#include "Observer.h"
#include "Stylesheet.h"
#include "FontStyle.h"

namespace spider {

void Element::show() {
    this->setVisible(true);
}
void Element::hide() {
    this->setVisible(false);
}
void Element::mouseClick(int mouseButton, int x, int y) {

}
GraphicsContext *Element::createGraphics() {
    return this->windowElement->createGraphics();
}

void Element::processMessage(const sp_message& message)
{
	if (message.predicate == "spacify:device:mouse:event:move")
	{
		auto *pos = (rectangle *)message.data;
		this->mouseMove(pos->x, pos->y);
	}
	if (message.predicate == "spacify:device:mouse:event:up")
	{
		auto *pos = (rectangle *)message.data;
		this->mouseUp(1, pos->x, pos->y);
	}
	if (message.predicate == "spacify:device:mouse:event:down")
	{
		auto *pos = (rectangle *)message.data;
		this->mouseDown(1, pos->x, pos->y);
	}
}


void Element::click(int mouseButton, int x, int y) {
	int xx = this->getAbsoluteBounds() != NULL ? x - this->getAbsoluteBounds()->y : x;
    int yy = this->getAbsoluteBounds() != NULL ? y - this->getAbsoluteBounds()->y : y;
	MouseEventArgs *me = new MouseEventArgs(mouseButton, xx, yy);

	this->notify(string("click"), this, me);
	for(vector<Node *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
		Element *elm = static_cast<Element *>(*it);

		if (elm->getAbsoluteBounds() != NULL)
		if(x > elm->getAbsoluteBounds()->x && x < elm->getAbsoluteBounds()->x + elm->getAbsoluteBounds()->width &&
			y > elm->getAbsoluteBounds()->y && y < elm->getAbsoluteBounds()->y + elm->getAbsoluteBounds()->height) {

			elm->click(mouseButton, x , y);
		}
	}
}


void Element::mouseDown(int mouseButton, int x, int y) {
	int xx = this->getAbsoluteBounds() != NULL ? x - this->getAbsoluteBounds()->y : x;
    int yy = this->getAbsoluteBounds() != NULL ? y - this->getAbsoluteBounds()->y : y;
	MouseEventArgs *me = new MouseEventArgs(mouseButton, xx, yy);

	this->notify(string("mousedown"), this, me);
	for(vector<Node *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
		Element *elm = static_cast<Element *>(*it);
        if (elm->getAbsoluteBounds() != NULL)
		if(x > elm->getAbsoluteBounds()->x && x < elm->getAbsoluteBounds()->x + elm->getAbsoluteBounds()->width &&
			y > elm->getAbsoluteBounds()->y && y < elm->getAbsoluteBounds()->y + elm->getAbsoluteBounds()->height) {

			elm->mouseDown(mouseButton, x, y);
		}
	}
}
void Element::mouseUp(int mouseButton, int x, int y) {
	int xx = this->getAbsoluteBounds() != NULL ? x - this->getAbsoluteBounds()->y : x;
    int yy = this->getAbsoluteBounds() != NULL ? y - this->getAbsoluteBounds()->y : y;
	MouseEventArgs *me = new MouseEventArgs(mouseButton, xx, yy);

	this->notify(string("mouseup"), this, me);
	for(vector<Node *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
		Element *elm = static_cast<Element *>(*it);
        if (elm->getAbsoluteBounds() != NULL)
		if(x > elm->getAbsoluteBounds()->x && x < elm->getAbsoluteBounds()->x + elm->getAbsoluteBounds()->width &&
			y > elm->getAbsoluteBounds()->y && y < elm->getAbsoluteBounds()->y + elm->getAbsoluteBounds()->height) {

			elm->mouseUp(mouseButton, x, y);
		}
	}
}
void Element::addClass(string value) {
    this->m_classList->push_back(value);
}

bool Element::hasClass(string value) {
   return  std::find(this->m_classList->begin(), this->m_classList->end(), value) != this->m_classList->end();
}

void Element::removeClass(string value) {
    this->m_classList->erase(std::find(this->m_classList->begin(), this->m_classList->end(), value), this->m_classList->end());
}

FontStyle Element::getFontStyle() {
    return this->fontStyle;
}
void Element::applyStylesheet(Stylesheet *style) {

}

void Element::applyColorAttributeFromSkin (string attr, string prop) {
    if (this->m_skin == NULL) {
        this->m_skin = new Skin("skin.png");
    }
    cout << prop << "\r\n";
    cout << this->m_skin->colors << "\r\n";
    cout << attr << "\r\n";
    if (this->m_skin->colors->find(prop) != this->m_skin->colors->end()) {
        pixel *color = (*this->m_skin->colors)[prop];

        this->set(attr, spider_pixel_to_hex(color));
    }
}

void Element::applyImageAttributeFromSkin (string attr, string prop) {
    if (this->m_skin == NULL) {
        this->m_skin = new Skin("skin.png");
    }
    cout << attr << "\r\n";
    cout << m_skin << "\r\n";
    cout << this->m_skin->colors << "\r\n";
    cout << attr << "\r\n";
    if (this->m_skin->images->find(prop) != this->m_skin->images->end()) {
        Image *img = (*this->m_skin->images)[prop];

        this->setObject(attr, (void *)img);
    }
}

Element::Element(Spider *spider, WindowElement *window, Element *parent) : Node(static_cast<Node*>(parent)) {
    this->m_classList = new vector<string>;
    this->absoluteBounds = NULL;
	this->setScrollable(false);
	this->m_spider = spider;
	this->m_skin = parent->getSkin();
	this->visible = true;
	this->scrollX = 0;
	this->scrollY = 0;
    this->data = "";
	this->observers = new vector<Observer *>();
	this->windowElement = window;
	this->setParent(parent);
	this->fontStyle = FontStyle("Tahoma", 13, 1, false, false);

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
    if (this->m_skin->hasImage(this->Element::getType() + ".background.image")) {
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
        this->windowElement = parent->getWindowElement();
	}
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->width = 0;
	this->height = 0;
	this->margins = new margin();
	this->margins->left = 0;
	this->margins->top = 0;
	this->margins->right = 0;
	this->margins->bottom = 0;
	this->padding = new margin();
	this->padding->left = 0;
	this->padding->top = 0;
	this->padding->right = 0;
	this->padding->bottom = 0;

}
void Element::invalidate() const
{
    rectangle *rect = this->getAbsoluteBounds();
    if (rect == NULL)
        return;
    auto *we = (WindowElement *)this->getWindowElement();
    we->invalidateRegion(*rect);
}
margin *Element::getMargins() {
	return this->margins;
}
margin *Element::getPadding() {
	return this->padding;
}
Element::~Element() {

}
int Element::getHeight() {
	return this->height;
};
int Element::getWidth() {
	return this->width;
}
int Element::getX() {
	return this->x;
}

void Element::processEvent(const SPEvent& event)
{
	switch (event.type)
	{
	case SP_EVENT_MOUSE_DOWN:
		{
			auto *mouseEventArgs = dynamic_cast<MouseEventArgs *>(event.args);
			if (mouseEventArgs != nullptr)
			{
				if (mouseEventArgs->getX() > this->getAbsoluteBounds()->x && mouseEventArgs->getX() < this->getAbsoluteBounds()->y + this->getWidth() &&
					mouseEventArgs->getY() >this->getAbsoluteBounds()->y && mouseEventArgs->getY() < this->getAbsoluteBounds()->y + this->getHeight())
				{
					this->dispatchEvent("mousedown", mouseEventArgs, this);
				}

			}
		}
	case SP_EVENT_MOUSE_UP:
		{
			auto *mouseEventArgs = dynamic_cast<MouseEventArgs *>(event.args);
			if (mouseEventArgs != nullptr)
			{
				if (mouseEventArgs->getX() > this->getAbsoluteBounds()->x && mouseEventArgs->getX() < this->getAbsoluteBounds()->y + this->getWidth() &&
					mouseEventArgs->getY() >this->getAbsoluteBounds()->y && mouseEventArgs->getY() < this->getAbsoluteBounds()->y + this->getHeight())
				{
					this->dispatchEvent("mouseup", mouseEventArgs, this);
				}

			}
		}
	case SP_EVENT_MOUSE_MOVE:
		{
			auto *mouseEventArgs = dynamic_cast<MouseEventArgs *>(event.args);
			if (mouseEventArgs != nullptr)
			{
				if (mouseEventArgs->getX() > this->getX() && mouseEventArgs->getX() < this->getX() + this->getWidth() &&
					mouseEventArgs->getY() > this->getY() && mouseEventArgs->getY() < this->getY() + this->getHeight())
				{
					this->dispatchEvent("mousemove", mouseEventArgs, this);
				}
			}
		}
	default:
		break;
	}
	for (auto & it : *this->children)
	{
		auto *elm = dynamic_cast<Element *>(it);
		elm->processEvent(event);
	}
}

void Element::processMessage(const SPMessage& message)
{
	for (auto & it : *this->children)
	{
		auto *elm = dynamic_cast<Element *>(it);

		elm->processMessage(message);
	}
}

int Element::getY() {
	return this->y;
}
int Element::getZ() {
	return this->z;
}
void Element::setWidth(int w) {
	this->width = w;
}
void Element::setHeight(int h) {
	this->height = h;

}
void Element::setX(int x) {
	this->x = x;
}
void Element::setY(int y) {
	this->y = y;
}
void Element::setZ(int z) {
	this->z = z;
}

void Element::set(const std::string& title, const std::string& val) {
    int n = 0;
        (*this->getStringAttributes())[title] = val;
    try {
        n = stoi(val);
        this->setIntegerAttribute(title, n);
    } catch (const boost::bad_lexical_cast e) { 
    }

    if(val.find("#") == 0) {
        Color c = Color(val);
        this->setColorAttribute(title, c);
    }
}

void Element::setId(std::string id) {
	this->id = id;
}
std::string Element::getId() {
	return this->id;
}


std::string Element::getType() {
    return "element";
}

void Element::draw(int x, int y, GraphicsContext *c) {
    if (!this->isVisible()) {
        return;
    }

	position pos;
	std::vector<Node *> *children = this->getChildNodes();
	x += this->getX() ;
	y += this->getY();
	if (this->absoluteBounds == NULL)
    this->absoluteBounds = new rectangle;

    this->absoluteBounds->x = x + this->getMargins()->left;
    this->absoluteBounds->y = y + this->getMargins()->bottom;
    this->absoluteBounds->width = this->getWidth() - this->getMargins()->left + this->getMargins()->right;
    this->absoluteBounds->height = this->getHeight() - this->getMargins()->top + this->getMargins()->bottom;

	int width =  this->getWidth();
	int height = this->getHeight();

	rectangle rect2;
	rect2.x = 0;
	rect2.y = 0;
	rect2.width = width;
	rect2.height = height;
	if (this->clipView) {
        c->setClip(*absoluteBounds);
	}
    Color bgColor = this->getColorAttribute("bgcolor", Color(0, 0, 0, 1));
    Color fgColor = this->getColorAttribute("fgcolor", Color(255, 255, 255, 1));
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
	Color color(255, 0, 0, 255);
    //c->drawRectangle(0, 0, this->getWidth(), this->getHeight() , &color);
    string text = this->getInnerText();
    // draw text
    if (!text.empty())
        c->drawString(this->getInnerText(), FontStyle(fontFamily, fontSize, fontSize / 2, false, false), fgColor, x - scrollX, y - scrollY, this->getWidth(), this->getHeight());

	// adjust for scroll
    x -= this->scrollX;
    y -= this->scrollY;
	for(std::vector<Node *>::iterator it = children->begin(); it != children->end(); ++it) {
		Element *elm = static_cast<Element *>(*it);
		if(elm != NULL) {
			elm->draw(x + this->getPadding()->left - scrollX, y  + this->getPadding()->top - scrollY, c);
		}
	}
	rectangle rect;
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

void Element::scroll(int scrollX, int scrollY, int x, int y) {
    int xx = this->getAbsoluteBounds() != NULL ? x - this->getAbsoluteBounds()->y : x;
    int yy = this->getAbsoluteBounds() != NULL ? y - this->getAbsoluteBounds()->y : y;
    cout << "Current scrolling element is " << this->getType() << endl;
    bool foundElement = false;
    if (this->clipView) {
        ((WindowElement *)this->getWindowElement())->deepestView = this;
    }
    if (string(this->getType()) == string("toplistview")) {
        cout << "Test" << endl;
    }
	for(vector<Node *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
        if (((WindowElement *)this->getWindowElement())->deepestView == NULL) {
            break;
        }
		Element *elm = static_cast<Element *>(*it);
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

void Element::scroll(int x, int y) {
    if (this->clipView) {
        this->scrollX += x;
        this->scrollY += y;
        if (scrollY < 0) {
            scrollY = 0;
        }
        this->invalidate();
    }
}

void Element::scrollTo(int x, int y) {
    if (this->clipView) {
        this->scrollX = x;
        this->scrollY = y;

        if (scrollY < 0) {
            scrollY = 0;
        }
        this->invalidate();

    }

}

string Element::getInnerText() {
    return this->data;
}
void Element::setInnerText(string value) {
	 this->data = value;
}
}


