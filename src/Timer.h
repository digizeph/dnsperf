#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

class Timer {
public:
    void operator()(std::function<void(void)>, int, int);
};

#endif
