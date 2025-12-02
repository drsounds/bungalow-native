#include "Server.h"
namespace spider {
Server::Server()
{
    //ctor
}

void Server::request(string method, string uri, void *data, spider_server_reply *reply) {
    if (strcmp(method.c_str(), "GET") == 0) {
        if (strcmp(uri.c_str(), "spacify:internal:home") == 0) {

        }
    }
}
Server::~Server()
{
    //dtor
}
}