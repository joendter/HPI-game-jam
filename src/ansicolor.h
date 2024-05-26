#ifndef ANSICOLOR_H
#define ANSICOLOR_H
#include <string>

struct RGBColor {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    RGBColor(unsigned char red = 0, unsigned char green = 0,
             unsigned char blue = 0);
    operator std::string() const;
};

std::string coloredString(std::string baseString,
                          RGBColor foreground = RGBColor(255, 255, 255),
                          RGBColor background = RGBColor());

std::string foregroundColor(std::string baseString,
                            RGBColor foreground = RGBColor(255, 255, 255));
std::string backgroundColor(std::string baseString,
                            RGBColor background = RGBColor());

#endif
