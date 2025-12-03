#ifndef COLOR_H
#define COLOR_H
#include "SPType.h"
#include <string>
namespace spider {
#ifdef SPTYPE_CLASS
#ifndef COLOR_CLASS
class Color : public SPType {
    short r;
    short g;
    short b;
    short a;
public:
    string getType() {
        return "Color";
    }
    short getR();
    short getG();
    short getB();
    short getA();
    void setR(short r);
    void setG(short g);
    void setB(short b);
    void setA(short a);
    Color();
    Color(short r, short g, short b, short a);
    Color(const string& html);
    string toHTMLColor();
};
#define COLOR_CLASS
#endif
#endif
}
#endif // COLOR_H
