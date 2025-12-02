#include "Server.h"
namespace spider {
Server::Server()
{
    //ctor
}

void Server::request(stringmethod, stringuri, void *data, spider_server_reply *reply) {
    if (strcmp(method, "GET") == 0) {
        if (strcmp(uri, "spacify:internal:home") == 0) {

        }
    }
}
Server::~Server()
{
    //dtor
}
