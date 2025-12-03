//
// Created by Alexander Forselius on 2025-12-03.
//

#include "App.h"

spider::App::App(GraphicsContext* graphicsContext)
{
    this->graphicsContext = graphicsContext;
    this->windows = new vector<WindowElement *>();
    this->messages = new queue<sp_message>();
}

spider::sp_message spider::App::dequeueNextMessage() {
    auto message = this->messages->front();
    this->messages->pop();
    return message;
}

void spider::App::postMessage(sp_message message)
{
    this->messages->push(message);
}

void spider::App::processMessage(const sp_message& message)
{
    for (auto it = this->windows.begin(); it != this->windows.end(); ++it) {
        (*it)->processMessage(message);
    }
}
