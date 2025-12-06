#ifndef IMAGELIBRARY_H
#define IMAGELIBRARY_H
#include "libspider.h"
#include <map>
using namespace std;

namespace spider {
    class SPImage;
    class ImageLibrary
    {
        protected:
            map<string, void *> *mImages;
        private:
        public:
            ImageLibrary();
            virtual ~ImageLibrary();
            SPImage *get(string uri);
            void set(string uri, SPmage *image);
    };
}
#endif // IMAGELIBRARY_H
