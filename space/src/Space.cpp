//
// Created by Alexander Forselius on 2025-12-03.
//

#include "Space.h"

#include "SPSkin.h"
#include "libspace.h"
#include "SPWindowElement.h"

space::Space::Space()
{ 
    this->m_windows = new vector<SPWindowElement *>();
    this->m_messages = new queue<SPMessage>();
    this->m_events = new queue<SPEvent>();
}

space::SPWindowElement* space::Space::createWindow(SPSkin *skin)
{
    auto *windowElement = new SPWindowElement(this, skin);
    return windowElement;
}

void space::Space::addWindow(SPWindowElement* window)
{
    this->m_windows->push_back(window);
}

void space::Space::notify(const string& event, SPObject* sender, SPEventArgs* data)
{
    SPObservable::notify(event, sender, data);
    for (auto window : *this->m_windows)
    {
        window->notify(event, sender, data);
    }
}
space::SPMessage space::Space::dequeueNextMessage() {
    auto message = this->m_messages->front();
    this->m_messages->pop();
    return message;
}

void space::Space::postMessage(const SPMessage& message) const
{
    this->m_messages->push(message);
}

void space::Space::processEvent(const SPEvent& event) const
{
    for (auto & m_window : *this->m_windows) {
        m_window->processEvent(event);
    }
}

void space::Space::processMessage(const SPMessage& message) const
{
    for (auto & m_window : *this->m_windows) {
        m_window->processMessage(message);
    }
}
