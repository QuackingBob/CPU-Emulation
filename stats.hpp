#ifndef STATS_HPP
#define STATS_HPP


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


#endif
