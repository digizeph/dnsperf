#include "timer.h"


void Timer::operator()(std::function<void(void)> func, unsigned int interval)
{
    //std::thread([func, interval]() {
        while (true)
        {
            func();
            std::cout<<"HEY\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    //}).detach();
}
