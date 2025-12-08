#ifndef SPIDERSERVER_H
#define SPIDERSERVER_H

#include <string>
using namespace std;
namespace space {
class SPSpiderServer
{
    public:
        SPSpiderServer();
        virtual ~SPSpiderServer();
        void request(string method, string uri, void *data);
    protected:
    private:
};
}

#endif // SPIDERSERVER_H
