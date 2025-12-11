#ifndef SPCOLOR_H
#define SPCOLOR_H
#include "SPObject.h"
#include <string>
namespace space {
    class SPColor : public SPObject {
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
        SPColor alpha(short amount) const;
        SPColor lighten(float luminance = 0) const;
        SPColor();
        SPColor(short r, short g, short b, short a);
        SPColor tint(const SPColor& tint) const;
        explicit SPColor(const string& html);
        string toHTMLColor();
    };

    class SPGradient
    {
    protected:
        short direction = 0;
        SPColor start;
        SPColor end;
    public:
        SPGradient() {}
        SPGradient(const SPColor& start, const SPColor& end, short direction) {
            this->start = start;
            this->end = end;
            this->direction = direction;
        }
        SPColor getStart() const { return start; }
        void setStart(const SPColor& value) { this->start = value; }
        SPColor getEnd() const { return end; }
        void setEnd(const SPColor& value) { this->end = value; }
        short getDirection() const { return direction; }
        void setDirection(short value) { this->direction = value; }
    };
}
#endif // COLOR_H
