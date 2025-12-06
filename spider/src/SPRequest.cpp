#include "SPRequest.h"
namespace spider {
SPRequest::SPRequest()
{
    if (spider::handlers == NULL) {
        spider::handlers = new std::vector<ISPRequestHandler *>;
    }
    //ctor
}
ISPRequestHandler *SPRequest::getMatchingHandlerForUri(string uri) {
    for (std::vector<ISPRequestHandler *>::iterator it = spider::handlers->begin(); it != spider::handlers->end(); ++it) {
        ISPRequestHandler *handler = (ISPRequestHandler *)*it;
        if (handler->handlesUri(uri)) {
            return handler;
        }
    }
}
SPResponse *SPRequest::request(string method, string uri, std::map<string, string> *headers, void *data) {
    ISPRequestHandler *handler = this->getMatchingHandlerForUri(uri);
    SPResponse *response = handler->processRequest(method, uri, headers, data);
    return response;
}
SPRequest::~SPRequest()
{
    //dtor
}
}
