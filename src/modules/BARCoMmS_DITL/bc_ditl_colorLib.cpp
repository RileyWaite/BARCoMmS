#include "bc_ditl_colorLib.h"

Color::Color()
{
    BLUE = QBrush(QColor(156,224,210));
    BABYBLUE = QBrush(QColor(155,194,230));
    PEA = QBrush(QColor(198,224,180));
    ORANGE = QBrush(QColor(255,192,0));
    YELLOW = QBrush(QColor(255,253,155));
    GRAY = QBrush(QColor(217,217,217));
    GREEN = QBrush(QColor(200,255,135));
    BABYGREEN = QBrush(QColor(168,223,154));
    PEACH = QBrush(QColor(255,199,161));
    BROWN = QBrush(QColor(198,89,17));
    bg = QBrush(QColor(239,235,231));
    WHITE = QBrush(Qt::white);
    darkGRAY = QBrush(Qt::darkGray);

    lBLUE = QBrush(QColor(156,224,210,OPA));
    lBABYBLUE = QBrush(QColor(155,194,230,OPA));
    lPEA = QBrush(QColor(198,224,180,OPA));
    lORANGE = QBrush(QColor(255,192,0,OPA));
    lYELLOW = QBrush(QColor(255,253,155,OPA));
    lGRAY = QBrush(QColor(217,217,217,OPA));
    lGREEN = QBrush(QColor(200,255,135,OPA));
    lBABYGREEN = QBrush(QColor(168,223,154,OPA));
    lPEACH = QBrush(QColor(255,199,161,OPA));
    lBROWN = QBrush(QColor(198,89,17,OPA));

    WARN = QBrush(Qt::red);
}
Color::Color(std::string in){load(in);}

void Color::load(std::string list)
{
    std::ifstream fin(list);
    if(fin.fail()) qDebug() << "Failed to load Color reference file \""
                            << QString::fromStdString(list)
                            << "\"." << endl;
    std::string n, c;
    unsigned char i=0;
    while(fin >> n >> c)
    {
        Color::Pair pair;
        pair.name = n;
        pair.color = c;
        pairs.push_back(pair);
        ++i;
    }
    if(i%2!=0) qDebug() << "Uneven mapping in Color reference file \""
                        << QString::fromStdString(list)
                        << "\"." << endl;
}

QBrush Color::colorFromEvent(std::string in, bool opaque)
{
    for(unsigned short i(0);i<pairs.size();++i)
        if(in==pairs[i].name) return Color::colorFromString(pairs[i].color, opaque);

    qDebug() << "Unspecified reference to ORIGIN: "
             << QString::fromStdString(in)
             << " in Color::colorFromOrigin.\n";
    return randColor();
}

QBrush Color::colorFromString(std::string in, bool opaque)
{
    if(!opaque)
    {
        if(in=="BLUE") return BLUE;
        if(in=="BABYBLUE") return BABYBLUE;
        if(in=="PEA") return PEA;
        if(in=="ORANGE") return ORANGE;
        if(in=="YELLOW") return YELLOW;
        if(in=="GRAY") return GRAY;
        if(in=="GREEN") return GREEN;
        if(in=="BABYGREEN") return BABYGREEN;
        if(in=="PEACH") return PEACH;
        if(in=="BROWN") return BROWN;
        if(in=="bg") return bg;
        if(in=="WHITE") return WHITE;
        if(in=="WARN") return WARN;
        return randColor();
    }
    else
    {
        if(in=="BLUE") return lBLUE;
        if(in=="BABYBLUE") return lBABYBLUE;
        if(in=="PEA") return lPEA;
        if(in=="ORANGE") return lORANGE;
        if(in=="YELLOW") return lYELLOW;
        if(in=="GRAY") return lGRAY;
        if(in=="GREEN") return lGREEN;
        if(in=="BABYGREEN") return lBABYGREEN;
        if(in=="PEACH") return lPEACH;
        if(in=="BROWN") return lBROWN;
        if(in=="WARN") return WARN;
        if(in=="bg") return bg;
        if(in=="WHITE") return WHITE;
        return randColor();
    }
}

QBrush Color::randColor()
{
    static int prevNum;
    int num = qrand()%9;
    while(num==prevNum) num = qrand()%9;

    switch(num)
    {
    case 0: return lBLUE;
    case 1: return lBABYBLUE;
    case 2: return lPEA;
    case 3: return lORANGE;
    case 4: return lYELLOW;
    case 5: return lGREEN;
    case 6: return lBABYGREEN;
    case 7: return lPEACH;
    case 8: return lBROWN;
    }

    prevNum = num;
}
