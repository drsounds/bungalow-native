#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>
using namespace std;
namespace space {
class SPResource
{
    public:
        SPResource(string uri);
        SPResource();
        virtual ~SPResource();
        string getName() {
            return this->name;
        }
    protected:
        string uri;
        string name;
        SPResource *author;
        SPResource *collection;
        SPResource *playlist;

    private:
};
}
#endif // RESOURCE_H
