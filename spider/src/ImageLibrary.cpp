#include "SPImageLibrary.h"

#include "SPImage.h"

namespace spider {
SPImage *SPImageLibrary::get(string uri) {
    return static_cast<Image *>((*this->mImages)[uri]);
}
void SPImageLibrary::set(string uri, Image *image) {
    (*this->mImages)[uri] = image;
}
SPImageLibrary::ImageLibrary()
{
    //ctor
}

SPImageLibrary::~ImageLibrary()
{
    //dtor
}
}
