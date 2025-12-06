#ifndef COLOR_H
#define COLOR_H
#include "SPObject.h"
#include <string>
namespace spider {
class SPColor : virtual public SPObject {
    short r;
    short g;
    short b;
    short a;
public:
    string getType() override {
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
    SPColor();
    SPColor(short r, short g, short b, short a);
    SPColor(const string& html);
    string toHTMLColor();
};
}
#endif // COLOR_H
