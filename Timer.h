#ifndef BIGINTEGER_TIMER_H
#define BIGINTEGER_TIMER_H

#include <exception>


class Timer
{
private:
    std::ostream& os;
    std::string scope_name;

    bool paused;
    long long paused_duration;

    std::chrono::time_point<std::chrono::_V2::system_clock> t0;
    std::chrono::time_point<std::chrono::_V2::system_clock> t1;

public:
    Timer(std::ostream& arg, const char *s)
            :   os(arg),
                paused(false),
                scope_name(s),
                paused_duration(0),
                t0(std::chrono::high_resolution_clock::now())
    {}

    void pause()
    {
        if (paused)
        {
            std::string err_message;

            err_message += "Timer in scope \"";
            err_message += scope_name;
            err_message += "\" is already paused.";

            throw std::logic_error(err_message);
        }
        paused = true;
        t1 = std::chrono::high_resolution_clock::now();
    }

    void unpause()
    {
        using namespace std::chrono;

        if (!paused)
        {
            std::string err_message;

            err_message += "Timer in scope \"";
            err_message += scope_name;
            err_message += "\" was never paused.";

            throw std::logic_error(err_message);
        }
        paused_duration += duration_cast<milliseconds>(high_resolution_clock::now() - t1).count();
        paused = false;
    }

    ~Timer()
    {
        using namespace std::chrono;

        t1 = high_resolution_clock::now();
        os  << '{' << scope_name << "} elapsed time: "
            << (double)(duration_cast<milliseconds>(t1 - t0).count() - paused_duration) / 1000.0
            << "sec\n";
    }
};



#endif //BIGINTEGER_TIMER_H
