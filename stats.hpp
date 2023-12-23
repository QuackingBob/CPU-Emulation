#ifndef STATS_HPP
#define STATS_HPP


class stats {
public:
    static int transistor_count;
    static void reset()
    {
        transistor_count = 0;
    }
};


#endif
