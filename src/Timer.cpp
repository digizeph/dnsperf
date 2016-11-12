#include "Timer.h"


/**
 * Timer thread function takes a function and call it with interval time
 *
 * @param func the pointer to the function to be called
 * @param interval the interval time of how frequent the function is called. The unit is milisecond.
 *
 */
void Timer::operator()(std::function<void(void)> func, unsigned int interval)
{
    while (true)
    {
        func();
        std::cout<<"HEY\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
    }
}
