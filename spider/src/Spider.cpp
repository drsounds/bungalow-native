//
// Created by Alexander Forselius on 2025-12-03.
//

#include "../include/Spider.h"
#include "Skin.h"
#include "libspider.h"
#include "WindowElement.h"

spider::Spider::Spider(GraphicsContext* graphicsContext)
{
    this->m_graphicsContext = graphicsContext;
    this->m_windows = new vector<WindowElement *>();
    this->m_messages = new queue<SPMessage *>();
}

spider::WindowElement* spider::Spider::createWindow()
{
    auto *windowElement = new WindowElement(this);
    windowElement->m_skin = new Skin("skin.png");
    return windowElement;
}

spider::SPMessage spider::Spider::dequeueNextMessage() {
    auto message = this->m_messages->front();
    this->m_messages->pop();
    return message;
}

void spider::Spider::dispatchEvent(const SPEvent& event) const
{
    this->m_events->push(event);
}

void spider::Spider::postMessage(const SPMessage& message)
{
    this->m_messages->push(message);
}

void spider::Spider::processEvent(const SPEvent& event)
{
    for (auto it = this->m_windows->begin(); it != this->m_windows->end(); ++it) {
        (*it)->processEvent(event);
    }
}

void spider::Spider::processMessage(const SPMessage& message)
{
    for (auto it = this->m_windows->begin(); it != this->m_windows->end(); ++it) {
        (*it)->processMessage(message);
    }
}
