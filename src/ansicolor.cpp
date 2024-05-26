#include "ansicolor.h"

RGBColor::RGBColor(unsigned char red, unsigned char green, unsigned char blue)
    : red(red), green(green), blue(blue){};

RGBColor::operator std::string() const {
    return std::string() + std::to_string((int)red) + ";" +
           std::to_string((int)green) + ";" + std::to_string((int)blue);
};

std::string coloredString(std::string baseString, RGBColor foreground,
                          RGBColor background) {
    return backgroundColor(foregroundColor(baseString, foreground), background);
};

std::string foregroundColor(std::string baseString, RGBColor foreground) {
    return std::string() + "\033[38;2;" + (std::string)foreground + "m" +
           baseString + "\033[39m";
};

std::string backgroundColor(std::string baseString, RGBColor background) {
    return std::string() + "\033[48;2;" + (std::string)background + "m" +
           baseString + "\033[49m";
};
