#include "Timer.h"


/**
 * Timer thread function takes a function and call it with interval time
 *
 * @param func the pointer to the function to be called
 * @param interval the interval time of how frequent the function is called. The unit is milisecond.
 *
 */
void Timer::operator()(std::function<void(void)> func, int interval, int count = -1)
{
    if (count > 0) {
        count--;
        func();
        while (count > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            func();
            count--;
        }
    } else if (count == 0) {
        return;
    } else {
        while (true) {
            func();
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    }
}
