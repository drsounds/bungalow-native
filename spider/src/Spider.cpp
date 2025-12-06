//
// Created by Alexander Forselius on 2025-12-03.
//

#include "Spider.h"

#include "SPSkin.h"
#include "libspider.h"
#include "SPWindowElement.h"

spider::Spider::Spider(SPGraphicsContext* graphicsContext)
{
    this->m_graphicsContext = graphicsContext;
    this->m_windows = new vector<SPWindowElement *>();
    this->m_messages = new queue<SPMessage>();
    this->m_events = new queue<SPEvent>();
}

spider::SPWindowElement* spider::Spider::createWindow(SPSkin *skin)
{
    auto *windowElement = new SPWindowElement(this, skin);
    return windowElement;
}

spider::SPMessage spider::Spider::dequeueNextMessage() {
    auto message = this->m_messages->front();
    this->m_messages->pop();
    return message;
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
