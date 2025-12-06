#ifndef SKIN_H
#define SKIN_H
#include <map>
#include <string>
using namespace std;
namespace spider {
class SPImage;
class SPColor;
class pixel;
class slice {
public:
    SPImage *image;
    int x1;
    int y1;
    int x2;
    int y2;
    int leftBorder;
    int topBorder;
    int rightBorder;
    int bottomBorder;
    slice(SPImage *image, int x1, int x2, int y1, int y2, int leftBorder, int topBorder, int rightBorder, int bottomBorder);
};
class Skin
{
    public:
        map<string, SPImage *> *images;
        map<string, pixel *> *colors;
        map<string, slice *> *slices;
        SPImage *image;
        Skin();
        Skin(const string& bitmap);
        virtual ~Skin();
        bool hasColor(string selector);
        bool hasImage(string selector);
        SPColor getColor(string selector, string def);
        SPImage *getImage(string selector, string def);

    protected:
    private:
};
}
#endif // SKIN_H
