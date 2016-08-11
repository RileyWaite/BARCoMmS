#ifndef BC_DITL_COLORLIB_H
#define BC_DITL_COLORLIB_H

#include <QBrush>
#include <QDebug>

#include <vector>
#include <string>
#include <fstream>

#include "bc_ditl_constants.cpp"

class Color{ // Singleton
    QBrush BLUE;
    QBrush BABYBLUE;
    QBrush PEA;
    QBrush ORANGE;
    QBrush YELLOW;
    QBrush GRAY;
    QBrush GREEN;
    QBrush BABYGREEN;
    QBrush PEACH;
    QBrush BROWN;
    QBrush bg;
    QBrush WHITE;
    QBrush darkGRAY;

    QBrush lBLUE;
    QBrush lBABYBLUE;
    QBrush lPEA;
    QBrush lORANGE;
    QBrush lYELLOW;
    QBrush lGRAY;
    QBrush lGREEN;
    QBrush lBABYGREEN;
    QBrush lPEACH;
    QBrush lBROWN;

    QBrush WARN;

    struct Pair
    {
        std::string name;
        std::string color;
    };

    std::vector<Pair> pairs;

public:
    Color();
    Color(std::string);

    QBrush colorFromEvent(std::string, bool opaque = true);
    QBrush colorFromString(std::string, bool opaque = true);
    QBrush randColor();
    void load(std::string);
};

#endif // BC_DITL_COLORLIB_H
