#ifndef STATS_HPP
#define STATS_HPP

#include <chrono>

using namespace std;

class stats {
public:
    static int transistor_count;
    static int success_count;
    static int case_count;

    static void reset()
    {
        transistor_count = 0;
        success_count = 0;
        case_count = 0;
    }
};

// because templates are not compiled till instantiated, I have to put this in the header file
template <typename T, typename... A>
T time_it(double &time_micro_s, T (*func)(A...), A... args)
{
    auto a = std::chrono::high_resolution_clock::now();
    T out = func(args...);
    auto b = std::chrono::high_resolution_clock::now();
    time_micro_s = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(b - a).count());
    return out;
}

#endif
