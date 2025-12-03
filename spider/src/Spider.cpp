//
// Created by Alexander Forselius on 2025-12-03.
//

#include "../include/Spider.h"

#include "libspider.h"
#include "WindowElement.h"

spider::Spider::Spider(GraphicsContext* graphicsContext)
{
    this->m_graphicsContext = graphicsContext;
    this->m_windows = new vector<WindowElement *>();
    this->m_messages = new queue<SPMessage>();
    this->m_events = new queue<SPEvent>();
}

spider::WindowElement* spider::Spider::createWindow()
{
    auto *windowElement = new WindowElement(this);
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

void spider::Spider::postMessage(const SPMessage& message) const
{
    this->m_messages->push(message);
}

void spider::Spider::processEvent(const SPEvent& event) const
{
    for (auto & m_window : *this->m_windows) {
        m_window->processEvent(event);
    }
}

void spider::Spider::processMessage(const SPMessage& message) const
{
    for (auto & m_window : *this->m_windows) {
        m_window->processMessage(message);
    }
}
