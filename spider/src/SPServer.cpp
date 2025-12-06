#include "SPServer.h"
namespace spider {
SPServer::SPServer()
{
    //ctor
}

void SPServer::request(string method, string uri, void *data, spider_server_reply *reply) {
    if (strcmp(method.c_str(), "GET") == 0) {
        if (strcmp(uri.c_str(), "spacify:internal:home") == 0) {

        }
    }
}
SPServer::~SPServer()
{
    //dtor
}
}