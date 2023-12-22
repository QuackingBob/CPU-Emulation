#ifndef PROGRESSBAR_HPP
#define PROGRESSBAR_HPP

#include <iostream>
#include <iomanip>
#include <cmath>

class ProgressBar {
public:
    ProgressBar(int total, int width = 40, char symbol = '#', char background = '-');

    void update(int current);

private:
    int total_;
    int width_;
    char symbol_;
    char background_;
};

ProgressBar::ProgressBar(int total, int width, char symbol, char background)
    : total_(total), width_(width), symbol_(symbol), background_(background) {}

void ProgressBar::update(int current) {
    float progress = static_cast<float>(current) / total_;
    int bar_width = static_cast<int>(progress * width_);

    std::cout << "\r[";
    for (int i = 0; i < bar_width; ++i) {
        std::cout << symbol_;
    }
    for (int i = bar_width; i < width_; ++i) {
        std::cout << background_;
    }

    std::cout << "] " << std::setw(3) << round(progress * 100.0) << "%";
    std::cout.flush();

    if (current == total_) {
        std::cout << std::endl;
    }
}

#endif