//
// Created by Alexander Forselius on 2025-12-03.
//

#include "Spider.h"

#include "SPSkin.h"
#include "libspider.h"
#include "SPWindowElement.h"

space::Spider::Spider()
{ 
    this->m_windows = new vector<SPWindowElement *>();
    this->m_messages = new queue<SPMessage>();
    this->m_events = new queue<SPEvent>();
}

space::SPWindowElement* space::Spider::createWindow(SPSkin *skin)
{
    auto *windowElement = new SPWindowElement(this, skin);
    return windowElement;
}

space::SPMessage space::Spider::dequeueNextMessage() {
    auto message = this->m_messages->front();
    this->m_messages->pop();
    return message;
}

void space::Spider::postMessage(const SPMessage& message) const
{
    this->m_messages->push(message);
}

void space::Spider::processEvent(const SPEvent& event) const
{
    for (auto & m_window : *this->m_windows) {
        m_window->processEvent(event);
    }
}

void space::Spider::processMessage(const SPMessage& message) const
{
    for (auto & m_window : *this->m_windows) {
        m_window->processMessage(message);
    }
}
