#ifndef IREQUESTHANDLER_H
#define IREQUESTHANDLER_H
#include <map>
#include <string>
#include "SPResponse.h"
#include <map>
using namespace std;
namespace spider {
/**
 * Request handler for Spider
 */
class ISPRequestHandler
{
    public:
        ISPRequestHandler();
        virtual ~ISPRequestHandler();

        /**
         * Returns whether this handles this type of URI
         **/
        virtual bool handlesUri(string uri) {
            return false;
        }

        /**
         * Processes request
         **/
        virtual SPResponse *processRequest(string method, string uri, std::map<string, string> *headers, void *payload) {
            return NULL;
        }

    protected:
    private:
};
}
#endif // IREQUESTHANDLER_H
