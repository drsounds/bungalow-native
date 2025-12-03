#include "WindowElement.h"

#include "GraphicsContext.h"

#include "Element.h"
#include "MainWindowElement.h"

namespace spider
{
    WindowElement::WindowElement(GraphicsContext* gc)
    {
        this->gc = gc;
    }

    void WindowElement::draw() {
        std::vector<Node *> *elements = this->getChildNodes();
        for (std::vector<Node *>::iterator it = elements->begin(); it != elements->end(); ++it) {
            Node *node = (Node *)*it;
            Element *elm = static_cast<Element *>(node);
            if (elm->isVisible())
                elm->draw(0, 0, this->gc);
        }
    }
    void WindowElement::invalidateRegion(rectangle rect) {
        gc->invalidateRegion(rect);
    }
    void WindowElement::navigate(string uri) {
        this->mainWindow->navigate(uri);
    }
    void WindowElement::scroll(int x, int y) {
        deepestView = (Element *)this->mainWindow;
        this->mainWindow->scroll(x, y);
    }
    void WindowElement::scrollTo(int x, int y) {

    }
    void WindowElement::pack() {

        auto gc = this->createGraphics();

        int width = gc->getWidth();
        int height = gc->getHeight();
        for (vector<Node *>::iterator it = this->getChildNodes()->begin(); it != this->getChildNodes()->end(); ++it) {
            Element *elm = (Element *)static_cast<Node *>(*it);
            elm->setX(0);
            elm->setY(0);
            elm->setWidth(width);
            elm->setHeight(height);
            elm->pack();
        }
    }
    void WindowElement::scroll(int scrollX, int scrollY, int mouseX, int mouseY) {
        this->deepestView = this->mainWindow;
        this->mainWindow->scroll(scrollX, scrollY, mouseX, mouseY);
        if (this->deepestView != NULL) {
            cout << "Scrolling on" << endl;
            this->deepestView->scroll(scrollX, scrollY);
            this->deepestView = NULL;
        }
    }
    void sample_click(spider::Element *elm, void *data) {
        //MessageBox(((WindowElement *)elm->getWindowNode())->getHandle(), (LPCSTR)"Test",(LPCSTR)L"A", 0);
    }
    void WindowElement::SampleLayout() {
        this->setColorAttribute("bgcolor", Color(127, 127, 127, 1));
        this->setWindowElement(this);
        this->mainWindow = new MainWindowElement(this, wne Skin(string("skin.png"), this->createGraphics()));
        this->mainWindow->setWindowElement((WindowElement *)this);
        this->mainWindow->setVisible(true);
        this->mainWindow->layout();
        this->appendChild(mainWindow);
    }
}
