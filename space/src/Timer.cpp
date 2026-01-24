#include "Timer.h"

void Timer::start() {
    if (this->async)
    {
        std::thread([this->after, this->task]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(this->after));
            this->task();
        }).detach();
    }
    else
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(this->after));
        this->task();
    }
}