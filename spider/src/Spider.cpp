//
// Created by Alexander Forselius on 2025-12-03.
//

#include "Spider.h"

spider::Spider::Spider(GraphicsContext* graphicsContext)
{
    this->m_graphicsContext = graphicsContext;
    this->m_windows = new vector<WindowElement *>();
    this->m_messages = new queue<sp_message>();
}

spider::WindowElement* spider::Spider::createWindow()
{
    WindowElement *windowElement = new WindowElement(this);
    windowElement->skin = new spider::Skin("skin.png");
}

spider::sp_message spider::Spider::dequeueNextMessage() {
    auto message = this->m_messages->front();
    this->m_messages->pop();
    return message;
}

void spider::Spider::dispatchEvent(const sp_event& event)
{
    this->m_events.push(event);
}

void spider::Spider::postMessage(const sp_message& message)
{
    this->m_messages->push(message);
}

void spider:app:dispatchEvent(const sp_event& event)
{

}

void spider::Spider::processEvent(const sp_event& event)
{
    for (auto it = this->m_windows.begin(); it != this->m_windows.end(); ++it) {
        (*it)->processEvent(event);
    }
}

void spider::Spider::processMessage(const sp_message& message)
{
    for (auto it = this->m_windows.begin(); it != this->m_windows.end(); ++it) {
        (*it)->processMessage(message);
    }
}
