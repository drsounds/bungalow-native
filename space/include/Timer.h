#ifndef H_TIMER
#define H_TIMER
// Based on https://stackoverflow.com/questions/14650885/how-to-create-timer-events-using-c-11

#include <functional>
#include <chrono>
#include <future>
#include <cstdio>

class Timer
{
public:
    template <class callable, class... arguments>
    int after;
    bool async;
    callable f;
    arguments args;
    Timer(int after, bool async, callable&& f, arguments&&... args)
    {
        this->callable = f;
        this->args = args;
        this->task = new std::function<typename std::result_of<callable(arguments...)>::type()>(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));
    }
};
#endif