#ifndef SERVER_H
#define SERVER_H

#include <string>
using namespace std;

namespace spider {
   typedef void (*spider_server_reply)(int code, string data);
class Server
{
    public:
        Server();
        virtual ~Server();
        void request(string method, string uri, void *data, spider_server_reply *reply);
};
}
#endif // SERVER_H
